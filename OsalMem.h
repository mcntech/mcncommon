#ifndef _OSAL_MEM_H_
#define _OSAL_MEM_H_

#ifdef __cplusplus
extern "C" 
{
#endif
unsigned long OsalAllocPhysMem(unsigned long *pphysAddr, unsigned long *pvirtAddr, unsigned long numBytes);
void OsalFreePhysMem(unsigned long virtAddr);

#ifdef __cplusplus
}
#endif

#endif	// _OSAL_MEM_H_

