/*
 * I2C.cpp
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#include <peripheral/I2C/I2C.h>
#include <slib/Log/Log.h>

//*****************************************************************************
// @params:
// I2C: I2C0, I2C1, I2C2, I2C3
// speed: only support I2C_SPEED_STANDARD, I2C_SPEED_FAST
//*****************************************************************************
I2C::I2C(){
    // TODO Auto-generated constructor stub
}
I2C::I2C(uint8_t I2C_, uint8_t I2C_SPEED_)
{
    // TODO Auto-generated constructor stub
    Log::logDoing("Initialize I2C %d", I2C_);

    uint32_t SYSCTL_PERIPH_I2C;
    uint32_t SYSCTL_PERIPH_GPIO;

    uint32_t GPIO_P_I2CSCL;
    uint32_t GPIO_P_I2CSDA;

    uint32_t GPIO_PORT_BASE;
    uint32_t GPIO_PIN_SCL;
    uint32_t GPIO_PIN_SDA;

    switch(I2C_){

    case I2C_0:
        SYSCTL_PERIPH_I2C   = SYSCTL_PERIPH_I2C0;
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;

        GPIO_P_I2CSCL       = GPIO_PB2_I2C0SCL;
        GPIO_P_I2CSDA       = GPIO_PB3_I2C0SDA;

        GPIO_PORT_BASE      = GPIO_PORTB_BASE;
        GPIO_PIN_SCL        = GPIO_PIN_2;
        GPIO_PIN_SDA        = GPIO_PIN_3;

        I2C_BASE            = I2C0_BASE;

        break;

    case I2C_1:
        SYSCTL_PERIPH_I2C   = SYSCTL_PERIPH_I2C1;
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOA;

        GPIO_P_I2CSCL       = GPIO_PA6_I2C1SCL;
        GPIO_P_I2CSDA       = GPIO_PA7_I2C1SDA;

        GPIO_PORT_BASE      = GPIO_PORTA_BASE;
        GPIO_PIN_SCL        = GPIO_PIN_6;
        GPIO_PIN_SDA        = GPIO_PIN_7;

        I2C_BASE            = I2C1_BASE;

        break;

    case I2C_2:
        SYSCTL_PERIPH_I2C   = SYSCTL_PERIPH_I2C2;
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOE;

        GPIO_P_I2CSCL       = GPIO_PE4_I2C2SCL;
        GPIO_P_I2CSDA       = GPIO_PE5_I2C2SDA;

        GPIO_PORT_BASE      = GPIO_PORTE_BASE;
        GPIO_PIN_SCL        = GPIO_PIN_4;
        GPIO_PIN_SDA        = GPIO_PIN_5;

        I2C_BASE            = I2C2_BASE;

        break;

    case I2C_3:
        SYSCTL_PERIPH_I2C   = SYSCTL_PERIPH_I2C3;
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOD;

        GPIO_P_I2CSCL       = GPIO_PD0_I2C3SCL;
        GPIO_P_I2CSDA       = GPIO_PD1_I2C3SDA;

        GPIO_PORT_BASE      = GPIO_PORTD_BASE;
        GPIO_PIN_SCL        = GPIO_PIN_0;
        GPIO_PIN_SDA        = GPIO_PIN_1;

        I2C_BASE            = I2C3_BASE;

        break;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C); // Enable I2C1 peripheral
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_I2C)));
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO); // Enable GPIOA peripheral
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO)));

    // Use alternate function
    GPIOPinConfigure(GPIO_P_I2CSCL);
    GPIOPinConfigure(GPIO_P_I2CSDA);

    GPIOPinTypeI2CSCL(GPIO_PORT_BASE, GPIO_PIN_SCL); // Use pin with I2C SCL peripheral
    GPIOPinTypeI2C(GPIO_PORT_BASE, GPIO_PIN_SDA); // Use pin with I2C peripheral


    switch(I2C_SPEED_){
    case I2C_SPEED_STANDARD:
        I2CMasterInitExpClk(I2C_BASE, SysCtlClockGet(), false); // Enable and set frequency to 100 kHz
        break;
    case I2C_SPEED_FAST:
        I2CMasterInitExpClk(I2C_BASE, SysCtlClockGet(), true); // Enable and set frequency to 400 kHz
        break;
    case I2C_SPEED_FAST_PLUS:
        break;
    case I2C_SPEED_HIGH:
        break;
    }

    Log::logDone("Initialize I2C %d", I2C_);
}

I2C::~I2C()
{
    // TODO Auto-generated destructor stub
}

bool I2C::WriteBurst(uint8_t addr,uint8_t regAddr,uint8_t *data,uint8_t length){
    I2CMasterSlaveAddrSet(I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done

    uint8_t i = 0;
    for (i = 0; i < length - 1; i++) {
        I2CMasterDataPut(I2C_BASE, data[i]); // Place data into data register
        I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // Send continues condition
        while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done
    }

    I2CMasterDataPut(I2C_BASE, data[length - 1]); // Place data into data register
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Send finish condition
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done

    return true;
}

bool I2C::Write(uint8_t addr, uint8_t regAddr, uint8_t data){
    WriteBurst(addr, regAddr, &data, 1);
    return true;
}

bool I2C::ReadBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length){
    I2CMasterSlaveAddrSet(I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(I2C_BASE, addr, true); // Set to read mode

    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); // Send start condition
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done

    data[0] = I2CMasterDataGet(I2C_BASE); // Place data into data register
    uint8_t i = 1;
    for (i = 1; i < length - 1; i++) {
        I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT); // Send continues condition
        while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done
        data[i] = I2CMasterDataGet(I2C_BASE); // Place data into data register
    }

    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); // Send finish condition
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done
    data[length - 1] = I2CMasterDataGet(I2C_BASE); // Place data into data register

    return true;
}

bool I2C::Read(uint8_t addr, uint8_t regAddr, uint8_t *data) {
    I2CMasterSlaveAddrSet(I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(I2C_BASE, addr, true); // Set to read mode

    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE); // Tell master to read data
    while (I2CMasterBusy(I2C_BASE)); // Wait until transfer is done
    *data = I2CMasterDataGet(I2C_BASE); // Read data

    return true;
}
