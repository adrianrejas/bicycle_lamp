/**
 * @file LedDriverImpl.cpp
 * @author your name (you@domain.com)
 * @brief Source code containing the implementation of the methods defined for LedDriverImpl class
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <LedDriver.h>
#include <LedDriverImpl.h>
#include <Arduino.h>
#include <TimerOne.h>

/**
 * @brief Singleton instance of the LED driver implementation
 * 
 */
LedDriverImpl* LedDriverImpl::instance = 0; 

/**
 * @brief Construct a new Led Driver object
 * 
* @param led_red R pin number
* @param led_green G pin number
* @param led_blue B pin number
* @param flash_period periodicity of the flash in microseconds
* @param initial_status initial status to set the LED peripheral
    */
LedDriverImpl::LedDriverImpl(uint8_t led_red, uint8_t led_green, uint8_t led_blue, uint32_t flash_period, LedDriver::Status initial_status) {
    this->led_red = led_red;
    this->led_green = led_green;
    this->led_blue = led_blue;
    this->status = initial_status;
    pinMode(this->led_red, OUTPUT);
    pinMode(this->led_green, OUTPUT);
    pinMode(this->led_blue, OUTPUT);
    Timer1.initialize(flash_period);         // initialize timer1, and set it at the periodicity requested
    Timer1.attachInterrupt(this->callback);  // attaches callback() function as a timer overflow interrupt
}

/**
 * @brief Destroy the Led Driver object
 * 
 */
LedDriverImpl::~LedDriverImpl() {
    Timer1.detachInterrupt(); // dettach callback() function as a timer overflow interrupt
    Timer1.stop(); // stop timer1 interruptions processing
}

/**
 * @brief Get the Instance object. In works according to singleton pattern, because this LED driver works in base of 
 * ATMega microcontroller Timer1 interruptions, and only a single ISR can be attached to the corresponding interruption.
 * 
 * @param led_red R pin number
 * @param led_green G pin number
 * @param led_blue B pin number
 * @param flash_period periodicity of the flash in microseconds
 * @param initial_status initial status to set the LED peripheral
 * @return LedDriverImpl* Instance representing the LED driver
 */
LedDriverImpl *LedDriverImpl::getInstance(uint8_t led_red, uint8_t led_green, uint8_t led_blue, uint32_t flash_period, LedDriver::Status initial_status) {
    if (LedDriverImpl::instance == nullptr) {
        LedDriverImpl::instance = new LedDriverImpl(led_red, led_green, led_blue, flash_period, initial_status);
    }
    return LedDriverImpl::instance;
}

/**
 * @brief Set the led peripheral to constant red light
 * 
 */
void LedDriverImpl::redOn() {
    this->status = STATUS_RED_ON;
}

/**
 * @brief Set the led peripheral to flashing red light
 * 
 */
void LedDriverImpl::redFlash() {
    this->status = STATUS_RED_FLASH;
}

/**
 * @brief Set the led peripheral to constant white light
 * 
 */
void LedDriverImpl::whiteOn() {
    this->status = STATUS_WHITE_ON;
}

/**
 * @brief Set the led peripheral to flashing white light
 * 
 */
void LedDriverImpl::whiteFlash() {
    this->status = STATUS_WHITE_FLASH;
}

/**
 * @brief Set the led peripheral to off
 * 
 */
void LedDriverImpl::ledOff() {
    this->status = STATUS_OFF;
}

/**
 * @brief Callback function used by the timer1 interrupt. It will set the pins of the LED peripheral
 * according to the status configured for the LED and the toggle status if flashing.
 * 
 */
void LedDriverImpl::callback(){
    switch (LedDriverImpl::instance->status)
    {
        case STATUS_OFF:
            digitalWrite(LedDriverImpl::instance->led_red, LOW);
            digitalWrite(LedDriverImpl::instance->led_green, LOW);
            digitalWrite(LedDriverImpl::instance->led_blue, LOW);
            break;
        case STATUS_RED_ON:
            digitalWrite(LedDriverImpl::instance->led_red, HIGH);
            digitalWrite(LedDriverImpl::instance->led_green, LOW);
            digitalWrite(LedDriverImpl::instance->led_blue, LOW);
            break;
        case STATUS_RED_FLASH:
            if (LedDriverImpl::instance->toggle) {
                digitalWrite(LedDriverImpl::instance->led_red, HIGH);
                digitalWrite(LedDriverImpl::instance->led_green, LOW);
                digitalWrite(LedDriverImpl::instance->led_blue, LOW);
                LedDriverImpl::instance->toggle = 0;
            } else {
                digitalWrite(LedDriverImpl::instance->led_red, LOW);
                digitalWrite(LedDriverImpl::instance->led_green, LOW);
                digitalWrite(LedDriverImpl::instance->led_blue, LOW);
                LedDriverImpl::instance->toggle = 1;
            }
            break;
        case STATUS_WHITE_ON:
            digitalWrite(LedDriverImpl::instance->led_red, HIGH);
            digitalWrite(LedDriverImpl::instance->led_green, HIGH);
            digitalWrite(LedDriverImpl::instance->led_blue, HIGH);
            break;
        case STATUS_WHITE_FLASH:
            if (LedDriverImpl::instance->toggle) {
                digitalWrite(LedDriverImpl::instance->led_red, HIGH);
                digitalWrite(LedDriverImpl::instance->led_green, HIGH);
                digitalWrite(LedDriverImpl::instance->led_blue, HIGH);
                LedDriverImpl::instance->toggle = 0;
            } else {
                digitalWrite(LedDriverImpl::instance->led_red, LOW);
                digitalWrite(LedDriverImpl::instance->led_green, LOW);
                digitalWrite(LedDriverImpl::instance->led_blue, LOW);
                LedDriverImpl::instance->toggle = 1;
            }
            break;
        default:
            digitalWrite(LedDriverImpl::instance->led_red, LOW);
            digitalWrite(LedDriverImpl::instance->led_green, LOW);
            digitalWrite(LedDriverImpl::instance->led_blue, LOW);
            break;
    }
}