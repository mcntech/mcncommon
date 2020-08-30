#ifndef __DELIVER_STRM_H
#define __DELIVER_STRM_H
#include "OsalThrd.h"
#include "SeStrmBase.h"
#include "OsalTypes.h"

#define MAX_DELIVERY_SAMPLE_SIZE (16 * 2048)

class CStreamOut
{

public:
	CStreamOut();
    virtual ~CStreamOut();

	virtual mf_uint32  Deliver(mf_uchar *pData, long DataLen);
	virtual mf_uint32  DeliverEndOfStream();
	virtual void SetStatusCallback(void	*pCallbackCtx, pfnStatusCallback_t pfnStatusCallback) {
		m_pfnStatusCallback = pfnStatusCallback;
		m_pCallbackCtx = pCallbackCtx;
	};

	virtual void Start();
	virtual void Reinit(){}
	virtual void Pause();
	virtual void Stop();	// Flush
	virtual void Eos();
	virtual void NewSegment(long StartTime90kHz){};
	virtual void Exit();

	virtual void SetParam(unsigned long ulParamId, unsigned long ulValue){}
	virtual unsigned long GetParam(unsigned long ulParamId){return 0;}

	/* Followinf functions are for debug purpose, during file writes */
	void EnableLoop(int EnbleLoop) {m_EnableLoop = EnbleLoop;}
	void SetMaxDataLen(int MaxDataLen) {m_MaxDataLen = MaxDataLen;}

	static  mf_uint32 MF_APPENTRY InitThread(void *lpParam);
	virtual void Reply(mf_uint32 dw);
	virtual mf_uint32 ThreadProc(void); 

	virtual mf_uint32 DoBufferProcessingLoop(void); 
	virtual mf_bool CheckRequest(mf_uint32 * pParam);

	mf_uint32	        m_hThread;

	mf_uint32			m_dwCmd;
	mf_uint32			m_dwCmdPending;

protected:
	pfnStatusCallback_t	m_pfnStatusCallback;

protected:
	int				m_EnableLoop;		// Used for debug purpose on file wirites
	unsigned long	m_MaxDataLen;
	mf_uchar		*m_pData;
	int				m_FileOut;
	void			*m_pCallbackCtx;
};

#endif //__DELIVER_STRM_H


