#include "services.h"
#include "states.h"
#include <addons/TokenHelper.h>

FirebaseAuth auth;
FirebaseConfig config;
FirebaseData fbdo;

const int MAX_EVENTS = 10;
String eventQueue[MAX_EVENTS][2];
int eventCount = 0;

// Source pour la stratégie du temps :
// https://youtu.be/CZH4DJAtAVU?si=vRSGo8eH1al1UC0o
void initTime()
{
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

bool getCurrentTime(struct tm *timeinfo)
{
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

void initWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connexion au WiFi ...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connexion au WiFi réussie.");
}

void initFirebase()
{
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

void logEvent(String eventType)
{
    if (eventCount >= MAX_EVENTS)
    {
        Serial.println("File d'attente Firestore pleine!");
        return;
    }

    eventQueue[eventCount][0] = eventType;
    eventQueue[eventCount][1] = getCurrentTimestamp();
    eventCount++;
    Serial.printf("Événement ajouté à la file d'attente: %s à %s\n", eventType.c_str(), eventQueue[eventCount - 1][1].c_str());
}

void updateServices()
{
    // À cause que l'envoi Firestore est synchrone (bloque la loop) on le lance seulement
    // lorsque le coffre est idle, pour ne pas interrompre le servo moteur, la matrice
    // ou l'écran 4 digits.
    if (eventCount == 0 || !isReadyForFirebase() || !Firebase.ready())
    {
        return;
    }

    FirebaseJson content;
    content.set("fields/type/stringValue", eventQueue[0][0]);
    content.set("fields/horodatage/stringValue", eventQueue[0][1]);
    content.set("fields/coffre/stringValue", "coffre1");

    if (Firebase.Firestore.createDocument(
            &fbdo,
            PROJECT_ID,
            "",
            DOCUMENT_PATH,
            content.raw()))
    {
        Serial.println("Evenement enregistré!");

        for (int i = 0; i < eventCount - 1; i++)
        {
            eventQueue[i][0] = eventQueue[i + 1][0];
            eventQueue[i][1] = eventQueue[i + 1][1];
        }

        eventCount--;
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}