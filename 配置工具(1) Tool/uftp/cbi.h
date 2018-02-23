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
 * MCF5272 USB TEST SUITE                                                  *
 * File: cbi.c                                                             *
 *                                                                         *
 * Purpose:                                                                *
 *   Control/Bulk/Interrupt transfers stuff definition                     *
 *-------------------------------------------------------------------------*/

#ifndef _CBI_H_
#define _CBI_H_

#include "motusb.h"

#ifdef __cplusplus
//extern 'C' {
#endif

#include <pshpack1.h>
#include "progress.h"

typedef struct  {
    // -------------------------------------
    // This setup by CBIOpen proc
    // -------------------------------------
    usb_t  pipe_in;             // BULK IN    pipe 
    usb_t  pipe_out;            // BULK OUT   pipe 
    usb_t  pipe_int;            // INTERRUPT  pipe
    usb_t  device;              // device handle

    // ---------------------------------------------
    // This field can be setup by CBISetProgressProc 
    // ---------------------------------------------
    CRITICAL_SECTION    csProgress;     // Critical Section to protect progress Params 
    BOOL                csInitialized;  // Flag that csProgress initialized
    PROGRESS_ROUTINE    progress;       // progress routine callback 
    void*               progressParam;  // progress routine misc param

} CBI_PIPE_INFO, *PCBI_PIPE_INFO;

#include <poppack.h>

BOOL 
CBIOpen(
    IN  usb_t          device, 
    IN  OUT UCHAR     *interfaceNum, 
    OUT PCBI_PIPE_INFO pipeInfo
  );

void 
CBIClose(
    IN  PCBI_PIPE_INFO pipeInfo
  );

BOOL 
CBIWrite(
    IN PCBI_PIPE_INFO    pipeInfo, 
    IN PVOID             buffer, 
    IN UINT              dataLength, 
    IN DWORD             MaxTransferSize,
    IN PROGRESS_ROUTINE  progressProc, 
    IN LPVOID            progressParam
  );

BOOL 
CBIRead(
    IN PCBI_PIPE_INFO    pipeInfo,   
    IN PVOID             buffer,   
    IN UINT              dataLength,          
    IN DWORD             TransferUnit,
    IN PROGRESS_ROUTINE  progressProc, 
    IN LPVOID            progressParam
  );

BOOL 
CBIVendorRequest(
    IN PCBI_PIPE_INFO pipeInfo,  
    IN LPVOID         command, 
    IN DWORD          cmdsize
  );

BOOL 
CBIGetStatus(
    IN  PCBI_PIPE_INFO pipeInfo, 
    OUT /*USHORT*/unsigned int        *cbi_status 
  );

#ifdef __cplusplus
//};
#endif

#endif //_CBI_H_