// Watch video here: https://www.youtube.com/watch?v=O5Ye5xJF44c

/* 
GSR connection pins to Arduino microcontroller

Arduino           GSR

GND               GND
5V                VCC
A2                SIG

D13             RED LED

*/

/*
 GSR, standing for galvanic skin response, is a method of 
 measuring the electrical conductance of the skin. Strong 
 emotion can cause stimulus to your sympathetic nervous 
 system, resulting more sweat being secreted by the sweat 
 glands. Grove – GSR allows you to spot such strong emotions 
 by simple attaching two electrodes to two fingers on one hand,
 an interesting gear to create emotion related projects, like 
 sleep quality monitor. http://www.seeedstudio.com/wiki/Grove_-_GSR_Sensor
 */

// const int LED = 13;
const int GSR= A0;
int sensorValue = 0;
int gsrAvg = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(100);
  }
  gsrAvg = sum / 10;
  Serial.print("GSR Average: ");
  Serial.println(gsrAvg);
//  int humanResistance = ((1024 + 2*gsrAvg) * 10000) / (516 - gsrAvg);
//  Serial.print("Human Resistance: ");
//  Serial.println(humanResistance);
}
