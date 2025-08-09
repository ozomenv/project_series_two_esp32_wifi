#pragma once
#include <WiFi.h>
#include <WebServer.h>
#include <Core/Routing.h>

const char* ssid = "Citroen_CX_AP";
const char* password = "12345678Cx";
unsigned long startMillis;

Routing Routing;
WebServer server(80);
class WifiCore {
public:
    void init() {
        WiFi.mode(WIFI_OFF);
        WiFi.persistent(false);
        Routing.init();
    }
    void handle() {
        server.handleClient();

        unsigned long elapsed = millis() - startMillis;

        if (elapsed > 100 && elapsed < 11000 && WiFi.getMode() == WIFI_OFF) {
            Serial.println("📡 Запускаю точку доступу...");
            WiFi.mode(WIFI_AP);
            WiFi.softAP(ssid, password);
            server.begin();
            Serial.print("IP точки доступу: ");
            Serial.println(WiFi.softAPIP());
        }

        if (elapsed > 40000 && WiFi.getMode() == WIFI_AP) {
            Serial.println("⛔ Вимикаю точку доступу...");
            WiFi.mode(WIFI_MODE_NULL);

            delay(50);
            WiFi.softAPdisconnect(true);
            WiFi.enableAP(false);

            startMillis = millis();
        }
    }
};