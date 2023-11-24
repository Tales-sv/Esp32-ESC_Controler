// ESP32 ESC controler with PWM Signal
// Author: Tales-sv

#include <Arduino.h>

#define REVERSIBLE_ESC //coment if your ESC is configurated with only direction (non-reversible, only foward or foward/break)

#define OUTPUT_ESC 25 //Signal output pin
#define CHANNEL_ESC 1 //lec channel used for generating a pwm signal

u_int16_t PWM_width_us = 0; //PWM high width in Microseconds (us) (amount of time the signal is high)
u_int16_t DutyCycle = 0;    //Duty Cycle of the pwm signal generated

bool speed_up = 1; //switch the generated signal, speed up or slow down

void Send_PWM_Signal (bool print); //func to send the signal to esc

void setup() {

  Serial.begin(115200);
   
  //setup ledc channel:
  pinMode(OUTPUT_ESC, OUTPUT);            // Setting the signal output pin

  ledcSetup(CHANNEL_ESC, 50, 16);         // CHANNEL_ESC config: freq: 50Hz (20mS) Resolution: 16 bits (0 a 65535)
  ledcAttachPin(OUTPUT_ESC, CHANNEL_ESC); // Attach the signal output pin to a ledc channel, necessary for generating PWM with ledc

  delay(20);
  //some ESCs need a initial stop signal to connect

 #ifdef REVERSIBLE_ESC // if your esc is foward/reverse configurated:
  PWM_width_us = 1500; // Reversible esc: stop

 #else                 // if your esc is single direction configurated:
  PWM_width_us = 1000; // Non-reversible esc: stop

 #endif
  Send_PWM_Signal(1); //generate the PWM signal

}//end setup()

void loop() {
    //ramp test:
    if(speed_up) PWM_width_us = constrain(PWM_width_us+10,1000,2000); //speed up
    else      PWM_width_us = constrain(PWM_width_us-10,1000,2000); //slow down 

    if (PWM_width_us >= 2000) speed_up = 0;        //changes the test, speed up or slow down
    else if (PWM_width_us <= 1000) speed_up = 1;

  //input test: (us values direction may not be exact, most ESCs have a configurable dead band) Ex: 2020us must be 100%

  //reversible esc: (Direction may be reversed by esc configuration)
    // PWM_width_us = 1000; // -100% (backward)
    // PWM_width_us = 1250; // -50% (backward)
    // PWM_width_us = 1500; // 0%
    // PWM_width_us = 1750; // 50% (foward)
    // PWM_width_us = 2000; // 100% (foward)
     
  //non-reversible esc:
    // PWM_width_us = 1000; // 0%
    // PWM_width_us = 1500; // 50%
    // PWM_width_us = 2000; // 100%


    Send_PWM_Signal(1);
    
    delay(20); //delay fo An accel ramp, witch is very usefull for safe controling of your motor
}//end loop()

void Send_PWM_Signal(bool print) {

    DutyCycle = map(PWM_width_us, 1000, 2000, 3275, 6553);  // Dutycycle to generate a pwm signal with that width in microseconds(us)
    ledcWrite(CHANNEL_ESC, DutyCycle);                      // generating a PWM with the proper width in us

    if(print){
        Serial.print("PWM width: ");
        Serial.print(PWM_width_us);
        Serial.print(" us");
        Serial.print(" ");

  #ifdef REVERSIBLE_ESC // if your esc is foward/reverse configurated:
        Serial.print("Speed: ");
        Serial.print(map(PWM_width_us,1000,2000,-100,100)); //print the speed in percentage
        Serial.print("% - ");
        Serial.print("Direction: ");        //Direction may be reversed by esc configuration
        if(PWM_width_us>1500) Serial.print("Foward");
        else Serial.print("Reverse");

  #else                 // if your esc is single direction configurated:
        // if your esc is single direction configurated:
        Serial.print("Speed: ");
        Serial.print(map(PWM_width_us,1000,2000,0,100)); //print the speed in percentage
        Serial.print("% - ");

  #endif
    Serial.println();

    }//end if print

}//end Send_PWM_Signal()