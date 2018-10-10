/*
 * QEI.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: 16138
 */

#include <peripheral/QEI/QEI.h>

QEI::QEI(){}
QEI::~QEI(){}

/**
 * @brief Construct a new QEI::QEI object
 * 
 * @param QEI_ QEI_0 v QEI_1
 */
QEI::QEI(QEI_ QEI_)
{
    uint32_t SYSCTL_PERIPH_GPIO_;
    uint32_t SYSCTL_PERIPH_QEI;
    uint32_t GPIO_P_PHA;
    uint32_t GPIO_P_PHB;
    uint32_t GPIO_PORT_BASE;
    uint8_t  GPIO_PIN_;

    switch(QEI_){
    case QEI_0:
        QEI_BASE = QEI0_BASE;
        GPIO_PORT_BASE = GPIO_PORTD_BASE;
        SYSCTL_PERIPH_GPIO_ = SYSCTL_PERIPH_GPIOD;
        SYSCTL_PERIPH_QEI = SYSCTL_PERIPH_QEI0;
        GPIO_P_PHA = GPIO_PD6_PHA0;
        GPIO_P_PHB = GPIO_PD7_PHB0;
        GPIO_PIN_ = GPIO_PIN_0_QEI_0 |  GPIO_PIN_1_QEI_0;

        break;
    case QEI_1:
        QEI_BASE = QEI1_BASE;
        GPIO_PORT_BASE = GPIO_PORTC_BASE;
        SYSCTL_PERIPH_GPIO_ = SYSCTL_PERIPH_GPIOC;
        SYSCTL_PERIPH_QEI = SYSCTL_PERIPH_QEI1;
        GPIO_P_PHA = GPIO_PC5_PHA1;
        GPIO_P_PHB = GPIO_PC6_PHB1;
        GPIO_PIN_ = GPIO_PIN_0_QEI_1 |  GPIO_PIN_1_QEI_1;
        break;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO_);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO_)));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_QEI)));

    if(QEI_ == QEI_0){
        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //In Tiva include this is the same as "_DD" in older versions (0x4C4F434B)
        HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
    }

    GPIOPinConfigure(GPIO_P_PHA);
    GPIOPinConfigure(GPIO_P_PHB);
    GPIOPinTypeQEI(GPIO_PORT_BASE, GPIO_PIN_);
    GPIOPinTypeQEI(GPIO_PORT_BASE, GPIO_PIN_);

    QEIDisable(QEI_BASE);

    // Configure quadrature encoder, use an arbitrary top limit of QEI_MAX_POSITION
    QEIConfigure(QEI_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET  | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), QEI_MAX_POSITION);
    QEIIntDisable(QEI_BASE, QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
    QEIPositionSet(QEI_BASE, QEI_START_POSITION);

    QEIVelocityDisable(QEI_BASE);
    QEIVelocityConfigure(QEI_BASE, QEI_VELDIV_1, SysCtlClockGet()/QEI_VELOCITY_FRQ); //  measure the velocity each 1ms
    QEIVelocityEnable(QEI_BASE);

    QEIEnable(QEI_BASE);
}

/**
 * @brief Swap Pharse A and B
 * 
 */
void QEI::swap(){
    QEIConfigure(QEI_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET  | QEI_CONFIG_QUADRATURE | QEI_CONFIG_SWAP), QEI_MAX_POSITION);
}

/**
 * @brief Get current Qei Position 0 --> QEI_MAX_POSITION
 * 
 * @return uint32_t 
 */
uint32_t QEI::getPos(){
    return QEIPositionGet(QEI_BASE);
}

/**
 * @brief Gets the current direction of rotation.
 * 
 * @return int32_t Returns 1 if moving in the forward direction or -1 if moving in the reverse direction.
 */
int32_t  QEI::getDirection(){
    return QEIDirectionGet(QEI_BASE);
}

/**
 * @brief QEIVelocityGet
 * 
 * @return uint32_t Returns the number of pulses captured in the given time period.
 */
uint32_t QEI::getVelocity(){
    return QEIVelocityGet(QEI_BASE);
}

