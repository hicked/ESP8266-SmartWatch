#pragma once
#include "ESP8266WiFi.h"
#include <WiFiClient.h>
//#include <WifiLocation.h>
#include <ESP8266HTTPClient.h>

class APIClient {
    private:
        // Location stuff
        const char* Host = "www.unwiredlabs.com";
        String endpoint = "/v2/process.php";
        String token = ""; // ADD THIS
        String jsonString = "{\n";
        double latitude = 0.0;
        double longitude = 0.0;
        double accuracy = 0.0;


        // Weather stuff
        const char* weatherServer = "api.openweathermap.org"; // Open Weather Map API server name
        String WeatherAPIKey = "fed34549abe9c0a9d0332c84b0dcb197"; // account sign in is my email, pwd "MYNAMEandYOURNAME"
        String text;

        int jsonend = 0;
        bool startJson = false;
        const int JSON_BUFF_DIMENSION = 2500;

        
            
    public:
        String location = "Ottawa,CA"; // MIGHT NOT NEED THIS since API uses long and lat
        float tempNow;
        float tempLatter;
        float humidityNow;
        float humidityLatter;
        String weatherNow;
        String weatherLatter;

        APIClient();
        void UpdateLocation();
        void UpdateWeather();
};
