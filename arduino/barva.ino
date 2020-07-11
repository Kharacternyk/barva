/*
 * Inspects value provided by barva.
 * Puts high voltage on first (value / STEP) pins,
 * starting from MIN_PIN and never exceeding MAX_PIN.
 */

#define MIN_PIN 3
#define MAX_PIN 12
#define STEP    4

int value;

void update() {
    for (int pin = MIN_PIN; pin <= MAX_PIN; ++pin) {
        if ((pin - MIN_PIN + 1) * STEP <= value) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
    }
}

void setup() {
    for (int pin = MIN_PIN; pin <= MAX_PIN; ++pin) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        value = Serial.read();
        Serial.println(value, DEC);
        update();
    }
}
