#include "D:\Programs\Microchip\ccomp\h\config.h"
#include "D:\Programs\Microchip\ccomp\h\usart.h"
#include "D:\Programs\Microchip\ccomp\h\stdio.h"


#define _XTAL_FREQ 48000000

void main(void) {
	
// Declaring variables:
	unsigned char conf1=0x00, conf2=0x00, port=0x00;
	unsigned int ADCres;
	char res[5];
	char message[5], temp;
	int i;
	
// SPI configuration bits (B0 = SDI, B1 = SCK, C7 = SDO):
	/*TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 0;
	TRISCbits.TRISC7 = 0;
	
	OpenSPI(SPI_FOSC_16, MODE_00, SMPMID); DESCOMENTAR DEPOIS */
	
// Setting the ADC bits and functions (A0 = LED pin, B2 = sensor pin):
	TRISAbits.TRISA0 = 1;
	TRISBbits.TRISB2 = 1;
	
	/* ADC Configuration bits:
		\ ADC_FOSC_64 - OK - Select 64 TOSC
		\ ADC_RIGHT_JUST - OK - Select right justify
		\ ADC_12_TAD - OK - Select 12 TAD time
		\ ADC_CH12 - OK - Select channel 12
		\ ADC_INT_OFF - OK - Select Interupt off
	 	\ ADC_REF_VDD_VSS - OK - Select VDD & VSS as REF
		\ ADC_9ANA - OK - AN0 to AN8 are analog.
	*/
	
	conf1 = ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_12_TAD;
	conf2 = ADC_CH12 & ADC_INT_OFF & ADC_REF_VDD_VSS;
	port = ADC_9ANA;
	
	
	OpenADC(conf1, conf2, port);
	
// Setting USART comm module (C6 = Transmission bit):
	TRISC = 0x00;
	TRISCbits.TRISC6 = 0;
	TRISCbits.TRISC7 = 1;
	
	Delay1KTCYx(4);
	
	while(1){
// Setup to make a LED blink on pin RA4:
		LATAbits.LATA4 = 1;
		Delay10KTCYx(1000);
		LATAbits.LATA4 = 0;
		Delay10KTCYx(1000);
	
// Initializing the ADC:
		ConvertADC();
	
// Reading ADC:
		ADCres = (unsigned int) ReadADC();
		CloseADC();
	
// Initializing USART:
		OpenUSART(USART_TX_INT_OFF & 
        	USART_RX_INT_OFF & 
        	USART_ASYNCH_MODE & 
         	USART_EIGHT_BIT & 
        	USART_CONT_RX & 
        	USART_BRGH_LOW,
			77);
		
// Formating the string to be transmited:
		sprintf(res, "A1=%d\r\n", ADCres);
	
// Transmiting string:
		putsUSART(res);
		Delay1KTCYx(4);

		CloseUSART();
     	}
}
