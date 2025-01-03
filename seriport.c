#include "stdint.h"
#include "stdbool.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "string.h"
#include "seriport.h"
#include "lcd.h"

char uartzaman[] = "00:00:00";
char uartmetin[] = "Emre";

int gelenveri;
bool saatmi=false;
bool karaktermi=false;
int gelensaatno=0;
int gelenkarakterno=0;
char geldiVeri[16];

void haberlesmeal() {


         while(UARTCharsAvail(UART0_BASE))
         {

          gelenveri=UARTCharGet(UART0_BASE);

          if (gelenveri=='%'){
            saatmi=true;
            karaktermi=false;
            gelensaatno=0;
            TimerDisable(TIMER0_BASE, TIMER_A);
          }

          else if (saatmi==true) {
            uartzaman[gelensaatno]=gelenveri;
            gelensaatno++;

            if (gelensaatno==8) {
             saatmi=false;
             gelensaatno=0;
             TimerEnable(TIMER0_BASE, TIMER_A);
                                 }
           }

          else if (gelenveri=='/') {
              karaktermi=true;
              gelenkarakterno=0;
              LCD_temizle();
              TimerDisable(TIMER0_BASE, TIMER_A);
          }

          else if (karaktermi==true) {
              LCD_temizle();
              uartmetin[gelenkarakterno] = gelenveri;
              gelenkarakterno++;
              gelenveri=0;
              uartmetin[gelenkarakterno]=gelenveri;
              TimerEnable(TIMER0_BASE, TIMER_A);

              if (gelenkarakterno==16) {
                  karaktermi=false;
                  gelenkarakterno=0;
                  LCD_temizle();
             }
             }

}
}

void haberlesmever(char *x){
    int b;
    UARTCharPut(UART0_BASE, '(');
    for (b=0;b<strlen(x);b++){
     UARTCharPut(UART0_BASE,x[b]);
     }
     UARTCharPut(UART0_BASE, '\n');
}
