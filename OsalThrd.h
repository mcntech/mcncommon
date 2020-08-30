#ifndef __OSAL_THRD__
#define __OSAL_THRD__

#include "OsalTypes.h"

#define SE_STRM_THRD_PRIORITY		249

#define MSG_QUEUE_CRATE_READ		0x00000001
#define MSG_QUEUE_CRATE_WRITE		0x00000002
#define	MSG_QUEUE_INVALID			-1	

#define MAX_MSG_QUEUE_NAME			256


void ConvertTToC(char* pszDest, const unsigned short* pszSrc);
void ConvertCToT(unsigned short* pszDest, const char* pszSrc);

void osalSleep(int Ms);

long osalGetTime();

bool osalCloseHandle(unsigned long	ulHandle);
unsigned long osalGetTickCount();


unsigned long 
osalCreateThread(
	void			*pThrdFunc,
	void			*pCtx, 
	unsigned long	*pulHandle);

unsigned long 
osalGetCurrentThreadId();

void
osalSetThreadPriority(
		unsigned long ulThrdId,
		unsigned long lPriority);///wince[0,255],linux[20,-20)

void
osalExitThread();

bool
osalWaitForThreadCompletion(
	unsigned long ulHandle,
	unsigned long ulTimeOut);

unsigned long 
osalCreateMsgQueue(
	char			*pszName,
	long			lMsgSize,	
	unsigned long	*pulHandle);

unsigned long 
osalCreateMsgQueueEx(
	char			*pszName,
	long			lMsgSize,	
	unsigned long	ulFlags,
	unsigned long	*pulHandle);

bool osalReadMsgQueue(
	unsigned long	ulHandle, 
	char			*pData, 
	long			lSize, 
	unsigned long	*pulBytesRead, 
	bool			fBlocking, 
	unsigned long   *pulFlags);

bool osalWriteMsgQueue(
	unsigned long hMsgQ,
	char			*pData,
	long			lSize,
	unsigned long	ulTimeout,
	unsigned long	ulFlags
	);

bool osalWaitForMsgQueue(
	unsigned long	ulHandle,
	unsigned long	ulTimeOut);

bool osalCloseMsgQueue(
	unsigned long	ulHandle);


unsigned long osalCreateEvent(
	bool bManualReset,
	bool bInitialState,
	char *pszName
);

bool osalWaitForEvent(
  	unsigned long	ulHandle,
	unsigned long	ulTimeOut
	);

bool osalResetEvent(
  	unsigned long	ulHandle);

bool osalSetEvent(
  	unsigned long	ulHandle);

bool osalResetEvent(
  	unsigned long	ulHandle);

bool osalCloseEvent(
  	unsigned long	ulHandle);


unsigned long osalCreateMutex(
	bool bOwn,
	char *pszName						///< Not Used
);

bool osalReleaseMutex (
	unsigned long hMutex);

bool osalAcquireMutex (
	unsigned long	hMutex, 
	unsigned long	ulTimeOut);

bool osalCloseMutex (unsigned long hMutex);

int  osalGetErrorCode(void);

bool osalCloseHandle(
  	unsigned long	ulHandle);

/*
unsigned long OsalHtonl(unsigned long ulVal); 
unsigned short OsalHtons(unsigned short usVal);
*/

#endif //__OSAL_THRD__

