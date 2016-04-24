// dexters KK2.0 automatic flight system addon board software //
// debug sketch 11-12-2014 works ok //
// last PID and state's saved in eeprom true gui button // 
// responses OK //

/*
 ********************************************************************
 x            x
 x&x          x&x
 X           X
 .         .
 .       . 
 .     .                   CHECK KK2.0 RECIEVER INPUTS 
 .   .                  *********************************
 < > ****************** HEIGHT SENSOR PLACED UNDER QUAD  
 < >                   *********************************
 .   .                     USE THIS ONLEY WHEN NOVICE 
 .     .
 .       .
 .         .
 X          X
 x&x        x&x
 x          x                 
 ********************************************************************
 // ALL QUADS NEED TO BE TUNED //
 // 
 */

#include <Servo.h> 
#include <NewPing.h> 
#include <EEPROM.h>
#include <PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>   // i added for own use a digital compas for just under 4 dollar so i putt this also in this sketch , an GUI also ,,
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // max sensor value 500 means 5 meter 
#define addr0  0
#define addr1  1
#define addr2  2
#define addr3  3
#define addr4  4
#define addr5  5
#define addr6  6
#define addr7  7
#define addr8  8
#define led  13
#define piezo  10
int auxv,auxs,val,horim,horiz,vertm,verti,auxset,decent,Kp,Ki,Kd,pid,autodelay,autoheigth; 
double cm,throtv,throts,system,mem1,sys,height1,height,up,sensor,trh1,trh2,trh3,trh4,Setpoint,trhm1,trhm2;
PID altPID(&height1, &throts, &Setpoint,Kp,Ki,Kd, DIRECT);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
int safety =1; // safety switch value//
int signal =0; 
Servo throttle,aux;  
void setup() {
  mag.begin();
  Serial.begin(57600); // starting serial port data for APC220 wireles tx rx baud rate 57600 for GUI //  
  aux.attach(7);   // servo conection out pin 7 to kk2.0 aux input //
  throttle.attach(8); // servo conection out pin 8 to kk2.0 throttle input //
  aux.writeMicroseconds(auxset);   // set aux output to autolevel on on kk2.0 //
  pinMode(led, OUTPUT);
  pinMode(piezo,OUTPUT);
  pinMode(4, INPUT); 
  pinMode(5, INPUT); 
  pinMode(6, INPUT); 
  pinMode(9, INPUT); 
  altPID.SetMode(AUTOMATIC);
  digitalWrite(led, LOW);   // turn the LED on 
  digitalWrite(piezo, LOW);   // turn the PIEZO on 
  delay(1000);               // wait for a second
  digitalWrite(led, HIGH);   // turn the LED on 
  digitalWrite(piezo, HIGH);   // turn the PIEZO on 
  delay(1000);               // wait for a second
  digitalWrite(led, LOW); 
  auxset =    EEPROM.read(addr1 )*10;
  decent =    EEPROM.read(addr2 )*10;
  autoheigth = EEPROM.read(addr3);
  autodelay =  EEPROM.read(addr4);
  Kp   =    EEPROM.read(addr5 );
  Ki   =    EEPROM.read(addr6 );
  Kd   =    EEPROM.read(addr7 );
  pid  =   EEPROM.read(addr8 );
  if (auxset < 1000 || auxset > 1800 )auxset =1000;
  if (Kp>20)Kp =2;
  if (Ki>20)Ki =5;
  if (Kd>20)Kd =1;
  if (Kp<=0)Kp =2;
  if (Ki<=0)Ki =5;
  if (Kd<=0)Kd =1;
  if (decent>500)decent =250;
  trhm1 =10.00; // min for pid throttle output constrain you can change it ,this builds a pid output constrain from input throttle - this value  
  trhm2 =10.00; // max for pid throttle output constrain you can change it ,this builds a pid output constrain from input throttle + this value 
  system = 0;
  throtv = pulseIn(6, HIGH, 25000); //checking throttle input from rx
  auxv = pulseIn(5, HIGH, 25000); //checking throttle input from rx 
  if (throtv > 1025||auxv > 1300) { // !! if throttle is higher then 1025 then safety goes first and when aux switch not in good pos it wil not turn on !! //
    throttle.writeMicroseconds(1000); // throttle on 0 before start 
    delay (1000);  
    safety =1; // safety wil be fase 1 = disable trhottle input , and output 0 throttle  = disabled mode //
    return;
  }
  else if (throtv < 1025||auxv < 1300)
  {
    safety =2; // if input throttle = near 0 then safety wil be fase 2 = working quadcopter going to safety fase 3 later = addon board armed mode //
  }
}
void loop() {
  { 
    sensors_event_t event; 
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    float declinationAngle = 0.22;
    heading += declinationAngle;
    if(heading < 0)
      heading += 2*PI;   
    if(heading > 2*PI)
      heading -= 2*PI;
    float headingDegrees = heading * 180/M_PI; 
    // new sensor stuff above
    trh1 = throtv - 10.5; // value - throttle for min throttle constrain you can change this //
    trh2 = throtv + 15.5; // value + throttle for max throttle constrain you can change this //
    if (autoheigth >5) autoheigth =0; 
    if (autodelay >5) autodelay =0;
    if (pid >5) pid =0; 
    val = Serial.read() - '0';
    delay (25);
    if (val == 55) autoheigth = autoheigth + 5 ; 
    if (val == 56) autodelay = autodelay + 5 ; 
    if (val == 17) pid = pid + 5 ; 
    if (val == 58) height = height +100 ; 
    if (val == 46) height = height -100; 
    if (val == 2)  auxset =1000;
    if (val == 3)  auxset =1800;
    if (val == 4)  decent = decent +10;
    if (val == 5)  decent = decent -10;
    if (val == 63)  Kp = Kp -1; 
    if (val == 69)  Kp = Kp +1; 
    if (val == 27)  Ki = Ki -1; 
    if (val == 28)  Ki = Ki +1; 
    if (val == 22) Kd = Kd -1;   
    if (val == 34) Kd = Kd +1;  
    if (val == 8) digitalWrite(led,LOW);
    if (val == 9) digitalWrite(piezo,HIGH);
    if (val == 1) {
      EEPROM.write(addr1,auxset/10);
      EEPROM.write(addr2,decent/10);
      EEPROM.write(addr3,autoheigth);
      EEPROM.write(addr4,autodelay);
      EEPROM.write(addr5,Kp) ;
      EEPROM.write(addr6,Ki) ;
      EEPROM.write(addr7,Kd) ;
      EEPROM.write(addr8,pid) ;
      auxset =    EEPROM.read(addr1 )*10;
      decent =    EEPROM.read(addr2 )*10;
    } 
    if (val == 6) {
    // ad a function to one of the function buttons conected to the flight case buttons also   
    }
    if (val == 7) {
    // ad a function to one of the function buttons conected to the flight case buttons also  
    }
    sensor = cm/ US_ROUNDTRIP_CM; 
    Serial.print((char)1); 
    Serial.print (throts);
    Serial.print((char)2);
    Serial.print (throtv);
    Serial.print((char)3);
    Serial.print (height);
    Serial.print((char)4);
    Serial.print (auxv);
    Serial.print((char)5);
    Serial.print (auxset);
    Serial.print((char)6);
    Serial.print (cm); 
    Serial.print((char)7);
    Serial.print (sensor);
    Serial.print((char)8); 
    Serial.print (safety); 
    Serial.print((char)9); 
    Serial.print (horiz);
    Serial.print((char)10);
    Serial.print (verti);
    Serial.print((char)11);
    Serial.print (decent);
    Serial.print((char)12); 
    Serial.print (trh1);  
    Serial.print((char)13);
    Serial.print (trh2);
    Serial.print((char)14);
    Serial.print (headingDegrees);
    Serial.print((char)15);
    Serial.print (autoheigth);
    Serial.print((char)16);
    Serial.print (autodelay);
    Serial.print((char)17);
    Serial.print (pid);
    Serial.print((char)18);
    Serial.print (Kp);
    Serial.print((char)19);
    Serial.print (Ki);
    Serial.print((char)20);
    Serial.print (Kd);
    Serial.print((char)21);
    Serial.flush();
    trh3 = throtv - trhm1;
    trh4 = throtv + trhm2;
    altPID.SetOutputLimits(trh3,trh4);
    digitalWrite(piezo,LOW);
    horim = pulseIn(4, HIGH, 25000); //checking gimbal horizontal input 
    auxv = pulseIn(5, HIGH, 25000); //checking aux input
    throtv = pulseIn(6, HIGH, 25000); //checking throttle input
    vertm = pulseIn(9, HIGH, 25000); //checking gimbal vertical  input  i need to a bigger pinned arduino to bypass these also for other cool stuff ??
    horiz =map(horim, 1700, 1300,-20,100); 
    verti =map(vertm, 1700, 1300,-20,100);
    cm = sonar.ping();
    aux.writeMicroseconds(auxset);  
    throtv = pulseIn(6, HIGH, 25000); 
    auxv = pulseIn(5, HIGH, 25000); 
    if(cm >0)height1 = cm;
    if (auxv < 1300 && safety == 2){ // = normal mode ?? when switch back and throttle in use , watch throttle when switching back from auto mode !! !!!!
      if (autoheigth ==0) height = height1; 
      Setpoint= height;
      throttle.writeMicroseconds(throtv);
      digitalWrite(led, HIGH);  
      system =throtv ; 
      \ 
      sys =throtv;
    }
    else if (auxv > 1300 && pid == 0){ // PID mode still working this one out ! 
      cm = sonar.ping();
      altPID.Compute();
      throttle.writeMicroseconds(throts);
    }
    else if (auxv > 1300 && pid == 5){ 
      mem1 =sys;  
      if(height<height1){ 
        system = sys - 0.35;// take speed down by 0.35 digit of the system you can change this// 
        throts = mem1;
        sys = constrain(system,trh1,trh2);
        throttle.writeMicroseconds(sys);  
        digitalWrite(led, HIGH);
        if (autodelay ==5) delay (decent); 
      }
      if(height>height1){     
        system = sys + 0.55  ;// take speed up by 0.55 digit of the system you can change this // 
        throts = mem1; 
        sys = constrain(system,trh1,trh2); 
        throttle.writeMicroseconds(sys); 
        digitalWrite(led, LOW);
        digitalWrite(piezo,HIGH);
      }
    }
  }
}
















