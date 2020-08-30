#ifndef __TRANSFORM_STRM_H
#define __TRANSFORM_STRM_H

#include "SeStrmBase.h"
#include "OsalTypes.h"


#define MAX_DELIVERY_SAMPLE_SIZE (16 * 2048)

class CTransform
{

public:
	CTransform(){}
    CTransform(void *pSrc, void *pDest){};

    virtual ~CTransform(){};

	void Start();
	void Pause();
	void Stop();	// Flush
	void Eos();
	void Exit();

	static  mf_uint32 MF_APPENTRY InitThread(void *lpParam);
	virtual void Reply(mf_uint32 dw);
	virtual mf_uint32 ThreadProc(void); 

	virtual mf_uint32 DoBufferProcessingLoop(void); 
	virtual mf_bool CheckRequest(mf_uint32 * pParam);

private:
	mf_uint32	m_hThread;
	mf_uint32				m_dwCmd;
	mf_uint32				m_dwCmdPending;

};

#endif //__TRANSFORM_STRM_H