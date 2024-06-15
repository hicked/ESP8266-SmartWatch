#include "Network.h"

Network::Network() {}

bool Network::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void Network::scan(bool autoConnect = false) {
    numberOfNetworks = WiFi.scanNetworks();
    Serial.print(numberOfNetworks);
    Serial.println(" networks found");
    
    for (uint8_t i = 0; i < min(numberOfNetworks, MAX_NETWORKS); i++) {
        Serial.print((i+1));
        Serial.println(" - " + WiFi.SSID(i));
        
        // Allocate memory for SSID
        char* ssid = new char[(WiFi.SSID(i)).length() + 1];
        (WiFi.SSID(i)).toCharArray(ssid, (WiFi.SSID(i)).length() + 1);

        // Create network data structure
        // Ensure that your 'networks' array is defined correctly
        networks[i] = {ssid, getNetworkTypeFromInt(WiFi.encryptionType(i)), WiFi.RSSI(i) + 127};

    }

    if (autoConnect) {
        for (uint8_t i = 0; i < min(numberOfNetworks, MAX_NETWORKS); i++) {
            if (this->isConnected() == false) {
                char* ssid = networks[i].ssid;
                if (strcmp(ssid, "SSID1") == 0) {
                    connectToNetwork(networks[i], "password1");
                }
                else if (strcmp(ssid, "SSID2") == 0) {
                    connectToNetwork(networks[i], "password2");
                }
                else if (strcmp(ssid, "SSID3") == 0) {
                    connectToNetwork(networks[i], "password3");
                }
                else if (strcmp(ssid, "SSID4") == 0) {
                    connectToNetwork(networks[i], "password4");
                }
                else if (strcmp(ssid, "SSID5") == 0) {
                    connectToNetwork(networks[i], "password5");
                }
            }
            else {
                break;
            }
        }
        // Deallocate memory for SSID at the end of the loop since were done assigning it to the object
        //delete[] ssid;
    }
    if (!this->isConnected()) {
        Serial.println("Could not autoconnect");
    }
}


char* Network::getNetworkTypeFromInt(int type) {
    switch (type) {
        case ENC_TYPE_NONE:
            return "Open";
        case ENC_TYPE_WEP:
            return "WEP";
        case ENC_TYPE_TKIP:
            return "WPA";
        case ENC_TYPE_CCMP:
            return "WPA2";
        case ENC_TYPE_AUTO:
            return "Auto";
        default:
            return "Unknown";
    }
}

void Network::connectToNetwork(AP& network, char* password) {
    unsigned long timeSinceConnectReq = millis();
    WiFi.begin(network.ssid, password);
    Serial.println(network.ssid);
    while (WiFi.status() != WL_CONNECTED && millis() - timeSinceConnectReq < 10000) {
        Serial.print(".");
        delay(1000);
    }
    if (this->isConnected()) {
        Serial.println(" Connected");
    }
    else {
        Serial.println("Timed out");
    }
}
