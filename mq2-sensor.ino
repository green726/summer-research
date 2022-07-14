  #include <MQ2.h>
  
  int pin = A0;
  
  MQ2 mq2(pin);

  float lpgArr[50];

  float coArr[50];

  float smokeArr[50];

  int index = 0;
  
  void setup(){
    mq2.begin();
    Serial.begin(9600);
    Serial.setTimeout(2000);

    Serial.println("mq2 sensor successfully connected - send data in the serial monitor to print all gathered data - lpg to print lpg - co to print co - smoke to print smoke");
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
    // float* values = mq2.read(true); //true to print the values in the Serial

    float lpg = mq2.readLPG();
  
    float co = mq2.readCO();
  
    float smoke = mq2.readSmoke();

    if (index <= 50) {
      lpgArr[index] = lpg;
      coArr[index] = co;
      smokeArr[index] = smoke;
    }

    String input = Serial.readStringUntil('\n');

    if (input == "data") {
      printArr(lpgArr, "lpg num ");
      printArr(coArr, "co num ");
      printArr(smokeArr, "smoke num ");
    } else if (input == "lpg") {
      printArr(lpgArr, "lpg num ");
    }
    else if (input == "co") {
      printArr(coArr, "co num ");
    } 
    else if (input == "smoke") {
        printArr(smokeArr, "smoke num ");
    }


    index++;

    // delay(1000);
  }
