#ifndef __StrmIn_h
#define __StrmIn_h

#include "StreamOut.h"
#include "SeStrmBase.h"
#include "OsalThrd.h"
class CStreamIn 
{

public:
	CStreamIn(
		CStreamOut	*pVidStreamOut,
		CStreamOut	*pAudStreamOut,
		mf_uint32	*phr);

	CStreamIn(){ m_Eos = 0; m_EnableLoop = 0;}

    virtual ~CStreamIn();

    virtual mf_uint32 FillBuffer(
		mf_uchar	*data,
		long		bufferLen,
		long		*pActaulLen);

	virtual mf_uint32 DoBufferProcessingLoop(void);
	mf_bool	CheckRequest(mf_uint32 * pParam);
	void	Reply(mf_uint32 dw);
	mf_uint32	ThreadProc();

	static unsigned long MF_APPENTRY InitThread(void * lpParam);
	virtual int GetStreamParams(
		int *pWidth,
		int *pHeight,
		int *pFormat) {
			return  0;	// FAIL
	}

	virtual int SetStreamParams(
		int Width,
		int Height,
		int Format) {
			return  0;	// FAIL
	}

	virtual void Start();
	virtual void Stop();
	virtual void Exit();
	virtual void SetParam(unsigned long ulParamId, unsigned long ulValue){}
	virtual long GetParam(unsigned long ulParamId){return 0;}
	void EnableLoop(int EnbleLoop) {m_EnableLoop = EnbleLoop;}
	int  IsEos(){return m_Eos;}
	virtual void SetStatusCallback(void *pCallbackCtx, pfnStatusCallback_t pfnStatusCallback) {
		m_pfnStatusCallback = pfnStatusCallback;
		m_pCallbackCtx = pCallbackCtx;
	};

	virtual int IsInitOk() { return 0;}
	mf_uint32 m_hThread;

protected:
	pfnStatusCallback_t	m_pfnStatusCallback;

protected:
	CStreamOut *m_pStreamOut;
	CStreamOut *m_pAudStreamOut;
	mf_uint32		m_dwCmd;
	mf_uint32		m_dwCmdPending;
	int			m_Eos;
	int			m_EnableLoop;
	void		*m_pCallbackCtx;
};

#endif //__StrmIn_h

