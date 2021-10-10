// @file           iactor.h
// @author         flow@p0cki.net
// @date           09.2021
// @brief          interface of all actors

#ifndef _IACTOR_h
#define _IACTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/** Actor type */
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

/** Actor subtype */
enum actor_subtype
{
	ACTOR_SUB_UNDEFINED = 1,
	ACTOR_SUB_RESERVE1 = 2,
	ACTOR_SUB_RESERVE2 = 3
};

/** Actor subtype */
enum neopixel_effect
{
	EFFECT_SET_HUE = 1,
	EFFECT_SET_SAT = 2,
	EFFECT_SET_VAL = 3,
	EFFECT_SET_HSV = 4,
	EFFECT_SET_RGB = 5,
	EFFECT_SET_R = 6,
	EFFECT_SET_G = 7,
	EFFECT_SET_B = 8,
	EFFECT_FADE_2_COLOR = 9,
	EFFECT_TWINKLE_RANDOM = 10,
	EFFECT_FADE_BRIGHTNESS = 11,
	EFFECT_COLORSHIFT = 12,
	EFFECT_NIGHTRIDER = 13,
};

/** Actor RGB struct */
struct actor_rgb {
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

/** Actor neopixel struct */
struct actor_neopixel {
	short led; /**< Which Led, -1 is all Leds */
	neopixel_effect effect_type;
	union {
		struct CRGB {
			union {
				struct {
					union {
						uint8_t r;
						uint8_t red;
					};
					union {
						uint8_t g;
						uint8_t green;
					};
					union {
						uint8_t b;
						uint8_t blue;
					};
				};
				uint8_t raw[3];
			};
		} CRGB; /// Representation of an RGB pixel (Red, Green, Blue)
		struct CHSV {
			union {
				struct {
					union {
						uint8_t hue;
						uint8_t h;
					};
					union {
						uint8_t saturation;
						uint8_t sat;
						uint8_t s;
					};
					union {
						uint8_t value;
						uint8_t val;
						uint8_t v;
					};
				};
				uint8_t raw[3];
			};
		} CHSV; /// Representation of an HSV pixel (hue, saturation, value (aka brightness)).
	};
	union
	{
		struct default
		{

		} default;
		struct randompulse
		{

		} randompulse;
		struct colorshift
		{
			short direction;
			bool sensorResult;
		} colorshift;
		struct twinkle_random
		{

		} twinkle_random;
		struct fade_2_color
		{
			// Nutzt CHSV / CRGB Struct
		};
		struct fade_brightness
		{
			bool sensorResult;
			byte maxBrightness;
		} fade_brightness;
		struct nightrider
		{

		} nightrider;
	} var;
};

/** Actor event struct */
struct actor_event {
	unsigned int		actorid;				/**< unique sensor identifier */
	int32_t				type;					/**< sensor type */
	int32_t				timestamp;				/**< time is in milliseconds */
	union {
		float			data[4];				///< Raw data
		float			pwmsignal;				/**< pwm signal */
		char*			savedata;				/**< data savings */
		float			voltage;				/**< voltage in volts (V) */
		bool			digital;				/**< 0/1 */
		actor_rgb		rgb;					/**< color in RGB component values */
		actor_neopixel	neopixel;
	};  ///< Union for the wide ranges of data we can carry
};

/** Actor pins */
union actor_pins {
	struct {
		unsigned short	pin1;		/**< pin 1 */
	} eins;
	struct {
		unsigned short	pin1;		/**< pin 1 */
		unsigned short	pin2;		/**< pin 2 */
	} zwei;
	struct {
		unsigned short	pin1;		/**< pin 1 */
		unsigned short	pin2;		/**< pin 2 */
		unsigned short	pin3;		/**< pin 3 */
	} drei;

};

class IActor
{
    public:
        virtual					~IActor()					= default;
        virtual actor_type		getType()					= 0;
		virtual actor_subtype	getSubtype()				= 0;
		virtual char*			getName()					= 0;
		virtual actor_pins		getPin()					= 0;
		virtual actor_event		getEvent()					= 0;
		virtual bool			setEvent(actor_event event)	= 0;
		virtual bool			setEvent(int event)			= 0;
		virtual bool			setEvent(float event)		= 0;
		virtual bool			fireEvent()					= 0;
		virtual bool			setPin(actor_pins p)		= 0;
};

#endif