/*
 * main.h
 *
 *  Created on: Nov 19, 2023
 *      Author: ahadz
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "stm32f746xx.h"

#define 	PC13 				(1 << 13)
#define 	BUTTON_PRESSED 		GPIOC->IDR & PC13

void BUTTON_CONF(void);
void Delay(void);
void UART3_CONF(void);
void UART3_TX_EN(void);
void DMA1_UART3_TX_CONF(void);
void PRINT_TAB(char Tab[]);

void BUTTON_CONF(void){
	//GPIO PORT C CLOCK ENABLE
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	//INPUT
	GPIOC->MODER &= ~(GPIO_MODER_MODER13);
	//NO PULL UP, NO PULL DOWN
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR13);
}

void Delay(void){
	uint32_t time;
	for(time = 0; time < 99999; time++){}
}

void UART3_CONF(void){
	//GPIO PORT C CLOCK ENABLE
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	//PD8 - USART3_TX (ALTERNATE FUNCTION)
	GPIOD -> MODER |= GPIO_MODER_MODER8_1;
	GPIOD -> AFR[1] |= 0x7;
	//PD9 - USART3_RX (ALTERNATE FUNCTION)
	GPIOD -> MODER |= GPIO_MODER_MODER9_1;
	GPIOD -> AFR[1] |= (0x7 << 4);
	//OPEN - DRAIN
	GPIOD -> OTYPER |= GPIO_OTYPER_OT9;

	//USART3 CLOCK ENABLE
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	//BAUD RATE - 115200
	USART3 -> BRR = 16000000 / 115200;
	//FRAME 8N1
}

void UART3_TX_EN(void){
	//USART ENABLE
	USART3 -> CR1 |= USART_CR1_UE;
	//TRANSMITTER ENABLE
	USART3 -> CR1 |= USART_CR1_TE;
	//RECEIVER ENABLE
	//USART3 -> CR1 |= USART_CR1_RE;
}

void DMA1_UART3_TX_CONF(void){
	//UART3_TX -> DMA1 CHANNEL 4
	DMA1->SxCR |= DMA1_SxCR_CHSEL_2;

	//DMA1 CLOCK ENABLE
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	//SET PERIFFERAL ADDRESS TO UART DATA REGISTER

}

void PRINT_TAB(char Tab[]){
	while(!(USART3 -> ISR & USART_ISR_TXE)){  }
	for(uint8_t i = 0; i < 5; i++){
		//Tab[i] TO BUFFER
		USART3 -> TDR = Tab[i];
		while(!(USART3 -> ISR & USART_ISR_TXE)){  }
	}
	//ENTER -> NEW LINE
	USART3 -> TDR = 0x0D;
	while(!(USART3 -> ISR & USART_ISR_TXE)){  }
}

#endif /* MAIN_H_ */
