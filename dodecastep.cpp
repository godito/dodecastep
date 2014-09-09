*/

	created as quadstep by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

	Modified 2014 by Sebastian M. Strauch to control three Quadstepper motor boards in parallel
	
	I like beer, too.

*/

//#include "WProgram.h"
#include "Arduino.h"
#include "dodecastep.h"

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define STEPMIN	800

dodecastep::dodecastep()
{	
	pinMode(11, OUTPUT); //PB5
	pinMode(5, OUTPUT); //PE3
	pinMode(6, OUTPUT); //PH3
//	pinMode(46, OUTPUT); //PL3 one more board might give us 4 more moters, if needed, but then the library shall be renamed hexakaidekastep
	
	//make sure the step lines are low on startup
	cbi(PORTB, 5);
	cbi(PORTE, 3);
	cbi(PORTH, 3);
//	cbi(PORTL, 3);
	
	Serial.begin(9600);
}

/////////////////////////////////////////////////////////
///////   Pin connections ///////////////////////////////
/////////////////////////////////////////////////////////
void dodecastep::board_pins(int bnum, int b_dir, int b_ms1, int b_ms2, int b_ms3)
	{
	if(bnum == 1)
	{
		pinMode(b_dir, OUTPUT);
		pinMode(b_ms1, OUTPUT);
		pinMode(b_ms2, OUTPUT);
		pinMode(b_ms3, OUTPUT);
		
		digitalWrite(b_dir, LOW);
		_b_dir_1 = b_dir;
		_b_ms_11 = b_ms1;
		_b_ms_12 = b_ms2;
		_b_ms_13 = b_ms3;
	}
	else if(bnum == 2)
	{
		pinMode(b_dir, OUTPUT);
		pinMode(b_ms1, OUTPUT);
		pinMode(b_ms2, OUTPUT);
		pinMode(b_ms3, OUTPUT);
		
		digitalWrite(b_dir, LOW);
		_b_dir_2 = b_dir;
		_b_ms_21 = b_ms1;
		_b_ms_22 = b_ms2;
		_b_ms_23 = b_ms3;
	}
	else if(bnum == 3)
	{
		pinMode(b_dir, OUTPUT);
		pinMode(b_ms1, OUTPUT);
		pinMode(b_ms2, OUTPUT);
		pinMode(b_ms3, OUTPUT);
		
		digitalWrite(b_dir, LOW);
		_b_dir_3 = b_dir;
		_b_ms_31 = b_ms1;
		_b_ms_32 = b_ms2;
		_b_ms_33 = b_ms3;
	}
	}

void dodecastep::motor_pins(int motnum,int motor_enable)
{	
	if(motnum == 1)
	{
		pinMode(motor_enable, OUTPUT);
		digitalWrite(motor_enable, HIGH);		
		_motor_enable_1 = motor_enable;
	}
	else if(motnum == 2)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_2 = motor_enable;
	}
	else if(motnum == 3)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_3 = motor_enable;
	}
	else if(motnum == 4)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_4 = motor_enable;
	}
	else if(motnum == 5)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_5 = motor_enable;
	}
	else if(motnum == 6)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_6 = motor_enable;
	}
	else if(motnum == 7)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_7 = motor_enable;
	}
	else if(motnum == 8)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_8 = motor_enable;
	}
	else if(motnum == 9)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_9 = motor_enable;
	}
	else if(motnum == 10)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_10 = motor_enable;
	}
	else if(motnum == 11)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_11 = motor_enable;
	}
	else if(motnum == 12)
	{
		pinMode(motor_enable, OUTPUT);		
		digitalWrite(motor_enable, HIGH);
		_motor_enable_12 = motor_enable;
	}
	else Serial.println("error: incorrect value for motor_pins, motor number"); //print error code
}

/////////////////////////////////////////////////////////
///////   Motor settings  ///////////////////////////////
/////////////////////////////////////////////////////////
void dodecastep::motor_go(int motnum, int step_size, int number_of_steps, int torque)
{
	_torque = torque;
	
	if(motnum == 1) //1st motor on 1st board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_1, dir);
		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step1); //high time
				cbi(PORTB, 5);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_1, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step2); 
				cbi(PORTB, 5);
				delayMicroseconds(step2);
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step4);
				cbi(PORTB, 5);
				delayMicroseconds(step4); 
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step8);
				cbi(PORTB, 5);
				delayMicroseconds(step8); 
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, HIGH);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step16); 
				cbi(PORTB, 5);
				delayMicroseconds(step16); 
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_1, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 2) //2nd motor on 1st board
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_1, dir);
		
		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step1); 
				cbi(PORTB, 5);
				delayMicroseconds(step1); 
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_2, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step2); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step2); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step4); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step4); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step8); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step8); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, HIGH);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step16); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step16); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_2, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 3) //3rd motor on 1st board
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_1, dir);
		
		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step1); //high time
				cbi(PORTB, 5);
				delayMicroseconds(step1); //low time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_3, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step2); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step2); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step4); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step4); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step8); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step8); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, HIGH);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step16); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step16); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_3, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 4) //4th motor on 1st board
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);

		digitalWrite(_b_dir_1, dir);

		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_4, LOW);   
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step1); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step1); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_4, HIGH);    
		}

		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, LOW);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step2); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step2); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_4, HIGH);    
		}

		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_11, LOW);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step4); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step4); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_4, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step8); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step8); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_4, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_11, HIGH);    
			digitalWrite(_b_ms_12, HIGH);    
			digitalWrite(_b_ms_13, HIGH);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTB, 5);
				delayMicroseconds(step16); //low time
				cbi(PORTB, 5);
				delayMicroseconds(step16); // high time
			}
			cbi(PORTB, 5);
			digitalWrite(_motor_enable_4, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 5) //1st motor on 2nd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_2, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_5, LOW);    // enable motor 5
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTE, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);    // disable motor 5
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_5, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step2); 
				cbi(PORTE, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_5, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step4);
				cbi(PORTE, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_5, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step8);
				cbi(PORTE, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, HIGH);
			
			digitalWrite(_motor_enable_5, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step16); 
				cbi(PORTE, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 6) //2nd motor on 2nd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_2, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_6, LOW);    // enable motor 6
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTE, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_5, HIGH);    // disable motor 6
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_6, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step2); 
				cbi(PORTE, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_6, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_6, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step4);
				cbi(PORTE, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_6, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_6, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step8);
				cbi(PORTE, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_6, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, HIGH);
			
			digitalWrite(_motor_enable_6, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step16); 
				cbi(PORTE, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_6, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 7) //3rd motor on 2nd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_2, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_7, LOW);    // enable motor 7
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTE, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_7, HIGH);    // disable motor 7
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_7, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step2); 
				cbi(PORTE, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_7, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_7, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step4);
				cbi(PORTE, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_7, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_7, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step8);
				cbi(PORTE, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_7, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, HIGH);
			
			digitalWrite(_motor_enable_7, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step16); 
				cbi(PORTE, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_7, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 8) //4th motor on 2nd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_2, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_8, LOW);    // enable motor 8
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTE, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_8, HIGH);    // disable motor 8
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, LOW);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_8, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step2); 
				cbi(PORTE, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_8, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_21, LOW);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_8, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step4);
				cbi(PORTE, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_8, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, LOW);
			
			digitalWrite(_motor_enable_8, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step8);
				cbi(PORTE, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_8, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_21, HIGH);    
			digitalWrite(_b_ms_22, HIGH);    
			digitalWrite(_b_ms_23, HIGH);
			
			digitalWrite(_motor_enable_8, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTE, 3);
				delayMicroseconds(step16); 
				cbi(PORTE, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_8, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}

	if(motnum == 9) //1st motor on 3rd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_3, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_9, LOW);    // enable motor 9
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTH, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_9, HIGH);    // disable motor 9
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_9, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step2); 
				cbi(PORTH, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_9, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_9, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step4);
				cbi(PORTH, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_9, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_9, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step8);
				cbi(PORTH, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_9, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, HIGH);
			
			digitalWrite(_motor_enable_9, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step16); 
				cbi(PORTH, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_9, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}

	if(motnum == 10) //2nd motor on 3rd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_3, dir); //2nd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_10, LOW);    // enable motor 10
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTH, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_10, HIGH);    // disable motor 10
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_10, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step2); 
				cbi(PORTH, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_10, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_10, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step4);
				cbi(PORTH, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_10, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_10, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step8);
				cbi(PORTH, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_10, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, HIGH);
			
			digitalWrite(_motor_enable_10, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step16); 
				cbi(PORTH, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_10, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
		if(motnum == 11) //3rd motor on 3rd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_3, dir); //3rd board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_11, LOW);    // enable motor 11
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTH, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_11, HIGH);    // disable motor 11
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_11, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step2); 
				cbi(PORTH, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_11, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_11, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step4);
				cbi(PORTH, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_11, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_11, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step8);
				cbi(PORTH, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_11, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, HIGH);
			
			digitalWrite(_motor_enable_11, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step16); 
				cbi(PORTH, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_11, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
		if(motnum == 12) //4rd motor on 3rd board
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_b_dir_3, dir); //4th board direction pinMode		
		// check to see what step size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_12, LOW);    // enable motor 10
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step1); //high time
				cbi(PORTH, 3);
				delayMicroseconds(step1); // low time
			}
			cbi(PORTE, 3);
			digitalWrite(_motor_enable_12, HIGH);    // disable motor 10
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, LOW);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_12, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step2); 
				cbi(PORTH, 3);
				delayMicroseconds(step2);
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_12, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_b_ms_31, LOW);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_12, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step4);
				cbi(PORTH, 3);
				delayMicroseconds(step4); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_12, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, LOW);
			
			digitalWrite(_motor_enable_12, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step8);
				cbi(PORTH, 3);
				delayMicroseconds(step8); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_12, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_b_ms_31, HIGH);    
			digitalWrite(_b_ms_32, HIGH);    
			digitalWrite(_b_ms_33, HIGH);
			
			digitalWrite(_motor_enable_12, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				sbi(PORTH, 3);
				delayMicroseconds(step16); 
				cbi(PORTH, 3);
				delayMicroseconds(step16); 
			}
			cbi(PORTH, 3);
			digitalWrite(_motor_enable_12, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	}
	
void dodecastep::stall(int motnum)
{
	if(motnum == 1)
	{
		digitalWrite(_motor_enable_1, LOW);
	}
	else if(motnum == 2)
	{
		digitalWrite(_motor_enable_2, LOW);
	}	
	else if(motnum == 3)
	{
		digitalWrite(_motor_enable_3, LOW);
	}	
	else if(motnum == 4)
	{
		digitalWrite(_motor_enable_4, LOW);
	}
	else Serial.println("error: incorrect value for stall"); //print error code		
}

void dodecastep::current_control(int step)
{
	if(step == 1)
	{
		step1 = STEPMIN + (_torque * 260);
	}
	else if(step == 2)
	{
		step2 = (STEPMIN + (_torque * 260)) / 2;
	}
	else if(step == 4)
	{
		step4 = (STEPMIN + (_torque * 260)) / 4;
	}
	else if(step == 8)
	{
		step8 = (STEPMIN + (_torque * 260)) / 8;
	}
	else if(step == 16)
	{
		step16 = (STEPMIN + (_torque * 260)) / 16;
	}
}
