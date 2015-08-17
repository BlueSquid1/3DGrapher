#ifndef COMMONUTIL_H
#define COMMONUTIL_H

struct st_cpg {                                         /* struct CPG   */
	union {                                   /* FRQCR        */
		unsigned short WORD;                /*  Word Access */
		struct {                            /*  Bit  Access */
			unsigned short : 3;      /*              */
			unsigned short CKOEN : 1;      /*    CKOEN     */
			unsigned short : 2;      /*              */
			unsigned short STC : 2;      /*    STC       */
			unsigned short : 2;      /*              */
			unsigned short IFC : 2;      /*    IFC       */
			unsigned short : 2;      /*              */
			unsigned short _PFC : 2;      /*    PFC       */
		}       BIT;                 /*              */
	}           FRQCR;                  /*              */
};                                                      /*              */

struct st_wdt {                                         /* struct WDT   */
	union {                                   /* WTCNT        */
		unsigned char  READ;                /*  Read  Access*/
		unsigned short WRITE;               /*  Write Access*/
	}           WTCNT;                  /*              */
	union {                                   /* WTCSR        */
		union {                             /*  Read  Access*/
			unsigned char BYTE;           /*   Byte Access*/
			struct {                      /*   Bit  Access*/
				unsigned char TME : 1;  /*    TME       */
				unsigned char WTIT : 1;  /*    WT/IT     */
				unsigned char RSTS : 1;  /*    RSTS      */
				unsigned char WOVF : 1;  /*    WOVF      */
				unsigned char IOVF : 1;  /*    IOVF      */
				unsigned char CKS : 3;  /*    CKS       */
			}      BIT;            /*              */
		}         READ;                /*              */
		unsigned short WRITE;               /*  Write Access*/
	}           WTCSR;                  /*              */
};

#define CPG    (*(volatile struct st_cpg   *)0xFFFFFF80)/* CPG   Address*/
#define WDT    (*(volatile struct st_wdt   *)0xFFFFFF84)/* WDT   Address*/


class CommonUtil
{
public:
	static void MR_CPUSpeedNormal();
	static void MR_CPUSpeedDouble();
};

#endif