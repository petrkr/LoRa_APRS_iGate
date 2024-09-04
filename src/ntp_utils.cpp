#include "configuration.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

extern bool             eth_connected;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

namespace NTP_Utils {

    void checkNtp() {
        if (!eth_connected) {
            return;
        }

        timeClient.update();
    }

    void startNtp() {
        if (!eth_connected) {
            return;
        }

        Serial.println("Starting NTP...");
        timeClient.begin();
    }

    void setup() {
        startNtp();
    }

}