#pragma once
#include <ESP8266WiFi.h>

struct AP {
    char* ssid;
    char* type;
    int strength;
};

class Network {
    private:
        static const int MAX_NETWORKS = 50;

        char* getNetworkTypeFromInt(int type);
        bool connectToNetworkIfKnown(AP& network, char* mySSID, char* password);

    public:
        AP currentNetwork;
        AP networks[MAX_NETWORKS];
        int numberOfNetworks = 0;
        Network();

        bool isConnected();
        void scan(bool autoConnect);
        void connectToNetwork(AP& network, char* password);
};
