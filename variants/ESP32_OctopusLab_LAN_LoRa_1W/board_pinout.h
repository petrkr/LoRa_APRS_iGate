#ifndef BOARD_PINOUT_H_
#define BOARD_PINOUT_H_
    #undef HAS_DISPLAY
    //    #define BOARD_I2C_SDA       2
    //    #define BOARD_I2C_SCL       16
    // #define OLED_RST            -1
    #define RADIO_SCLK_PIN      33
    #define RADIO_MISO_PIN      35
    #define RADIO_MOSI_PIN      32
    #define RADIO_CS_PIN        5
    #define RADIO_DIO1_PIN      34
    #define RADIO_RST_PIN       -1
    #define RADIO_BUSY_PIN      39
    #define RADIO_RXEN          2
    #define RADIO_TXEN          16
    #define RADIO_WAKEUP_PIN        RADIO_DIO1_PIN
    #define GPIO_WAKEUP_PIN         GPIO_NUM_3
#endif
