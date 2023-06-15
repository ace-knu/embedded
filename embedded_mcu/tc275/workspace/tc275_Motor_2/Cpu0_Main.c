#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

IfxCpu_syncEvent g_cpuSyncEvent = 0;

// Port Registers
#define PORT02_BASE         (0xF003A200)
#define PORT02_OMR          (*(volatile unsigned int*) (PORT02_BASE + 0x04))
#define PORT02_IOCR0        (*(volatile unsigned int*) (PORT02_BASE + 0x10))
#define PORT02_IOCR4        (*(volatile unsigned int*) (PORT02_BASE + 0x10))
#define PORT02_IN           (*(volatile unsigned int*) (PORT02_BASE + 0x24))

#define PORT10_BASE         (0xF003B000)
#define PORT10_OMR          (*(volatile unsigned int*) (PORT10_BASE + 0x04))
#define PORT10_IOCR0        (*(volatile unsigned int*) (PORT10_BASE + 0x10))

#define P0                  0
#define PC0                 3
#define PC1                 11
#define PC7                 27
#define PS0                 0
#define PS1                 1
#define PS7                 7
#define PCL0                16
#define PCL1                17
#define PCL7                23


// SCU Registers
#define SCU_BASE            (0xF0036000)
#define SCU_WDTSCON0        (*(volatile unsigned int*)(SCU_BASE + 0x0F0))
#define SCU_WDT_CPU0CON0    (*(volatile unsigned int*)(SCU_BASE + 0x100))
#define SCU_EICR2           (*(volatile unsigned int*)(SCU_BASE + 0x218))
#define SCU_IGCR0           (*(volatile unsigned int*)(SCU_BASE + 0x22C))

#define LCK                 1
#define ENDINIT             0
#define INP0                12
#define EIEN0               11
#define REN0                9
#define FEN0                8
#define EXIS0               4
#define IGP0                14


// SRC Registers
#define SRC_BASE            (0xF0038000)
#define SRC_CCU60_SR0       (*(volatile unsigned int*)(SRC_BASE + 0x420))
#define SRC_SCUERU0         (*(volatile unsigned int*)(SRC_BASE + 0xCD4))

#define TOS                 11
#define SRE                 10
#define SRPN                0


// CCU60 Registers
#define CCU60_BASE          (0xF0002A00)
#define CCU60_CLC           (*(volatile unsigned int*)(CCU60_BASE + 0x00))
#define CCU60_T12           (*(volatile unsigned int*)(CCU60_BASE + 0x20))
#define CCU60_T12PR         (*(volatile unsigned int*)(CCU60_BASE + 0x24))
#define CCU60_TCTR0         (*(volatile unsigned int*)(CCU60_BASE + 0x70))
#define CCU60_TCTR4         (*(volatile unsigned int*)(CCU60_BASE + 0x78))
#define CCU60_INP           (*(volatile unsigned int*)(CCU60_BASE + 0xAC))
#define CCU60_IEN           (*(volatile unsigned int*)(CCU60_BASE + 0xB0))

#define DISS                1
#define DISR                0
#define CTM                 7
#define T12PRE              3
#define T12CLK              0
#define T12STR              6
#define T12RS               1
#define INPT12              10
#define ENT12PM             7


/* VADC Registers */
#define VADC_BASE       (0xF0020000)
#define VADC_CLC        (*(volatile unsigned int*)(VADC_BASE + 0x000))
#define VADC_GLOBCFG    (*(volatile unsigned int*)(VADC_BASE + 0x080))
#define VADC_G4ARBCFG   (*(volatile unsigned int*)(VADC_BASE + 0x1480))
#define VADC_G4ARBPR    (*(volatile unsigned int*)(VADC_BASE + 0x1484))
#define VADC_G4ICLASS0  (*(volatile unsigned int*)(VADC_BASE + 0x14A0))
#define VADC_G4QMR0     (*(volatile unsigned int*)(VADC_BASE + 0x1504))
#define VADC_G4QINR0    (*(volatile unsigned int*)(VADC_BASE + 0x1510))
#define VADC_G4CHCTR6   (*(volatile unsigned int*)(VADC_BASE + 0x1618))
#define VADC_G4RES1     (*(volatile unsigned int*)(VADC_BASE + 0x1704))
#define VADC_G4CHCTR7   (*(volatile unsigned int*)(VADC_BASE + 0x161C))
#define VADC_G4CHASS    (*(volatile unsigned int*)(VADC_BASE + 0x1488))

#define DISS            1
#define DISR            0
#define ANONC           0
#define ASEN0           24
#define CSM0            3
#define PRIO0           0
#define CMS             8
#define STCS            0
#define FLUSH           10
#define TREV            9
#define ENGT            0
#define RF              5
#define REQCHNR         0
#define RESPOS          21
#define RESREG          16
#define ICLSEL          0
#define VF              31
#define RESULT          0
#define CHNR            20
#define ASSCH7          7


// GTM
#define GTM_CLC                     (*(volatile unsigned int*)(GTM_BASE + 0x9FD00))
#define GTM_TOUTSEL0                (*(volatile unsigned int*)(GTM_BASE + 0x9FD30))
#define GTM_TOUTSEL6                (*(volatile unsigned int*)(GTM_BASE + 0x9FD48))

#define DISS                        1
#define DISR                        0
#define SEL1                        2
#define SEL7                        14

/* GTM Registers */
// GTM - CMU
#define GTM_BASE                    (0xF0100000)
#define GTM_CMU_CLK_EN              (*(volatile unsigned int*)(GTM_BASE + 0x00300))
#define GTM_CMU_FXCLK_CTRL          (*(volatile unsigned int*)(GTM_BASE + 0x00344))
#define EN_FXCLK                    22
#define FXCLK_SEL                   0

// GTM - TOM0
#define GTM_TOM0_TGC0_GLB_CTRL      (*(volatile unsigned int*)(GTM_BASE + 0x08030))
#define GTM_TOM0_TGC0_ENDIS_CTRL    (*(volatile unsigned int*)(GTM_BASE + 0x08070))
#define GTM_TOM0_TGC0_OUTEN_CTRL    (*(volatile unsigned int*)(GTM_BASE + 0x08078))
#define GTM_TOM0_TGC0_FUPD_CTRL     (*(volatile unsigned int*)(GTM_BASE + 0x08038))
#define GTM_TOM0_CH1_CTRL           (*(volatile unsigned int*)(GTM_BASE + 0x08040))
#define GTM_TOM0_CH1_SR0            (*(volatile unsigned int*)(GTM_BASE + 0x08044))
#define GTM_TOM0_CH1_SR1            (*(volatile unsigned int*)(GTM_BASE + 0x08048))

#define GTM_TOM0_TGC1_GLB_CTRL      (*(volatile unsigned int*)(GTM_BASE + 0x08230))
#define GTM_TOM0_TGC1_ENDIS_CTRL    (*(volatile unsigned int*)(GTM_BASE + 0x08270))
#define GTM_TOM0_TGC1_OUTEN_CTRL    (*(volatile unsigned int*)(GTM_BASE + 0x08278))
#define GTM_TOM0_TGC1_FUPD_CTRL     (*(volatile unsigned int*)(GTM_BASE + 0x08238))
#define GTM_TOM0_CH9_CTRL           (*(volatile unsigned int*)(GTM_BASE + 0x08240))
#define GTM_TOM0_CH9_SR0            (*(volatile unsigned int*)(GTM_BASE + 0x08244))
#define GTM_TOM0_CH9_SR1            (*(volatile unsigned int*)(GTM_BASE + 0x08248))

#define UPEN_CTRL1                  18
#define HOST_TRIG                   0
#define ENDIS_CTRL1                 2
#define OUTEN_CTRL1                 2
#define RSTCN0_CH1                  18
#define FUPD_CTRL1                  2
#define CLK_SRC_SR                  12
#define SL                          11


void initButton(void);
void initMotor(void);
void initVADC(void);
void VADC_startConversion(void);
unsigned int VADC_readResult(void);
void initGTM(void);

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    //initERU();
    initMotor();
    initGTM();
    initVADC();
    initButton();

    GTM_TOM0_TGC1_GLB_CTRL |= ((0x01) << HOST_TRIG);

    unsigned short duty = 0;

    while(1)
    {
        VADC_startConversion();
        unsigned int adcResult = VADC_readResult();

        duty = 12500 * adcResult / 4096;

        if( (PORT02_IN & (0x1 << P0)) == 0) {
            // Run MOTOR Foward
            // to run motor Foward :
            // PWMA (D3) = HIGH
            // DIRA (D12) = HIGH
            // BRAKE_A (D9) = LOW

            PORT10_OMR |= ((0x01) << PS1);      // Set DIRA to HIGH
            PORT02_OMR |= ((0x01) << PCL7);     // Set BRAKE_A to LOW

        } else {
            // Run MOTOR Backward
            // to run motor Foward :
            // PWMA (D3) = HIGH
            // DIRA (D12) = LOW
            // BRAKE_A (D9) = LOW

            PORT10_OMR |= ((0x01) << PCL1);     // Set DIRA to LOW
            PORT02_OMR |= ((0x01) << PCL7);     // Set BRAKE_A to LOW
        }

        GTM_TOM0_CH9_SR1 = duty;    // Set PWMA
    }
    return (1);
}

void initButton(void)
{
    PORT02_IOCR0 &= ~(0x1F << PC0);

    PORT02_IOCR0 |= (0x02 << PC0);
}

void initMotor(void)
{
    PORT10_IOCR0 &= ~(0x1F << PC1);
    PORT02_IOCR0 &= ~(0x1F << PC1);
    PORT02_IOCR4 &= ~(0x1F << PC7);

    PORT10_IOCR0 |= (0x10 << PC1);  // Set D12 to OUTPUT (DIRA)
    PORT02_IOCR0 |= (0x11 << PC1);  // Set D3 to PWM OUTPUT (PWMA)
    PORT02_IOCR4 |= (0x10 << PC7);  // Set D9 to OUTPUT (BRAKE_A)
}

void initVADC(void)
{
    /* VADC Enable */
    /* Password Access to unlock WDTCPU0CON0 */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) & ~(1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) != 0);

    /* Modify Access to clear ENDINIT bit */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) | (1 << LCK)) & ~ (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) == 0);

    VADC_CLC &= ~(1 << DISR);                 // Enable VADC Module

    /* Password Access to unlock WDTSCPU0CON0 */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) & ~(1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) != 0);

    /* Modify Access to clear ENDINIT bit */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) | (1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) == 0);

    while((VADC_CLC & (1 << DISS)) != 0);     // Wait until module is enabled

    //VADC_GLOBCFG |= ((1<<31) | (1<<15) | 0x9);

    VADC_G4ARBPR |=  ((0x3) << PRIO0);        // Highest Priority for Request Source 0
    VADC_G4ARBPR &= ~((0x01) << CSM0);        // Conversion Start Mode : Wait-for-start mode
    VADC_G4ARBPR |=  ((0x01) << (ASEN0));     // Arbitration Source Input 0 Enable

    VADC_G4QMR0  &= ~((0x03) << ENGT);        // Enable Conversion Requests
    VADC_G4QMR0  |=  ((0x01) << ENGT);

    VADC_G4QMR0  |=  ((0x01) << FLUSH);       // Clear all Queue Entries

    VADC_G4ARBCFG |=  ((0x3) << ANONC);       // Analog Converter : Normal Operation

    VADC_G4ICLASS0 &= ~((0x7) << CMS);        // Group-specific Class 0

    /* VADC Group 4 Channel 7 Setting */
    VADC_G4CHCTR7 |=  ((0x01) << RESPOS);     // Read Results Right-aligned
    VADC_G4CHCTR7 &= ~((0xF) << RESREG);      // Store Result in Group Result Register G4RES1
    VADC_G4CHCTR7 &= ~((0x3) << ICLSEL);      // Use Group-specific Class 0



    VADC_G4CHCTR7 |=  ((0x01) << RESREG);
    VADC_G4CHASS |= 0x1 << ASSCH7;
}

void VADC_startConversion(void)
{
    /* No fill and Start Queue */
    VADC_G4QINR0 &= ~(0x1F);                 // Request Channel Number : 6
    VADC_G4QINR0 |=  (0x07);

    VADC_G4QINR0 &= ~((0x01) << RF);         // No fill : it is converted once

    VADC_G4QMR0 |=   ((0x01) << TREV);       // Generate a Trigger Event
}

unsigned int VADC_readResult(void)
{
    unsigned int result;

    while( (VADC_G4RES1 & (0x1 << VF)) == 0);
    result = VADC_G4RES1 & ((0xFFFF) << RESULT);

    return result;
}

void initGTM(void)
{
    /* Password Access to unlock WDTSCON0 */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) & ~(1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) != 0);


    /* Modify Access to clear ENDINIT bit */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) | (1 << LCK)) & ~ (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) == 0);

    GTM_CLC &= ~(1 << DISR); // enable VADC

    /* Password Access to unlock WDTSCON0 */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) & ~(1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) != 0);

    /* Modify Access to clear ENDINIT bit */
    SCU_WDT_CPU0CON0 = ((SCU_WDT_CPU0CON0 ^ 0xFC) | (1 << LCK)) | (1 << ENDINIT);
    while((SCU_WDT_CPU0CON0 & (1 << LCK)) == 0);

    while((GTM_CLC & (1 << DISS)) != 0);       // Wait until module is enabled


    GTM_CMU_FXCLK_CTRL &= ~((0x0F) << FXCLK_SEL);
    GTM_CMU_CLK_EN |= ((0x02) << EN_FXCLK);

    GTM_TOM0_TGC1_GLB_CTRL |= ((0x02) << UPEN_CTRL1);
    GTM_TOM0_TGC1_ENDIS_CTRL |= ((0x02) << ENDIS_CTRL1);
    GTM_TOM0_TGC1_OUTEN_CTRL |= ((0x02) << OUTEN_CTRL1);

    GTM_TOM0_CH9_CTRL |= ((0x01) << SL);
    GTM_TOM0_CH9_CTRL |= ((0x01) << CLK_SRC_SR);

    GTM_TOM0_CH9_SR0 = 12500 - 1;

    GTM_TOUTSEL0 &= ~((0x03) << SEL1);
}
