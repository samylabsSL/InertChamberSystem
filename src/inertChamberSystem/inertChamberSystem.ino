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

// sensores
int OxigenPin = A0;
AtmosphereSensor sensor(OxigenPin);

// Camara inerte
int gasValvePin=R1; 
int airValvePin = R2; 
int recirculationValvePin =R3; 
int pumpPin =R4 ;
InertChamber chamber(gasValvePin,airValvePin,recirculationValvePin, pumpPin);

// UMBRALES DE CAMBIO DE ESTADO
float MIN_O2_FILLING;
float MIN_HUMIDITY_FILLING;

float MIN_O2_STABILIZING;
float MIN_HUMIDITY_STABILIZING;
float MAX_PRESSURE_STABILIZING;

float MAX_O2_WORKING;
float MAX_HUMIDITY_WORKING;
float MIN_PRESSURE_WORKING;

float MAX_PRESSURE;

// Variables 
String command="";

void setup(){
	Serial.begin(9600);
}

void run(){
	int status = chamber.getStatus();
	// procesamos los comandos
	if(command.equalsIgnoreCase(F("start"))
	{
		if (status== chamber.STOPPED){
			chamber.setStatus(chamber.FILLING);			
		}else{
			Serial.println("start : Chamber already started");
		}
		return; 
	}if(command.equalsIgnoreCase(F("stop")){
		if (status!= chamber.STOPPED){
			chamber.setStatus(chamber.STOPPED);
		}else{
			Serial.println("start : Chamber already stopped");
		}
		return; 
	}
	command = "";	
	
	
	float actualPressure = sensor.readPressure();
	if(actualPressure> MAX_PRESSURE)
	{
		chamber.releasePressure();
	}
	
	// Si no, evaluamos segun estado de la camara y los sensores
	float actualOxigen = sensor.readOxigen();
	
	float actualHumidity = sensor.readHumidity();
	
	switch (status_){
		case FILLING: 
			if (actualOxigen < MIN_O2_FILLING &&
				actualOxigen < MIN_HUMIDITY_FILLING){
					chamber.setState(STABILIZING);
			}
		break;
		case STABILIZING: 
			if (actualOxigen < MIN_O2_STABILIZING &&
				actualOxigen < MIN_HUMIDITY_STABILIZING &&
				actualOxigen < MAX_PRESSURE_WORKING){
					chamber.setState(WORKING);
			}
		break;
		case WORKING:
			if (actualOxigen > MIN_O2_WORKING &&
				actualOxigen > MIN_HUMIDITY_WORKING &&
				actualOxigen > MIN_PRESSURE_WORKING	){
					chamber.setState(STABILIZING);
			}
		break;
		case STOPPING: 
			runStopping();
		break;
		default: 				
		break;
	}
	
}

void serialEvent()
{
	if (Serial.available()){
		command = Serial.readStringUntil('\n');
	}
}

void setState(int status)
{
	switch (status){
		case chamber.FILLING: 
			Serial.println(F("Status : FILLING"));
		break;
		case chamber.STABILIZING: 
			Serial.println(F("Status : STABILIZING"));
		break;
		case chamber.WORKING:
			Serial.println(F("Status : WORKING"));
		break;
		case chamber.STOPPING: 
			Serial.println(F("Status : STOPPING"));
		break;
		case chamber.STOPPED: 
			Serial.println(F("Status : STOPPED"));
		break;
		default:
		break;
	}
	chamber.setStatus(status);
}


