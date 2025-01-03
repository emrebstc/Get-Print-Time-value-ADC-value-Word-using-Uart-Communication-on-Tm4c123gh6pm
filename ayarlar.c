#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "ayarlar.h"
#include "kesmeler.h"
#include "lcd.h"

void ayar() {

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(),9600,UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);


    TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC);

    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet())/25);

    IntMasterEnable();
    IntEnable(INT_TIMER0A);

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerIntRegister(TIMER0_BASE, TIMER_A, timerAkesme);

    ADCSequenceConfigure(ADC0_BASE, 1,ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    TimerEnable(TIMER0_BASE, TIMER_A);
    ADCSequenceEnable(ADC0_BASE, 1);

    ADCIntEnable(ADC0_BASE, 1);

    LCD_ayar();
}

