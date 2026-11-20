#include "constants.h"
#include "buttons.h"
#include "display.h"
#include "matrix.h"
#include "servo.h"
#include "states.h"
#include "services.h"
#include "code.h"

// ChatGPT a corrigé le dépassement : le handshake TLS/ECDSA de Firebase dépassait la stack par défaut de 8 Ko.
// [Voir prompt ci-dessous.]
size_t getArduinoLoopTaskStackSize(void)
{
    return 16384;
}

void setup()
{
    Serial.begin(9600);

    // TM1637
    initDisplay();
    Serial.println("Écran TM1637 initialisé.");

    // NeoMatrix
    initMatrix();
    Serial.println("Matrice NeoPixel initialisée.");

    // Servo moteur
    initServo();
    Serial.println("Servo moteur initialisé.");

    // Boutons
    initButtons();
    Serial.println("Boutons initialisés.");

    // Services
    initWiFi();
    initFirebase();
    initTime();
    Serial.println("Services initialisés.");
}

void loop()
{
    updateState();
    updateServo();
    updateMatrix();
    updateServices();
}

/* Prompt utilisé pour générer le code ci-dessus :
 |   Peux-tu m'expliquer cette erreur et comment faire pour la corriger ?
 |   Erreur : 
 |   Guru Meditation Error: Core  1 panic'ed (Unhandled debug exception). 
 |   Debug exception reason: Stack canary watchpoint triggered (loopTask) 
 |   Core  1 register dump:
 |   PC      : 0x4011387e  PS      : 0x00060e36  A0      : 0x801159f4  A1      : 0x3ffb01f0  
 |   A2      : 0x3ffb0d48  A3      : 0x3ffb0e50  A4      : 0x3ffb0e74  A5      : 0x00000000  
 |   A6      : 0x000000c0  A7      : 0x3ffb01f0  A8      : 0x00002c1d  A9      : 0x3ffb0700  
 |   A10     : 0x97db474a  A11     : 0x000001b8  A12     : 0x97db474a  A13     : 0x3ffb0704  
 |   A14     : 0x04fe6f29  A15     : 0x00002c1d  SAR     : 0x00000018  EXCCAUSE: 0x00000001  
 |   EXCVADDR: 0x00000000  LBEG    : 0x400894f8  LEND    : 0x40089514  LCOUNT  : 0x00000000  
 |
 |
 |   Backtrace: 0x4011387b:0x3ffb01f0 0x401159f1:0x3ffb0c50 0x40116d96:0x3ffb0e40 0x401177df:0x3ffb0f00 0x40117e44:0x3ffb1160 0x40107fe5:0x3ffb1290 0x4011939c:0x3ffb12e0 0x40118f3b:0x3ffb15e0 0x400e1321:0x3ffb1750 0x400e4383:0x3ffb19b0 0x400dfd46:0x3ffb1c40 0x400e0061:0x3ffb1c80 0x4012d5d2:0x3ffb1cc0 0x4012cee7:0x3ffb1d30 0x4012c96e:0x3ffb1d90 0x4012b2ea:0x3ffb1df0 0x4012a7fd:0x3ffb1e40 0x401233ad:0x3ffb1e90 0x401232ff:0x3ffb1ec0 0x400ec9d9:0x3ffb1ef0 0x400ecbc5:0x3ffb1f30 0x400eccdb:0x3ffb1f70 0x400f1d92:0x3ffb1fa0 0x400d8f63:0x3ffb2010 0x400d33f2:0x3ffb2050 0x400d2e04:0x3ffb20d0 0x400d15ab:0x3ffb20f0 0x4014297e:0x3ffb2120 0x4008f22d:0x3ffb2150
 |
 |
 |
 |
 |   ELF file SHA256: fcda6d8fd
 |
 |   Rebooting...
*/