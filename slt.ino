// This file shows an example implementation of a low-pass filter on an Arduino.
// Note that there are many potential improvements to this code.

float xn1 = 0;
float yn1 = 0;
float xn0 = 0;
float yn0 = 0;
int k = 0;
int sensorPin = A0;
int sensorValue = 0;
int stepcount = 0;
int t1 = 0;
int t2 = 0;
int t3 = 0;
int clc_st=0;
int hld_st=0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Test signal
  float t = micros() / 1.0e6;
  //float xn = sin(2*PI*2*t) + 0.2*sin(2*PI*50*t);
  float xn = analogRead(sensorPin);
  // Compute the filtered signal
  float yn = 0.969 * yn1 + 0.0155 * xn + 0.0155 * xn1;

  //delay(1);
  xn1 = xn;
  yn1 = yn;

  if (k % 3 == 0) {
    // This extra conditional statement is here to reduce
    // the number of times the data is sent through the serial port
    // because sending data through the serial port
    // messes with the sampling frequency

    // Output
    Serial.print(xn);
    Serial.print(" ");
    Serial.print(2 * yn);
    Serial.print(" ");
    Serial.println(stepcount);
  }



  if (xn1 > 400) {
    if (xn0 < 400) {
      stepcount = stepcount + 1;
      t1 = millis();
      
      
    }

  }

  else if (xn1 < 270) {
    if (xn0 > 270) {
      t2 = millis();
      if((t2-t1)<500){
      clc_st=1;
      hld_st=0;
      Serial.println("click");
      delay(1000);
    }

    else{
      hld_st=1;
      clc_st=0;
      Serial.println("hold");
      delay(1000);
      }
    }
  }

  else{
    clc_st=0;
    hld_st=0;
    }

  xn0 = xn1;

  
 

  k = k + 1;


  //delay(10);
}
