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
 * File: uftp_def.h                                                        *
 *                                                                         *
 * Purpose:                                                                *
 *   UFTP library internal definitions                                     *
 *-------------------------------------------------------------------------*/

#ifndef _UFTP_DEF_H_
#define _UFTP_DEF_H_

#include "cbi.h"
#include <assert.h>
#include <stdio.h>
#include <list.h>

//#define TRACE0( a  )   
//#define ASSERT( a  )   
//#define TRACE1(a, b)   

#ifdef _cplusplus
//   extern 'C' {
#endif // __cplusplus

#include <pshpack1.h>


typedef struct {
    BYTE  cbSize;   
    char* pchData;
} UFTP_STRING;

typedef struct {
    BYTE  cbRequestType;
    DWORD cbFileLen;
    BYTE  cbFileName;   
    void* sFileName;   
} UFTP_WRITE_REQUEST;

typedef struct {
    BYTE  cbRequestType;
    BYTE  cbFileName;   
    void* sFileName;
} UFTP_READ_REQUEST;

typedef struct {
    BYTE  cbRequestType;
    BYTE  cbFileName;   
    void* sFileName;
} UFTP_DELETE_REQUEST;


typedef struct {
    BYTE  cbRequestType;
    BYTE  cbFileName;   
    char* szFileName;      
} UFTP_GET_FILE_INFO_REQUEST;

typedef struct {
    BYTE  cbRequestType;
	BYTE  cbNameLen;
	char* szFileName;
} UFTP_GETDIR_REQUEST;

typedef struct {
    BYTE  cbRequestType;
    DWORD dwTransferLen;
} UFTP_SET_TRANSFER_LEN_REQUEST;


typedef struct {
    BYTE dwPacketType;
} UFTP_PACKET, *PUFTP_PACKET;

typedef struct {
    HANDLE hFile;
    HANDLE hMapFile;
    LPVOID pvMap;
} UFTP_WRITE_CONTEXT;

typedef struct {
    HANDLE hFile;
    DWORD  dwFileLength;
} UFTP_READ_CONTEXT;

typedef struct {
    DWORD   dwBufferSize;
    DWORD   dwFilesCount;
    LPVOID  lpBuffer;
} UFTP_GETDIR_CONTEXT;

typedef struct {
   DWORD  dwFileLength;
} UFTP_FILE_INFO_CONTEXT;


//typedef struct _UFTP_REQUEST;
typedef struct _UFTP_HANDLE {
    DWORD                dwSize;
    CBI_PIPE_INFO        cbiInterface;
    LIST         reqList;
    CRITICAL_SECTION     reqListCS;
    PROGRESS_ROUTINE     progressProc; 
    LPVOID               progressParam;
    DWORD                LastError;
    DWORD                TransferUnit;
} UFTP_HANDLE, *PUFTP_HANDLE;

typedef struct _UFTP_REQUEST {
    DWORD       dwRequestType;
    DWORD       dwRequestSize;
    LPVOID      RequestBuffer;
    union {
        UFTP_WRITE_CONTEXT      WriteContext;
        UFTP_READ_CONTEXT       ReadContext;
        UFTP_FILE_INFO_CONTEXT  FileInfoContext;
        UFTP_GETDIR_CONTEXT     GetDirContext;
    };      
    PUFTP_HANDLE hUFTP;
    LINK     Link;
} UFTP_REQUEST, *PUFTP_REQUEST;


#include <poppack.h>

BOOL 
Uftp_BuildWriteRequest(
    PUFTP_REQUEST request, 
    LPCTSTR       path,
    DWORD         dwFileSize
  );

BOOL 
Uftp_BuildReadRequest(
    PUFTP_REQUEST request, 
    LPCTSTR   lpszFileName
  );

BOOL 
Uftp_BuildDelRequest(
    PUFTP_REQUEST request, 
    LPCTSTR   lpszFileName
  );

BOOL 
Uftp_BuildFileInfoRequest(
    PUFTP_REQUEST request, 
    LPCTSTR   lpszFileName
  );

#ifdef _cplusplus
//    }
#endif // __cplusplus


#endif // _UFTP_DEF_H_