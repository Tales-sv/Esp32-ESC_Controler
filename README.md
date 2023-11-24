# Esp32-ESC_Controler
Simple example code that generates a PWM signal with 1-2ms pulse width, used for controlling Eletronic Speed Controler (ESC) or Servo motor.

# Warning about ESC configuration
Most of the comercial ESCs have some configurations, which you can change according to your application, here some of them: (Different names may appear)
- Running mode: Motor reversion control, enabe or disable reversion and/or brake.
  - Foward
  - Foward/Reverse
- Motor direction: Motor direction control, changes the direction of the motor spin.
  - Normal
  - Reverse
- Input Curve: Add a curve to the input signal interpretation.
  - Linear
  - Custom
- Dead Band: Adds a threshold to extreme values
  - 2us to 150us (Values may change from ESC to ESC)

**These settings can change the way your esc reacts to your input signal.**

# Signal
Esc only foward:
- 1000us to 2000us: 0 to 100%
  
Esc foward/reverse:
- 1000us to 1500us: -100% to 0% (reverse)
- 1500us: 0% (stoped)
- 1500us to 2000us: 0% to 100% (foward)
  
Servo:
- 1000us to 2000us: 0 to 180 degrees

# Acceleration Ramp 
It's very importan to manage your motor acceleration rate. If you don't do it properly, you may damage your motor/ESC.

Some good ESCs already do it, some not. 

**Be carefull.**
