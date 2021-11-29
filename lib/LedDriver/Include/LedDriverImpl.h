/**
 * @file LedDriverImpl.h
 * @author your name (you@domain.com)
 * @brief Class containing the definition of a class implementing the generic LED driver
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LEDDRIVERIMPL_H
#define LEDDRIVERIMPL_H

#include <LedDriver.h>
#include <stdint.h>

/**
 * @brief Implementation of the generic LED driver using RGB led and Timer1 ATMega328 interrupts
 * 
 */
class LedDriverImpl: public LedDriver
{
    protected:

    /**
     * @brief Pin configured for LED R pin
     * 
     */
    uint8_t led_red;

    /**
     * @brief Pin configured for LED G pin
     * 
     */
    uint8_t led_green;

    /**
     * @brief Pin configured for LED B pin
     * 
     */
    uint8_t led_blue;

    /**
     * @brief Current status defined for the LED peripheral
     * 
     */
    LedDriver::Status status;

    /**
     * @brief toggle status, used for generating the flash sequence if required
     * 
     */
    bool toggle = 0;

    /**
     * @brief Singleton instance of the LED driver implementation
     * 
     */
    static LedDriverImpl* instance;

    /**
     * @brief Callback function used by the timer1 interrupt. It will set the pins of the LED peripheral
     * according to the status configured for the LED and the toggle status if flashing.
     * 
     */
    static void callback();

    /**
     * @brief Construct a new Led Driver object
     * 
    * @param led_red R pin number
    * @param led_green G pin number
    * @param led_blue B pin number
    * @param flash_period periodicity of the flash in microseconds
    * @param initial_status initial status to set the LED peripheral
     */
    LedDriverImpl(uint8_t led_red, uint8_t led_green, uint8_t led_blue, uint32_t flash_period, LedDriver::Status initial_status);

    /**
     * @brief Destroy the Led Driver object
     * 
     */
    ~LedDriverImpl();

    public:

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
    static LedDriverImpl *getInstance(uint8_t led_red, uint8_t led_green, uint8_t led_blue, uint32_t flash_period, LedDriver::Status initial_status);

    /**
     * @brief Set the led peripheral to constant red light
     * 
     */
    void redOn();

    /**
     * @brief Set the led peripheral to flashing red light
     * 
     */
    void redFlash();

    /**
     * @brief Set the led peripheral to constant white light
     * 
     */
    void whiteOn();
    
    /**
     * @brief Set the led peripheral to flashing white light
     * 
     */
    void whiteFlash();

    /**
     * @brief Set the led peripheral to off
     * 
     */
    void ledOff();

};

#endif