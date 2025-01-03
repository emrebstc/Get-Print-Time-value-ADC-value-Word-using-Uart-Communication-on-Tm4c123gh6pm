#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "kesmeler.h"
#include "lcd.h"
#include "inttostring.h"
#include "string.h"
#include "seriport.h"

extern char uartmetin[];
extern char uartzaman[];

void timerAkesme()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    uint32_t adcverisi[4];
    uint32_t ortalama;
    uint32_t temp;
    char sicaklik[3] = "00";
    saatguncelle();

    LCD_temizle();
    LCD_yaz(uartmetin,0,1);
    LCD_yaz(uartzaman,1,9);

    ADCProcessorTrigger(ADC0_BASE, 1);
    SysCtlDelay(1000);

    if (ADCIntStatus(ADC0_BASE, 1, false)) {
        ADCIntClear(ADC0_BASE, 1);
        ADCSequenceDataGet(ADC0_BASE, 1, adcverisi);

            ortalama = (adcverisi[0]+adcverisi[1]+adcverisi[2]+adcverisi[3])/4;
            temp = (1475-((2475*ortalama)/4096))/10;
            uint32_to_string(temp,sicaklik);

            haberlesmever(sicaklik);
            haberlesmeal();

            LCD_yaz(&sicaklik[0],1,1);
            LCD_yaz(&sicaklik[1],1,2);


    }

}

void  saatguncelle() {

     int saniye = (uartzaman[6] - '0') * 10 + (uartzaman[7] - '0');
     int dakika = (uartzaman[3] - '0') * 10 + (uartzaman[4] - '0');
     int saat   = (uartzaman[0] - '0') * 10 + (uartzaman[1] - '0');
     saniye++;
     if (saniye == 60) {
         saniye = 0;
         dakika++;
         if (dakika == 60) {
             dakika = 0;
             saat++;
             if (saat == 24) {
                 saat = 0;
             }
         }
     }

     uartzaman[1] = saat % 10 + '0';
     uartzaman[0] = (saat / 10) + '0';
     uartzaman[4] = dakika % 10 + '0';
     uartzaman[3] = (dakika / 10) + '0';
     uartzaman[7] = saniye % 10 + '0';
     uartzaman[6] = (saniye / 10) + '0';
}
