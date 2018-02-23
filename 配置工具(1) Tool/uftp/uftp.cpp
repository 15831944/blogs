/*********************************************************************
 *
 * Copyright:
 *	MOTOROLA, INC. All Rights Reserved.  
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Motorola, Inc. This 
 *  software is provided on an "AS IS" basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, MOTOROLA 
 *  DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED, INCLUDING 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 *  PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH REGARD TO THE 
 *  SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF) AND ANY 
 *  ACCOMPANYING WRITTEN MATERIALS.
 * 
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL MOTOROLA BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING 
 *  WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS 
 *  INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY
 *  LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.   
 * 
 *  Motorola assumes no responsibility for the maintenance and support
 *  of this software
 ********************************************************************/

/*-------------------------------------------------------------------------*
 * MCF5272 UFTP LIBRARY                                                    *
 * File: uftp.c                                                            *
 *                                                                         *
 * Purpose:                                                                *
 *   All UFTP stuff implemented here                                       *
 *-------------------------------------------------------------------------*/
#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "uftp_def.h"
#include "uftp.h"
#include "malloc.h"
#include "NetPort.h"
//#include "../MyStru.h"
#include "usb.h"

extern SocketInterfStru  SocketInterf;

#define VENDOR_COMMAND_SET 0xFF

// Prototipes
BOOL BulkWriteFile(PUFTP_REQUEST request);
BOOL BulkReadFile(PUFTP_REQUEST request);
BOOL BulkFileInfo(PUFTP_REQUEST request);
BOOL BulkGetDir(PUFTP_REQUEST request);
BOOL BulkKHComm(PUFTP_REQUEST request);

extern void SaveDebugToFile(char filename[], unsigned char DbgBuf[], unsigned int len);
//
// Routines used for BULK I/O throught UFTP protocol
// NULL means no bulk operation to particular UFTP request is required
//
typedef BOOL (*BULKIO_PROC)(PUFTP_REQUEST);
BULKIO_PROC bulk_io[] = {
    NULL,               // N/A
    BulkReadFile,       // UFTP_READ
    BulkWriteFile,      // UFTP_WRITE
    BulkFileInfo,       // UFTP_GET_FILE_INFO
    BulkGetDir,         // UFTP_GET_DIR
    NULL,               // UFTP_SET_TRANSFER_LENGTH
    NULL,               // UFTP_DELETE
	BulkKHComm			// UFTP_KH_COMM
};

// Macro for safe closing handle
#define CLOSE_HANDLE( file ) {          \
    if (file != INVALID_HANDLE_VALUE) { \
        CloseHandle( file );            \
        file = INVALID_HANDLE_VALUE;    \
    }                                   \
}                                   

/*-------------------------------------------------------------------------*
 * Uftp_AllocateRequest()                                                  *
 * ----------------------                                                  *
 *                                                                         *
 * Purpose:                                                                *
 *   Function allocates request and attaches it to request list            *
 *-------------------------------------------------------------------------*/
PUFTP_REQUEST 
Uftp_AllocateRequest(
    HUFTP hUFTP, 
    UINT requestType
  )
{
    PUFTP_REQUEST request;
    PUFTP_HANDLE  uftp = (PUFTP_HANDLE)hUFTP;

    ASSERT(requestType <= UFTP_MAX_REQUEST_TYPE);
    if (requestType > UFTP_MAX_REQUEST_TYPE)
        return NULL;

    request = (PUFTP_REQUEST) calloc(1, sizeof(UFTP_REQUEST));
    if ( !request )
        return NULL;

    request->dwRequestType = requestType;
    request->hUFTP = uftp;

    EnterCriticalSection(&uftp->reqListCS);
    AddToEndOfList(&uftp->reqList, &request->Link);
    LeaveCriticalSection( &uftp->reqListCS );

    return ( request );
}

/*-------------------------------------------------------------------------*
 * Uftp_FreeRequest()                                                      *
 * ------------------                                                      *
 *                                                                         *
 * Purpose:                                                                *
 *   Function cleanups request and all info                                *
 *-------------------------------------------------------------------------*/
void Uftp_FreeRequest(UFTP_REQUEST *request)
{   
    ASSERT(request != 0);
    if (!request)
        return;

    // Remove request from queque
    EnterCriticalSection( &request->hUFTP->reqListCS );
    DeleteFromList(&request->hUFTP->reqList, &request->Link);
    LeaveCriticalSection( &request->hUFTP->reqListCS );

    if (request->RequestBuffer) {
        free((void*)request->RequestBuffer);
        request->RequestBuffer = NULL;
    }

    // Free context
    switch (request->dwRequestType) {
        case UFTP_WRITE: {
            UFTP_WRITE_CONTEXT *writeCtx;
            writeCtx = &request->WriteContext;
            if ( writeCtx->pvMap ) {
                UnmapViewOfFile( writeCtx->pvMap );
                writeCtx->pvMap = NULL;
            }
            CLOSE_HANDLE(writeCtx->hMapFile);
            CLOSE_HANDLE(writeCtx->hFile);
        }               
        break;


        case UFTP_READ: {
            CLOSE_HANDLE(request->ReadContext.hFile);
        }
        break;
    }

    free ( (void*)request );    
}

/*-------------------------------------------------------------------------*
 * Uftp_VerifyHandle()                                                     *
 * -------------------                                                     *
 *                                                                         *
 * Purpose:                                                                *
 *   Function verifies UFTP handle                                         *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_VerifyHandle(HUFTP hUFTP)
{
    PUFTP_HANDLE  uftp = (PUFTP_HANDLE)hUFTP;
    return  (uftp != NULL) && (uftp->dwSize == sizeof(UFTP_HANDLE));
}


/*-------------------------------------------------------------------------*
 * Uftp_SendRequest()                                                      *
 * ------------------                                                      *
 *                                                                         *
 * Purpose:                                                                *
 *   Function sends UFTP request to device, waits for status and perform   *
 *   bulk data transfer if needed                                          *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_SendRequest( 
    PUFTP_REQUEST request 
  )
{
//    DWORD dwReaded = 0;
    BULKIO_PROC bulkIoProc;
    PUFTP_HANDLE hUFTP = request->hUFTP;
    DWORD        status;
	unsigned int fanhui;

//	int buflen = 1;//request->dwRequestSize;
	char *buf;
	buf = (char *)malloc(request->dwRequestSize);
	memcpy(buf, request->RequestBuffer, request->dwRequestSize);
	free(buf);
    hUFTP->LastError = UFTP_SUCCESS;

    status = USBLockDevice( hUFTP->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        hUFTP->LastError = status;

        USBLockDevice( hUFTP->cbiInterface.device, 
                       USB_UNLOCK_DEVICE );
        return FALSE;
    }

    TRACE0("Enter Uftp_SendRequest");
    if (!CBIVendorRequest(&hUFTP->cbiInterface, 
                          request->RequestBuffer, 
                          request->dwRequestSize))    
    {
        TRACE0("Uftp_SendRequest Failed");
        hUFTP->LastError = GetLastError();

        if (hUFTP->LastError != USB_STATUS_IO_TIMEOUT) {
            USBLockDevice( hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
        }
	//如果是超时，服位重发
        // In case of timeout try to reset the device
        status = USBResetDevice(hUFTP->cbiInterface.device, NULL);
        if (status == USB_STATUS_OK) {
           if (!CBIVendorRequest(&hUFTP->cbiInterface, 
                                  request->RequestBuffer, 
                                  request->dwRequestSize)) 
           {
               USBLockDevice( hUFTP->cbiInterface.device, 
                              USB_UNLOCK_DEVICE );
               return FALSE;
           }
        } 
        else {
            USBLockDevice( hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
        }
    }

//上面发送成功，下面开始接收返回的状态
    status = CBIGetStatus(&hUFTP->cbiInterface, 
				&fanhui);
                 //(USHORT*)&hUFTP->LastError);

    if (hUFTP->LastError != UFTP_SUCCESS)
        hUFTP->LastError |= UFTP_STATUS_MASK;

    if ((!status) || hUFTP->LastError != UFTP_SUCCESS)  {
        USBLockDevice( hUFTP->cbiInterface.device, 
                       USB_UNLOCK_DEVICE );
        return FALSE;
    }

//接收到成功的状态后，继续接收数据
    bulkIoProc = bulk_io[request->dwRequestType];
    if ( bulkIoProc ) 
    {
        // Start the bulk operations immediately
        if (!bulkIoProc( request )) {
            TRACE0("Exit Uftp_SendRequest: BulkIO Failed");
            hUFTP->LastError = GetLastError();

            USBLockDevice( hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
        }
    }

    TRACE0("Exit Uftp_SendRequest");
    USBLockDevice( hUFTP->cbiInterface.device, 
                   USB_UNLOCK_DEVICE );
    return TRUE;
}

/*-------------------------------------------------------------------------*
 * Uftp_GetSimple()                                                        *
 * ------------------                                                      *
 *                                                                         *
 * Purpose:                                                                *
 *      一般usb通讯是pc先给下位机发命令，下位机再回答，这里的用法是，上位机*
 *   不发命令，直接从下位机接收，一般用于下位机要连续发送数据			   *
 *																		   *
 *-------------------------------------------------------------------------*/
BOOL
Uftp_GetSimple(
    HUFTP hUFTP
	)
{
	PUFTP_REQUEST  request;
	DWORD        status;

    TRACE0("Enter Uftp_KHComm");
    
    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    request = Uftp_AllocateRequest(hUFTP, UFTP_KH_COMM);
    if ( !request ) {
        TRACE0("Uftp_KHComm: Failed to allocate request");
        return FALSE;
    }

	status = USBLockDevice( request->hUFTP->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        request->hUFTP->LastError = status;

        USBLockDevice( request->hUFTP->cbiInterface.device, 
                       USB_UNLOCK_DEVICE );
        return FALSE;
    }

	if (!BulkKHComm( request )) {
            TRACE0("Exit Uftp_SendRequest: BulkIO Failed");
            request->hUFTP->LastError = GetLastError();

            USBLockDevice( request->hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
	}

	USBLockDevice( request->hUFTP->cbiInterface.device, 
                   USB_UNLOCK_DEVICE );

	Uftp_FreeRequest( request );
	return TRUE;
}

BOOL
Uftp_SendSimple(
    PUFTP_REQUEST request 
  )
{
//    DWORD dwReaded = 0;
    PUFTP_HANDLE hUFTP = request->hUFTP;
    DWORD        status;
	unsigned int fanhui;

//	int buflen = 1;//request->dwRequestSize;
	char *buf;
	buf = (char *)malloc(request->dwRequestSize);
	memcpy(buf, request->RequestBuffer, request->dwRequestSize);
	free(buf);
    hUFTP->LastError = UFTP_SUCCESS;

    status = USBLockDevice( hUFTP->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        hUFTP->LastError = status;

        USBLockDevice( hUFTP->cbiInterface.device, 
                       USB_UNLOCK_DEVICE );
        return FALSE;
    }

    TRACE0("Enter Uftp_SendRequest");
    if (!CBIVendorRequest(&hUFTP->cbiInterface, 
                          request->RequestBuffer, 
                          request->dwRequestSize))    
    {
        TRACE0("Uftp_SendRequest Failed");
        hUFTP->LastError = GetLastError();

        if (hUFTP->LastError != USB_STATUS_IO_TIMEOUT) {
            USBLockDevice( hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
        }
	//如果是超时，服位重发
        // In case of timeout try to reset the device
        status = USBResetDevice(hUFTP->cbiInterface.device, NULL);
        if (status == USB_STATUS_OK) {
           if (!CBIVendorRequest(&hUFTP->cbiInterface, 
                                  request->RequestBuffer, 
                                  request->dwRequestSize)) 
           {
               USBLockDevice( hUFTP->cbiInterface.device, 
                              USB_UNLOCK_DEVICE );
               return FALSE;
           }
        } 
        else {
            USBLockDevice( hUFTP->cbiInterface.device, 
                           USB_UNLOCK_DEVICE );
            return FALSE;
        }
    }
    status = CBIGetStatus(&hUFTP->cbiInterface, 
				&fanhui);
                 //(USHORT*)&hUFTP->LastError);

    if (hUFTP->LastError != UFTP_SUCCESS)
        hUFTP->LastError |= UFTP_STATUS_MASK;

    if ((!status) || hUFTP->LastError != UFTP_SUCCESS)  {
        USBLockDevice( hUFTP->cbiInterface.device, 
                       USB_UNLOCK_DEVICE );
        return FALSE;
    }

	return TRUE;
}
/*-------------------------------------------------------------------------*
 * Uftp_Connect()                                                          *
 * --------------                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   Functon connects to UFTP interface, creates UFTP handle that should   *
 *   be used by all UFTP library routines                                  *
 *-------------------------------------------------------------------------*/
HUFTP 
Uftp_Connect(
    usb_t  device
  )
{
    USB_CONFIGURATION_DESCRIPTOR configDesc;
    USB_INTERFACE_DESCRIPTOR     ifaceDesc;
    UCHAR                        i;
    UCHAR                        interfaceNum = 0; // interface with CBI, uftp
    DWORD                        status;
    PUFTP_HANDLE                 uftp;
    CBI_PIPE_INFO                cbiInterface;
    BYTE                         ConfigIndex = 0;
    DWORD                        size = sizeof(USB_CONFIGURATION_DESCRIPTOR);
    UCHAR                        configValue;

    USBGetConfiguration(device, &configValue, 0);
    if (configValue == 0) {
        USB_INTERFACE_SETTING interfaceSetting;
    
        interfaceSetting.InterfaceIndex  = 0;
        interfaceSetting.AltSetting      = 0;
        interfaceSetting.MaxTransferSize = UFTP_MAX_TRANSFER_SIZE; 

        status = USBSetConfiguration(device, 
                                     0,
                                     1,
                                     &interfaceSetting, 
                                     0);
        if (status != USB_STATUS_OK) {
            return (HUFTP) NULL;
        }
    }

    status = USBGetConfigDesc( device, 
                               ConfigIndex, 
                               &configDesc, 
                               &size,
                               NULL);

    if (status != USB_STATUS_OK)
        return (HUFTP) NULL;

    ASSERT(size == sizeof(USB_CONFIGURATION_DESCRIPTOR));

    // Open CBI with vendor specific command set
    for (i=interfaceNum; i<configDesc.bNumInterfaces; i++) 
    {
        if (CBIOpen(device, &interfaceNum, &cbiInterface)) {
            status = USBGetInterfaceDesc(device, 
                                         ConfigIndex, 
                                         interfaceNum, 
                                         0, 
                                         &ifaceDesc,  NULL);
            if (status != USB_STATUS_OK)
                return (HUFTP) NULL;

            if (ifaceDesc.bInterfaceSubClass != VENDOR_COMMAND_SET)
                CBIClose( &cbiInterface );
            else {
                uftp = (PUFTP_HANDLE)calloc(1, sizeof(UFTP_HANDLE));
                if ( uftp )
                {
                    uftp->dwSize = sizeof ( UFTP_HANDLE );
                    uftp->cbiInterface = cbiInterface;
                    InitializeCriticalSection( &uftp->reqListCS );
                    InitializeList(&uftp->reqList);
                    uftp->progressProc    = NULL; 
                    uftp->progressParam   = NULL;
                    uftp->LastError       = UFTP_SUCCESS;
                    Uftp_SetTransferLength(uftp, UFTP_DEFAULT_BLOCK_SIZE);
                }
                return (HUFTP) uftp;
            }
        }
    }

    return (HUFTP) NULL;
}

/*-------------------------------------------------------------------------*
 * Uftp_Disconnect()                                                       *
 * -----------------                                                       *
 *                                                                         *
 * Purpose:                                                                *
 *   Functon releases UFTP handle                                          *
 *-------------------------------------------------------------------------*/
void 
Uftp_Disconnect(
    HUFTP hUFTP
  )
{
    PUFTP_HANDLE  uftp = (PUFTP_HANDLE)hUFTP;
    if (Uftp_VerifyHandle( hUFTP ))
    {
        USBLockDevice(uftp->cbiInterface.device, USB_TOTAL_UNLOCK);
        CBIClose( &uftp->cbiInterface );
        DeleteCriticalSection( &uftp->reqListCS );
    }
}


/*-------------------------------------------------------------------------*
 * Uftp_Disconnect()                                                       *
 * -----------------                                                       *
 *                                                                         *
 * Purpose:                                                                *
 *   Sets file copy progress notification routine                          *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_SetProgressRoutine(
    HUFTP               hUFTP,
    PROGRESS_ROUTINE    progressRoutine, 
    LPVOID              param
  )
{
    PUFTP_HANDLE  uftp = (PUFTP_HANDLE)hUFTP;
    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    uftp->progressProc = progressRoutine;
    uftp->progressParam = param;
    return TRUE;
}


/*-------------------------------------------------------------------------*
 * Uftp_GetFileInfo()                                                      *
 * ------------------                                                      *
 *                                                                         *
 * Purpose:                                                                *
 *   Returns file information on device be give file name                  *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_GetFileInfo(
    HUFTP           hUFTP, 
    LPCTSTR         lpszFileName, 
    UFTP_FILE_INFO* fileInfo
  )
{
    PUFTP_REQUEST   request;
    BOOL            bOK;

    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;
    
    TRACE1("Enter Uftp_GetFileInfo for %s", lpszFileName);

    fileInfo->dwFileLength = 0xFFFFFFFF;
    request = Uftp_AllocateRequest(hUFTP, UFTP_GET_FILE_INFO );
    if ( !request ) {
        TRACE0("Failed to allocate request");
        return FALSE;
    }

    if (!Uftp_BuildFileInfoRequest(request, lpszFileName))
    {
        TRACE0("Failed to build request");
        Uftp_FreeRequest( request );
        return FALSE;
    }

    bOK = Uftp_SendRequest( request );    
    if ( bOK ) {
        fileInfo->dwFileLength = request->FileInfoContext.dwFileLength;     
    }

    Uftp_FreeRequest(  request );
    TRACE1("Exit Uftp_GetFileInfo dwFileLength = %d", 
           fileInfo->dwFileLength);
    return bOK;
}


/*-------------------------------------------------------------------------*
 * Uftp_SetTransferUnitToDevice()                                          *
 * ------------------------------                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   Sends selected transfer length for file transmitting to device        *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_SetTransferUnitToDevice(
    HUFTP hUFTP, 
    DWORD dwTransferLength
  )
{
    PUFTP_REQUEST  request;
    UFTP_SET_TRANSFER_LEN_REQUEST *setTransLen;
    BOOL bOK;
    TRACE1("Enter Uftp_SetTransferLength = %d", dwTransferLength);

    request = Uftp_AllocateRequest(hUFTP, UFTP_SET_TRANSFER_LENGTH );
    if ( !request ) {
        TRACE0("Uftp_SetTransferUnitToDevice: Failed to allocate request");
        return -1;
    }

    request->dwRequestSize = sizeof(UFTP_SET_TRANSFER_LEN_REQUEST);
    request->RequestBuffer = malloc( request->dwRequestSize );
    if ( !request->RequestBuffer ) {
        TRACE0("Uftp_SetTransferLength: Failed to allocate request");
        return FALSE;
    }

    setTransLen = (UFTP_SET_TRANSFER_LEN_REQUEST*) request->RequestBuffer;
    setTransLen->cbRequestType = UFTP_SET_TRANSFER_LENGTH;
    setTransLen->dwTransferLen = dwTransferLength;

    bOK = Uftp_SendRequest( request ); 

    Uftp_FreeRequest( request );
    return bOK;
}


/*-------------------------------------------------------------------------*
 * Uftp_SetTransferLength()                                                *
 * ------------------------                                                *
 *                                                                         *
 * Purpose:                                                                *
 *   Selects transfer length for file transmitting                         *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_SetTransferLength(
    HUFTP hUFTP, 
    DWORD dwTransferLength
  )
{
    PUFTP_HANDLE uftp = (PUFTP_HANDLE)hUFTP;
    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    uftp->TransferUnit = dwTransferLength;
    return TRUE;
}


/*-------------------------------------------------------------------------*
 * Uftp_SendFile()                                                         *
 * ---------------                                                         *
 *                                                                         *
 * Purpose:                                                                *
 *   Transmites file from HOST to device                                   *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_SendFile(
    HUFTP hUFTP, 
    LPCTSTR lpszPathName
  )
{
    PUFTP_REQUEST       request;
    UFTP_WRITE_CONTEXT *context;
    DWORD               dwFileSize;
    BOOL                bOK;
    SECURITY_ATTRIBUTES sa = {0};
    PUFTP_HANDLE        uftp = (PUFTP_HANDLE)hUFTP;
    DWORD               status;

    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;
  
    request = Uftp_AllocateRequest( hUFTP, UFTP_WRITE );
    if ( !request ) 
    {
        TRACE0("Uftp_SendFile failed to allocate request");
        return FALSE;
    }

    context = &request->WriteContext;
    context->hFile = CreateFile(lpszPathName,    
                       GENERIC_READ,        
                       FILE_SHARE_READ,     
                       &sa,              // No SECURITY_ATTRIBUTES structure
                       OPEN_EXISTING,    // No special create flags
                       0,                // No special attributes
                       NULL);            // No template file
    if (context->hFile == INVALID_HANDLE_VALUE) {
        TRACE0("Uftp_SendFile failed to open file");
        Uftp_FreeRequest( request );
        return FALSE;
    }

    dwFileSize = GetFileSize( context->hFile, NULL );
    if (dwFileSize == 0xFFFFFFFF) 
    {
        TRACE0("Uftp_SendFile failed: file size is bad");
        Uftp_FreeRequest( request );
        return FALSE;
    }       

    if (dwFileSize != 0) {
        context->hMapFile = CreateFileMapping(context->hFile, &sa, 
                            PAGE_READONLY|SEC_COMMIT, 0, 0, NULL);

        if (!context->hMapFile) 
        {
            DWORD dwError = GetLastError();
            TRACE1("Uftp_SendFile failed to create map file: %d", dwError);
            Uftp_FreeRequest( request );
            return FALSE;
        }

        context->pvMap = MapViewOfFile(context->hMapFile, 
                                       FILE_MAP_READ,0,0,0);
        if ( !context->pvMap ) 
        {
            TRACE0("Uftp_SendFile failed to create map view of file");
            Uftp_FreeRequest( request );
            return FALSE;
        }
    }
    else {
        context->hMapFile = NULL;
        context->pvMap    = 0;
    }


    if (!Uftp_BuildWriteRequest( request, 
                                 lpszPathName, 
                                 dwFileSize ))
    {
        TRACE0("Uftp_SendFile failed to build request");
        Uftp_FreeRequest( request );
        return FALSE;
    }

    // Write to device must be syncronized
    bOK = FALSE;

    status = USBLockDevice( uftp->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        uftp->LastError = status;
        return FALSE;
    }

    if (Uftp_SetTransferUnitToDevice( uftp, uftp->TransferUnit ))
        bOK = Uftp_SendRequest( request );

    USBLockDevice( uftp->cbiInterface.device, 
                   USB_UNLOCK_DEVICE );

    Uftp_FreeRequest( request );
    return bOK;
}

/*-------------------------------------------------------------------------*
 * Uftp_GetFile()                                                          *
 * --------------                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   Receives file from device to host                                     *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_GetFile(
    HUFTP   hUFTP, 
    LPCTSTR lpszDestFileName, 
    LPCTSTR lpszSrcFileName
  )
{   
    UFTP_FILE_INFO fileInfo;
    PUFTP_REQUEST  request;
    UFTP_READ_CONTEXT *context;
    SECURITY_ATTRIBUTES sa = {0};
    DWORD   status;
    BOOL bOK;
    PUFTP_HANDLE        uftp = (PUFTP_HANDLE)hUFTP;

    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    status = Uftp_GetFileInfo(hUFTP, lpszSrcFileName, &fileInfo);  
    if (fileInfo.dwFileLength == 0xFFFFFFFF)
        return FALSE;
    
    request = Uftp_AllocateRequest( hUFTP, UFTP_READ );
    if ( !request ) {
        TRACE0("Failed to allocate request");
        return -1;
    }

    context = &request->ReadContext;
    context->hFile = CreateFile(
                       lpszDestFileName,// File name    
                       GENERIC_WRITE,   // Open for write access     
                       0,               // 
                       &sa,             // no SECURITY_ATTRIBUTES structure
                       CREATE_ALWAYS,   // No special create flags
                       0,               // No special attributes
                       NULL);           // No template file
    if (context->hFile == INVALID_HANDLE_VALUE) 
    {
        TRACE0("Uftp_GetFile failed to open file");
        Uftp_FreeRequest( request );
        return FALSE;
    }
    bOK = TRUE;
    context->dwFileLength = fileInfo.dwFileLength;
    TRACE1("context->dwFileLength = %d\n", context->dwFileLength);

    if (context->dwFileLength)
    {
        if (!Uftp_BuildReadRequest(request, lpszSrcFileName))
        {
            TRACE0("Failed to build request");
            Uftp_FreeRequest(  request );
            return FALSE;
        }   

        status = USBLockDevice( uftp->cbiInterface.device, 
                                USB_LOCK_DEVICE );
        if (status != USB_STATUS_OK) {
            uftp->LastError = status;
            return FALSE;
        }

        bOK = FALSE;
        if (Uftp_SetTransferUnitToDevice( uftp, uftp->TransferUnit ))
            bOK = Uftp_SendRequest( request );

        USBLockDevice( uftp->cbiInterface.device, 
                        USB_UNLOCK_DEVICE );
    }
    Uftp_FreeRequest( request );
    return bOK;
}

/*-------------------------------------------------------------------------*
 * Uftp_ReadDir()                                                          *
 * --------------                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   Reads directory content on device                                     *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_ReadDir(
    HUFTP hUFTP, 
    TCHAR** rgFileNames[], 
    DWORD *dwFilesCount
  )
{
    PUFTP_REQUEST  request;
    BOOL           bOK;
    DWORD          status;
	char FileName[] = "/mnt/";
	char NameLen = (char)strlen(FileName);
	UFTP_GETDIR_REQUEST *dir_info;

    TRACE0("Enter Uftp_ReadDir");
    *dwFilesCount = 0;
    *rgFileNames = NULL;
    
    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    request = Uftp_AllocateRequest(hUFTP, UFTP_GET_DIR);
    if ( !request ) {
        TRACE0("Uftp_ReadDir: Failed to allocate request");
        return -1;
    }

    request->dwRequestSize = sizeof(UFTP_GETDIR_REQUEST) - sizeof(void*) + NameLen + 1;
    request->RequestBuffer = malloc( request->dwRequestSize );
	dir_info = (UFTP_GETDIR_REQUEST*)request->RequestBuffer;
    dir_info->cbRequestType = UFTP_GET_DIR;
	dir_info->cbNameLen = (char)(NameLen + 1);
	memcpy(&dir_info->szFileName, FileName, NameLen+1);

    status = USBLockDevice( request->hUFTP->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        request->hUFTP->LastError = status;
        return FALSE;
    }

    bOK = Uftp_SendRequest( request ); 

    USBLockDevice( request->hUFTP->cbiInterface.device, 
                   USB_UNLOCK_DEVICE );

    if ( bOK ) {
        BYTE *p;
        DWORD i;
        BYTE  name_len;

        *dwFilesCount = request->GetDirContext.dwFilesCount;
        if ( *dwFilesCount ) {
            *rgFileNames = (char**) malloc(*dwFilesCount * sizeof(char**));       
            p = (BYTE*)request->GetDirContext.lpBuffer;
            for (i = 0; i < *dwFilesCount; i++, p += name_len) {
                name_len = *p++;
                (*rgFileNames)[i] = (char*) malloc( name_len + 1 );
                strncpy((*rgFileNames)[i], (char*)p, name_len);
                (*rgFileNames)[i][name_len] = '\0';
            }
        }
    } else {
        TRACE0("Uftp_ReadDir Failed");
    }

    Uftp_FreeRequest( request );
    return bOK;
}


/*-------------------------------------------------------------------------*
 * Uftp_DelFile()                                                          *
 * --------------                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   Removes file from device                                              *
 *-------------------------------------------------------------------------*/
BOOL 
Uftp_DelFile(
    HUFTP hUFTP, 
    LPCTSTR FileName
  )
{
    PUFTP_REQUEST  request;
    BOOL bOK;

    TRACE0("Enter Uftp_DelFile");

    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    request = Uftp_AllocateRequest( hUFTP, UFTP_DELETE );
    if ( !request ) {
        TRACE0("Failed to allocate request");
        return FALSE;
    }

    if (!Uftp_BuildDelRequest(request, FileName))
    {
        TRACE0("Failed to build request");
        Uftp_FreeRequest( request );
        return FALSE;
    }

    bOK = Uftp_SendRequest( request );    
    Uftp_FreeRequest( request );
    TRACE0("Exit Uftp_DelFile");
    return bOK;
}

/*-------------------------------------------------------------------------*
 * Uftp_DelFile()                                                          *
 * ---------------                                                         *
 *                                                                         *
 * Purpose:                                                                *
 *   Returns last UFTP error                                               *
 *-------------------------------------------------------------------------*/
DWORD Uftp_GetLastError(HUFTP hUFTP)
{
    PUFTP_HANDLE uftp = (PUFTP_HANDLE)hUFTP;
    
    if (!Uftp_VerifyHandle( hUFTP ))
        return (DWORD)-1;

    return (uftp->LastError == UFTP_SUCCESS) ? 
            GetLastError() : uftp->LastError ;
}

/*-------------------------------------------------------------------------*
 * Uftp_GetErrorText()                                                     *
 * -------------------                                                     *
 *                                                                         *
 * Purpose:                                                                *
 *   Returns error message for specified UFTP error                        *
 *-------------------------------------------------------------------------*/
LPTSTR
Uftp_GetErrorText(
     DWORD  errCode 
   )
{
    LPTSTR buffer;

    if (IS_UFTP_ERROR(errCode))
    {
        buffer = (char *)LocalAlloc(LMEM_FIXED, 256);
        switch (errCode)
        {
            case UFTP_FILE_DOES_NOT_EXIST:
                strcpy(buffer, "Specified file doesn't exist");
                break;
            case UFTP_MEMORY_ALLOCATION_FAIL:
                strcpy(buffer, "Device memory allocation failure");
                break;
            case UFTP_NO_POSITION_FOR_NEW_FILE:
                strcpy(buffer, "File count restriction error");
                break;
            case UFTP_NOT_ENOUGH_SPACE_FOR_FILE:
                strcpy(buffer, "No enought free space");
                break;

            case -1:
                strcpy(buffer, "Invalid UFTP handle");
                break;
        }
        
    }
    else 
        buffer = (TCHAR*)USBGetErrorText( errCode );

    ASSERT (buffer != NULL);
    return buffer;
}


/*-------------------------------------------------------------------------*
 * Uftp_KHComm()                                                          *
 * --------------                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   应用于科汇的通讯				                                       *
 *-------------------------------------------------------------------------*/
#define ERR_NUM	10

BOOL 
Uftp_KHComm(
    HUFTP hUFTP, 
    TCHAR *msg, 
    DWORD len,
	bool bNeedRequest
  )
{
    PUFTP_REQUEST  request;
    BOOL           bOK;
    DWORD          status;
	unsigned char *pbuf;

//	return -100;
    TRACE0("Enter Uftp_KHComm");
    if( (!msg) || (!len))
		return FALSE;
    
    if (!Uftp_VerifyHandle( hUFTP ))
        return FALSE;

    request = Uftp_AllocateRequest(hUFTP, UFTP_KH_COMM);
    if ( !request ) {
        TRACE0("Uftp_KHComm: Failed to allocate request");
        return FALSE;
    }

    request->dwRequestSize = len + 3;
    if(!(request->RequestBuffer = (void *)malloc( request->dwRequestSize)))
	{
		TRACE0("Failed to allocate RequestBuffer");
        return FALSE;
    }

	pbuf = (unsigned char *)request->RequestBuffer;
	*pbuf = (unsigned char)UFTP_KH_COMM;
	memcpy(pbuf+1, &len, 2);
	memcpy(pbuf+3, msg, len);
//	memcpy(request->RequestBuffer, msg, request->dwRequestSize);

    status = USBLockDevice( request->hUFTP->cbiInterface.device, 
                            USB_LOCK_DEVICE );
    if (status != USB_STATUS_OK) {
        request->hUFTP->LastError = status;
        return FALSE;
    }

	if(bNeedRequest)
		bOK = Uftp_SendRequest( request );
	else
		bOK = Uftp_SendSimple( request );

    USBLockDevice( request->hUFTP->cbiInterface.device, 
                   USB_UNLOCK_DEVICE );

    Uftp_FreeRequest( request );
    if ( bOK ) {
		TRACE0("KH_Comm is successed!");
    }
	else
		return FALSE;

	return TRUE;
}

/*
BOOL
PcUsbComm(
    HUFTP hUFTP, 
    TCHAR *msg, 
    DWORD len,
	bool bNeedRequest
  )
{
	RcvPtr = &(RcvBuf[0]);
	return Uftp_KHComm(hUFTP, msg, len, bNeedRequest);
}
*/

//发送给ner_server的接口
BOOL
PcUsbComm(
    HUFTP hUFTP, 
    TCHAR *msg, 
    DWORD len,
	bool bNeedRequest
  )
{
	int i = 0;
	if(SocketInterf.Socket)
	{
//		SetDebugHistory(msg, len, false);
		int ret=send(SocketInterf.Socket[0], (const char*)msg, len , 0);
		if(ret==SOCKET_ERROR)
		{
			closesocket( SocketInterf.Socket[0] );
			WSACleanup( );
			SocketInterf.Socket[0] = 0;
			return FALSE;
		}
		if(bNeedRequest)
			while(!NetRcv(NULL))
				Sleep(20);
	}
	return TRUE;
}
/*-------------------------------------------------------------------------*
 *                     BULK TRANSFER HANDLERS                              *
 *-------------------------------------------------------------------------*/

BOOL 
BulkWriteFile(
    PUFTP_REQUEST request
  )
{
    UFTP_WRITE_CONTEXT *writeCtx = &request->WriteContext;
    UFTP_WRITE_REQUEST *writeReq = (UFTP_WRITE_REQUEST*) request->RequestBuffer;

    if (!writeReq->cbFileLen)
        return TRUE;

    ASSERT(writeCtx->hFile != INVALID_HANDLE_VALUE);
    ASSERT(writeCtx->pvMap != NULL);


    return  CBIWrite(&request->hUFTP->cbiInterface, 
                    writeCtx->pvMap, 
                    writeReq->cbFileLen, 
                    request->hUFTP->TransferUnit,
                    request->hUFTP->progressProc,
                    request->hUFTP->progressParam
        );
} 

BOOL 
BulkFileInfo(
    PUFTP_REQUEST request
  )
{
    return CBIRead(&request->hUFTP->cbiInterface, 
                   &request->FileInfoContext, 
                   sizeof(request->FileInfoContext), 
                   request->hUFTP->TransferUnit, NULL, NULL);
}

BOOL 
BulkReadFile(
    PUFTP_REQUEST request
  )
{
    char* buffer;
    BOOL  bResult = FALSE;
    DWORD dwWritten;

    ASSERT(request->ReadContext.hFile != INVALID_HANDLE_VALUE);

    if (!request->ReadContext.dwFileLength)
        return TRUE;

    buffer = (char *)malloc(request->ReadContext.dwFileLength);
    if ( !buffer ) {
        TRACE0("Failed to allocate buffer");
        return FALSE;
    }
    else if (CBIRead(&request->hUFTP->cbiInterface, 
                      buffer, 
                      request->ReadContext.dwFileLength,
                      request->hUFTP->TransferUnit,
                      request->hUFTP->progressProc,
                      request->hUFTP->progressParam)) 
    {       
        if (WriteFile(request->ReadContext.hFile, 
                       buffer, 
                       request->ReadContext.dwFileLength,
                       &dwWritten, 
                       NULL)) 
        {
            bResult = TRUE;
        }
        else {
            TRACE0("Copy file to user buffer failed");
        }   
    } else {
        TRACE0("USBCBIRead failed");
        bResult = FALSE;
    }

    free( buffer );
    return bResult;
}

BOOL 
BulkGetDir(
    PUFTP_REQUEST request
  )
{
    TCHAR buffer[10];
    UFTP_GETDIR_CONTEXT *context = &request->GetDirContext;

    TRACE0("Enter BulkGetDir");
    memset(context, 0, sizeof(UFTP_GETDIR_CONTEXT));

    if (!CBIRead(&request->hUFTP->cbiInterface, buffer, 8, 
                  0x7ffffff, NULL, NULL)) 
    {
        TRACE0("BulkGetDir: Failed Get Buffer Size");
        return FALSE;
    }

    memcpy(context, buffer, 8);
    
    TRACE1("dwBufferSize = %d", context->dwBufferSize);
    TRACE1("dwFilesCount = %d", context->dwFilesCount);

    if (!context->dwBufferSize) {
        if ( context->dwFilesCount != 0 ) {
            TRACE0("BulkGetDir: File Count Missmatch");
            return FALSE;
        }

        // No files on device
        return TRUE;
    }

    context->lpBuffer = malloc( context->dwBufferSize );
    if ( !context->lpBuffer ) {
        TRACE0("BulkGetDir: Failed to allocate buffer");
        return FALSE;
    }

    if (!CBIRead(&request->hUFTP->cbiInterface, 
                  context->lpBuffer, 
                  context->dwBufferSize, 0x7ffffff, NULL, NULL) )
    {
        free(context->lpBuffer);
        context->lpBuffer = NULL;
        TRACE0("BulkGetDir: Failed to read dir content");
        return FALSE;
    }

    TRACE0("Exit BulkGetDir - OK");
    return TRUE;
}

//
//	读数据的函数，先从usb读4个字节控制码
//	再从usb里读控制码里表示的长度个字节的数据
//	读出数据后进行解析，处理
//
BOOL
BulkKHComm(
    PUFTP_REQUEST request
  )
{
	int KhCommLen;
	TCHAR buffer[4];
	BOOL bLastPackage = FALSE;

    TRACE0("Enter BulkKHComm");

    if (!CBIRead(&request->hUFTP->cbiInterface, buffer, 4, 
                  0x7ffffff, NULL, NULL)) 
    {
        TRACE0("BulkKHComm: Failed Get Buffer Size");
        return FALSE;
    }

    memcpy(&KhCommLen, buffer, 4);
	bLastPackage = (KhCommLen & 0x01000000)? FALSE : TRUE;
	KhCommLen &= 0xffffff;

    if(KhCommLen <= 0)
		return FALSE;

    if (!CBIRead(&request->hUFTP->cbiInterface, 
                  RcvPtr, 
                  KhCommLen, 0x7ffffff, NULL, NULL) )
    {
        TRACE0("BulkGetDir: Failed to read KH's Comm content");
        return FALSE;
    }

	if(!bLastPackage)
	{
		RcvPtr += KhCommLen;
		BulkKHComm(request);
	}
	else
	{
		RcvPut = RcvPtr - RcvBuf + KhCommLen;
		SaveDebugToFile("c:\\Pzk200e_debug.txt", RcvBuf, RcvPut);
		if (Dispose(RcvBuf,RcvPut) == FALSE)
		{
//			AfxMessageBox("命令处理时发现错误，退出主线程");
			TRACE0("Exit BulkKHComm - ERROR");
			return FALSE;
		}
		TRACE0("Exit BulkKHComm - OK");
	}
    return TRUE;
}
