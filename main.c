#include "MKL46Z4.h"

#define MY_DELAY_CNT           (1000000)

#define RED_LED_PIN            (1<<29)
#define GREEN_LED_PIN          (1<<5) 


void init_led()
{
		uint32_t *temp;		
    /* Enable clock for PORTE & PORTD*/
    SIM->SCGC5 |= ( SIM_SCGC5_PORTD_MASK
                    | SIM_SCGC5_PORTE_MASK ); //12.2.9 (Register 5)
    /* 
	* Initialize the RED LED (PTE29): GPIO Mode
    */
	//PTE, PTD   tuong duong 2 con tro: FPTE, FPTD. ???? P114.
    PORTE->PCR[29] = PORT_PCR_MUX(1);

    /* Set the pins direction to output */
    FPTE->PDDR |= RED_LED_PIN;

    /* Set the initial output state to high */
    FPTE->PSOR |= RED_LED_PIN;	//C1
		
		temp = (uint32_t *)(0xF80FF100u+0x4);	//C2
		*temp |= RED_LED_PIN;									//C2

    /* 
    * Initialize the Green LED (PTD5)
    */

    /* Set the PTD5 pin multiplexer to GPIO mode */
    PORTD->PCR[5]= PORT_PCR_MUX(1);
    /* Set the pins direction to output */
    FPTD->PDDR |= GREEN_LED_PIN;

    /* Set the initial output state to high */
    FPTD->PSOR |= GREEN_LED_PIN;
}

void my_delay()
{
    uint32_t    i;
    for (i = 0; i < MY_DELAY_CNT; i++)
    {
       //__asm("nop");
    }
}
void delay(uint32_t n)
{
	int i;
		for(i=0; i<=n;i++){}
	
}
int main(void)
{
		init_led();
	
    while (1)   
    {
        delay(500000);
        /*Blink Red Led */
        //FPTE->PTOR |= RED_LED_PIN;
				delay(1000000);
				/*Blink Green Led*/
        FPTD->PTOR |= GREEN_LED_PIN;
			
    }
}
/* EOF */
