#ifndef __OSAL_TYPES__
#define __OSAL_TYPES__

   
//=============================================================================
//  data types used by media framework. To be used with new modules
//
//=============================================================================
#define mf_uint32		unsigned long
#define mf_int32		long
#define mf_uchar		unsigned char
#define mf_false		0
#define mf_true			1
#define mf_bool			bool
#define mf_ok			0
#define mf_fail			-1
#define mf_error		-1
#define mf_noerror		mf_ok



//=============================================================================
//  Data types to fiacilitate porting of code from WIN32/WinCe Modules
//
//=============================================================================

#if defined(UNDER_CE) || defined(WINDOWS) || defined(WIN32)
#define MF_APPENTRY		__stdcall //WINAPI
#define MF_WAIT_INFINITE	0xFFFFFFFFL
#elif defined (LINUX32)||(NC_LINUX)
#define MF_APPENTRY
#define MF_WAIT_INFINITE	0xFFFFFFFF

#ifndef NULL
#define NULL  0
#endif

#define FALSE 0
#define TRUE  1
#define CALLBACK
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned int HWND;
typedef unsigned int ULONG;
//typedef unsigned int BOOL;

#define BOOL    mf_bool

#define WORD    short
typedef unsigned char* PBYTE;

typedef unsigned int BOOL32;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef int INT;
typedef void * HANDLE;

typedef signed char  SINT8;
typedef signed short SINT16;
//typedef unsigned char BOOL;


typedef struct _RECT{
    long left,top,right, bottom;
} RECT;

#define S_FALSE -1
#define S_OK 0
#define E_FAIL S_FALSE
#define NOERROR S_OK
#define DWORD	unsigned long
#define HWAVEOUT unsigned long
typedef struct WAVEHDR{
	unsigned long dwBufferLength;
	char*		lpData;
	unsigned long   dwFlags;
}WAVEHDR_t;

//=============================================================================
//====================== data types required by  Sokcet If ====================

#define SOCKET int
#define SOCKET_ERROR	-1
#define INVALID_SOCKET     -1

#define SOCKADDR sockaddr
#define LPSOCKADDR sockaddr *
#define LPSOCKADDR_IN sockaddr_in *
#define SOCKADDR_IN sockaddr_in
#define ULONG unsigned long
#define USHORT unsigned short
#define LPDIRECTDRAWSURFACE void *
#define LPDIRECTDRAW void *

#define IN
#define WINAPI
#define LPVOID void *
#define LPARAM void *
#define VOID void
#define __try
#define __except(a) if(0)
#define HMODULE void *
#define TCHAR char
#define TEXT
#define __cdecl
#define HRESULT long
#define INFINITE MF_WAIT_INFINITE 
#define WAIT_OBJECT_0 true

#endif



#ifdef LINUX32

#define DD_OK 0
#define S_FALSE -1
#define S_OK 0
#define E_FAIL S_FALSE
#define NOERROR S_OK
#define DWORD	unsigned long
#define HWAVEOUT unsigned long

#define TCHAR char
#define HWND unsigned long*
//#define TEXT(A) A
#define LPCTSTR char*

#endif

#define WAIT_TIMEOUT         258L

#endif //__OSAL_TYPES__




