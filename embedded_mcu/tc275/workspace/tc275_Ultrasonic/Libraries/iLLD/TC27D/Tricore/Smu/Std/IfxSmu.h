/**
 * \file IfxSmu.h
 * \brief SMU  basic functionality
 * \ingroup IfxLld_Smu
 *
 * \version iLLD_1_0_1_15_0_1
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \defgroup IfxLld_Smu_Std_func_fsp FSP Functions
 * \ingroup IfxLld_Smu_Std
 * \defgroup IfxLld_Smu_Std_func SMU Functions
 * \ingroup IfxLld_Smu_Std
 * \defgroup IfxLld_Smu_Std_datastructures Data Structures
 * \ingroup IfxLld_Smu_Std
 */

#ifndef IFXSMU_H
#define IFXSMU_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxSmu_cfg.h"
#include "Cpu/Std/Ifx_Types.h"
#include "_PinMap/IfxSmu_PinMap.h"
#include "IfxSmu_reg.h"
#include "IfxSmu_regdef.h"
#include "IfxSmu_bf.h"
#include "_Utilities/Ifx_Assert.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Smu_Std_datastructures
 * \{ */
/** \brief SMU Alarm Configuration
 * Ifx_SMU.AGCF[][]
 */
typedef enum
{
    IfxSmu_AlarmConfig_noAction      = 0,  /**< \brief No Action. Reset value. Alarm disabled. */
    IfxSmu_AlarmConfig_interruptSet0 = 2,  /**< \brief Sends an interrupt request to the interrupt system according to the Interrupt Generation Configuration Set 0 */
    IfxSmu_AlarmConfig_interruptSet1 = 3,  /**< \brief Sends an interrupt request to the interrupt system according to the Interrupt Generation Configuration Set 1 */
    IfxSmu_AlarmConfig_interruptSet2 = 4,  /**< \brief Sends an interrupt request to the interrupt system according to the Interrupt Generation Configuration Set 2 */
    IfxSmu_AlarmConfig_nmi           = 5,  /**< \brief Sends an NMI request to the SCU */
    IfxSmu_AlarmConfig_scuReset      = 6,  /**< \brief Sends a reset request to SCU */
    IfxSmu_AlarmConfig_cpuIdle       = 7   /**< \brief Triggers a CPU idle request */
} IfxSmu_AlarmConfig;

/** \brief SMU Commands
 */
typedef enum
{
    IfxSmu_Cmd_start                  = 0,  /**< \brief Forces the SSM to go to the RUN state from the START state. */
    IfxSmu_Cmd_activateFsp            = 1,  /**< \brief Activates the Fault Signaling Protocol. */
    IfxSmu_Cmd_releaseFsp             = 2,  /**< \brief Turns the FSP into the fault free state. */
    IfxSmu_Cmd_activatePes            = 3,  /**< \brief Triggers the activation of the Port Emergency Stop (PES). */
    IfxSmu_Cmd_stopRecoveryTimer      = 4,  /**< \brief Stop the recovery Timer. Argument ARG shall be set to the recovery timer instance available in the product. */
    IfxSmu_Cmd_enableClearAlarmStatus = 5,  /**< \brief Alarm Status Clear Enable Command */
    IfxSmu_Cmd_triggerAlarm           = 6   /**< \brief Triggers a software based alarm. ARG specifies the alarm index according to the mapping defined in "Alarm Mapping" */
} IfxSmu_Cmd;

typedef enum
{
    IfxSmu_Fsp_Mode_bistable,      /**< \brief Bi-stable fault signalling protocol */
    IfxSmu_Fsp_Mode_timeSwitching  /**< \brief Time switching protocol */
} IfxSmu_Fsp_Mode;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Smu_Std_datastructures
 * \{ */
/** \brief FSP Configuration Structure
 */
typedef struct
{
    IfxSmu_Fsp_Mode mode;                                  /**< \brief FSP mode */
    float32         faultStateTime;                        /**< \brief Minimal fault state time in sec */
    float32         faultFreeStateFrequencyMin;            /**< \brief Min fault free state frequency in Hz, only valid if mode=IfxSmu_Fsp_Mode_timeSwitching */
    float32         faultFreeStateFrequencyMax;            /**< \brief Max fault free state frequency in Hz, only valid if mode=IfxSmu_Fsp_Mode_timeSwitching */
    boolean         emergencyStopEnabled;                  /**< \brief If TRUE, the emergency stop port is triggered on FSP fault state */
    boolean         enableFaultToRunStateTransition;       /**< \brief Enable Fault to Run State Transition */
} IfxSmu_configFsp;

/** \} */

/** \addtogroup IfxLld_Smu_Std_func_fsp
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Turns the FSP into the fault free state.
 * \param smu Pointer to SMU module registers
 */
IFX_INLINE boolean IfxSmu_releaseFsp(Ifx_SMU *smu);

/** \brief Initialize the FSP configuartion to default
 * \param config FSP Configuration Structure
 * \return None
 */
IFX_INLINE void IfxSmu_initFspConfig(IfxSmu_configFsp *config);

/** \brief Activates the Fault Signaling Protocol.
 * \param smu Pointer to SMU module registers
 */
IFX_INLINE boolean IfxSmu_activateFsp(Ifx_SMU *smu);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initialize the FSP
 *
 * Fault state time >= tFSP_FS = tSMU_FS *(SMU_FSP.TFSP_HIGH[] & SMU_FSP.TFSP_LOW[] + 1)
 *  with tSMU_FS = <SMU_FSP.PRE1>. SMU_FSP.TFSP_HIGH[] / fBACK
 *  and SMU_FSP.PRE1 should enable tFSP_FS >= 500ms  (Ref: TC27xC UM v2.2: SMU_FSP.TFSP_HIGH)
 * Fault free state period (Time switching only) = tSMU_FFS = fBACK / <SMU_FSP.PRE2>
 *
 * Note: TSMU_FS * SMU_FSP.TFSP_LOW > 250us
 * \param smu Pointer to SMU module registers
 * \param config FSP Configuration Structure
 */
IFX_EXTERN boolean IfxSmu_initFsp(Ifx_SMU *smu, IfxSmu_configFsp *config);

/** \brief Return FSP frequency (Time switching only)
 * \param smu Pointer to SMU module registers
 */
IFX_EXTERN float32 IfxSmu_getFspFaultFreeFrequency(Ifx_SMU *smu);

/** \brief Return the minimal fault state time
 * \param smu Pointer to SMU module registers
 */
IFX_EXTERN float32 IfxSmu_getFspFaultStateTime(Ifx_SMU *smu);

/** \brief Set the alarm FSP configuration
 * \param smu Pointer to SMU Module Registers
 * \param alarm Alarm to be configured
 * \param enabled If TRUE, the alarm event triggers the FSP, else no action
 * \return None
 */
IFX_EXTERN void IfxSmu_enableAlarmFsp(Ifx_SMU *smu, IfxSmu_Alarm alarm, boolean enabled);

/** \} */

/** \addtogroup IfxLld_Smu_Std_func
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Triggers the activation of the Port Emergency Stop (PES).
 * \param smu Pointer to SMU module registers
 */
IFX_INLINE boolean IfxSmu_activatePes(Ifx_SMU *smu);

/** \brief Stop the recovery Timer. Argument ARG shall be set to the recovery timer instance available in the product.
 * \param smu Pointer to SMU module registers
 * \param timer Recovery Timer
 */
IFX_INLINE boolean IfxSmu_stopRecoveryTimer(Ifx_SMU *smu, IfxSmu_RecoveryTimer timer);

/** \brief Alarm Status Clear Enable Command.
 * \param smu Pointer to SMU module registers
 */
IFX_INLINE boolean IfxSmu_enableClearAlarmStatus(Ifx_SMU *smu);

/** \brief Triggers a software based alarm. ARG specifies the alarm index according to the mapping defined in "Alarm Mapping"
 * \param smu Pointer to SMU module registers
 * \param alarm Alarm list
 */
IFX_INLINE boolean IfxSmu_triggerAlarm(Ifx_SMU *smu, IfxSmu_Alarm alarm);

/** \brief Forces the SSM to go to the RUN state from the START state.
 * \param smu Pointer to SMU module registers
 */
IFX_INLINE boolean IfxSmu_start(Ifx_SMU *smu);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Unlock the SMU configuration (temporary)
 * Ref: TC27xC UM v2.2: 9.4.6 SMU Control Interface
 * Ref: TC27xC UM v2.2: 9.5.2 SMU Configuration Registers
 * \param smu Pointer to SMU module registers
 * \param cmd SMU Command
 * \param arg Argument to be used with the command
 */
IFX_EXTERN boolean IfxSmu_cmd(Ifx_SMU *smu, uint8 cmd, uint8 arg);

/** \brief Unlock the SMU configuration (temporary)
 * Ref: TC27xC UM v2.2: 9.4.10.1 Register Write Protection
 * \param smu Pointer to SMU module registers
 */
IFX_EXTERN boolean IfxSmu_unlock(Ifx_SMU *smu);

/** \brief Lock the SMU configuration (temporary)
 * Ref: TC27xC UM v2.2: 9.4.10.1 Register Write Protection
 * \param smu Pointer to SMU module registers
 * \return None
 */
IFX_EXTERN void IfxSmu_lock(Ifx_SMU *smu);

/** \brief Lock the SMU configuration up to the next application reset
 * Ref: TC27xC UM v2.2: 9.4.10.1 Register Write Protection
 * \param smu Pointer to SMU module registers
 * \return None
 */
IFX_EXTERN void IfxSmu_lockForever(Ifx_SMU *smu);

/** \brief Set the SMU alarm configuration
 * \param smu Pointer to SMU module registers
 * \param alarm Alarm to be configured
 * \param config Alarm configuration
 * \return None
 */
IFX_EXTERN void IfxSmu_setAlarmConfig(Ifx_SMU *smu, IfxSmu_Alarm alarm, IfxSmu_AlarmConfig config);

/** \brief Return the alarm status
 * \param smu Pointer to SMU Module Registers
 * \param alarm Alarm for which to return the status
 * \return TRUE means the alarm is set and FALSE means the alarm is not set.
 */
IFX_EXTERN boolean IfxSmu_isAlarmSet(Ifx_SMU *smu, IfxSmu_Alarm alarm);

/** \brief Get the alarm flag
 * \param smu Pointer to SMU Module Registers
 * \return Return the next set alarm, if no alarm is set , return IfxSmu_Alarm_noAlarm
 */
IFX_EXTERN IfxSmu_Alarm IfxSmu_getAlarm(Ifx_SMU *smu);

/** \brief Clear the alarm flag
 * \param smu Pointer to SMU Module Registers
 * \param alarm Alarm for which the flag should be cleared
 * \return None
 */
IFX_EXTERN void IfxSmu_clearAlarm(Ifx_SMU *smu, IfxSmu_Alarm alarm);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE boolean IfxSmu_activatePes(Ifx_SMU *smu)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_activatePes, 0);
}


IFX_INLINE boolean IfxSmu_stopRecoveryTimer(Ifx_SMU *smu, IfxSmu_RecoveryTimer timer)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_stopRecoveryTimer, timer);
}


IFX_INLINE boolean IfxSmu_enableClearAlarmStatus(Ifx_SMU *smu)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_enableClearAlarmStatus, 0);
}


IFX_INLINE boolean IfxSmu_triggerAlarm(Ifx_SMU *smu, IfxSmu_Alarm alarm)
{
    uint8 index = alarm & 0xFF;
    IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, (alarm >> 8) == IfxSmu_AlarmGroup_5);
    return IfxSmu_cmd(smu, IfxSmu_Cmd_triggerAlarm, index);
}


IFX_INLINE boolean IfxSmu_start(Ifx_SMU *smu)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_start, 0);
}


IFX_INLINE boolean IfxSmu_releaseFsp(Ifx_SMU *smu)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_releaseFsp, 0);
}


IFX_INLINE void IfxSmu_initFspConfig(IfxSmu_configFsp *config)
{
    config->emergencyStopEnabled            = FALSE;
    config->enableFaultToRunStateTransition = FALSE;
    config->faultFreeStateFrequencyMin      = 0;
    config->faultFreeStateFrequencyMax      = 0;
    config->faultStateTime                  = 1e-3;
    config->mode                            = IfxSmu_Fsp_Mode_bistable;
}


IFX_INLINE boolean IfxSmu_activateFsp(Ifx_SMU *smu)
{
    return IfxSmu_cmd(smu, IfxSmu_Cmd_activateFsp, 0);
}


#endif /* IFXSMU_H */
