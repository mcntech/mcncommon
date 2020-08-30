#ifndef __AVFRAME_H__
#define __AVFRAME_H__

class CAvFrame 
{
public:
	CAvFrame(long lFrameSize)
	{
		m_lFrameSize = lFrameSize;
		m_pFrameData = (char *)malloc(lFrameSize);
		m_lPtsMs   = 0;
		m_lOffset   = -1;
		m_lRef = 1;
	}

	~CAvFrame()
	{
		if(m_pFrameData)
			free(m_pFrameData);
	}
	long AddRef() {return ++m_lRef; return m_lRef;}
	long Release() {m_lRef--; if(!m_lRef) delete this;return 0;}

public:
	long	m_lPtsMs;
    char	*m_pFrameData;
    long	m_lFrameSize;
    long	m_lStrmId;
    long	m_lFlags;
    void	*m_pPriv;
    long	m_lOffset;                            ///< byte position in stream, -1 if unknown
	long	m_lRef;
};
#endif //__AVFRAME_H__