/**
 * @file LedDriver.h
 * @author your name (you@domain.com)
 * @brief Clas containing an abstract class representing a generic LED peripheral driver interface.
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LEDDRIVER_H
#define LEDDRIVER_H

/**
 * @brief Abstract class representing a generic LED peripheral driver interface.
 * 
 */
class LedDriver
{
    public:
    /**
     * @brief Status possibles in the LED peripheral
     * 
     */
    enum Status {
        STATUS_OFF,
        STATUS_RED_ON,
        STATUS_RED_FLASH,
        STATUS_WHITE_ON,
        STATUS_WHITE_FLASH
    };

    /**
     * @brief Destroy the Led Driver object
     * 
     */
    virtual ~LedDriver() {}

    /**
     * @brief Set the led peripheral to constant red light
     * 
     */
    virtual void redOn() = 0;

    /**
     * @brief Set the led peripheral to flashing red light
     * 
     */
    virtual void redFlash() = 0;

    /**
     * @brief Set the led peripheral to constant white light
     * 
     */
    virtual void whiteOn() = 0;

    /**
     * @brief Set the led peripheral to flashing white light
     * 
     */
    virtual void whiteFlash() = 0;

    /**
     * @brief Set the led peripheral to off
     * 
     */
    virtual void ledOff() = 0;
};

#endif