#include "services.h"
#include <addons/TokenHelper.h>

FirebaseAuth auth; 
FirebaseConfig config; 
FirebaseData fbdo;

void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi ...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void initFirebase() {
    config.api_key = API_KEY;
    config.token_status_callback = tokenStatusCallback;

    auth.user.email = "";
    auth.user.password = "";
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("Firebase sign up successful");
    }
    else
    {
        Serial.printf("Firebase sign up failed: %s\n", config.signer.signupError.message.c_str());
    }

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}