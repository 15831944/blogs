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
 * File: cbi.c                                                             *
 *                                                                         *
 * Purpose:                                                                *
 *   Control/Bulk/Interrupt transfers stuff                                *
 *-------------------------------------------------------------------------*/
#include "stdafx.h"
#include <windows.h>
#include "cbi.h"

//#define TRACE0
//#define ASSERT
//#define TRACE1


DWORD bulkTime;

/* Interface Classes */
#define MASS_STORAGE_INTERFACE  0x08    

/* CBI Interface Protocol Codes */
#define NONE                    0x00
#define CBI_TRANSFER_PROTOCOL   0x00


/*-------------------------------------------------------------------------*
 * CBIOpen()                                                               *
 * -------------------------                                               *
 * Description:                                                            *
 *    Opens CBI pipe set on device                                         *
 *-------------------------------------------------------------------------*/
BOOL 
CBIOpen(
    usb_t          device,              /* device handle    */
    UCHAR         *interfaceNum,        /* interface index */
    PCBI_PIPE_INFO cbi                  /* returned CBI pipe info */
  )
{
    UCHAR bulkin_epnum, bulkout_epnum, interpt_epnum;
    BOOL  bulkin_found, bulkout_found, interpt_found;
    BOOL  fCBI_Found = 0;
    UCHAR i, j;  
    DWORD status;

    BYTE   ConfigIndex = 0;

    USB_CONFIGURATION_DESCRIPTOR configDesc;
    USB_INTERFACE_DESCRIPTOR     ifaceDesc;
    USB_ENDPOINT_DESCRIPTOR      epDesc;

    DWORD size = sizeof(USB_CONFIGURATION_DESCRIPTOR);

    status = USBGetConfigDesc( device, 
                               ConfigIndex,
                               &configDesc, 
                               &size,
                               NULL);
    if (status != USB_STATUS_OK)
        return FALSE;

    ASSERT(size == sizeof(USB_CONFIGURATION_DESCRIPTOR));

    cbi->pipe_in  = NULL;
    cbi->pipe_out = NULL;
    cbi->pipe_int = NULL;

    // Lookup for 
    for (i=*interfaceNum; i<configDesc.bNumInterfaces 
                         && !fCBI_Found; *interfaceNum = i++) 
    {
        USBGetInterfaceDesc(device, ConfigIndex, i, 0, &ifaceDesc,  NULL);
        if (status != USB_STATUS_OK) 
            return FALSE;

        if (ifaceDesc.bInterfaceClass    != MASS_STORAGE_INTERFACE ||
            ifaceDesc.bInterfaceProtocol != CBI_TRANSFER_PROTOCOL  ||
            ifaceDesc.bNumEndpoints      != 3)
        {
            continue;
        }

        // Mark neither of endpoints have been found 
        bulkin_found = bulkout_found = interpt_found = FALSE;

        for (j=0; j<ifaceDesc.bNumEndpoints; j++ )
        {
            status = USBGetEndpointDesc(device, ConfigIndex, i, 
                                        0, j, &epDesc,  NULL);
            if (status != USB_STATUS_OK)
                return FALSE;

            switch (epDesc.bmAttributes) {
                case USB_ENDPOINT_TYPE_BULK:
                    if (USB_ENDPOINT_DIRECTION_IN(epDesc.bEndpointAddress)) 
                    {
                        if (bulkin_found)
                            return FALSE;
                        
                        bulkin_epnum = epDesc.bEndpointAddress;
                        bulkin_found = TRUE;
                    } 
                    else {
                        if (bulkout_found)   
                            return FALSE;
                        
                        bulkout_epnum = epDesc.bEndpointAddress;
                        bulkout_found = TRUE;
                    }
                    break;

                case USB_ENDPOINT_TYPE_INTERRUPT:
                    if (interpt_found)      
                        return FALSE;
                
                    interpt_epnum = epDesc.bEndpointAddress;
                    interpt_found = TRUE;
                    break;
                        
                default:
                    return FALSE;
            }
        }

        // Mark all endpoints have been found flag
        fCBI_Found = bulkin_found & bulkout_found & interpt_found;
    }
    
    if ( fCBI_Found )
    {
        //
        // Open all pipes for CBI interface
        //
        status = USBOpenPipe(device, 
                             bulkin_epnum, 
                             &cbi->pipe_in);

        if (status != USB_STATUS_OK) {
            TRACE0("Can't open BULKIN PIPE\n");
            return FALSE;
        }

        status = USBOpenPipe(device, 
                             bulkout_epnum, 
                             &cbi->pipe_out);

        if (status != USB_STATUS_OK) {
            TRACE0("Can't open BULKOUT PIPE\n");
            CBIClose( cbi );
            return FALSE;
        }

        status = USBOpenPipe(device, 
                             interpt_epnum, 
                             &cbi->pipe_int);

        if (status != USB_STATUS_OK) {
            TRACE0("Can't open INTERRUPT PIPE\n");
            CBIClose( cbi );
            return FALSE;
        }

        cbi->device = device;
        return TRUE;
    }

    return FALSE;
}


/*-------------------------------------------------------------------------*
 * CBIClose()                                                              *
 * -------------------------                                               *
 * Description:                                                            *
 *    Close CBI pipe set.                                                  *
 *-------------------------------------------------------------------------*/
void 
CBIClose(
    PCBI_PIPE_INFO cbi
  )
{
    if (cbi->pipe_in)
        USBClosePipe(&cbi->pipe_in);

    if (cbi->pipe_out)
        USBClosePipe(&cbi->pipe_out);

    if (cbi->pipe_int)
        USBClosePipe(&cbi->pipe_int);
}


/*-------------------------------------------------------------------------*
 * CBIWrite()                                                              *
 * -------------------------                                               *
 * Description:                                                            *
 *    Writes data to Bulk OUT endpoint for given CBI Pipe Set              *
 *-------------------------------------------------------------------------*/
BOOL 
CBIWrite(
   PCBI_PIPE_INFO    cbi,           /* CBI pipe info  */
   PVOID             buffer,        /* Write Buffer   */
   UINT              dataLength,    /* Write Buffer Length */
   DWORD             TransferUnit,  /* Transfer Length (-1 to use MOTUSB max. transfer length)*/
   PROGRESS_ROUTINE  progressProc,  /* Progress Notify Routine Pointer */
   LPVOID            progressParam  /* Progress Notify Routine Parameter */
  )
{
    DWORD  bOk;
    DWORD  transfersCount = (dataLength / TransferUnit);
    DWORD  bytesInLast = dataLength % TransferUnit;
    TCHAR *pData = (TCHAR*)buffer;
    DWORD  tmstart, tmstop;
    PROGRESS_STRUCT pr;


    ASSERT( buffer );
    if ( !buffer )
        return FALSE;

    pr.eventCode  = EVENT_START;
    pr.timeMs     = 0;
    pr.bytesDone  = 0;
    pr.bytesTotal = dataLength;
    pr.param      = progressParam;
    if ( progressProc )
        progressProc( &pr );


    TRACE0("Enter USBCBIWrite");

    pr.eventCode = EVENT_UPDATE;
    tmstart = GetTickCount();
    for (;transfersCount--; pData += TransferUnit) {
        bOk = USBWritePipe(cbi->pipe_out, pData, 
                           TransferUnit, NULL);         
        if (bOk != USB_STATUS_OK) {
            goto WriteComplete;
        }

        // Progress Notification
        if (progressProc) {
            tmstop = GetTickCount();
            pr.bytesDone += TransferUnit;
            pr.timeMs = tmstop - tmstart;
            if ( pr.timeMs )
                progressProc( &pr );
        }
    }

    if (bytesInLast) {
        bOk = USBWritePipe(cbi->pipe_out, pData, 
                           bytesInLast, NULL);
        if (bOk != USB_STATUS_OK) {
            goto WriteComplete;
        }

        // Progress Notification
        if (progressProc) {
            tmstop = GetTickCount();
            pr.bytesDone += bytesInLast;
            pr.timeMs = tmstop - tmstart;
            if ( pr.timeMs )
                progressProc( &pr );
        }
    }

WriteComplete:
    pr.eventCode = EVENT_STOP;
    if (progressProc)
        progressProc( &pr );

    TRACE0("Exit USBCBIWrite success");
    SetLastError(bOk);
    return (bOk == USB_STATUS_OK);
}


/*-------------------------------------------------------------------------*
 * CBIRead()                                                               *
 * -------------------------                                               *
 * Description:                                                            *
 *    Reads data from Bulk IN endpoint for given CBI Pipe Set              *
 *-------------------------------------------------------------------------*/
BOOL 
CBIRead(
    PCBI_PIPE_INFO   pipeInfo,          /* CBI pipe info  */
    PVOID            buffer,            /* Read Buffer    */
    UINT             dataLength,        /* Read Buffer Length */
    DWORD            TransferUnit,      /* Transfer Length (-1 to use MOTUSB max. transfer length)*/
    PROGRESS_ROUTINE progressProc,      /* Progress Notify Routine Pointer */
    LPVOID           progressParam      /* Progress Notify Routine Parameter */
  )
{
    DWORD bOk;
    DWORD transfersCount = (dataLength / TransferUnit);
    DWORD bytesInLast = dataLength % TransferUnit;
    TCHAR *pData = (TCHAR*)buffer;
    DWORD dwRead;
    DWORD tmstart, tmstop;
    PROGRESS_STRUCT pr;

    ASSERT( buffer );
    if ( !buffer )
        return FALSE;


    TRACE0("Enter USBCBIRead");

    pr.eventCode  = EVENT_START;
    pr.timeMs     = 0;
    pr.bytesDone  = 0;
    pr.bytesTotal = dataLength;
    pr.param      = progressParam;
    if ( progressProc )
        progressProc( &pr );


    pr.eventCode  = EVENT_UPDATE;
    tmstart = GetTickCount();       
    for (;transfersCount--; pData += TransferUnit)
    {
        dwRead = TransferUnit;
        bOk = USBReadPipe(pipeInfo->pipe_in, 
                          pData, &dwRead, NULL);           

        if (bOk != USB_STATUS_OK) {
            goto ReadComplete;
        }

        // Progress Notification
        if (progressProc) {
            tmstop = GetTickCount();
            pr.bytesDone += TransferUnit;
            pr.timeMs = tmstop - tmstart;
            if ( pr.timeMs )
                progressProc( &pr );
        }       
    }

    if (bytesInLast) {
        dwRead = bytesInLast;
        bOk = USBReadPipe(pipeInfo->pipe_in, 
                          pData, &dwRead, NULL);

        if (bOk != USB_STATUS_OK) {
            goto ReadComplete;
        }
        
        // Progress Notification
        if (progressProc) {
            tmstop = GetTickCount();
            pr.bytesDone += bytesInLast;
            pr.timeMs = tmstop - tmstart;
            if ( pr.timeMs )
                progressProc( &pr );
        }
    }

ReadComplete:
    pr.eventCode = EVENT_STOP;
    if (progressProc)
        progressProc( &pr );

    TRACE0("Exit USBCBIRead success");
    SetLastError(bOk);
    return (bOk == USB_STATUS_OK);
}


/*-------------------------------------------------------------------------*
 * CBIVendorRequest()                                                      *
 * -------------------------                                               *
 * Description:                                                            *
 *    Performs CBI Vendor Request with command OUT data stage.             *
 *    It used to send any UFTP commands                                    *
 *-------------------------------------------------------------------------*/
BOOL 
CBIVendorRequest(
    PCBI_PIPE_INFO cbi,     /* CBI pipe info  */
    LPVOID command,         /* Command Buffer */
    DWORD  cmdsize          /* Command Buffer Length */
  )
{
    DWORD  Status;
    USB_CLASS_OR_VENDOR_REQUEST request;
    
    memset(&request, 0, sizeof(USB_CLASS_OR_VENDOR_REQUEST));

    // Build class out request
    request.Type   = ClassRequest;
    request.Target = INTERFACE_TARGET( 0 );
    Status = USBClassOrVendorRequest(cbi->device, 
                                     &request, command, cmdsize, NULL);
    SetLastError( Status );
    return (Status == USB_STATUS_OK);
}


/*-------------------------------------------------------------------------*
 * CBIGetStatus()                                                          *
 * -------------------------                                               *
 * Description:                                                            *
 *    Reads 2 bytes from interrupt pipe and returns it into cbi_status.    *
 *-------------------------------------------------------------------------*/
BOOL 
CBIGetStatus(
    PCBI_PIPE_INFO pipeInfo,        /* CBI pipe info    */
    /*USHORT*/unsigned int        *cbi_status       /* returned status  */
  )
{
    DWORD  Status;
    DWORD  dwRead = 2;
    Status = USBReadPipe(pipeInfo->pipe_int, cbi_status, &dwRead, NULL);
    SetLastError( Status );
    return (Status == USB_STATUS_OK);
}
