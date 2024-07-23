#include <ETH.h>
#include "configuration.h"
#include "boards_pinout.h"
#include "wifi_utils.h"
#include "display.h"
#include "utils.h"

extern Configuration    Config;

bool        EthConnected        = false;
uint32_t    previousEthMillis   = 0;
uint8_t     ethCounter          = 0;


namespace ETH_Utils {

    void checkEth() {

    }

    void startEthernet() {
        displayShow("", "Connecting to LAN", "", " ...", 0);
        Serial.println("\nConnecting to LAN...");
        ETH.begin(ETH_PHY_LAN8720, 1, 23, 18, -1, ETH_CLOCK_GPIO17_OUT);
    }


    void setup() {
        startEthernet();
    }

}