/*
 * task.c
 *
 *  Created on: Nov 28, 2022
 *      Author: nguye
 */
#include "task.h"
#include "uart_msg.h"
#include "global.h"
#include <stdio.h>

void task0() {
	printf("Task0 start at: %d ms\r\n", timestamp);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

void task1() {
	printf("Task1 start at: %d ms\r\n", timestamp);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}

void task2() {
	printf("Task2 start at: %d ms\r\n", timestamp);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void task3() {
	printf("Task3 start at: %d ms\r\n", timestamp);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
}

void task4() {
	printf("Task4 start at: %d ms\r\n", timestamp);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
}
