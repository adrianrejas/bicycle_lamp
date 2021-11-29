/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief Source file with the main function of the firmware loaded over the microcontroller.
 * The firmware will represent the logic of a bicycle lamp.
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <main.h>
#include <LedDriver.h>
#include <LedDriverImpl.h>
#include <FSMBikeLamp.h>

/**
 * @brief Driver used for interacting with the LED.
 * 
 */
LedDriver *led_driver;

/**
 * @brief Object representing the FSM containing the business logic of the bycicle lamp.
 * 
 */
FSMBikeLamp *fsm;

/**
 * @brief Variable used as semaphore for triggering the bottom half ISR
 * (the one executed in the main thread) associated with the button 1.
 * 
 */
bool button_1_pressed = 0;

/**
 * @brief Variable used as semaphore for triggering the bottom half ISR
 * (the one executed in the main thread) associated with the button 2.
 * 
 */
bool button_2_pressed = 0;

 /**
 * @brief Top half ISR (the ISR itself) associated with the button 1.
 * It will set the variable used as semaphore for trigerring the 
 * corresponding bottom half ISR.
 * 
 */
void button_1_isr()
{
  button_1_pressed = 1;
}

 /**
 * @brief Top half ISR (the ISR itself) associated with the button 2.
 * It will set the variable used as semaphore for trigerring the 
 * corresponding bottom half ISR.
 * 
 */
void button_2_isr()
{
  button_2_pressed = 1;
}

/**
 * @brief Code to be executed in the main tread.
 * 
 * @return int Result of the main thread (unused)
 */
int main(void)
{
  // Init microcontroller hardware
	init();
  
  // Init serial port (for debugging purposes)
  Serial.begin(9600);
  
  // Configuring pins associated with buttons 1 and 2 for triggering
  // their respectives top half ISRs when pressed
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), button_1_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), button_2_isr, RISING);

  // Init the driver for managing the LED.
  led_driver = LedDriverImpl::getInstance(LED_PIN_R, LED_PIN_G, LED_PIN_B, LED_PERIOD_MICRO, LedDriver::Status::STATUS_OFF);

  // Init the FSM containing the business logic.
  fsm = new FSMBikeLamp(FSMBikeLamp::State::LED_RED_OFF, led_driver);

  Serial.println("Setup finished");

  // Enter in the main thread endless loop 
	for (;;) {
    // If bottom half ISR for button 1 triggered from top half ISR
    if (button_1_pressed) {
      // Bottom half ISR for button 1
      Serial.println("Pressed button 1");
      // Update FSM status with the new action
      fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
      // Reset bottom half ISR triggering variable
      button_1_pressed = 0;
    }
    // If bottom half ISR for button 2 triggered from top half ISR
    if (button_2_pressed) {
      // Bottom half ISR for button 2
      Serial.println("Pressed button 2");
      // Update FSM status with the new action
      fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
      // Reset bottom half ISR triggering variable
      button_2_pressed = 0;
    }
	}
	return 0;
}
