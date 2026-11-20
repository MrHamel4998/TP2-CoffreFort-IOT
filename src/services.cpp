#include "services.h"
#include <addons/TokenHelper.h>

FirebaseAuth auth; 
FirebaseConfig config; 
FirebaseData fbdo;

// Source pour la stratégie du temps : 
// https://youtu.be/CZH4DJAtAVU?si=vRSGo8eH1al1UC0o
void initTime() {
    configTime(GMT_OFFSET, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

    struct tm timeinfo;

    Serial.println("Synchronisation de l'heure...");
    while (!getLocalTime(&timeinfo))
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Heure synchronisée.");
}

bool getCurrentTime(struct tm *timeinfo) {
    return getLocalTime(timeinfo);
}

String getCurrentTimestamp()
{
    struct tm timeinfo;

    if (!getCurrentTime(&timeinfo))
    {
        return "";
    }

    char buffer[20];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    return String(buffer);
}

void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connexion au WiFi ...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connexion au WiFi réussie.");
}

void initFirebase() {
    config.api_key = API_KEY;
    config.token_status_callback = tokenStatusCallback;

    auth.user.email = "";
    auth.user.password = "";
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("Connexion à Firebase réussie.");
    }
    else
    {
        Serial.printf("Connexion à Firebase échouée: %s\n", config.signer.signupError.message.c_str());
    }

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}