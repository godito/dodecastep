/*

	created as quadstep by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

	Modified 2014 by Sebastian M. Strauch to control three Quadstepper motor boards in parallel
	
	I like beer, too.

*/

#ifndef dodecastep_h
#define dodecastep_h

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class dodecastep
{
  public:
	dodecastep();
	void motor_pins(int motnum,int motor_enable);
	void board_pins(int bnum, int b_dir, int b_ms1, int b_ms2, int b_ms3);
    void motor_go(int motnum, int step_size, int number_of_steps, int torque);
	void stall(int motnum);
	//void motor1rpm(int direction,int level);
 
  private:
	void current_control(int step);
	int _torque;
	int step1;
	int step2;
	int step4;
	int step8;
	int step16;
	
	int _motor_enable_1;
	int _motor_enable_2;
	int _motor_enable_3;
	int _motor_enable_4;
	int _motor_enable_5;
	int _motor_enable_6;
	int _motor_enable_7;
	int _motor_enable_8;	
	int _motor_enable_9;
	int _motor_enable_10;
	int _motor_enable_11;
	int _motor_enable_12;

	int _b_ms_11;
	int _b_ms_12;
	int _b_ms_13;
	
	int _b_ms_21;
	int _b_ms_22;
	int _b_ms_23;
	
	int _b_ms_31;
	int _b_ms_32;
	int _b_ms_33;
	
	int _b_dir_1;
	int _b_dir_2;
	int _b_dir_3;
	
};//fucking important semicolon!
#endif

