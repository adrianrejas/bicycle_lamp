/**
 * @file FSMBikeLamp.h
 * @author your name (you@domain.com)
 * @brief Header file containing the declaration fo a class representing a bicycle lamp FSM.
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef FSMBIKELAMP_H
#define FSMBIKELAMP_H

#include <LedDriver.h>

/**
 * @brief Class representing a bicycle lamp FSM.
 * 
 */
class FSMBikeLamp
{
    public:

    /**
     * @brief List of possible states of the FSM.
     * 
     */
    enum State {
        LED_RED_OFF,
        LED_RED_ON,
        LED_RED_FLASH,
        LED_WHITE_OFF,
        LED_WHITE_ON,
        LED_WHITE_FLASH,
        NUMBER_OF_STATES
    };

    /**
     * @brief List of possible actions that can cause a change of state in the FSM.
     * 
     */
    enum Action {
        BUTTON_1_PRESSED,
        BUTTON_2_PRESSED,
        NUMBER_OF_ACTIONS
    };

    /**
     * @brief Construct a new bicycle lamp FSM instance
     * 
     * @param initial_state Initial state of the FSM
     * @param led_driver Led driver instance used by FSM logic.
     */
    FSMBikeLamp(State initial_state, LedDriver *led_driver);

    /**
     * @brief Destroy the bicycle lamp FSM instance
     * 
     */
    ~FSMBikeLamp();

    /**
     * @brief Get the current state of the bicycle lamp FSM
     * 
     * @return State current FSM state
     */
    State getCurrentState();

    /**
     * @brief Set the Current State of the bicycle lamp FSM
     * 
     * @param state  State to set on FSM state
     */
    void setCurrentState(State state);

/**
 * @brief Update the state of the bicycle lamp FSM when received an action
 * 
 * @param action Action triggering the change
 */
    void updateState(Action action);

    protected:

    /**
     * @brief type representing a function for being executed when the FSM enters in 
     * a certain state
     * 
     */
    typedef void (FSMBikeLamp::*state_function)();

    /**
     * @brief Current state of the FSM
     * 
     */
    State current_state;

    /**
     * @brief LED driver instance used by FSM logic
     * 
     */
    LedDriver *led_driver;

    /**
     * @brief Array with the functions for being executed when entering in a 
     * new state
     * 
     */
    state_function state_functions[NUMBER_OF_STATES] = {&FSMBikeLamp::ledOff,
            &FSMBikeLamp::ledOnRed,
            &FSMBikeLamp::ledFlashRed,
            &FSMBikeLamp::ledOff,
            &FSMBikeLamp::ledOnWhite,
            &FSMBikeLamp::ledFlashWhite
    };

    /**
     * @brief Matrix of states to move the FSM depending on the current state and the 
     * action received.
     * 
     */
    State transitions[NUMBER_OF_STATES][NUMBER_OF_ACTIONS] = {{LED_RED_ON, LED_RED_OFF},
            {LED_RED_FLASH, LED_WHITE_ON},
            {LED_RED_OFF, LED_WHITE_FLASH},
            {LED_WHITE_ON, LED_WHITE_OFF},
            {LED_WHITE_FLASH, LED_RED_ON},
            {LED_WHITE_OFF, LED_RED_FLASH}
    };

    /**
     * @brief Function executed at LED_RED_OFF and LED_WHITE_OFF states. It set the led to off
     * 
     */
    void ledOff();

    /**
     * @brief Function executed at LED_RED_ON states. It set the led to constant red light
     * 
     */
    void ledOnRed();

    /**
     * @brief Function executed at LED_WHITE_ON states. It set the led to constant white light
     * 
     */
    void ledOnWhite();

    /**
     * @brief Function executed at LED_RED_FLASH states. It set the led to flashing red light
     * 
     */
    void ledFlashRed();

    /**
     * @brief Function executed at LED_WHITE_FLASH states. It set the led to flashing white light
     * 
     */
    void ledFlashWhite();

};

#endif