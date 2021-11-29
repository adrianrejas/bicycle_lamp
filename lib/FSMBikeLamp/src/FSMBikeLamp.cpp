/**
 * @file FSMBikeLamp.cpp
 * @author your name (you@domain.com)
 * @brief Source code containing the implementation of the methods defined for FSMBikeLamp class
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Arduino.h>
#include <FSMBikeLamp.h>

/**
 * @brief Construct a new bicycle lamp FSM instance
 * 
 * @param initial_state Initial state of the FSM
 * @param led_driver Led driver instance used by FSM logic.
 */
FSMBikeLamp::FSMBikeLamp(FSMBikeLamp::State initial_state, LedDriver *led_driver) {
    this->led_driver = led_driver;
    this->current_state = initial_state;
    Serial.print("Inited FSM with state ID ");
    Serial.println(this->current_state);
    state_function action_to_do = this->state_functions[this->current_state];
    if (action_to_do != nullptr) {
        (this->*action_to_do)();
    }
}

/**
 * @brief Destroy the bicycle lamp FSM instance
 * 
 */
FSMBikeLamp::~FSMBikeLamp() {};

/**
 * @brief Get the current state of the bicycle lamp FSM
 * 
 * @return FSMBikeLamp::State current FSM state
 */
FSMBikeLamp::State FSMBikeLamp::getCurrentState() {
    return this->current_state;
}

/**
 * @brief Set the Current State of the bicycle lamp FSM
 * 
 * @param state  State to set on FSM state
 */
void FSMBikeLamp::setCurrentState(FSMBikeLamp::State state) {
    // Update the current state to the one set
    this->current_state = state;
    // After update the current state, get the function with the code to be
    // executed at the new state from the state_functions array
    state_function action_to_do = this->state_functions[this->current_state];
    // If action to do not null, execute the action
    if (action_to_do != nullptr) {
        (this->*action_to_do)();
    }
}


/**
 * @brief Update the state of the bicycle lamp FSM when received an action
 * 
 * @param action Action triggering the change
 */
void FSMBikeLamp::updateState(FSMBikeLamp::Action action) {
    Serial.print("Action ID ");
    Serial.print(action);
    Serial.print(" for FSM in state ID ");
    Serial.println(this->current_state);
    // Update the current state to the one set from the transitions matrix
    // using as input the current state and the action received
    this->current_state = this->transitions[this->current_state][action];
    Serial.print("Change FSM to state id ");
    Serial.println(this->current_state);
    // After update the current state, get the function with the code to be
    // executed at the new state from the state_functions array
    state_function action_to_do = this->state_functions[this->current_state];
    // If action to do not null, execute the action
    if (action_to_do != nullptr) {
        (this->*action_to_do)();
    }
}

/**
 * @brief Function executed at LED_RED_OFF and LED_WHITE_OFF states. It set the led to off
 * 
 */
void FSMBikeLamp::ledOff() {
    this->led_driver->ledOff();
}

/**
 * @brief Function executed at LED_RED_ON states. It set the led to constant red light
 * 
 */
void FSMBikeLamp::ledOnRed() {
    this->led_driver->redOn();
}

/**
 * @brief Function executed at LED_WHITE_ON states. It set the led to constant white light
 * 
 */
void FSMBikeLamp::ledFlashRed() {
    this->led_driver->redFlash();
}

/**
 * @brief Function executed at LED_RED_FLASH states. It set the led to flashing white light
 * 
 */
void FSMBikeLamp::ledOnWhite() {
    this->led_driver->whiteOn();
}

/**
 * @brief Function executed at LED_WHITE_FLASH states. It set the led to flashing white light
 * 
 */
void FSMBikeLamp::ledFlashWhite() {
    this->led_driver->whiteFlash();
}