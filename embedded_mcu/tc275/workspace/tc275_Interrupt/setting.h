/*
 * setting.h
 *
 *  Created on: 2021. 12. 29.
 *      Author: hrkim
 */

#ifndef SETTING_H_
#define SETTING_H_
/* Define PORT10 Registers for LED */
#define PORT10_BASE     (0xF003B000)
#define PORT10_IOCR0    (*(volatile unsigned int*)(PORT10_BASE + 0x10))
#define PORT10_OMR      (*(volatile unsigned int*)(PORT10_BASE + 0x04))

#define PC1             11
#define PCL1            17
#define PS1             1

/* Define PORT02 Registers for Switch2 */
#define PORT02_BASE     (0xF003A200)
#define PORT02_IOCR0    (*(volatile unsigned int*)(PORT02_BASE + 0x10))
#define PORT02_IN       (*(volatile unsigned int*)(PORT02_BASE + 0x24))

#define PC1             11
#define P1              1

/* Define SCU Registers for Interrupt */
#define SCU_BASE        (0xF0036000)
#define SCU_WDTSCON0    (*(volatile unsigned int*)(SCU_BASE + 0x0F0))
#define SCU_EICR1       (*(volatile unsigned int*)(SCU_BASE + 0x214))
#define SCU_IGCR0       (*(volatile unsigned int*)(SCU_BASE + 0x22C))

#define LCK             1
#define ENDINIT         0
#define INP0            12
#define EIEN0           11
#define FEN0            8
#define EXIS0           4
#define IGP0            14

/* Define SRC Registers for Interrupt */
#define SRC_BASE        (0xF0038000)
#define SRC_SCUERU0     (*(volatile unsigned int*)(SRC_BASE + 0xCD4))

#define TOS             11
#define SRE             10
#define SRPN            0

void init_LED(void);
void init_Switch(void);
void init_ERU(void);




#endif /* SETTING_H_ */
