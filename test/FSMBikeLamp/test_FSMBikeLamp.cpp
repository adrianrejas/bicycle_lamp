/**
 * @file test_FSMBikeLamp.cpp
 * @author your name (you@domain.com)
 * @brief Source code containing unitary test cases for testing the different possible transitions in the 
 * bicycle lamp FSM.
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <unity.h>
#include <LedDriver.h>
#include <FSMBikeLamp.h>

/**
 * @brief Mock implementation of the LED driver for testing the business logic 
 * related to the bicycle lamp FSM.
 * 
 */
class LedDriverMock: public LedDriver {

    protected:

    /**
     * @brief Status set in the mock Led
     * 
     */
    LedDriver::Status status;
    
    public:

    /**
     * @brief Construct a new Led Driver Mock object
     * 
     * @param initial_status 
     */
    LedDriverMock(LedDriver::Status initial_status) {
        this->status = initial_status;
    }
    
    /**
     * @brief Destroy the Led Driver Mock object
     * 
     */
    ~LedDriverMock() {}

    /**
     * @brief Get the Driver Status 
     * 
     * @return LedDriver::Status Current mock LED status
     */
    LedDriver::Status getDriverStatus() {
        return status;
    }

    /**
     * @brief Set the Driver Status
     * 
     * @param status Status to set in the mock LED
     */
    void setDriverStatus(LedDriver::Status status) {
        this->status = status;
    }
    
    /**
     * @brief Set the mock led to constant red light
     * 
     */
    void redOn() {
        this->status = STATUS_RED_ON;
    }

    /**
     * @brief Set the mock led to flashing red light
     * 
     */
    void redFlash() {
        this->status = STATUS_RED_FLASH;
    }

    /**
     * @brief Set the mock led to constant white light
     * 
     */
    void whiteOn() {
        this->status = STATUS_WHITE_ON;
    }

    /**
     * @brief Set the mock led to flashing white light
     * 
     */
    void whiteFlash() {
        this->status = STATUS_WHITE_FLASH;
    }

    /**
     * @brief Set the mock led to off
     * 
     */
    void ledOff() {
        this->status = STATUS_OFF;
    }
};

/**
 * @brief Instance of the mock led driver used by the tests
 * 
 */
LedDriverMock *led_driver_mock;

/**
 * @brief Instance of the bicycle lamp FSM used by the tests
 * 
 */
FSMBikeLamp *fsm;

/**
 * @brief Configuration common to be executed before every test (unused)
 * 
 */
void setUp(void) {}

/**
 * @brief Deconfiguration common to be executed after every test (unused)
 * 
 */
void tearDown(void) {}

/**
 * @brief Test for checking the business logic in the initial case (state RED_OFF, led to OFF)
 * 
 */
void test_initial_status() {
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_OFF);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_OFF);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state RED_OFF
 * (change to state RED_ON, led to RED_ON)
 * 
 */
void test_button1_pressed_at_red_led_off () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_OFF);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_OFF);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_ON);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_RED_ON);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state RED_OFF
 * (no changes)
 * 
 */
void test_button2_pressed_at_red_led_off () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_OFF);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_OFF);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_OFF);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_OFF);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state RED_ON
 * (change to state RED_FLASH, led to RED_FLASH)
 * 
 */
void test_button1_pressed_at_red_led_on () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_RED_ON);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_ON);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_FLASH);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_RED_FLASH);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state RED_ON
 * (change to state WHITE_ON, led to WHITE_ON)
 * 
 */
void test_button2_pressed_at_red_led_on () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_RED_ON);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_ON);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_ON);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_WHITE_ON);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state RED_FLASH
 * (change to state RED_OFF, led to OFF)
 * 
 */
void test_button1_pressed_at_red_led_flash () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_RED_FLASH);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_FLASH);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_OFF);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_OFF);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state RED_FLASH
 * (change to state WHITE_FLASH, led to WHITE_FLASH)
 * 
 */
void test_button2_pressed_at_red_led_flash () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_RED_FLASH);
    fsm->setCurrentState(FSMBikeLamp::State::LED_RED_FLASH);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_FLASH);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_WHITE_FLASH);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state WHITE_OFF
 * (change to state WHITE_ON, led to WHITE_ON)
 * 
 */
void test_button1_pressed_at_white_led_off () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_OFF);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_OFF);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_ON);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_WHITE_ON);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state WHITE_OFF
 * (no changes)
 * 
 */
void test_button2_pressed_at_white_led_off () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_OFF);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_OFF);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_OFF);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_OFF);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state WHITE_ON
 * (change to state WHITE_FLASH, led to WHITE_FLASH)
 * 
 */
void test_button1_pressed_at_white_led_on () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_WHITE_ON);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_ON);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_FLASH);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_WHITE_FLASH);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state WHITE_ON
 * (change to state RED_ON, led to RED_ON)
 * 
 */
void test_button2_pressed_at_white_led_on () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_WHITE_ON);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_ON);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_ON);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_RED_ON);
}

/**
 * @brief Test for checking the business logic when pressing button 1 in state WHITE_FLASH
 * (change to state WHITE_OFF, led to OFF)
 * 
 */
void test_button1_pressed_at_white_led_flash () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_WHITE_FLASH);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_FLASH);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_1_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_WHITE_OFF);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_OFF);
}

/**
 * @brief Test for checking the business logic when pressing button 2 in state WHITE_FLASH
 * (change to state RED_FLASH, led to RED_FLASH)
 * 
 */
void test_button2_pressed_at_white_led_flash () {
    led_driver_mock->setDriverStatus(LedDriver::Status::STATUS_WHITE_FLASH);
    fsm->setCurrentState(FSMBikeLamp::State::LED_WHITE_FLASH);
    fsm->updateState(FSMBikeLamp::Action::BUTTON_2_PRESSED);
    TEST_ASSERT_TRUE(fsm->getCurrentState() == FSMBikeLamp::State::LED_RED_FLASH);
    TEST_ASSERT_TRUE(led_driver_mock->getDriverStatus() == LedDriver::Status::STATUS_RED_FLASH);
}

/**
 * @brief Main function to be executed by the microcontroller during the execution of the tests
 * 
 * @return int 
 */
int main( void) {
    // Initialization before execution of all tests (initialization fo both
    // mock LED and FSM)
    led_driver_mock = new LedDriverMock(LedDriver::Status::STATUS_OFF);
    fsm = new FSMBikeLamp(FSMBikeLamp::State::LED_RED_OFF, led_driver_mock);
    // Init tests, executing them one by one
    UNITY_BEGIN();
    RUN_TEST(test_initial_status);
    RUN_TEST(test_button1_pressed_at_red_led_off);
    RUN_TEST(test_button2_pressed_at_red_led_off);
    RUN_TEST(test_button1_pressed_at_red_led_on);
    RUN_TEST(test_button2_pressed_at_red_led_on);
    RUN_TEST(test_button1_pressed_at_red_led_flash);
    RUN_TEST(test_button2_pressed_at_red_led_flash);
    RUN_TEST(test_button1_pressed_at_white_led_off);
    RUN_TEST(test_button2_pressed_at_white_led_off);
    RUN_TEST(test_button1_pressed_at_white_led_on);
    RUN_TEST(test_button2_pressed_at_white_led_on);
    RUN_TEST(test_button1_pressed_at_white_led_flash);
    RUN_TEST(test_button2_pressed_at_white_led_flash);
    // Finish tests and uninitialize elements set previously.
    UNITY_END();
    delete led_driver_mock;
    delete fsm;
}