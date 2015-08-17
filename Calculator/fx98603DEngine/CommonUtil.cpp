#include "CommonUtil.h"

void CommonUtil::MR_CPUSpeedNormal()
{
	WDT.WTCSR.WRITE = 96;
	WDT.WTCNT.WRITE = 0;
	CPG.FRQCR.BIT._PFC = 1;
	CPG.FRQCR.BIT.STC = 0;
}

void CommonUtil::MR_CPUSpeedDouble()
{
	WDT.WTCSR.WRITE = 96;
	WDT.WTCNT.WRITE = 0;
	CPG.FRQCR.BIT._PFC = 1;
	CPG.FRQCR.BIT.STC = 1;
}
