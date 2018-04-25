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

class inertChamber{

public : 

// Estados posibles
const int STOPPED=0;
const int FILLING=1;
const int STABILIZING=2;
const int WORKING=3;
const int STOPPING=4;

private: 


// estado
int status_;
int lastStatus_;

// elementos del sistema
int gasValve_; 
int airValve_; // normalmente cerrada.
int recirculationValve_; 
int pump_;


public: 

	int inertChamber( int gasValve, int airValve, int recirculationValve, int pump ){
		gasValve_= gasValve; 
		airValve_= airValve; 
		int recirculationValve_=recirculationValve; 
		int pump_= pump;
		
		pinMode(gasValve_,OUTPUT);
		pinMode(airValve_,OUTPUT);
		pinMode(recirculationValve_,OUTPUT);
		pinMode(recirculationValve_,OUTPUT);
	}

	void setStatus(int status_){
		this.status_=status_;
		switch (status_){
			case FILLING: 
				runFilling();
			break;
			case STABILIZING: 
				runStabilizing();
			break;
			case WORKING:
				runWorking();
			break;
			case STOPPING: 
				runStopping();
			break;
			default: 
				runStopped();
			break;
		}
	}
	
	void getStatus(){
		return status_;
	}
	
	void runStopped(){
		digitalWrite(gasValve_, LOW); 
		digitalWrite(airValve_, LOW); 
		digitalWrite(recirculationValve_, LOW); 
		digitalWrite(pump_, LOW);
	}
	
	void runFilling(){
		digitalWrite(gasValve_, HIGH); 
		digitalWrite(airValve_, HIGH); 
		digitalWrite(recirculationValve_, LOW); 
		digitalWrite(pump_, LOW);
	}
	
	void runStabilizing(){
		digitalWrite(gasValve_, HIGH); 
		digitalWrite(airValve_, LOW); 
		digitalWrite(recirculationValve_, HIGH); 
		digitalWrite(pump_, HIGH);
	}
	
	void runWorking(){
		digitalWrite(gasValve_, LOW); 
		digitalWrite(airValve_, HIGH); 
		digitalWrite(recirculationValve_, HIGH); 
		digitalWrite(pump_, HIGH);
	}
	
	void runStopping(){
		void runWorking(){
		digitalWrite(gasValve_, LOW); 
		digitalWrite(airValve_, HIGH); 
		digitalWrite(recirculationValve_, LOW); 
		digitalWrite(pump_, LOW);	
	}
	
	void releasePressure(){
		digitalWrite(airValve_, LOW); 
		delay(100);
		digitalWrite(airValve_, HIGH); 
	}
};
