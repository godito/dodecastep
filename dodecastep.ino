/*
  SparkFun Electronics 2011
  Aaron Weiss, aaron at sparkfun dot com
  Beer-ware License: You can do whatever you want with this sketch.
                     If we meet someday, you can buy me a beer.
  Modified by Sebastian M Strauch in 2014 to use it with three Quadstepper motor driver boards in parallel without using 72 pins.
  Also, it is not possible to cesignate more STP pins without working the quadstep library.
  Fell free to do something cool with it, and I surely will accept a beer if we meet.
                     
  Dodecastepper Example Sketch. For use with an Arduino Mega2560, 3 quadstepper motor driver boards by sparkfun and up 
  to 12 1.8 degree bipolar stepper motor.

  You must connect the STP pin for each board as shown below.
  For rest of the pins, you choose where they go. 

  Board 1 STP pin: mega pin 11
  Board 2 STP pin: meag pin 5
  Board 3 STP pin: meag pin 6
  NOTE: Even if you run only one motor on the board, all the green leds will flash, since the share the STP Pin. You actually switch them on via ENABLE.
  
  Library Usage: 
  motor_pins(x,y)
  x: motor channel number
  y: enable pin assignment
  board_pins(x,y,a,b,c)
  x: board number
  y: direction pin assignment
  a: MS1 pin assignment
  b: MS2 pin assignment
  c: MS3 pin assignment  
  motor_go(x,y,z,l)
  x: motor channel number
  y: step size: 1, 2, 4, 8, or 16
  z: increments for given step size
     for full step: 1 increment = 1.8deg
     for half step: 1 increment = 0.9deg and so on
     negaitve numbers rotate in the opposite direction
  l: torque/speed (0-10), 0 is high speed/low torque/low current
                          10 is low speed/high torque/high current (2.0A max)
               
  stall(x)
  x: motor channel number, that I did not try yet.
*/

// include the motor library
#include <dodecastep.h>

// create an instance of the class motor
dodecastep dodecastep;

void setup() {
  
  // assign the pin connections of the boards
  dodecastep.board_pins(1,32,24,26,28);
  dodecastep.board_pins(2,33,25,27,29);

  // assign the enable_pin connections of the motors on board 1 (1,2,3,4)    
  dodecastep.motor_pins(3,34); //motor 3
  dodecastep.motor_pins(4,36); //motor 4
  
  
  // assign the pin connections of the motors on board 2 (5,6,7,8) 
  dodecastep.motor_pins(5,35);  //motor 5
  dodecastep.motor_pins(6,37);  //motor 6
 
   // assign the pin connections of the motors on board 3 (9,10,11,12) 
  dodecastep.motor_pins(9,38);  //motor 5
  dodecastep.motor_pins(10,39);  //motor 6
}

//1.8deg = 1step
void loop() {
  
  // step motor 4 for 200 increments CW
  dodecastep.motor_go(4,1,-200,2);
  delay(500);
  // step motor 4 for 200 increments CCW
  dodecastep.motor_go(4,1,200,2);
  delay(500);
 
  // holds the motor in one position with full torque/current
  //motor.stall(4);
  //delay(500); 
}
