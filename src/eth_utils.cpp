#include <ETH.h>
#include "configuration.h"
#include "network_manager.h"
#include "wifi_utils.h"
#include "display.h"
#include "utils.h"

extern Configuration    Config;
extern NetworkManager   *networkManager;

uint8_t                 ethCounter = 0;

namespace ETH_Utils {
    void startEthernet() {
        displayShow("", "Connecting to LAN", "", " ...", 0);
        Serial.println("\nConnecting to LAN...");

        networkManager->ethernetConnect(ETH_PHY_LAN8720, 1, 23, 18, -1, ETH_CLOCK_GPIO17_OUT);

        while (!networkManager->isEthernetConnected()) {
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
