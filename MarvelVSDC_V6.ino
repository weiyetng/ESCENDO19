
#include <Button.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define player1            10

#define player2            11

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20
#include <Servo.h>
#define Marvel_1    15
#define DC_2        14

#define ind_up A5
#define ind_right A9
#define ind_down A10
#define ind_left A11

Servo myservo;
Servo myservo2;
Button up_p1(2); 
Button right_p1(3);
Button down_p1(4); 
Button left_p1(5);

Button up_p2(6); 
Button right_p2(7);
Button down_p2(8); 
Button left_p2(9); 
Button mode_1(16);
Button mode_2(17);

int game_state=0;
int game_mode=0;
int inst_change = 2;
unsigned long currentTime,lastTime;
int inst = 16 ;
int prev_inst = 16;
long deltaTime;
int done1,done2;
int result1=0,result2=0;

int correct_P1 = 0;
int correct_P2 = 0;

int score,score2;
int deg_1=0;
int deg_2=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, player1, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, player2, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, player1, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, player2, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
void theaterChase2(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip2.numPixels(); i=i+3) {
        strip2.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip2.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void hero_effect(){
if (deg_1 ==0)
  {for (int pos = 0; pos <= 180; pos += 40) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
   }                    
   deg_1=180;}
else if (deg_1 ==180)
  {
  for (int pos = 180; pos >= 0; pos -= 40) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
   }
   deg_1=0;// waits 15ms for the servo to reach the position
  }}
 void hero_effect2(){
if (deg_2 ==0)
  {for (int pos = 0; pos <= 180; pos += 40) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos); // tell servo to go to position in variable 'pos'
   }                    
   deg_2=180;}
else if (deg_2 ==180)
  {
  for (int pos = 180; pos >= 0; pos -= 40) { // goes from 180 degrees to 0 degrees
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
   }
   deg_2=0;// waits 15ms for the servo to reach the position
  }
 }

void show_pixel(){
 if(game_state==0)
  {
  theaterChase(strip.Color(0, 0, 127), 50);

    for(int i=0;i<NUMPIXELS;i++)
    { 
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }
  }

   else if (game_state==1)
  {
    if(correct_P1==1){
   for(int i=0;i<score;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
   }
    }

  else if (correct_P1==0){
  pixels.setPixelColor(score+2, pixels.Color(0,0,0)); 
  pixels.show();
  pixels.setPixelColor(score+1, pixels.Color(0,0,0)); 
  pixels.show();
  pixels.setPixelColor(score, pixels.Color(0,0,0)); 
  pixels.show();
  }
}
  else if (game_state==2)
  {
    if(result1==1){
    for(int i=0;i<NUMPIXELS;i++)
    { 
    pixels.setPixelColor(i, pixels.Color(0,0,255)); // Moderately bright red color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }
    hero_effect();}
    else if(result1==0){//winning effect
    for(int i=0;i<NUMPIXELS;i++)
    { 
    // losing effect
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright red color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }
   }
    }

}
void show_pixel2(){
 if(game_state==0)
  {
  theaterChase2(strip2.Color(0, 0, 127), 50);
    for(int i=0;i<NUMPIXELS;i++)
    { 
    // pixels2.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels2.setPixelColor(i, pixels2.Color(0,0,0)); // Moderately bright green color.

    pixels2.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }
  }

   else if (game_state==1)
  {
    if(correct_P2==1){
   for(int i=0;i<score2;i++){

    // pixels2.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels2.setPixelColor(i, pixels2.Color(0,255,0)); // Moderately bright green color.

    pixels2.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
   }
    }

    else if (correct_P2==0){
    pixels2.setPixelColor(score2+2, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels2.setPixelColor(score2+1, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels2.setPixelColor(score2, pixels2.Color(0,0,0)); 
    pixels2.show();
    }
}
  else if (game_state==2)
  {
    if(result2==1)
    //winning effect
    { 
    for(int i=0;i<NUMPIXELS;i++){
    pixels2.setPixelColor(i, pixels2.Color(0,0,255)); // Moderately bright red color.

    pixels2.show(); 
    }
    hero_effect2();// This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }
    else if(result2==0){
    for(int i=0;i<NUMPIXELS;i++)
    { 
    // losing effect
    pixels2.setPixelColor(i, pixels2.Color(255,0,0)); // Moderately bright red color.

    pixels2.show(); // This sends the updated pixel color to the hardware.

  // Delay for a period of time (in milliseconds).
    }}
    }
}

void show_ind()
{
if(inst==1)
digitalWrite(ind_up,HIGH);
else if(inst ==2)
digitalWrite(ind_right,HIGH);
else if(inst==3)
digitalWrite(ind_down,HIGH);
else if(inst==4)
digitalWrite(ind_left,HIGH);
}


void dim_ind()
{
if(inst==1)
digitalWrite(ind_up,LOW);
else if(inst ==2)
digitalWrite(ind_right,LOW);
else if(inst==3)
digitalWrite(ind_down,LOW);
else if(inst==4)
digitalWrite(ind_left,LOW);
}

void check_ply1()
{
  int pressed = 0;
  if(up_p1.pressed()){
    hero_effect();
    pressed = 1;
    Serial.println("P1 pressed 1");
    }
  else if (right_p1.pressed()){
    hero_effect();
    pressed = 2;
    Serial.println("P1 pressed 2");}
  else if ( down_p1.pressed()){
    hero_effect();
    pressed = 3;
    Serial.println("P1 pressed 3");}
  else if ( left_p1.pressed()){
    hero_effect();
    pressed = 4;
    Serial.println("P1 pressed 4");}

  if( pressed == inst ){
         correct_P1 = 1;
         score++;
      }
   else if ( pressed == 0 ){
        return;
      }
  else 
  {
     correct_P1 = 0;
     if(score>=3)
     score=score-3;
     else if(score<3)
     score=0;
    }
    if(score>=20)
    {result1=1;
    result2=0;}
    show_pixel();
}
void check_ply2()
{
  int pressed = 0;
  if(up_p2.pressed()){
    hero_effect2();
    pressed = 1;
    Serial.println("P2 pressed 1");}
  else if (right_p2.pressed()){
    hero_effect2();
    pressed = 2;
    Serial.println("P2 pressed 2");}
  else if ( down_p2.pressed()){
    hero_effect2();
    pressed = 3;
    Serial.println("P2 pressed 3");}
  else if ( left_p2.pressed()){
    hero_effect2();
    pressed = 4;
    Serial.println("P2 pressed 4");}

  if( pressed == inst ){
         correct_P2 = 1;
         score2++;
      }
  else if ( pressed == 0 ){
        return;
      }
   else
   {correct_P2=0;
   if(score2>=3)
    score2=score2-3;
   else if(score2<3)
   score2=0;
   }
     if(score2>=20)
    {result1=0;
    result2=1;}
   show_pixel2();
   
}

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
    randomSeed(analogRead(0)); 
    lastTime = millis();
    currentTime = millis();

    strip.begin();
    strip.show(); 
    pixels.begin(); // This initializes the NeoPixel library.

    strip2.begin();
    strip2.show(); 
    pixels2.begin(); 

    up_p1.begin();
    right_p1.begin();
    down_p1.begin();
    left_p1.begin();
    up_p2.begin();
    right_p2.begin();
    down_p2.begin();
    left_p2.begin();
    mode_1.begin();
    mode_2.begin();

    pinMode(ind_up,OUTPUT);
    pinMode(ind_right,OUTPUT);
    pinMode(ind_left,OUTPUT);
    pinMode(ind_down,OUTPUT);

    while(game_mode==0)
    {if(mode_1.pressed())
    game_mode=1;
    else if(mode_2.pressed())
    game_mode=2;}

    show_pixel();
    show_pixel2();

    game_state=1;
    myservo.attach(15);
    myservo2.attach(14);
}

void loop() {
  // put your main code here, to run repeatedly:
    //currentTime = millis() ;
    //deltaTime = currentTime - lastTime;
      if(game_mode==1)
      {currentTime = millis() ;
    deltaTime = currentTime - lastTime;

   if(deltaTime - (inst_change*1000) > 0){
      dim_ind();
      lastTime = millis();
      while(prev_inst==inst)
      inst = random(1,5);
      prev_inst=inst;
      inst_change = random(1,3);
      show_ind();
     
      
      Serial.print("inst : ");Serial.println(inst);
      Serial.print("inst_change : ");Serial.println(inst_change);
      Serial.println();
      Serial.print("score 1 : ");Serial.println(score);
      Serial.print("score 2 : ");Serial.println(score2);
      Serial.println();
    }
    check_ply1();
    check_ply2();
    while(score>=20||score2>=20)
    {
      game_state=2;
      show_pixel();
      show_pixel2();
    }}
   else if(game_mode==2){
   if(millis()%430==0){
      dim_ind();
      lastTime = millis();
      while(prev_inst==inst)
      inst = random(1,5);
      prev_inst=inst;
      show_ind();
      done1=0;
      done2=0;
     
      
      Serial.print("inst : ");Serial.println(prev_inst);
      /*Serial.print("inst_change : ");Serial.println(inst_change);
      Serial.println();
      Serial.print("score 1 : ");Serial.println(score);
      Serial.print("score 2 : ");Serial.println(score2);
      Serial.println();*/
    }
    if(done1==0)
    check_ply1_2();
    if(done2==0)
    check_ply2_2();
    while(score>=20||score2>=20)
    {
      game_state=2;
      show_pixel();
      show_pixel2();
    }

}}

void check_ply1_2()
{
  int pressed = 0;
  if(up_p1.pressed()){
    hero_effect();
    pressed = 1;
    Serial.println("P1 pressed 1");
    done1=1;
    }
  else if (right_p1.pressed()){
    hero_effect();
    pressed = 2;
    Serial.println("P1 pressed 2");
    done1=1;}
  else if ( down_p1.pressed()){
    hero_effect();
    pressed = 3;
    Serial.println("P1 pressed 3");
    done1=1;}
  else if ( left_p1.pressed()){
    hero_effect();
    pressed = 4;
    Serial.println("P1 pressed 4");
done1=1;}

  if( pressed == inst ){
         correct_P1 = 1;
         score++;
      }
   else if ( pressed == 0 ){
        return;
      }
  else 
  {
     correct_P1 = 0;
     if(score>=3)
     score=score-3;
     else if(score<3)
     score=0;
    }
    if(score>=20)
    {result1=1;
    result2=0;}
    show_pixel();
}
void check_ply2_2()
{
  int pressed = 0;
  if(up_p2.pressed()){
    hero_effect2();
    pressed = 1;
    Serial.println("P2 pressed 1");
    done2=1;}
  else if (right_p2.pressed()){
    hero_effect2();
    pressed = 2;
    Serial.println("P2 pressed 2");
    done2=1;}
  else if ( down_p2.pressed()){
    hero_effect2();
    pressed = 3;
    Serial.println("P2 pressed 3");
    done2=1;}
  else if ( left_p2.pressed()){
    hero_effect2();
    pressed = 4;
    Serial.println("P2 pressed 4");
    done2=1;}

  if( pressed == inst ){
         correct_P2 = 1;
         score2++;
      }
  else if ( pressed == 0 ){
        return;
      }
   else
   {correct_P2=0;
   if(score2>=3)
    score2=score2-3;
   else if(score2<3)
   score2=0;
   }
     if(score2>=20)
    {result1=0;
    result2=1;}
   show_pixel2();
   
}

