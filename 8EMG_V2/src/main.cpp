#include <Arduino.h>
#include <Wire.h>
#include <ADS1X15.h>
#include "ICM42605_V2.h"

/* ADC */
//Class
ADS1115 ADC1(ADS1015_ADDRESS);
ADS1115 ADC2(0x49); //Verificar** 

uint16_t sensorEMG1;
uint16_t sensorEMG2;
uint16_t sensorEMG3;
uint16_t sensorEMG4;
uint16_t sensorEMG5;
uint16_t sensorEMG6;
uint16_t sensorEMG7;
uint16_t sensorEMG8;

/*IMU */
SPIClass* vspi = new SPIClass(VSPI);
ICM42605 IMU(*vspi,5);
uint8_t Ascale = AFS_2G, Gscale=GFS_250DPS, AODR=AODR_1000Hz, GODR=GODR_1000Hz;
int status;
int16_t ICM42605Data[7];

// Timing variables
unsigned long previousMillis = 0;
const long interval = 5; // 200Hz -> 5ms interval

void setup() {
  Serial.begin(115200);
  Serial.println("8EMG V2");
  delay(500);
  Wire.begin();

  /* ADC */
  ADC1.begin();
  ADC1.setGain();
  ADC2.begin();
  ADC2.setGain();

  /* IMU */
  status = IMU.begin(Ascale, Gscale, AODR, GODR);
  if(status < 0){
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  // Get the current time in milliseconds
  unsigned long currentMillis = millis();
  
  // Check if it's time to take a new measurement
  if (currentMillis - previousMillis >= interval) {
    // Save the time of the last measurement
    previousMillis = currentMillis;

    // Data Get
    float f1 = ADC1.toVoltage(1);
    float f2 = ADC2.toVoltage(1);
    sensorEMG1 = ADC1.readADC(0);
    sensorEMG2 = ADC1.readADC(1);
    sensorEMG3 = ADC1.readADC(2);
    sensorEMG4 = ADC1.readADC(3);
    sensorEMG5 = ADC2.readADC(0);
    sensorEMG6 = ADC2.readADC(1);
    sensorEMG7 = ADC2.readADC(2);
    sensorEMG8 = ADC2.readADC(3);
    IMU.readSensor(ICM42605Data);

  if(sensorEMG7>=65535){sensorEMG7=0;}
  if(sensorEMG8>=65535){sensorEMG8=0;}
  
    \
    // Serial Print
    String dataString = String(IMU.getAccelX(), 6) + "," +
                        String(IMU.getAccelY(), 6) + "," +
                        String(IMU.getAccelZ(), 6) + "," +
                        String(IMU.getGyroX(), 6) + "," +
                        String(IMU.getGyroY(), 6) + "," +
                        String(IMU.getGyroZ(), 6) + "," +
                        String(IMU.getTemperature_C(), 6) + "," +
                        String(sensorEMG1 * f1, 3) + "," +
                        String(sensorEMG2 * f1, 3) + "," +
                        String(sensorEMG3 * f1, 3) + "," +
                        String(sensorEMG4 * f1, 3) + "," +
                        String(sensorEMG5 * f2, 3) + "," +
                        String(sensorEMG6 * f2, 3) + "," +
                        String(sensorEMG7 * f2, 3) + "," +
                        String(sensorEMG8 * f2, 3) + "," +
                        String(currentMillis);
    Serial.println(dataString);
  }
}