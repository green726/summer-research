#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>

SensirionI2CScd4x scd4x;

float co2Arr[50];
float humArr[50];
float tempArr[50];

int index = 0;

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

void setup() {

    Serial.begin(9600);
    while (!Serial) {
        delay(100);
    }

    Serial.setTimeout(5000);

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);


    scd4x.startPeriodicMeasurement();

    Serial.println("scd40 sensor successfully connected - send data in the serial monitor to print all gathered data - send hum for humidity - temp for temperature - co2 for co2");
}

  void printArr(float arr[], String msg) {
    for (int i = 0; i < index; i++) {
      Serial.print(msg);
      Serial.print(i);
      Serial.write(" with value of: ");
      Serial.println(arr[i]);
    }
  }


void loop() {
    // Read Measurement
    uint16_t co2 = 0;
    float temp = 0.0f;
    float hum = 0.0f;

    scd4x.readMeasurement(co2, temp, hum);

    if (index <= 50) {
      humArr[index] = hum;
      co2Arr[index] = co2;
      tempArr[index] = temp;
    }

    String input = Serial.readStringUntil('\n');

    if (input == "data") {
      printArr(humArr, "hum num ");
      printArr(co2Arr, "co2 num ");
      printArr(tempArr, "temp num ");
    } else if (input == "hum") {
      printArr(humArr, "hum num ");

    } else if (input == "co2") {
      printArr(co2Arr, "co2 num ");

    } else if (input == "temp") {
      printArr(tempArr, "temp num ");

    }

    index++;
}

