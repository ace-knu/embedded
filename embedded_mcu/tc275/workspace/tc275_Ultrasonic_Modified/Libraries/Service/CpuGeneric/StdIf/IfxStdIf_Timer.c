/**
 * \file IfxStdIf_Timer.c
 * \brief Standard interface: Timer
 * \ingroup IfxStdIf
 *
 * \version disabled
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
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
 */

#include "IfxStdIf_Timer.h"

void IfxStdIf_Timer_initConfig(IfxStdIf_Timer_Config *config)
{
    config->frequency                  = 1000;
    config->isrPriority                = 0;
    config->isrProvider                = IfxSrc_Tos_cpu0;
    config->minResolution              = 0;
    config->trigger.outputMode         = IfxPort_OutputMode_pushPull;
    config->trigger.outputDriver       = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    config->trigger.risingEdgeAtPeriod = FALSE;
    config->trigger.outputEnabled      = FALSE;
    config->trigger.enabled            = FALSE;
    config->trigger.triggerPoint       = 0;
    config->trigger.isrPriority        = 0;
    config->trigger.isrProvider        = IfxSrc_Tos_cpu0;
    config->countDir                   = IfxStdIf_Timer_CountDir_up;
    config->startOffset 					   = 0.0;
}


static float32 IfxStdIf_Timer_nopGetFrequency(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return 0.0;
}
static Ifx_TimerValue IfxStdIf_Timer_nopGetPeriod(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return 0;
}
static float32 IfxStdIf_Timer_nopGetResolution(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return 0.0;
}
static Ifx_TimerValue IfxStdIf_Timer_nopGetTrigger(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return 0;
}
static boolean IfxStdIf_Timer_nopSetFrequency(IfxStdIf_InterfaceDriver stdIf, float32 frequency)
{
	IFX_UNUSED_PARAMETER(stdIf);
	IFX_UNUSED_PARAMETER(frequency);
	return FALSE;
}
static void IfxStdIf_Timer_nopUpdateInputFrequency(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
}
static void IfxStdIf_Timer_nopApplyUpdate(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
}
static void IfxStdIf_Timer_nopDisableUpdate(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
}
static float32 IfxStdIf_Timer_nopGetInputFrequency(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return 0.0;
}
static void IfxStdIf_Timer_nopRun(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
}
static boolean IfxStdIf_Timer_nopSetPeriod(IfxStdIf_InterfaceDriver stdIf, Ifx_TimerValue period)
{
	IFX_UNUSED_PARAMETER(stdIf);
	IFX_UNUSED_PARAMETER(period);
	return FALSE;
}
static void IfxStdIf_Timer_nopSetSingleMode(IfxStdIf_InterfaceDriver stdIf, boolean enabled)
{
	IFX_UNUSED_PARAMETER(stdIf);
	IFX_UNUSED_PARAMETER(enabled);
}
static void IfxStdIf_Timer_nopSetTrigger(IfxStdIf_InterfaceDriver stdIf, Ifx_TimerValue triggerPoint)
{
	IFX_UNUSED_PARAMETER(stdIf);
	IFX_UNUSED_PARAMETER(triggerPoint);
}
static void IfxStdIf_Timer_nopStop(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
}
static boolean IfxStdIf_Timer_nopAckTimerIrq(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return FALSE;
}
static boolean IfxStdIf_Timer_nopAckTriggerIrq(IfxStdIf_InterfaceDriver stdIf)
{
	IFX_UNUSED_PARAMETER(stdIf);
	return FALSE;
}


void IfxStdIf_Timer_initStdIf(IfxStdIf_Timer *stdIf, IfxStdIf_InterfaceDriver driver)
{
    stdIf->driver               = driver;
    stdIf->getFrequency         =&IfxStdIf_Timer_nopGetFrequency        ;
    stdIf->getPeriod            =&IfxStdIf_Timer_nopGetPeriod           ;
    stdIf->getResolution        =&IfxStdIf_Timer_nopGetResolution       ;
    stdIf->getTrigger           =&IfxStdIf_Timer_nopGetTrigger          ;
    stdIf->setFrequency         =&IfxStdIf_Timer_nopSetFrequency        ;
    stdIf->updateInputFrequency =&IfxStdIf_Timer_nopUpdateInputFrequency;
    stdIf->applyUpdate          =&IfxStdIf_Timer_nopApplyUpdate         ;
    stdIf->disableUpdate        =&IfxStdIf_Timer_nopDisableUpdate       ;
    stdIf->getInputFrequency    =&IfxStdIf_Timer_nopGetInputFrequency   ;
    stdIf->run                  =&IfxStdIf_Timer_nopRun                 ;
    stdIf->setPeriod            =&IfxStdIf_Timer_nopSetPeriod           ;
    stdIf->setSingleMode        =&IfxStdIf_Timer_nopSetSingleMode       ;
    stdIf->setTrigger           =&IfxStdIf_Timer_nopSetTrigger          ;
    stdIf->stop                 =&IfxStdIf_Timer_nopStop                ;
    stdIf->ackTimerIrq          =&IfxStdIf_Timer_nopAckTimerIrq         ;
    stdIf->ackTriggerIrq        =&IfxStdIf_Timer_nopAckTriggerIrq       ;
}
