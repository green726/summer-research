/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

// Adafruit_BME280 bme; // I2C
Adafruit_BME280 bme(BME_CS); // hardware SPI
// Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

float altArr[50];

float pressureArr[50];

float humidityArr[50];

float tempArr[50];

int index = 0;

void setup() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.setTimeout(1000);
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(1);
    }
    
    Serial.println("BME280 Connected Successfully - send data in the serial monitor to print the gathered sensor data");
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

    if (index <= 50)  {
      tempArr[index] = bme.readTemperature();
      humidityArr[index] = bme.readHumidity();
      pressureArr[index] = bme.readPressure() / 100.0f;
      altArr[index] = bme.readAltitude(SEALEVELPRESSURE_HPA);
    }

    String input = Serial.readStringUntil('\n');

    if (input == "data") {
      printArr(tempArr, "temp num ");
      printArr(humidityArr, "hum num ");
      printArr(pressureArr, "pressure num ");
      printArr(altArr, "alt num ");
    }

    index++;
}
