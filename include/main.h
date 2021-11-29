/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief Library containing the definitions of the pins used for connecting the microcontroller
 * with the LED peripheral and both buttons.
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAIN_H
#define MAIN_H

/**
 * @brief microcontroller pin where to connect the R pin of the LED peripheral
 * 
 */
#define LED_PIN_R 4

/**
 * @brief microcontroller pin where to connect the G pin of the LED peripheral
 * 
 */
#define LED_PIN_G 5

/**
 * @brief microcontroller pin where to connect the B pin of the LED peripheral
 * 
 */
#define LED_PIN_B 6

/**
 * @brief microcontroller pin where to connect the Button 1
 * 
 */
#define BUTTON_1  2

/**
 * @brief microcontroller pin where to connect the Button 2
 * 
 */
#define BUTTON_2  3


/**
 * @brief Flashing periodicity of the LED peripheral
 * 
 */
#define LED_PERIOD_MICRO  500000

#endif