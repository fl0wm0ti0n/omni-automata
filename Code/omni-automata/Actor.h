// @file           actor.h
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#ifndef _ACTOR_h
#define _ACTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum actor_type
{
	ACTOR_TYP_UNDEFINED = 1,
	ACTOR_TYP_DIGITAL_OUT = 2,
	ACTOR_TYP_ANALOG_OUT = 3,
	ACTOR_TYP_SERVO = 4,
	ACTOR_TYP_BRUSHLESSMOTOR = 5,
	ACTOR_TYP_STEPMOTOR = 6,
	ACTOR_TYP_WS2812 = 7,
	ACTOR_TYP_PWM_OUT = 8,
	ACTOR_TYP_RGB = 9,
	ACTOR_TYP_LCD = 10,
	ACTOR_TYP_SRAM = 11,
	ACTOR_TYP_SDCARD = 12
};

enum actor_suhbtype
{
	ACTOR_SUB_UNDEFINED = 1,
	ACTOR_SUB_RESERVE1 = 2,
	ACTOR_SUB_RESERVE2 = 3
};

struct actor_color {
	union {
		float c[3];		///< Raw 3-element data
		/* RGB color space */
		struct {
			float r;	/**< Red component */
			float g;	/**< Green component */
			float b;	/**< Blue component */
		};				///< RGB data in floating point notation
	};					///< Union of various ways to describe RGB colorspace
	uint32_t rgba;		/**< 24-bit RGBA value */
};

struct actor_event {
	unsigned int		actorid;	/**< unique sensor identifier */
	int32_t				type;		/**< sensor type */
	int32_t				timestamp;	/**< time is in milliseconds */
	union {
		float			data[4];				///< Raw data
		float			pwmsignal;				/**< pwm signal */
		char*			savedata;				/**< data savings */
		float			voltage;				/**< voltage in volts (V) */
		bool			digital;				/**< 0/1 */
		actor_color		color;					/**< color in RGB component values */
	};  ///< Union for the wide ranges of data we can carry
};

class Actor
{

 public:
	 Actor(actor_type t, actor_suhbtype s, char n[], int p);
	 Actor(actor_type t, actor_suhbtype s, char n[], int p1, int p2, int p3);
	 virtual ~Actor();

	 actor_type getType()
		{return type_;}
	 
	 char* getName()
		{return name_;}
	 
	 int getValue()
		{return value_;}

	 int getPin()
		{ return pin1_;}

	 int setPin(int p)
	 {
		 pin1_ = p;
		 pinMode(pin1_, OUTPUT);
		 return true;
	 }
	
	 virtual bool setValue(int v);

protected:
		actor_type type_;
		char* name_;
		int value_;
		int pin1_;
		int	pin2_;
		int	pin3_;
		int id_;				// instance id
		static int current_id;	// static for sensor id shared between all instances

};
#endif