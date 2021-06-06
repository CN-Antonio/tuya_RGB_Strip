/*
 * @FileName: tuya_RGB_Strip.cpp
 * @Author: Antonio
 * @Email: dongyixiao2001@163.com
 * @LastEditors: Antonio
 * @Date: 2021-04-10 11:25:17
 * @LastEditTime: 2021-04-28 19:50:21
 * @Description: The functions that the user needs to actively call are in this file.
 */

/* 
配网模式：拉低Pin7
*/

#include <Arduino.h>
#include <TuyaWifi.h>
#include <FastLED.h>

TuyaWifi my_device;
SoftwareSerial DebugSerial(8, 9);

/* Current LED status */
unsigned char led_state = 0;
/* Connect network button pin */
int wifi_key_pin = 7;

/* DPID, DP type*/
#define DPID_POWER 20
#define DPID_MODE 21
#define DPID_BRIGHT 22
#define DPID_TEMP 23
#define DPID_SCENEMODE 50
#define DPID_MUSIC 51

bool power_status;
bool mode_status;
unsigned int bright_value;

unsigned char dp_array[][2] = {{DPID_POWER, DP_TYPE_BOOL},
                               {DPID_MODE, DP_TYPE_ENUM},
                               {DPID_BRIGHT, DP_TYPE_VALUE},
                               {DPID_TEMP, DP_TYPE_VALUE},
                               {DPID_SCENEMODE, DP_TYPE_RAW},
                               {DPID_MUSIC, DP_TYPE_RAW}};
/* PID, MCU version*/
unsigned char pid[] = {"gblpdmqp2emw9qug"};
unsigned char mcu_ver[] = {"1.0.0"};

// WS2812
#define NUM_LEDS 24
#define LED_DATA_PIN 13
CRGB leds[NUM_LEDS];

/* last time */
unsigned long last_time = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    DebugSerial.begin(9600);

    //Initialize led port, turn off led.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    //Initialize networking keys.
    pinMode(wifi_key_pin, INPUT_PULLUP);
    // function init
    wifi_key_led_init();

    // Enter the PID and MCU software version
    my_device.init(pid, mcu_ver);
    // incoming all DPs and their types array, DP numbers
    my_device.set_dp_cmd_total(dp_array, 6);
    // register DP download processing callback function
    my_device.dp_process_func_register(dp_process); //注册
    // register upload all DP callback function
    my_device.dp_update_all_func_register(dp_update_all);

    // WS2812
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // GRB ordering is typical

    last_time = millis();
}

void wifi_key_led_init(void)
{
}

void loop()
{
    my_device.uart_service(); //串口函数

    wifi_connect(); // 配网函数
}

void wifi_connect(void)
{
    //Enter the connection network mode when Pin7 is pressed.
    if (digitalRead(wifi_key_pin) == LOW)
    {
        delay(80);
        if (digitalRead(wifi_key_pin) == LOW)
        {
            my_device.mcu_set_wifi_mode(SMART_CONFIG);
        }
    }

    /* LED blinks when network is being connected */
    if ((my_device.mcu_get_wifi_work_state() != WIFI_LOW_POWER) && (my_device.mcu_get_wifi_work_state() != WIFI_CONN_CLOUD) && (my_device.mcu_get_wifi_work_state() != WIFI_SATE_UNKNOW))
    {
        if (millis() - last_time >= 500)
        {
            last_time = millis();
            /* Toggle current LED status */
            if (led_state == LOW)
            {
                led_state = HIGH;
            }
            else
            {
                led_state = LOW;
            }

            digitalWrite(LED_BUILTIN, led_state);
        }
    }

    delay(10);
}

/**
 * @description: 注册函数，DP download callback function.
 * @param {unsigned char} dpid
 * @param {const unsigned char} value
 * @param {unsigned short} length
 * @return {unsigned char}
 */
unsigned char dp_process(unsigned char dpid, const unsigned char value[], unsigned short length)
{
    switch (dpid)
    {
    default:
        break;
    }
    return SUCCESS;
}

/**
 * @description: Upload all DP status of the current device.
 * @param {*}
 * @return {*}
 */
void dp_update_all(void)
{
    my_device.mcu_dp_update(DPID_POWER, power_status, 1);
    my_device.mcu_dp_update(DPID_MODE, mode_status, 1);
    my_device.mcu_dp_update(DPID_BRIGHT, bright_value, 1);
}