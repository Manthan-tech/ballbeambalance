#include <Servo.h>
Servo manthanservo;
int sp=9;
int trigPin = 5;    // Trigger
int echoPin = 6;    // Echo
long duration, cm, inches;
int lastcm=20;
int pos=72;


double kp=4;
double ki=0;
double kd=800;
double error=0;
double Setpoint=23;
unsigned long currentTime, previousTime;
double elapsedTime;
double cumError, rateError;
 double lastError;



 
void setup() {
 
  Serial.begin (10500);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  manthanservo.attach(sp);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(6);
  digitalWrite(trigPin, LOW);
 
 
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
 
  cm = (duration/2) / 29;     
  
  
 
  int disp=lastcm-cm;
  if(disp<0)
  disp=-disp;
  if(cm>46)
  cm=24;
  Serial.print(cm);
  Serial.print(" cm ");
if(disp<10)
  {

 
  double pid=computePID((double)cm);
  /*int d=constrain(cm,4,60);
  if(d<24)
  pos=map(d,4,24,60,74);
  else if(d>33)
  pos=map(d,33,58,76,82);
  else
  pos=75;.
  manthanservo.write(pos);
  Serial.print(pos);
    Serial.println();
    delay(50);
    
  }
  */
  pid=(int)pid;
  
  pid=map(pid,-110,110,40,120);
 
Serial.println(pid);
manthanservo.write(pid);
}
lastcm=cm;
}
double computePID(double inp){     
        currentTime = millis();                //get current time
        elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
        error = Setpoint - inp;                                // determine error
                       
        rateError = (error - lastError)/elapsedTime;   // compute derivative
 /*if(-3< error && error < 3)
    {
      cumError += error * elapsedTime;
      delay(50);
    }
    else
    {
      cumError = 0;
    }*/
        double out = kp*error + ki*cumError + kd*rateError;                 
 
        lastError = error;                                
 // out=constrain(out,-25,25);
         Serial.println(out);
    
        return out;                                        
}
