/**
 * \file IfxDts_Dts.c
 * \brief DTS DTS details
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2022 Infineon Technologies AG. All rights reserved.
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxDts_Dts.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

uint16 IfxDts_Dts_convertFromCelsius(float32 temperatureValue)
{
    sint32 dtsValue = (sint32)(temperatureValue + 285.5f) / 0.467f;

    if (dtsValue < 0)
    {
        dtsValue = 0;
    }
    else if (dtsValue > 1023)
    {
        dtsValue = 1023;
    }

    return (uint16)dtsValue;
}


float32 IfxDts_Dts_convertToCelsius(uint16 dtsValue)
{
    return ((float32)dtsValue * 0.467f) - 285.5f;
}


void IfxDts_Dts_initModule(const IfxDts_Dts_Config *config)
{
    IfxDts_enableSensor();

    /* wait for two measurements before enabling the limits */
    {
        int i;

        /* disable limits */
        MODULE_SCU.DTSLIM.B.LOWER = 0;
        MODULE_SCU.DTSLIM.B.UPPER = 1023;

        /* wait until DTS is ready */
        while (!IfxDts_isReady())
        {}

        /* two dummy measurements */
        for (i = 0; i < 2; ++i)
        {
            IfxDts_Dts_startSensor();

            while (IfxDts_Dts_isBusy())
            {}
        }
    }

    /* change to the requested limits */
    MODULE_SCU.DTSLIM.B.LOWER = IfxDts_Dts_convertFromCelsius(config->lowerTemperatureLimit);
    MODULE_SCU.DTSLIM.B.UPPER = IfxDts_Dts_convertFromCelsius(config->upperTemperatureLimit);

    /* lock configuration? */
    if (config->enableSecureLock == TRUE)
    {
        IfxDts_disableSensorControl();
    }
    else
    {
        /* do Nothing */
    }

    /* enable DTS IRQ */
    if (config->isrPriority > 0)
    {
        volatile Ifx_SRC_SRCR *src = IfxDts_getSrcPointer();
        IfxSrc_init(src, config->isrTypeOfService, config->isrPriority);
        IfxSrc_enable(src);
    }
}


void IfxDts_Dts_initModuleConfig(IfxDts_Dts_Config *config)
{
    config->sensorControlDisabled = FALSE;
    config->lowerTemperatureLimit = -40.0f; // Celsius
    config->upperTemperatureLimit = 170.0f; // Celsius

    config->isrTypeOfService      = IfxSrc_Tos_cpu0;
    config->isrPriority           = 0;

    config->enableSecureLock      = FALSE;
}
