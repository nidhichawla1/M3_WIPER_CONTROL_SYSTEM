/** @file main.c
 * @mainpage wiper control system
 * @brief Code to enact the car wiper system through onboard LEDs of STM32F4 discovery board with onboard push button
 * @author Nidhi Chawla
 * @bug no bug found */
 /**Include header file of STM32F4 series microcontroller
@file headers are included
#include "stm32f4xx_hal.h"
*/
#include "stm32f4xx_hal.h"

/** @file Function protoypes to configure GPIO pins as digital output and digital input
void Init_OnBoard_LEDs(void);
void configure_Button(void);
void Delay_ms(volatile int time_ms); //ms delay function
void frequency(volatile int time);
void led();
@param no parameters are given
@return no return is expected
*/
void Init_OnBoard_LEDs(void);
void configure_Button(void);
void Delay_ms(volatile int time_ms); //ms delay function
void frequency(volatile int time);
void led();


/**@brief  main code to call initialize functions, read state of push button and controlling LEDs */
/** @brief main function
 * @param no parameters are given
 * @return no return is expected
 */
int main(void)
{
//Init_OnBoard_LEDs(); // calls LEDs GPIO pins initialization function
configure_Button(); // call Push button GPIO pins initialization function
GPIO_PinState state; // Define a enum struct which contain boolean states
uint32_t i;

	/**@brief  Configure LEDs*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO

	GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
	GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
	GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
	GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
	//GPIOD->BSRR = 1<<14; // Set the BSRR bit 12 to 1 to turn respective LED on
   while(1)
   {
	   i=1;

	   state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); // read state of push button and save it in "state" variable
	   // if state is high, turn on  LEDs


	   if(state&&i==1){
	   		   GPIOD->BSRR = 1<<14; // Set the BSRR bit 14 to 1 to turn respective LED on
	   		   i++;
	   	   }
	  state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	   if(i==2)
	   {
		   state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		   while(!state){frequency(0.25);state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);}
		   i++;
	   }

	   if(i==3)
	   {
		   state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		   while(!state){frequency(1);state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);}
		   i++;
	   }
	   if(i==4)
	   {
		   state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		   		   while(!state){frequency(1.25);state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);}
		   		   i++;
	   }
	   if(i==5){i++;}

   //if(state &&i==6){
  		  // GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit 13 + 16 to 1 to turn respective LED off
  	   //}
   }
}

/**@brief Function void Init_OnBoard_LEDs to configure PD12-PD15 pin of as digital output pins
 * @param no parameters are given
 * @return no return is expected*/
void Init_OnBoard_LEDs(void)
{
	 __HAL_RCC_GPIOD_CLK_ENABLE(); //Enable clock to GPIOD
	GPIO_InitTypeDef BoardLEDs; // declare a variable of type struct GPIO_InitTypeDef
	BoardLEDs.Mode = GPIO_MODE_OUTPUT_PP; // set pin mode to output
	BoardLEDs.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15; // select pins PD12-PD15
	HAL_GPIO_Init(GPIOD, &BoardLEDs); // initialize PD12-PD15 pins by passing port name and address of BoardLEDs struct
}

/**@brief Function void configure_Button to configure PA0 pin of as a digital input pin
 * @param no parameter is given
 * @return no return is expected */
void configure_Button(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE(); //Enable clock to GPIOA
	GPIO_InitTypeDef PushButton;  // declare a variable of type struct GPIO_InitTypeDef
	PushButton.Mode = GPIO_MODE_INPUT; // set pin mode to input
	PushButton.Pin = GPIO_PIN_0;  // select pin PA0 only
	PushButton.Pull = GPIO_NOPULL; // set no internal pull-up or pull-down resistor
	HAL_GPIO_Init(GPIOA, &PushButton); //  initialize PA0 pins by passing port name and address of PushButton struct
}

/** @brief void Delay_ms
 * @param time in ms is given
 * @return no return is expected */
void Delay_ms(volatile int time_ms)
{
	      int j;
        for(j = 0; j < time_ms*4000; j++)
            {}  /* excute NOP for 1ms */
}
/**@brief void frequency
 * @param time
 * @return no return is expected
 */
void frequency(volatile int time)
{
	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
	    	//GPIOD->BSRR = 1<<14; // Set the BSRR bit 12 to 1 to turn respective LED on
	    			//for(i=0; i<10; i++){};
	    	//Delay_ms(0.25);
	    			//GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit 12 + 16 to 1 to turn respective LED off
	    			GPIOD->BSRR = 1<<15; // Set the BSRR bit 13 to 1 to turn respective LED on
	    			//for(i=0; i<10; i++){};
	    			Delay_ms(time);
	    			GPIOD->BSRR = 1<<(15+16); // Set the BSRR bit 13 + 16 to 1 to turn respective LED off
	    			GPIOD->BSRR = 1<<12; // Set the BSRR bit 14 to 1 to turn respective LED on
	    			//for(i=0; i<10; i++){};
	    			Delay_ms(time);
	    			GPIOD->BSRR = 1<<(12+16); // Set the BSRR bit 14 + 16 to 1 to turn respective LED off
	    			GPIOD->BSRR = 1<<13; // Set the BSRR bit 15 to 1 to turn respective LED on

	    			// Delay
	    			//for(i = 0; i < 10; i++){}; // Loop repeats 2,000,000 implementing a delay
	    			Delay_ms(time);
	    			GPIOD->BSRR = 1<<(13+16); // Set the BSRR bit 15 + 16 to 1 to turn respective LED off

	    			// Turn off LEDs
	    			//GPIOD->BSRR = 1<<(12+16); // Set the BSRR bit 12 + 16 to 1 to turn respective LED off
	    			//GPIOD->BSRR = 1<<(13+16); // Set the BSRR bit 13 + 16 to 1 to turn respective LED off
	    			//GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit 14 + 16 to 1 to turn respective LED off
	    			//GPIOD->BSRR = 1<<(15+16); // Set the BSRR bit 15 + 16 to 1 to turn respective LED off

	    			// Delay
	    			//for(i = 0; i < 2,000,000; i++){}; // Loop repeats 2,000,000 implementing a delay
	    			Delay_ms(time);
}
/**@brief void_led
 * @param no parameter is given
 * @return no return is expected
 */
void led()
{
	GPIOD->BSRR = 1<<14; // Set the BSRR bit 14 to 1 to turn respective LED on
	//if(c==6) GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit 14 + 16 to 1 to turn respective LED off


}
