/**
 * \file IfxI2c_I2c.c
 * \brief I2C I2C details
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2023 Infineon Technologies AG. All rights reserved.
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

#include "IfxI2c_I2c.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxI2c_I2c_initConfig(IfxI2c_I2c_Config *config, Ifx_I2C *i2c)
{
    config->i2c      = i2c;
    config->baudrate = 400000;
    config->pins     = NULL_PTR;
}


void IfxI2c_I2c_initDevice(IfxI2c_I2c_Device *i2cDevice, const IfxI2c_I2c_deviceConfig *i2cDeviceConfig)
{
    i2cDevice->i2c           = i2cDeviceConfig->i2c;
    i2cDevice->deviceAddress = i2cDeviceConfig->deviceAddress;
}


void IfxI2c_I2c_initDeviceConfig(IfxI2c_I2c_deviceConfig *i2cDeviceConfig, IfxI2c_I2c *i2c)
{
    i2cDeviceConfig->i2c           = i2c;
    i2cDeviceConfig->deviceAddress = 0xff;
}


void IfxI2c_I2c_initModule(IfxI2c_I2c *i2c, const IfxI2c_I2c_Config *config)
{
    Ifx_I2C *i2cSFR = config->i2c;
    i2c->i2c = i2cSFR;

    IfxI2c_enableModule(i2cSFR);
    IfxI2c_stop(i2cSFR);                                                                   // enter config Mode
    IfxI2c_configureAsMaster(i2cSFR);
    IfxI2c_setBaudrate(i2cSFR, config->baudrate);

    if (config->pins != NULL_PTR)
    {
        IfxI2c_initSclSdaPin(config->pins->scl, config->pins->sda, config->pins->padDriver);
    }

    IfxI2c_run(i2cSFR);
    i2c->baudrate  = IfxI2c_getBaudrate(i2cSFR);
    i2c->busStatus = IfxI2c_getBusStatus(i2cSFR);
    i2c->status    = IfxI2c_I2c_Status_ok;
}


IfxI2c_I2c_Status IfxI2c_I2c_read(IfxI2c_I2c_Device *i2cDevice, volatile uint8 *data, Ifx_SizeT size)
{
    IfxI2c_I2c_Status status = IfxI2c_I2c_Status_ok;
    Ifx_I2C          *i2c    = i2cDevice->i2c->i2c;
    uint32            packet;
    uint8             slAddr = i2cDevice->deviceAddress;

    union data
    {
        uint32 packet;
        uint8  packetbyte[4];
    }      rxdata;

    rxdata.packet = 0;

    sint32 bytesToReceive = size;
    uint32 bytes;

    // bus free?
    if (IfxI2c_busIsFree(i2c) == FALSE)
    {
        status                    = IfxI2c_I2c_Status_busNotFree;
        i2cDevice->i2c->busStatus = IfxI2c_getBusStatus(i2c);
        i2cDevice->i2c->status    = status;
        return status;
    }

    IfxI2c_clearAllProtocolInterruptSources(i2c);
    IfxI2c_clearAllErrorInterruptSources(i2c);

    // send device address with RnW bit set
    packet = slAddr | 1;                    // set read bit
    IfxI2c_setTransmitPacketSize(i2c, 1);   // send slave address packet with RnW = 1
    IfxI2c_setReceivePacketSize(i2c, size); // set number of bytes to reveive
    IfxI2c_writeFifo(i2c, packet);

    /* Poll until aribtration lost, nack, or rx mode flag is reset */
    while ((i2c->PIRQSS.U & ((1 << IFX_I2C_PIRQSS_AL_OFF) | (1 << IFX_I2C_PIRQSM_TX_END_OFF) | (1 << IFX_I2C_PIRQSS_RX_OFF))) == FALSE)
    {}

    IfxI2c_clearAllDtrInterruptSources(i2c);

    /* check status*/
    if (i2c->ERRIRQSS.U)
    {
        IfxI2c_clearAllErrorInterruptSources(i2c);
        status = IfxI2c_I2c_Status_error;
    }

    /*Check Arbitration Lost in Protocol Interrupts*/
    else if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_AL_OFF))
    {
        i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_AL_OFF);
        status        = IfxI2c_I2c_Status_al;
    }
    /*Check NACK in Protocol Interrupts*/
    else if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_NACK_OFF))
    {
        i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_NACK_OFF);
        status        = IfxI2c_I2c_Status_nak;
    }

    else if (size > 0)                                       // required to poll for nak

    {
        if (size > 32)                                       // if fifo is too small => disable global interrupts!
        {           // assumes TC is faster than i2c and therefor a fifo overflow is not possible
            boolean intEnabled = IfxCpu_disableInterrupts(); // disable global interrupts to prevent fifo overflow
            uint32  i;

            for (i = 0; i < (uint32)size; i += 4)
            {
                if (bytesToReceive >= 4)
                {
                    bytes           = 4;
                    bytesToReceive -= 4;
                }
                else
                {
                    bytes          = bytesToReceive;
                    bytesToReceive = 0;
                }

                uint32 ris = 0;

                while (!(ris = i2c->RIS.U)) // wait for fifo request or error

                {}

                // check request flags
                if (ris & ((1 << IFX_I2C_RIS_LSREQ_INT_OFF) | (1 << IFX_I2C_RIS_SREQ_INT_OFF) | (1 << IFX_I2C_RIS_LBREQ_INT_OFF) | (1 << IFX_I2C_RIS_BREQ_INT_OFF)))
                {
                    rxdata.packet = i2c->RXD.U;
                    uint32 k;

                    for (k = 0; k < bytes; k++)
                    {
                        data[i + k] = rxdata.packetbyte[k];
                    }

                    IfxI2c_clearLastSingleRequestInterruptSource(i2c);
                    IfxI2c_clearSingleRequestInterruptSource(i2c);
                    IfxI2c_clearLastBurstRequestInterruptSource(i2c);
                    IfxI2c_clearBurstRequestInterruptSource(i2c);
                }

                /* check errors. Must have enabled corresponding bits in Mask registers*/
                if (ris & (1 << IFX_I2C_RIS_I2C_ERR_INT_OFF)) // error flags
                {
                    IfxI2c_clearAllErrorInterruptSources(i2c);
                    status = IfxI2c_I2c_Status_error;
                    break;
                }

                /* check protocol interrupts. Must have enabled corresponding bits in Mask registers*/
                if (ris & (1 << IFX_I2C_RIS_I2C_P_INT_OFF)) // check protocol flags
                {
                    /*Check Arbitration Lost*/
                    if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_AL_OFF))
                    {
                        i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_AL_OFF);
                        status        = IfxI2c_I2c_Status_al;
                        break;
                    }

                    /*Check NACK*/
                    else if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_NACK_OFF))
                    {
                        i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_NACK_OFF);
                        status        = IfxI2c_I2c_Status_nak;
                        break;
                    }

                    /*Check TX_END*/
                    if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_TX_END_OFF))
                    {
                        /*Should not be cleared here, otherwise it will cause infinite while loop*/
                        status = IfxI2c_I2c_Status_ok; //Default value of status. Still kept for readability*/
                    }

                    /*Check and clear Address Match, General Call, Master Code and Receive Mode*/
                    if (i2c->PIRQSS.U & ((1 << IFX_I2C_PIRQSS_AM_OFF) | (1 << IFX_I2C_PIRQSS_GC_OFF) | (1 << IFX_I2C_PIRQSS_MC_OFF) | (1 << IFX_I2C_PIRQSS_RX_OFF)))
                    {
                        /*Just clearing the bits. Status need not be updated*/
                        i2c->PIRQSC.U = ((1 << IFX_I2C_PIRQSS_AM_OFF) | (1 << IFX_I2C_PIRQSS_GC_OFF) | (1 << IFX_I2C_PIRQSS_MC_OFF) | (1 << IFX_I2C_PIRQSS_RX_OFF));
                    }
                }
            }

            IfxCpu_restoreInterrupts(intEnabled); // (re-) enable global interrupts

            // TX_END: transmission finished
            while (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd) == FALSE)
            {}

            IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd);
        }
        else
        {
            // wait until all bytes are received
            while (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd) == FALSE)
            {}

            IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd);

            // check errors
            uint32 ris;
            ris = i2c->RIS.U;

            if (ris & (1 << IFX_I2C_RIS_I2C_ERR_INT_OFF)) // error flags
            {
                IfxI2c_clearAllErrorInterruptSources(i2c);
                status = IfxI2c_I2c_Status_error;
            }

            else if (ris & (1 << IFX_I2C_RIS_I2C_P_INT_OFF)) // check protocol flags
            {
                if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_AL_OFF))
                {
                    i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_AL_OFF);
                    status        = IfxI2c_I2c_Status_al;
                }

                else if (i2c->PIRQSS.U & (1 << IFX_I2C_PIRQSS_NACK_OFF))
                {
                    i2c->PIRQSC.U = (1 << IFX_I2C_PIRQSS_NACK_OFF);
                    status        = IfxI2c_I2c_Status_nak;
                }

                /*Clear remaining flags*/
                /*	Check and clear Address Match, General Call, Master Code, Transmission End and Receive Mode*/
                if (i2c->PIRQSS.U & ((1 << IFX_I2C_PIRQSS_AM_OFF) | (1 << IFX_I2C_PIRQSS_GC_OFF) | (1 << IFX_I2C_PIRQSS_MC_OFF) | (1 << IFX_I2C_PIRQSS_TX_END_OFF) | (1 << IFX_I2C_PIRQSS_RX_OFF)))
                {
                    /*Just clearing the bits. Status need not be updated*/
                    i2c->PIRQSC.U = ((1 << IFX_I2C_PIRQSS_AM_OFF) | (1 << IFX_I2C_PIRQSS_GC_OFF) | (1 << IFX_I2C_PIRQSS_MC_OFF) | (1 << IFX_I2C_PIRQSS_TX_END_OFF) | (1 << IFX_I2C_PIRQSS_RX_OFF));
                }
            }

            if ((status != IfxI2c_I2c_Status_error) && (status != IfxI2c_I2c_Status_al) && (status != IfxI2c_I2c_Status_nak))
            {
                // read fifo
                uint32 i;

                for (i = 0; i < (uint32)size; i += 4)
                {
                    if (bytesToReceive >= 4)
                    {
                        bytes           = 4;
                        bytesToReceive -= 4;
                    }
                    else
                    {
                        bytes          = bytesToReceive;
                        bytesToReceive = 0;
                    }

                    uint32 k;
                    rxdata.packet = i2c->RXD.U;
                    IfxI2c_clearLastSingleRequestInterruptSource(i2c);
                    IfxI2c_clearSingleRequestInterruptSource(i2c);
                    IfxI2c_clearLastBurstRequestInterruptSource(i2c);
                    IfxI2c_clearBurstRequestInterruptSource(i2c);

                    for (k = 0; k < bytes; k++)
                    {
                        data[i + k] = rxdata.packetbyte[k];
                    }
                }
            }
        }
    }

    IfxI2c_clearAllErrorInterruptSources(i2c);
    IfxI2c_clearAllProtocolInterruptSources(i2c);
    IfxI2c_releaseBus(i2c);
    i2cDevice->i2c->busStatus = IfxI2c_getBusStatus(i2c);
    i2cDevice->i2c->status    = status;
    return status;
}


IfxI2c_I2c_Status IfxI2c_I2c_write(IfxI2c_I2c_Device *i2cDevice, volatile uint8 *data, Ifx_SizeT size)
{
    IfxI2c_I2c_Status status = IfxI2c_I2c_Status_ok;
    Ifx_I2C          *i2c    = i2cDevice->i2c->i2c;
    uint8             slAddr = i2cDevice->deviceAddress;
    union data
    {
        uint32 packet;
        uint8  packetbyte[4];
    }      txdata;

    sint32 bytesToSend = size + 1; // +1 slave device address
    uint32 bytes;

    if (IfxI2c_busIsFree(i2c) == FALSE)
    {
        status                    = IfxI2c_I2c_Status_busNotFree;
        i2cDevice->i2c->busStatus = IfxI2c_getBusStatus(i2c);
        i2cDevice->i2c->status    = status;
        return status;
    }

    // build one packet containing the slave address

    IfxI2c_clearAllProtocolInterruptSources(i2c);
    IfxI2c_clearAllErrorInterruptSources(i2c);

    // try to seize control, if not return
    IfxI2c_setTransmitPacketSize(i2c, 1);
    IfxI2c_writeFifo(i2c, slAddr);
    IfxI2c_clearLastSingleRequestInterruptSource(i2c);
    IfxI2c_clearSingleRequestInterruptSource(i2c);
    IfxI2c_clearLastBurstRequestInterruptSource(i2c);
    IfxI2c_clearBurstRequestInterruptSource(i2c);

    // wait until packet is sent
    while (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd) == FALSE)
    {}

    IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd);

    // check status
    if (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_arbitrationLost) == TRUE)
    {
        IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_arbitrationLost);
        status = IfxI2c_I2c_Status_al;
    }
    else if (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_notAcknowledgeReceived) == TRUE)
    {
        IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_notAcknowledgeReceived);
        status = IfxI2c_I2c_Status_nak;
    }
    else if (size > 0)   // write i2c device

    {
        uint32  i, j = 0;

        // assumes TC is faster then i2c and therefor a fifo underflow is not possible
        boolean intEnabled = IfxCpu_disableInterrupts(); // disable global interrupts to prevent FIFO underflow
        IfxI2c_setTransmitPacketSize(i2c, size + 1);

        for (i = 0; i < (uint32)(size + 1); i += 4)
        {
            if (bytesToSend >= 4)
            {
                bytes        = 4;
                bytesToSend -= 4;
            }
            else
            {
                bytes       = bytesToSend;
                bytesToSend = 0;
            }

            txdata.packet = 0;

            for (j = 0; j < bytes; j++)
            {
                if ((i == 0) && (j == 0))
                {
                    txdata.packetbyte[j] = (uint8)slAddr;
                }

                else
                {
                    txdata.packetbyte[j] = (uint8)data[i + j - 1];
                }
            }

            do
            {
                // check errors
                uint32 ris;
                ris = i2c->RIS.U;

                if (ris & (1 << IFX_I2C_RIS_I2C_P_INT_OFF)) // check protocol flags
                {
                    IfxI2c_clearAllProtocolInterruptSources(i2c);
                    status = IfxI2c_I2c_Status_error;
                }

                if (ris & (1 << IFX_I2C_RIS_I2C_ERR_INT_OFF)) // error flags
                {
                    IfxI2c_clearAllErrorInterruptSources(i2c);
                    status = IfxI2c_I2c_Status_error;
                }
            } while (i2c->FFSSTAT.B.FFS == 8 && status != IfxI2c_I2c_Status_error); // wait to prevent FIFO overflow

            if (status == IfxI2c_I2c_Status_error)
            {
                break;
            }

            IfxI2c_writeFifo(i2c, txdata.packet);

            /* our write to FIFO will trigger any of the request source, we wait for it */
            while (!(i2c->RIS.U)) // wait for fifo request or error
            {}

            IfxI2c_clearLastSingleRequestInterruptSource(i2c);
            IfxI2c_clearSingleRequestInterruptSource(i2c);
            IfxI2c_clearLastBurstRequestInterruptSource(i2c);
            IfxI2c_clearBurstRequestInterruptSource(i2c);
        }

        IfxCpu_restoreInterrupts(intEnabled); // (re-) enable global interrupts

        // wait until all bytes are sent
        while (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd) == FALSE)
        {}

        IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd);

        // finally check errors
        uint32 ris;
        ris = i2c->RIS.U;

        if (ris & (1 << IFX_I2C_RIS_I2C_P_INT_OFF)) // check protocol flags
        {
            IfxI2c_clearAllProtocolInterruptSources(i2c);
            status = IfxI2c_I2c_Status_error;
        }

        if (ris & (1 << IFX_I2C_RIS_I2C_ERR_INT_OFF)) // error flags
        {
            IfxI2c_clearAllErrorInterruptSources(i2c);
            status = IfxI2c_I2c_Status_error;
        }
    }

    IfxI2c_releaseBus(i2c);
    i2cDevice->i2c->busStatus = IfxI2c_getBusStatus(i2c);
    i2cDevice->i2c->status    = status;
    return status;
}
