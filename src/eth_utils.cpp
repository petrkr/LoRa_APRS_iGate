#include <ETH.h>
#include "configuration.h"
#include "network_manager.h"
#include "display.h"
#include "board_pinout.h"

extern Configuration    Config;
extern NetworkManager   *networkManager;

namespace ETH_Utils {

    bool setup() {
        if (!Config.ethConfig.enabled) {
            Serial.println("\nEthernet is disabled");
            return false;
        }

        displayShow("", "Connecting to LAN", "", " ...", 0);
        Serial.println("\nConnecting to LAN...");

        networkManager->ethernetConnect(
            ETH_PHY_TYPE,
            LAN_PHY_ADDR,
            LAN_MDC_PIN,
            LAN_MDIO_PIN,
            LAN_POWER_PIN,
            LAN_CLOCK_MODE,
            false  // useMacFromEfuse
        );

        // Configure static IP if enabled
        if (Config.ethConfig.useStaticIP) {
            networkManager->setEthernetIP(
                Config.ethConfig.staticIP,
                Config.ethConfig.gateway,
                Config.ethConfig.subnet,
                Config.ethConfig.dns1,
                Config.ethConfig.dns2
            );
        }

        unsigned long startMillis = millis();
        int timeoutSec = 15;

        while (!networkManager->isEthernetConnected()) {
            delay(500);
            Serial.print(".");
            if (millis() - startMillis > timeoutSec * 1000) {
                Serial.println("\nEthernet connection timeout");
                displayShow("", "Ethernet timeout", "", "", 2000);
                return false;
            }
        }

        Serial.println("\nEthernet connected! IP: " + networkManager->getEthernetIP().toString());
        displayShow("", "LAN Connected!", networkManager->getEthernetIP().toString(), "", 2000);
        return true;
    }
}
