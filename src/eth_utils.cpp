#include "configuration.h"
#include "network_manager.h"
#include "board_pinout.h"
#include "display.h"
#include "utils.h"

extern Configuration    Config;
extern NetworkManager   *networkManager;

#ifdef HAS_ETH
#include <ETH.h>

uint8_t                 ethCounter = 0;
#endif

namespace ETH_Utils {
    void startEthernet() {
#ifdef HAS_ETH
        displayShow("", "Connecting to LAN", "", " ...", 0);
        Serial.println("\nConnecting to LAN...");

        networkManager->ethernetConnect(ETHERNET_PHY_TYPE, ETHERNET_PHY_ADDR, ETHERNET_PHY_MDC, ETHERNET_PHY_MDIO, ETHERNET_PHY_POWER, ETHERNET_CLK_MODE);

        while (!networkManager->isEthernetConnected()) {
            delay(1000);
            Serial.print(".");
            ethCounter++;
            if (ethCounter > 30) {
                Serial.println("\nEthernet connection failed");
                displayShow("", "Ethernet connection", "failed", " ...", 0);
                return;
            }
        }

        Serial.print("\nConnected as ");
        Serial.print(networkManager->getEthernetIP());
        displayShow("", "     Connected!!", "", "     loading ...", 1000);
#endif
    }

    void setup() {
#ifdef HAS_ETH
        startEthernet();
#endif
    }
}
