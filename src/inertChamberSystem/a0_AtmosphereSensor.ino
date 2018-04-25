/**
 * InertChamberSystem
Copyright (C) 2018  SamyLabs S.L.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
**/


#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_BME280.h>


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define DEFAULT_OXIGEN A0

class AtmosphereSensor{

private_
Adafruit_BME280 bme_; // I2C

// pin del oxigeno
int oxigen_ =A0;

AtmosphereSensor(int oxigen = DEFAULT_OXIGEN){
	bme_.begin;
	oxigen_= oxigen;
	pinMode(oxigen,ANALOG_INPUT);
}


public: 
float readOxigen(){
	float sensorVoltage=0;
    float value_O2 =0;
    float sensorValue =(float) analogRead(A0);
    sensorVoltage =(sensorValue/1024)*5.0;
    sensorVoltage = sensorVoltage/201*10000;
    value_O2 = sensorVoltage/7.43;    
	return value_O2;
}
	
float readPressure(){
	return bme_.readPressure();
}	

float readPressure(){
	return bme_.readPressure();
}
	
float readHumidity(){
	bme_.readHumidity();
}

float readTemperature()
{
	bme_.readTemperature();
}

};
