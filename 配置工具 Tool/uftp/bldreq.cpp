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
 * File: bldreq.c                                                          *
 *                                                                         *
 * Purpose:                                                                *
 *   This module responsible for building UFTP requests to                 *
 *   UFTP_REQUEST structure buffers                                        *
 *-------------------------------------------------------------------------*/
#include "stdafx.h"
#include <windows.h>
#include "uftp_def.h"
#include "uftp.h"

BOOL 
Uftp_BuildWriteRequest(
    PUFTP_REQUEST request, 
    LPCTSTR       path,
    DWORD         dwFileSize
  )
{
    int   fileNameLen;
    char  fname[_MAX_FNAME + _MAX_EXT];
    char  ext[_MAX_EXT];
    UFTP_WRITE_REQUEST* write = NULL;

    if (path == NULL) {
        ASSERT( 1 );            // File Name cann't be NULL
        return FALSE;
    }

    _splitpath(path, NULL, NULL, fname, ext);   
    if (*fname == '\0')
        return FALSE;

    strcat(fname, ext);
    fileNameLen = strlen(fname);

    request->dwRequestSize = sizeof(UFTP_WRITE_REQUEST) - 
                             sizeof(void*) + fileNameLen;
    request->RequestBuffer = malloc( request->dwRequestSize );
    if ( !request->RequestBuffer )
        return FALSE;

    write = (UFTP_WRITE_REQUEST*) request->RequestBuffer;
    write->cbRequestType = UFTP_WRITE;
    write->cbFileLen     = dwFileSize;
    write->cbFileName    = fileNameLen;
    memcpy(&write->sFileName, fname, fileNameLen);
    return TRUE;
}

BOOL 
Uftp_BuildReadRequest(
    PUFTP_REQUEST request, 
    LPCTSTR   lpszFileName
  )
{
    int   fileNameLen;
    UFTP_READ_REQUEST* read = NULL;

    if (lpszFileName == NULL) {
        ASSERT( 1 );            // File Name cann't be NULL
        return FALSE;
    }

    fileNameLen = strlen(lpszFileName);
    if (fileNameLen == 0)
        return FALSE;

    request->dwRequestSize = sizeof(UFTP_READ_REQUEST) - 
                             sizeof(void*) + fileNameLen;
    request->RequestBuffer = malloc( request->dwRequestSize );
    if ( !request->RequestBuffer ) {
        TRACE0("Failed to allocate RequestBuffer");
        return FALSE;
    }

    read = (UFTP_READ_REQUEST*) request->RequestBuffer;
    read->cbRequestType = UFTP_READ;
    read->cbFileName    = fileNameLen;
    memcpy(&read->sFileName, lpszFileName, fileNameLen);
    return TRUE;        
}


BOOL 
Uftp_BuildDelRequest(
    PUFTP_REQUEST request, 
    LPCTSTR   lpszFileName
  )
{
    int   fileNameLen;
    UFTP_DELETE_REQUEST* del = NULL;

    if (lpszFileName == NULL) {
        ASSERT( 1 );            // File Name cann't be NULL
        return FALSE;
    }

    fileNameLen = strlen(lpszFileName);
    if (fileNameLen == 0)
        return FALSE;

    request->dwRequestSize = sizeof(UFTP_DELETE_REQUEST) - 
                             sizeof(void*) + fileNameLen;
    request->RequestBuffer = malloc( request->dwRequestSize );
    if ( !request->RequestBuffer ) {
        TRACE0("Failed to allocate RequestBuffer");
        return FALSE;
    }

    del = (UFTP_DELETE_REQUEST*) request->RequestBuffer;
    del->cbRequestType = UFTP_DELETE;
    del->cbFileName    = fileNameLen;
    memcpy(&del->sFileName, lpszFileName, fileNameLen);
    return TRUE;        
}

BOOL Uftp_BuildFileInfoRequest(PUFTP_REQUEST request, 
                               LPCTSTR   lpszFileName)
{
    UFTP_GET_FILE_INFO_REQUEST *fileInfo;
    int fileNameLen;

    if (lpszFileName == NULL) {
        ASSERT( 0 );
        return FALSE;
    }

    fileNameLen = strlen( lpszFileName );
    if (fileNameLen == 0)
        return FALSE;

    request->dwRequestSize = sizeof(UFTP_GET_FILE_INFO_REQUEST) - 
                             sizeof(void*) + fileNameLen;
    request->RequestBuffer = malloc( request->dwRequestSize );
    if ( !request->RequestBuffer ) {
        TRACE0("Failed to allocate RequestBuffer");
        return FALSE;
    }

    fileInfo = (UFTP_GET_FILE_INFO_REQUEST*) request->RequestBuffer;
    fileInfo->cbRequestType = UFTP_GET_FILE_INFO;
    fileInfo->cbFileName = fileNameLen;
    memcpy(&fileInfo->szFileName, lpszFileName, fileNameLen);
    return TRUE;
}