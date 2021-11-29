/**
 * @file test_LedDriverImpl.cpp
 * @author your name (you@domain.com)
 * @brief Source code containing integration test cases for testing the physical interaction with the LED peripheral
 * using the driver implemented based on ATMega328 Timer1 interrupts and RGB LED. the test will be done by checking 
 * the status of the RGB LED pins.
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <unity.h>
#include <Arduino.h>
#include <main.h>
#include <LedDriver.h>
#include <LedDriverImpl.h>

/**
 * @brief Microcontroller pin used for checking the status of the RGB LED R pin
 * 
 */
#define LED_PIN_R_TEST 9

/**
 * @brief Microcontroller pin used for checking the status of the RGB LED G pin
 * 
 */
#define LED_PIN_G_TEST 10

/**
 * @brief Microcontroller pin used for checking the status of the RGB LED B pin
 * 
 */
#define LED_PIN_B_TEST 11

/**
 * @brief Flashing periodicity to be used by the LED driver in milliseconds
 * 
 */
#define LED_PERIOD_MILI  LED_PERIOD_MICRO/1000

/**
 * @brief Number of times to repeat the list of tests.
 * 
 */
#define REPETITIONS_OF_TESTS    2

/**
 * @brief instance of the LED driver to be used
 * 
 */
LedDriver *led_driver;

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
 * @brief Test the correct working of the ledOff() LED driver API function
 * 
 */
void test_led_off () {
    led_driver->ledOff();
    delay(1000);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == LOW);
    delay(LED_PERIOD_MILI);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == LOW);
}

/**
 * @brief Test the correct working of the redOn() LED driver API function
 * 
 */
void test_led_red_on () {
    led_driver->redOn();
    delay(1000);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == LOW);
    delay(LED_PERIOD_MILI);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == LOW);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == LOW);
}

/**
 * @brief Test the correct working of the whiteOn() LED driver API function
 * 
 */
void test_led_white_on () {
    led_driver->whiteOn();
    delay(1000);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == HIGH);
    delay(LED_PERIOD_MILI);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_R_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == HIGH);
    TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == HIGH);
}

/**
 * @brief Test the correct working of the redFlash() LED driver API function
 * 
 */
void test_led_red_flash () {
    int led_r_value;
    bool has_been_set = 0;
    bool has_been_unset = 0;
    led_driver->redFlash();
    delay(1000);
    for (int i = 0; i < 6; i++) {
        led_r_value = digitalRead(LED_PIN_R_TEST);
        if ((!has_been_set) && (led_r_value == HIGH))
            has_been_set = 1;
        if ((!has_been_unset) && (led_r_value == LOW))
            has_been_unset = 1;
        TEST_ASSERT_TRUE(digitalRead(LED_PIN_G_TEST) == LOW);
        TEST_ASSERT_TRUE(digitalRead(LED_PIN_B_TEST) == LOW);
        delay(LED_PERIOD_MILI);
    }
    TEST_ASSERT_TRUE(has_been_set);
    TEST_ASSERT_TRUE(has_been_unset);
}

/**
 * @brief Test the correct working of the whiteFlash() LED driver API function
 * 
 */
void test_led_white_flash () {
    int led_r_value, led_g_value, led_b_value;
    bool has_been_set = 0;
    bool has_been_unset = 0;
    led_driver->whiteFlash();
    delay(1000);
    for (int i = 0; i < 6; i++) {
        led_r_value = digitalRead(LED_PIN_R_TEST);
        led_g_value = digitalRead(LED_PIN_G_TEST);
        led_b_value = digitalRead(LED_PIN_B_TEST);
        if ((!has_been_set) && (led_r_value == HIGH))
            has_been_set = 1;
        if ((!has_been_unset) && (led_g_value == LOW))
            has_been_unset = 1;
        TEST_ASSERT_TRUE(led_r_value == led_g_value);
        TEST_ASSERT_TRUE(led_r_value == led_b_value);
        delay(LED_PERIOD_MILI);
    }
    TEST_ASSERT_TRUE(has_been_set);
    TEST_ASSERT_TRUE(has_been_unset);
}

/**
 * @brief Setup function executed by the test cases microcontroller firmware before endless execution of loop.
 * 
 */
void setup() {
    delay(2000);
    // Init the test case
    UNITY_BEGIN(); 
    // init the led driver and the check pins
    led_driver = LedDriverImpl::getInstance(LED_PIN_R, LED_PIN_G, LED_PIN_B, LED_PERIOD_MICRO, LedDriver::Status::STATUS_OFF);
    pinMode(LED_PIN_R_TEST, INPUT);
    pinMode(LED_PIN_G_TEST, INPUT);
    pinMode(LED_PIN_B_TEST, INPUT);
}

uint8_t i = 0;

/**
 * @brief Endless loop executed by the test cases microcontroller firmware. It will execute the test list.
 * 
 */
void loop() {
    // For REPETITIONS_OF_TESTS times, execute the whole list of LED driver test cases.
    if (i < REPETITIONS_OF_TESTS)
    {
        RUN_TEST(test_led_off);
        delay(1000);
        RUN_TEST(test_led_red_on);
        delay(1000);
        RUN_TEST(test_led_white_on);
        delay(1000);
        RUN_TEST(test_led_red_flash);
        delay(1000);
        RUN_TEST(test_led_white_flash);
        delay(1000);
        i++;
    }
    else if (i == REPETITIONS_OF_TESTS) {
        // Once finished the repetitions of the test, deconfigure the LED driver and end the test case.
        led_driver->ledOff();
        UNITY_END();
        delete led_driver;
    }
}