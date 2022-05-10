
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31_room = Adafruit_SHT31();
Adafruit_SHT31 sht31_box = Adafruit_SHT31();

// the setup routine runs once when you press reset
  unsigned long seconds_on = 0;   // time elapsed in seconds
  
void setup() {
  // initilize cierial communication at 9600 bits per second;
  Serial.begin(9600);
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31_box.begin(0x44)) {   // Set to 0x44 for alternate i2c addr
    Serial.println("Couldn't find SHT31_box");
  while (1) delay(1);
  }
  if (! sht31_room.begin(0x45)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31_room");
  while (1) delay(1);
  }
  
  Serial.print("There may be a voltage offset");
  Serial.println("Time (s), Voltage, Box Temp C, Box % RH, Room Temp C, Room % RH"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  float tb = sht31_box.readTemperature();
  float hb = sht31_box.readHumidity();
  float tr = sht31_room.readTemperature();
  float hr = sht31_room.readHumidity();

  int sensorValue = analogRead(A0);
  //Convert analog reading voltage (which goes forom 0-1023V) to a voltage in the range of 0-5V.
  float voltage = sensorValue * (5.0/1023.0);

  Serial.print( seconds_on );
  Serial.print( ", " );
  
  // print out value 
  Serial.print ((voltage + .02183427121212121213)/.0032728788636363636); // 8/6 fitting from 100 V to 420 V on the front panel
  Serial.print(", ");
  Serial.print(tb);
  Serial.print(" C, ");
  Serial.print(hb);
  Serial.print(" %,");
  Serial.print(tr);
  Serial.print(" C, ");
  Serial.print(hr);
  Serial.println(" %");

   delay( 1000 );
   seconds_on++;
}
