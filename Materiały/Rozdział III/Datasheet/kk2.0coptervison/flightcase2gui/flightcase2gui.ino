#include <EEPROM.h>
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
byte cbupw[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001
};
byte cbdown[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111
};

byte cbmidleup[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111
};

byte cbmidledown [8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte cbupright [8] = {
  0b11111,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte cbdownright [8] = {
  0b11111,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte cbmeterm [8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte cbmeterr [8] = {
  0b00000,
  0b01010,
  0b11111,
  0b01010,
  0b11111,
  0b01010,
  0b01110,
  0b11111
};
#include <Servo.h> 
int incomingByte = 0;
int cont =0;
int DEBUG = 1;
int ledPin = 13;
int buttnPin1 = 2;
int buttnPin2 = 7;
int buttnPin3 = 8;
int buttnPin4 = 9;
int buttnPin5 = 10;
int buttnsw = 3;
int buttnsww = 3;
int sensorValue = 0;
int mem1 = 0;
int mem2 = 1;
int memn = 2;
int memstore = 2;
int memstore1 = 0;
int memstore2 = 2;
int memstore3 = 0;
int memn1 = 0;
byte mem3 = 255;
int rssi = 0;
int rssi2 = 254;
int rssi3 =0;
int meter = 0;
int pos = 0;
int store = 90;
Servo myservo;  
int addr = 0;
int count =0;
int count1 =0;
int count2 =0;
int count3 =0;
int count4 =0;
int count5 =0;
int count6 =0;
int count7 =0;
int count8 =0;
int count9 =0;
int count10 =0;
int count11 =0;
int count12 =0;
int count13 =0;
int count14 =0;
int count15 =0;
int count16 =0;
int count17 =0;
int counter =0;
int knopje =0;
int buttnn1 ;
int buttnn2 ;
int buttnn3 ;
int buttnw1 ;
int buttnw2 ;
int buttnw3 ;
int val;
int op =1;
int sel =1;
int selc =1;
void setup(){
  lcd.createChar(1, cbupw);
  lcd.createChar(2, cbdown);
  lcd.createChar(3, cbmidledown);
  lcd.createChar(4, cbmidleup);
  lcd.createChar(5, cbupright);  
  lcd.createChar(6, cbdownright);
  lcd.createChar(7, cbmeterm);  
  lcd.createChar(8, cbmeterr);
  EEPROM.write(mem1,255);
  EEPROM.write(mem2,90);
  pinMode(ledPin, OUTPUT);
  pinMode(buttnPin1, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  digitalWrite(ledPin, HIGH);
  delay(400);
  digitalWrite(ledPin, LOW);
    Serial.begin(9600); // Set serial out if we want debugging
    Serial.println("Conection is made , Welcome Alientracker start !"); 
    lcd.begin(16,2);
    lcd.print(" TESTIN FLIGHT ");  //set up LCD'S number of rows and columns
    lcd.setCursor(0,1);
    lcd.print("*** CASE V1 ***"); 
    delay(2000);
    lcd.begin(16,2);  
}
void loop (){
     Serial.print((char)1); 
    Serial.print (buttnw1);
    Serial.print((char)2);
    Serial.print (buttnw2);
    Serial.print((char)3);
    Serial.print (buttnw3);
    Serial.print((char)4);
   buttnw1 = 2; 
   buttnw2 = 2; //select option
   buttnw3 = 2; 
    //val = Serial.read() - '0';
    //if (val == 8) digitalWrite(led,LOW);
    //if (val == 9) digitalWrite(piezo,HIGH); 
    delay (25);
  if (sel < 1 || sel > 6 ) sel = 1;
  else  if (sel == 1){ 
    int buttn1 = digitalRead(buttnPin1);
    int buttn2 = digitalRead(buttnPin2);
    int buttn3 = digitalRead(buttnPin3);
    lcd.begin(16,2);
    lcd.print("  MENU SELECT  ");
    if (op < 3 || op > 6 ) op = 3; 
    lcd.setCursor(0,1);
    if (buttn1 ==HIGH)op = op +1; 
    if (buttn2 ==HIGH)sel = 2; //select option
    if (buttn3 ==HIGH)op = op -1;  
    if (op ==3 )lcd.print("** TRACKER ON **"); 
    if (op ==4 )lcd.print("**  RSSI ON   **"); 
    if (op ==5 )lcd.print("*** NUCLEAR  ***"); 
    if (op ==6 )lcd.print("*** SWITCHES ***"); //make a choise and press select to go further //
    delay(250);
  } 
  else if (sel == 2){              
    int buttn1 = digitalRead(buttnPin1);
    int buttn2 = digitalRead(buttnPin2);
    int buttn3 = digitalRead(buttnPin3);
    if (buttn1 ==HIGH)sel = 1; 
    if (buttn2 ==HIGH)sel = op; //select option
    if (buttn3 ==HIGH)sel = 1;  
    lcd.begin(16,2);
    lcd.print(" ARE YOU SURE ?  ");
    lcd.setCursor(0,1);
    if (op ==3 )lcd.print("*** TRACKER ***"); 
    if (op ==4 )lcd.print("**  RSSI ON  **"); 
    if (op ==5 )lcd.print("*** NUCLEAR ***"); 
    if (op ==6 )lcd.print("**  SWITCHES **"); 
    delay(350);
    lcd.begin(16,2);
    lcd.print(" PRESS RED OK ");
    delay(750);
  }
  else if (sel == 3  ){  // tracker system option 1 //
    int buttn2 = digitalRead(buttnPin2);
    if (buttn2 ==HIGH)sel = 1; //select option
    counter = counter +1;
    lcd.begin(16,2);
    if (counter == 1 )knopje=1; //V-U stand 
    if (counter == 60)knopje=2;// s-meter
    if (counter == 100 )counter =0;
    rssi = analogRead(A0);
    count1 =map(rssi,1024,0,1,7);
    count2 =map(rssi-100,1024,0,1,7);
    count3 =map(rssi-200,1024,0,1,7);
    count4 =map(rssi-400,1024,0,1,7);
    count5 =map(rssi-500,1024,0,1,7);
    count6 =map(rssi-500,1024,0,1,7);
    count7 =map(rssi-400,1024,0,1,7);
    count8 =map(rssi-200,1024,0,1,7);
    count9 =map(rssi-200,1024,0,1,7);
    count10 =map(rssi-400,1024,0,1,7);
    count11 =map(rssi-500,1024,0,1,7);
    count12 =map(rssi-500,1024,0,1,7);
    count13 =map(rssi-400,1024,0,1,7);
    count14 =map(rssi-200,1024,0,1,7);
    count15 =map(rssi-100,1024,0,1,7);
    count16 =map(rssi,1024,0,1,7);
    if (knopje == 1)lcd.write(count1);
    if (knopje == 1)lcd.write(count2);
    if (knopje == 1)lcd.write(count3);
    if (knopje == 1)lcd.write(count4);
    if (knopje == 1)lcd.write(count5);
    if (knopje == 1)lcd.write(count6);
    if (knopje == 1)lcd.write(count7);
    if (knopje == 1)lcd.write(count8);
    if (knopje == 1)lcd.write(count9);
    if (knopje == 1)lcd.write(count10);
    if (knopje == 1)lcd.write(count11);
    if (knopje == 1)lcd.write(count13);
    if (knopje == 1)lcd.write(count14);
    if (knopje == 1)lcd.write(count15);
    if (knopje == 1)lcd.write(count16);
    if (knopje == 1)lcd.write(250);
    rssi = analogRead(A0) /4;
    rssi2 = EEPROM.read(mem1);
    if (knopje == 2) lcd.print("SIGNAL(");
    if (knopje == 2) lcd.setCursor(5,0); //print result to LCD display
    if (knopje == 2)lcd.setCursor(7,0); //print result to LCD display
    rssi3 = map(rssi,0,255,2000,0);
    if (knopje == 2) lcd.print(rssi3);
    if (knopje == 2) lcd.print("  S- )");
    delay(50);
    mem3 =EEPROM.read(mem1);
    memstore1 =EEPROM.read(memstore);
    memstore3 =EEPROM.read(memstore2);
    memn1 =EEPROM.read(memn);
    if(meter ==58)meter =0; 
    if(meter <=58)meter += 1;
    {
      if (meter==0) lcd.setCursor(0,1);
      if (meter==0) lcd.print ("      <  >      ");
      if (meter==1) lcd.setCursor(0,1);
      if (meter==1) lcd.print ("     <    >     ");
      if (meter==2) lcd.setCursor(0,1);
      if (meter==2) lcd.print ("   <        >   ");
      if (meter==3) lcd.setCursor(0,1);
      if (meter==3) lcd.print ("<-            ->");
      if (meter==4) lcd.setCursor(0,1);
      if (meter==4) lcd.print ("<--  ()()()  -->");
      if (meter==5) lcd.setCursor(0,1);
      if (meter==5) lcd.print ("<--    ()    -->");
      if (meter==6) lcd.setCursor(0,1);
      if (meter==6) lcd.print ("<-- LOADING  -->");
      if (meter==7) lcd.setCursor(0,1);
      if (meter==7) lcd.print ("<----      ---->");
      if (meter==8) lcd.setCursor(0,1);
      if (meter==8) lcd.print ("<-----    ----->");
      if (meter==9) lcd.setCursor(0,1);
      if (meter==9) lcd.print ("<------  ------>");
      if (meter==10) lcd.setCursor(0,1);
      if (meter==10) lcd.print("<-------------->");
      if (meter==11) lcd.setCursor(0,1);
      if (meter==11) lcd.print("<-------------->");
      ;
      if (meter==12) lcd.setCursor(0,1);
      if (meter==12) lcd.print("<-----    ----->");
      if (meter==13) lcd.setCursor(0,1);
      if (meter==13) lcd.print("<--          -->");
      if (meter==14) lcd.setCursor(0,1);
      if (meter==14) lcd.print(">-            -<");
      if (meter==15) lcd.setCursor(0,1);
      if (meter==15) lcd.print(">              <");
      if (meter==16) lcd.setCursor(0,1);
      if (meter==16) lcd.print("<-->            ");
      if (meter==17) lcd.setCursor(0,1);
      if (meter==17) lcd.print(" <-->           ");
      if (meter==18) lcd.setCursor(0,1);
      if (meter==18) lcd.print("  <-->          ");
      if (meter==19) lcd.setCursor(0,1);
      if (meter==19) lcd.print("   <-->          ");
      if (meter==20) lcd.setCursor(0,1);
      if (meter==20) lcd.print("    <-->         ");
      if (meter==21) lcd.setCursor(0,1);
      if (meter==21) lcd.print("      <-->       ");
      if (meter==22) lcd.setCursor(0,1);
      if (meter==22) lcd.print("        <-->     ");
      if (meter==23) lcd.setCursor(0,1);
      if (meter==23) lcd.print("           <-->  ");
      if (meter==24) lcd.setCursor(0,1);
      if (meter==24) lcd.print("            <--> ");
      if (meter==25) lcd.setCursor(0,1);
      if (meter==25) lcd.print("             <-->");
      if (meter==26) lcd.setCursor(0,1);
      if (meter==26) lcd.print("            <--> ");
      if (meter==27) lcd.setCursor(0,1);
      if (meter==27) lcd.print("         <-->    ");
      if (meter==28) lcd.setCursor(0,1);
      if (meter==28) lcd.print("       <-->      ");
      if (meter==29) lcd.setCursor(0,1);
      if (meter==29) lcd.print("   <-->          ");
      if (meter==30) lcd.setCursor(0,1);
      if (meter==30) lcd.print("  <-->           ");
      if (meter==31) lcd.setCursor(0,1);
      if (meter==31) lcd.print(" <-->            ");
      if (meter==32) lcd.setCursor(0,1);
      if (meter==32) lcd.print("<-->             ");
      if (meter==33) lcd.setCursor(0,1);
      if (meter==33) lcd.print("-->              ");
      if (meter==34) lcd.setCursor(0,1);
      if (meter==34) lcd.print("  # NO SIGNAL #  ");
      if (meter==34) delay(200);
      if (meter==35) lcd.setCursor(0,1);
      if (meter==35) lcd.print("      U.F.O      ");
      if (meter==35) delay(200);
      if (meter==36) lcd.setCursor(0,1);
      if (meter==36) lcd.print("  TRACKING SYS   ");
      if (meter==37) lcd.setCursor(0,1);
      if (meter==37) lcd.print("/ / / / / / / / /");
      if (meter==38) lcd.setCursor(0,1);
      if (meter==38) lcd.print(" / / / / / / / / ");
      if (meter==39) lcd.setCursor(0,1);
      if (meter==39) lcd.print("/ / / / / / / / /");
      if (meter==40) lcd.setCursor(0,1);
      if (meter==40) lcd.print("<^^^>            ");
      if (meter==41) lcd.setCursor(0,1);
      if (meter==41) lcd.print("     <^^^>       ");
      if (meter==42) lcd.setCursor(0,1);
      if (meter==42) lcd.print("          <^^^>  ");
      if (meter==43) lcd.setCursor(0,1);
      if (meter==43) lcd.print("           <^^^> ");
      if (meter==44) lcd.setCursor(0,1);
      if (meter==44) lcd.print("         <^^^>   ");
      if (meter==45) lcd.setCursor(0,1);
      if (meter==45) lcd.print("       <^^^>     ");
      if (meter==46) lcd.setCursor(0,1);
      if (meter==46) lcd.print("     <^^^>       ");
      if (meter==47) lcd.setCursor(0,1);
      if (meter==47) lcd.print("   <^^^>         ");
      if (meter==48) lcd.setCursor(0,1);
      if (meter==48) lcd.print(" / / / / / / / / ");
      if (meter==49) lcd.setCursor(0,1);
      if (meter==49) lcd.print("/ / / / / / / / /");
      if (meter==50) lcd.setCursor(0,1);
      if (meter==50) lcd.print("<^^^>            ");
      if (meter==51) lcd.setCursor(0,1);
      if (meter==51) lcd.print("     <^^^>       ");
      if (meter==52) lcd.setCursor(0,1);
      if (meter==52) lcd.print("          <^^^>  ");
      if (meter==53) lcd.setCursor(0,1);
      if (meter==53) lcd.print("           <^^^> ");
      if (meter==54) lcd.setCursor(0,1);
      if (meter==54) lcd.print("         <^^^>   ");
      if (meter==55) lcd.setCursor(0,1);
      if (meter==55) lcd.print("       <^^^>     ");
      if (meter==56) lcd.setCursor(0,1);
      if (meter==56) lcd.print("     <^^^>       ");
      if (meter==57) lcd.setCursor(0,1);
      if (meter==57) lcd.print("   <^^^>         ");
      if (meter==58) lcd.setCursor(0,1);
      if (meter==58) lcd.print("<^^^>            ");


      delay (100);
      if (rssi==memstore3)lcd.begin(16,2);
      if (rssi==memstore3)lcd.print("* SAME SIGNAL  *");
      if (rssi==memstore3)lcd.setCursor(0,1);
      if (rssi==memstore3)lcd.print(" * IDENTICAL *");
      if (rssi==memstore3)delay (2500);
      if (rssi==memstore3)return;
      if (analogRead(A0)>=900)EEPROM.write(memn,254);
      if (memn1<=analogRead(A0) /4)return;
      if (knopje == 1)return;
      if (analogRead(A0)<=900)cont='3';
      switch (cont)  {
      case '3'://0x0: //FD20DF:
        if (memstore3==rssi)lcd.begin(16,2);
        if (memstore3==rssi)lcd.print("* SAME SIGNAL  *");
        if (memstore3==rssi)lcd.setCursor(0,1);
        if (memstore3==rssi)lcd.print(" * IDENTICAL *");
        if (memstore3==rssi)delay (2500);
        if (memstore3==rssi)break;
        EEPROM.write(mem1,254);
        delay(10);
        if (analogRead(A0)>=980)break;
        delay(100);
        lcd.begin(16,2); 
        lcd.print("*START TRACKER*");
        delay(200);
        delayMicroseconds(1);
        digitalWrite(ledPin, HIGH);
        //myservo.write(0);
        delay(20);
        rssi = analogRead(A0) /4;
        mem3 =EEPROM.read(mem1);
        for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
        { 
          delay(20);
          if (analogRead(A0)>=950)break;
          digitalWrite(ledPin, HIGH);
          rssi = analogRead(A0) /4;
          mem3 =EEPROM.read(mem1);
          if (mem3 >rssi)EEPROM.write(memn,rssi);
          if (mem3 >rssi)EEPROM.write(mem1,rssi);
          if (mem3 >rssi)EEPROM.write(mem2,pos);
          if (mem3 >rssi)EEPROM.write(memstore,pos);
          if (mem3 >rssi)EEPROM.write(memstore2,rssi);
          myservo.write(pos); 
          delay(20);
          store =EEPROM.read(mem2);          
          digitalWrite(ledPin, LOW);
          if (analogRead(A0)>=950)break;
          if (mem3 >rssi) lcd.begin(0,16);
          if (mem3 >rssi) lcd.print("***FOUND NEW***");
          if (mem3 >rssi) delay(100);
          lcd.begin(16,2);
          lcd.print("SIGNAL(");
          lcd.setCursor(8,0); //print result to LCD display
          rssi3 = map(rssi,0,255,2000,0);
          lcd.print(rssi3);
          lcd.setCursor(10,0); //print result to LCD display
          lcd.print(" S-) ");
          meter =map(rssi,0,255,26,0);
          if (meter==0) lcd.setCursor(0,1);
          if (meter==0) lcd.print(">");
          if (meter==1) lcd.setCursor(0,1);
          if (meter==1) lcd.print("-");
          if (meter==2) lcd.setCursor(0,1);
          if (meter==2) lcd.print("->");
          if (meter==3) lcd.setCursor(0,1);
          if (meter==3) lcd.print("-->");
          if (meter==4) lcd.setCursor(0,1);
          if (meter==4) lcd.print("--->");
          if (meter==5) lcd.setCursor(0,1);
          if (meter==5) lcd.print("---->");
          if (meter==6) lcd.setCursor(0,1);
          if (meter==6) lcd.print("----->");
          if (meter==7) lcd.setCursor(0,1);
          if (meter==7) lcd.print("------>");
          if (meter==8) lcd.setCursor(0,1);
          if (meter==8) lcd.print("------->");
          if (meter==9) lcd.setCursor(0,1);
          if (meter==9) lcd.print("-------->");
          if (meter==10) lcd.setCursor(0,1);
          if (meter==10) lcd.print("--------->");
          if (meter==11) lcd.setCursor(0,1);
          if (meter==11) lcd.print("---------->");
          if (meter==12) lcd.setCursor(0,1);
          if (meter==12) lcd.print("----------=>");
          if (meter==13) lcd.setCursor(0,1);
          if (meter==13) lcd.print("----------==>");
          if (meter==14) lcd.setCursor(0,1);
          if (meter==14) lcd.print("---------10+=>");
          if (meter==15) lcd.setCursor(0,1);
          if (meter==15) lcd.print("----------20+=>");
          if (meter==16) lcd.setCursor(0,1);
          if (meter==16) lcd.print("----------30+==>");
          if (meter==17) lcd.setCursor(0,1);
          if (meter==17) lcd.print("x2==>");
          if (meter==18) lcd.setCursor(0,1);
          if (meter==18) lcd.print("x2===>");
          if (meter==19) lcd.setCursor(0,1);
          if (meter==19) lcd.print("x2====>");
          if (meter==20) lcd.setCursor(0,1);
          if (meter==20) lcd.print("x2=====>");
          if (meter==21) lcd.setCursor(0,1);
          if (meter==21) lcd.print("x2======>");
          if (meter==22) lcd.setCursor(0,1);
          if (meter==22) lcd.print("x2=======>");
          if (meter==23) lcd.setCursor(0,1);
          if (meter==23) lcd.print("x2========>");
          if (meter==24) lcd.setCursor(0,1);
          if (meter==24) lcd.print("x2=========>");
          if (meter==25) lcd.setCursor(0,1);
          if (meter==25) lcd.print("x2==========>");
          if (meter==26) lcd.setCursor(0,1);
          if (meter==26) lcd.print("x2=============>");
          // lcd patern !!        ("1234567890123456")
        }
        delay(10);
        digitalWrite(ledPin, HIGH);
        delay(10);
        delay(10);
        store =EEPROM.read(mem2);
        if (store == 0)store=memstore1;
        if (memstore1 == 0)store=90;
        myservo.write(store);
        store =EEPROM.read(mem2);
        lcd.begin(16,2);
        //1234567890123456//  
        lcd.print("SERVO STORED POS");  //set up LCD'S number of rows and columns
        lcd.setCursor(3,1);
        lcd.print(store);
        lcd.print(" DEGREE");
        delay(1000);
        lcd.begin(16,2);
        cont ='0'; 
        if (analogRead(A0)<=890) delay (200);
        if (analogRead(A0)<=890) lcd.begin(16,2);
        if (analogRead(A0)<=890) lcd.print(" (0)  ^^^^  (0) ");
        if (analogRead(A0)<=890) lcd.setCursor(0,1);
        // lcd patern !!                  ("1234567890123456")
        if (analogRead(A0)<=890) lcd.print("  (__________)  ");
        if (analogRead(A0)<=890) delay (200);
        if (analogRead(A0)<=890) lcd.begin(16,2);
        if (analogRead(A0)<=890) lcd.print(" (0)  ^^^^  (-) ");
        if (analogRead(A0)<=890) lcd.setCursor(0,1);
        // lcd patern !!                  ("1234567890123456")
        if (analogRead(A0)<=890) lcd.print("  (__<<  >>--)  ");
        if (analogRead(A0)<=890) delay (200);
        if (analogRead(A0)<=890) lcd.begin(16,2);
        if (analogRead(A0)<=890) lcd.print(" (0)  ^^^^  (0) ");
        if (analogRead(A0)<=890) lcd.setCursor(0,1);
        // lcd patern !!                  ("1234567890123456")
        if (analogRead(A0)<=890) lcd.print("  (__________)  ");
        if (analogRead(A0)<=890) delay (200);
        lcd.begin(16,2);
        break; 
      }
    }
  }
  else if (sel == 4  ){  // tracker system option 2 //
    lcd.begin(16,2);
    rssi = analogRead(A0) /4;
    lcd.print("SIGNAL(");
    lcd.setCursor(5,0); //print result to LCD display
    lcd.setCursor(7,0); //print result to LCD display
    rssi3 = map(rssi,0,255,2000,0);
    lcd.print(rssi3);
    lcd.print("  S- )");
    int buttn2 = digitalRead(buttnPin2);
    if (buttn2 ==HIGH)sel = 1; //select option
    delay(250);
  }
  else if (sel == 5  ){  // tracker system option 2 //
    lcd.begin(16,2);
    rssi = analogRead(A0);
    count1 =map(rssi,1024,0,1,7);
    count2 =map(rssi-100,1024,0,1,7);
    count3 =map(rssi-200,1024,0,1,7);
    count4 =map(rssi-400,1024,0,1,7);
    count5 =map(rssi-500,1024,0,1,7);
    count6 =map(rssi-500,1024,0,1,7);
    count7 =map(rssi-400,1024,0,1,7);
    count8 =map(rssi-200,1024,0,1,7);
    count9 =map(rssi-200,1024,0,1,7);
    count10 =map(rssi-400,1024,0,1,7);
    count11 =map(rssi-500,1024,0,1,7);
    count12 =map(rssi-500,1024,0,1,7);
    count13 =map(rssi-400,1024,0,1,7);
    count14 =map(rssi-200,1024,0,1,7);
    count15 =map(rssi-100,1024,0,1,7);
    count16 =map(rssi,1024,0,1,7);
    lcd.write(count1);
    lcd.write(count2);
    lcd.write(count3);
    lcd.write(count4);
    lcd.write(count5);
    lcd.write(count6);
    lcd.write(count7);
    lcd.write(count8);
    lcd.write(count9);
    lcd.write(count10);
    lcd.write(count11);
    lcd.write(count13);
    lcd.write(count14);
    lcd.write(count15);
    lcd.write(count16);
    lcd.write(250);
    delay(250);
    int buttn2 = digitalRead(buttnPin2);
    if (buttn2 ==HIGH)sel = 1; //select option
  }
    else if (sel == 6  ){
    lcd.begin(16,2);
    lcd.print("CONNECTED"); 
    buttnn1 = digitalRead(buttnPin1);
    buttnn2 = digitalRead(buttnPin2);
    buttnn3 = digitalRead(buttnPin3);
    if (buttnn1 ==HIGH)buttnw1 = 5; 
    if (buttnn2 ==HIGH)buttnw2 = 5; //select option
    if (buttnn3 ==HIGH)buttnw3 = 5;  
  }
}



