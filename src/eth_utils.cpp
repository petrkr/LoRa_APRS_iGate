#include <ETH.h>
#include "configuration.h"
#include "wifi_utils.h"
#include "display.h"
#include "utils.h"
#include <WiFi.h>

extern Configuration    Config;

bool        eth_connected       = false;
uint32_t    previousEthMillis   = 0;
uint8_t     ethCounter          = 0;


namespace ETH_Utils {

    void onEvent(arduino_event_id_t event) {
        String hostName = "iGATE-" + Config.callsign;
        switch (event) {
            case ARDUINO_EVENT_ETH_START:
            Serial.println("ETH Started");
            ETH.setHostname(hostName.c_str());
            break;
            case ARDUINO_EVENT_ETH_CONNECTED: Serial.println("ETH Connected"); break;
            case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.println("ETH Got IP");
            eth_connected = true;
            break;
            case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("ETH Disconnected");
            eth_connected = false;
            break;
            case ARDUINO_EVENT_ETH_STOP:
            Serial.println("ETH Stopped");
            eth_connected = false;
            break;
            default: break;
        }
    }

    void checkEth() {

    }

    void startEthernet() {
        displayShow("", "Connecting to LAN", "", " ...", 0);
        Serial.println("\nConnecting to LAN...");

        // SDK still have this have in WiFi class even for Ethernet events
        WiFi.onEvent(onEvent);

        #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
            // SDK 5.x (Arduino SDK 3.x)
            #pragma message("Compiling ETH init: SDK 5.x (Arduino core 3.x)")
            ETH.begin(ETH_PHY_LAN8720, 1, 23, 18, -1, ETH_CLOCK_GPIO17_OUT);
        #else
            // SDK 4.x (Arduino SDK 2.x)
            #pragma message("Compiling ETH init: SDK 4.x (Arduino core 2.x)")
            ETH.begin(1, -1, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_LAN8720, ETH_CLOCK_GPIO17_OUT);
        #endif

        while (!eth_connected) {
            delay(1000);
            Serial.print(".");
            ethCounter++;
            if (ethCounter > 10) {
                Serial.println("\nEthernet connection failed");
                displayShow("", "Ethernet connection", "failed", " ...", 0);
                return;
            }
        }
    }


    void setup() {
        startEthernet();
    }

}