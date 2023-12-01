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

#define PC13 (1 << 13)
#define BUTTON_PRESSED GPIOC->IDR & PC13

#endif /* MAIN_H_ */
