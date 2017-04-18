#ifndef __KFL_LIB__
#define __KFL_LIB__
#endif

void blink(int led, int times, int inteval_ms = 100) {
    digitalWrite(led, LOW);
    for (; times > 0; times--) {
        digitalWrite(led, HIGH);
        delay(inteval_ms);
        digitalWrite(led, LOW);
        delay(inteval_ms);
    }
}

float getTemperatureInC(int sensorPin, float vMax) {
    // take two readings and discard the first to make it more accurate
    int reading = analogRead(sensorPin);
    reading = analogRead(sensorPin); 
    float voltage = reading * vMax / 1024.0;
    float temperatureC = (voltage - 0.5) * 100 ;
    return temperatureC;
}

