#include <Arduino.h>

#include <HX711.h>
#include <Keypad.h>
#include <Preferences.h>

#define LOADCELL_DOUT_PIN 32
#define LOADCELL_SCK_PIN 33
#define BUZZER_PIN 25

HX711 scale;
float tareWeight = 0.0;
const float MAX_WEIGHT = 50.0;
const float WARNING_THRESHOLD = 45.0;

Preferences prefs;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {18, 19, 21, 22};
byte colPins[COLS] = {5, 17, 16, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String sequenceBuffer = "";
bool settingTare = false;

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale();
    scale.tare();

    prefs.begin("gas-scale", false);
    tareWeight = prefs.getFloat("tare", 0.0);
    prefs.end();
    
    Serial.println("Ready.");
}