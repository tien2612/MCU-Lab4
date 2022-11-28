/*
 * task.c
 *
 *  Created on: Nov 28, 2022
 *      Author: nguye
 */
#include "task.h"

void task0() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

void task1() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}

void task2() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void task3() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
}

void task4() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
}
