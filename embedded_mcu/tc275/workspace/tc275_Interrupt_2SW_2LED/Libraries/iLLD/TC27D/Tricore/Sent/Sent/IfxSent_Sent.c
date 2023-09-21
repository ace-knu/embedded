/**
 * \file IfxSent_Sent.c
 * \brief SENT SENT details
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
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
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxSent_Sent.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxSent_Sent_deInitModule(IfxSent_Sent *driver)
{
    Ifx_SENT *sentSFR = driver->sent;
    uint16    passwd  = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    IfxSent_resetModule(sentSFR);
    IfxScuWdt_setCpuEndinit(passwd);
}


boolean IfxSent_Sent_initChannel(IfxSent_Sent_Channel *channel, const IfxSent_Sent_ChannelConfig *config)
{
    boolean      result = TRUE;

    channel->driver = config->driver;
    Ifx_SENT    *sentSFR = config->driver->sent;
    Ifx_SENT_CH *sentCh  = &sentSFR->CH[config->channelId];
    channel->channel   = sentCh;
    channel->channelId = config->channelId;

    IfxSent_disableChannel(sentSFR, config->channelId);
    IfxSent_initializeChannelUnitTime(sentSFR, config->channelId, config->tUnit);

    Ifx_SENT_CH_WDT tempWDT;
    tempWDT.U      = 0;
    tempWDT.B.WDLx = config->watchDogTimerLimit;
    sentCh->WDT.U  = tempWDT.U;

    Ifx_SENT_CH_RCR tempRCR;
    tempRCR.U       = 0;
    tempRCR.B.IEP   = config->receiveControl.endPulseIgnored;
    tempRCR.B.ACE   = config->receiveControl.alternateCrcSelected;
    tempRCR.B.SNI   = config->receiveControl.statusNibbleEnabled;
    tempRCR.B.SDP   = config->receiveControl.serialDataProcessingEnabled;
    tempRCR.B.SCDIS = config->receiveControl.serialDataDisabledCrcDisabled;
    tempRCR.B.CDIS  = config->receiveControl.crcModeDisabled;
    tempRCR.B.CFC   = config->receiveControl.frameCheckMode;
    tempRCR.B.FRL   = config->receiveControl.frameLength;
    tempRCR.B.CRZ   = config->receiveControl.crcMethodDisabled;
    tempRCR.B.ESF   = config->receiveControl.extendedSerialFrameMode;
    tempRCR.B.IDE   = config->receiveControl.driftErrorsDisabled;
    tempRCR.B.SUSEN = config->receiveControl.suspendTriggered;
    sentCh->RCR.U   = tempRCR.U;

    IfxSent_enableChannel(sentSFR, config->channelId);

    Ifx_SENT_CH_VIEW tempVIEW;
    tempVIEW.U       = 0;
    tempVIEW.B.RDNP0 = config->nibbleControl.nibblePointer0;
    tempVIEW.B.RDNP1 = config->nibbleControl.nibblePointer1;
    tempVIEW.B.RDNP2 = config->nibbleControl.nibblePointer2;
    tempVIEW.B.RDNP3 = config->nibbleControl.nibblePointer3;
    tempVIEW.B.RDNP4 = config->nibbleControl.nibblePointer4;
    tempVIEW.B.RDNP5 = config->nibbleControl.nibblePointer5;
    tempVIEW.B.RDNP6 = config->nibbleControl.nibblePointer6;
    tempVIEW.B.RDNP7 = config->nibbleControl.nibblePointer7;
    sentCh->VIEW.U   = tempVIEW.U;

    Ifx_SENT_CH_IOCR tempIOCR;
    tempIOCR.U       = 0;
    tempIOCR.B.DEPTH = config->inputOutputControl.digitalGlitchFilterDepth;
    tempIOCR.B.OIE   = config->inputOutputControl.outputPulsePolarityHigh;
    tempIOCR.B.IIE   = config->inputOutputControl.inputPulsePolarityHigh;
    tempIOCR.B.CEC   = config->inputOutputControl.edgeCounterCleared;
    tempIOCR.B.CREG  = config->inputOutputControl.glitchRisingCleared;
    tempIOCR.B.CFEG  = config->inputOutputControl.glitchFallingCleared;
    tempIOCR.B.ETS   = config->inputOutputControl.externalTrigger;
    tempIOCR.B.CTR   = config->inputOutputControl.triggerMonitorCleared;
    sentCh->IOCR.U   = tempIOCR.U;

    Ifx_SENT_CH_INP tempINP;
    tempINP.U       = 0;
    tempINP.B.RSI   = config->interuptNodeControl.receiveSuccessInterruptNode;
    tempINP.B.RDI   = config->interuptNodeControl.receiveDataInterruptNode;
    tempINP.B.RBI   = config->interuptNodeControl.receiveBufferOverflowInterruptNode;
    tempINP.B.TDI   = config->interuptNodeControl.transferDataInterruptNode;
    tempINP.B.TBI   = config->interuptNodeControl.transferBufferUnderflowInterruptNode;
    tempINP.B.ERRI  = config->interuptNodeControl.errorInterruptNode;
    tempINP.B.SDI   = config->interuptNodeControl.serialDataReceiveInterruptNode;
    tempINP.B.WDI   = config->interuptNodeControl.watchdogErrorInterruptNode;
    sentCh->INP.U   = tempINP.U;

    sentCh->INTEN.U = config->enabledInterrupts.ALL;

    if (config->receiveControl.frameLength > 8)
    {
        /* Clear RSI and enable only RDI interrupt */
        sentCh->INTEN.B.RSI = 0;
        sentCh->INTEN.B.RDI = 1;
    }

    if (config->spcModeOn == TRUE)
    {
        uint16 timeOut = IFXSENT_CFG_TIMEOUT_VALUE;
        uint8  error   = 0;

        /* check if Transaction is in progress, before proceeding !!! */
        while ((sentCh->SCR.B.TRQ == 1) && (timeOut > 0))
        {
            /* Wait for Transaction to be completed */
            timeOut--;
        }

        if (timeOut == 0U)
        {
            error = 1U;
        }

        if (error == 0U)
        {
            Ifx_SENT_CH_SCR tempSCR;
            tempSCR.U      = 0;
            tempSCR.B.PLEN = config->transmitControl.pulseLength;
            tempSCR.B.TRIG = config->transmitControl.triggerSource;
            tempSCR.B.DEL  = config->transmitControl.pulseDelayLength;
            tempSCR.B.BASE = config->transmitControl.timeBase;
            sentCh->SCR.U  = tempSCR.U;

            if (config->transmitControl.spcMode == IfxSent_SpcMode_bidirectional)
            {
                /* Enable Buffer Underflow interrupt also */
                sentCh->INTEN.B.TBI = 1U;
            }
        }
    }

    const IfxSent_Sent_Pins *pinsConfig = (const IfxSent_Sent_Pins *)config->pins;

    if (pinsConfig != NULL_PTR)
    {
        const IfxSent_Sent_In *sentIn = pinsConfig->in;

        if (sentIn != NULL_PTR)
        {
            IfxSent_initSentPin(sentIn, pinsConfig->inMode, pinsConfig->pinDriver);
        }

        const IfxSent_Spc_Out *spcOut = pinsConfig->out;

        if (spcOut != NULL_PTR)
        {
            IfxSent_initSpcPin(spcOut, pinsConfig->outMode, pinsConfig->pinDriver);
        }
    }

    {
        IfxSrc_Tos tos = config->interrupt.isrProvider;

        if ((config->interrupt.priority != 0) || (tos == IfxSrc_Tos_dma))
        {
            volatile Ifx_SRC_SRCR *src = IfxSent_getChannelSrc(config->channelId);
            IfxSrc_init(src, tos, config->interrupt.priority);
            IfxSrc_enable(src);
        }
    }

    return result;
}


void IfxSent_Sent_initChannelConfig(IfxSent_Sent_ChannelConfig *config, IfxSent_Sent *driver)
{
    const IfxSent_Sent_ChannelConfig defaultChannelConfig = {
        .driver             = NULL_PTR,
        .channelId          = IfxSent_ChannelId_none,
        .tUnit              = 3E-6,  /* 3 uS */

        .watchDogTimerLimit = 0,

        .receiveControl     = {
            .endPulseIgnored               = FALSE,
            .alternateCrcSelected          = FALSE,
            .statusNibbleEnabled           = FALSE,
            .serialDataProcessingEnabled   = FALSE,
            .serialDataDisabledCrcDisabled = FALSE,
            .crcModeDisabled               = FALSE,
            .frameCheckMode                = IfxSent_FrameCheckMode_pastSyncPulse,
            .frameLength                   = 6,
            .crcMethodDisabled             = FALSE,
            .extendedSerialFrameMode       = IfxSent_ExtendedSerialFrameMode_standard,
            .driftErrorsDisabled           = FALSE,
            .suspendTriggered              = FALSE,
        },

        .nibbleControl                            = {
            .nibblePointer0 = IfxSent_Nibble_0,
            .nibblePointer1 = IfxSent_Nibble_1,
            .nibblePointer2 = IfxSent_Nibble_2,
            .nibblePointer3 = IfxSent_Nibble_3,
            .nibblePointer4 = IfxSent_Nibble_4,
            .nibblePointer5 = IfxSent_Nibble_5,
            .nibblePointer6 = IfxSent_Nibble_6,
            .nibblePointer7 = IfxSent_Nibble_7,
        },

        .inputOutputControl                       = {
            .digitalGlitchFilterDepth = IfxSent_DigitalGlitchesLength_2,
            .outputPulsePolarityHigh  = FALSE,
            .inputPulsePolarityHigh   = FALSE,
            .edgeCounterCleared       = TRUE,
            .glitchRisingCleared      = TRUE,
            .glitchFallingCleared     = TRUE,
            .externalTrigger          = IfxSent_ExternalTrigger_0,
            .triggerMonitorCleared    = FALSE,
        },

        .enabledInterrupts.ALL = IFXSENT_CFG_CHANNEL_INTEN,

        .interuptNodeControl   = {
            .receiveDataInterruptNode             = IfxSent_InterruptNodePointer_0,
            .receiveSuccessInterruptNode          = IfxSent_InterruptNodePointer_0,
            .receiveBufferOverflowInterruptNode   = IfxSent_InterruptNodePointer_0,
            .transferDataInterruptNode            = IfxSent_InterruptNodePointer_0,
            .transferBufferUnderflowInterruptNode = IfxSent_InterruptNodePointer_0,
            .errorInterruptNode                   = IfxSent_InterruptNodePointer_0,
            .serialDataReceiveInterruptNode       = IfxSent_InterruptNodePointer_0,
            .watchdogErrorInterruptNode           = IfxSent_InterruptNodePointer_0,
        },

        .pins                                     = NULL_PTR,

        /* SPC mode enable/disable   */
        .spcModeOn                                = FALSE,
    };
    *config        = defaultChannelConfig;
    config->driver = driver;
}


boolean IfxSent_Sent_initModule(IfxSent_Sent *driver, const IfxSent_Sent_Config *config)
{
    boolean   result  = TRUE;
    Ifx_SENT *sentSFR = config->module;
    driver->sent = sentSFR;

    uint16    passwd = IfxScuWdt_getCpuWatchdogPassword();

    if (IfxSent_isModuleEnabled(sentSFR) == FALSE)
    {
        IfxSent_enableModule(sentSFR);
    }

    IfxScuWdt_clearCpuEndinit(passwd);
    sentSFR->CLC.B.EDIS = (config->sleepModeEnabled != FALSE) ? 0 : 1;
    sentSFR->CLC.B.RMC  = 1;                                                       /* no divider required, pass clock 1:1*/

    IfxSent_initializeModuleClock(sentSFR, IfxSent_ClockDividerMode_normal, 1023); /* Fractional divider not required, pass 1:1*/
    IfxSent_setTimeStampPredivider(sentSFR, config->timeStampPreDivider);

    IfxScuWdt_setCpuEndinit(passwd);

    return result;
}


void IfxSent_Sent_initModuleConfig(IfxSent_Sent_Config *config, Ifx_SENT *sent)
{
    /* Default module initialization    */
    const IfxSent_Sent_Config defaultModuleConfig = {
        .module              = NULL_PTR,
        .sleepModeEnabled    = TRUE,
        .timeStampPreDivider = 0,
    };
    *config        = defaultModuleConfig;
    config->module = sent;
}


boolean IfxSent_Sent_readChannelSerialDataFrame(IfxSent_Sent_Channel *channel, IfxSent_Sent_Frame *frame)
{
    boolean           result  = TRUE;

    Ifx_SENT         *sentSFR = channel->driver->sent;
    IfxSent_ChannelId ChanIdx = channel->channelId;
    frame->data         = sentSFR->RDR[ChanIdx].U;
    frame->timeStamp    = sentSFR->RTS[ChanIdx].U;
    frame->statusNibble = channel->channel->RSR.B.SCN;

    return result;
}


boolean IfxSent_Sent_readChannelSerialMessageFrame(IfxSent_Sent_Channel *channel, IfxSent_Sent_SerialMessageFrame *message)
{
    boolean         result = TRUE;

    Ifx_SENT_CH    *sentCh = channel->channel;
    Ifx_SENT_CH_SDS sds;

    sds.U               = sentCh->SDS.U;

    message->serialData = sds.B.SD;
    message->messageId  = sds.B.MID;
    message->configBit  = (IfxSent_ConfigBit)sds.B.CON;
    message->crc        = sds.B.SCRC;

    return result;
}
