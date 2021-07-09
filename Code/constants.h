// @file           home_constants.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          define all constants

#ifndef _HOME_CONSTANTS_h
#define _HOME_CONSTANTS_h

// verwendete Hardware
// es darf immer nur eine Zeile true sein!
#define NANO		true
#define NodeMCUV3	false
#define UNO			false // noch nicht verwendet
#define MEGA		false // noch nicht verwendet


//****** WS2812 OUTPUT PINS ******
// PIN_WS2812_1:	5 (Nano), 15 (nodeMCU V3)
// PIN_WS2812_2:	12 (Nano), 4 (nodeMCU V3)
#if (NANO == true)
#define PIN_WS2812_1	5
#define PIN_WS2812_2	12
#endif
#if (NodeMCUV3 == true)
#define PIN_WS2812_1	4
#define PIN_WS2812_2	15
#endif

//****** ANZAHL DER WS2812B LEDS PRO STRIPE ******
#define	NUM_LEDS_1		15
#define	NUM_LEDS_2		60

//****** PWM OUTPUT PINS ******
// On most Arduino boards(those with the ATmega168 or ATmega328), this function works on pins 3, 5, 6, 9, 10,
// and 11. On the Arduino Mega, it works on pins 2 - 13 and 44 - 46. Older Arduino boards with an
// ATmega8 only support analogWrite() on pins 9, 10, and 11. 
// PIN_PWM_1:	6 (Nano), 0 (nodeMCU V3)
// PIN_PWM_2:	9 (Nano), 2 (nodeMCU V3)
#if (NANO == true)
#define PIN_PWM_1		9
#define PIN_PWM_2		
#endif
#if (NodeMCUV3 == true)
#define PIN_PWM_1		0
#define PIN_PWM_2		2
#endif


//****** INPUT PINS ******
#if (NANO == true)
#define	PIN_HUM_1		6
#define	PIN_TOUCH_2		4
#define	PIN_MOTION_1	8
#define	PIN_MOTION_2	
#define PIN_SONIC_1		
#define PIN_SONIC_2
#define PIN_GAS_MQ135_1	A6
#define PIN_GAS_MQ7_1	A7
#define PIN_DUST_1		12
#define PIN_ENCODER_SW	2
#define PIN_ENCODER_DT	11
#define PIN_ENCODER_CLK	12
#endif
#if (NodeMCUV3 == true)
#define	PIN_HUM_1		14
#define	PIN_TOUCH_2		16
#define	PIN_MOTION_1	10
#define	PIN_MOTION_2	
#define PIN_SONIC_1		
#define PIN_SONIC_2
#define PIN_GAS_MQ135_1	A0
#define PIN_GAS_MQ7_1	
#define PIN_DUST_1		
#define PIN_ENCODER_SW	9
#define PIN_ENCODER_DT	13
#define PIN_ENCODER_CLK	12
#endif


//****** DEFAULT *********
#define	DEFAULT_LOGLEVEL		debug
#define	DEFAULT_LOGTARGET		serial
#define	DEFAULT_LIGHTFDELAY		20
#define DEFAULT_THRESHOLD		0.5
#define DEFAULT_MAXVALUE		255
#define DEFAULT_MINVALUE		0
#define DEFAULT_ALLLEDS			-1
#define DEFAULT_BAUTRATE		9600

//****** DEFAULT WS2812 Values *********
#define DEFAULT_NEOPIXEL_MaxDunkelZyklen		1
#define DEFAULT_NEOPIXEL_MaxHellZyklen			1
#define DEFAULT_NEOPIXEL_MaxHelligkeit			255
#define DEFAULT_NEOPIXEL_MinHelligkeit			0
#define DEFAULT_NEOPIXEL_AnteilLedsZumAufhellen	8		// 4 = Viertel
#define DEFAULT_NEOPIXEL_AnteilLedsZumAbdunkeln 8		// 4 = Viertel
#define DEFAULT_NEOPIXEL_Inkrement				1		// 1 2.55 5.1 (für 255)
#define DEFAULT_NEOPIXEL_Dekrement				1		// 1 2.55 5.1 (für 255)
#define DEFAULT_NEOPIXEL_Timing					50		// 10 = Zentel  / 50 = 50stel

// Definitionen der einzelnen Schaltzeiten
#define		laufzeit_1		1UL
#define		laufzeit_5		5UL
#define		laufzeit_10		10UL
#define		laufzeit_15		15UL
#define		laufzeit_20		20UL
#define		laufzeit_25		25UL
#define     laufzeit_30		30UL
#define     laufzeit_50		50UL
#define     laufzeit_150	100UL
#define     laufzeit_100	150UL
#define     laufzeit_250	250UL
#define     laufzeit_500	500UL
#define     laufzeit_1k		1000UL
#define     laufzeit_1k5	1500UL
#define     laufzeit_2k		2000UL
#define     laufzeit_2k5	2500UL
#define     laufzeit_5k		5000UL

// Color Decisions

#define		   CHANGEHUE_AQUA		temp <= 20
#define		   CHANGEHUE_BLUE		temp > 20 && temp <= 23
#define		   CHANGEHUE_GREEN		temp > 23 && temp <= 25
#define		   CHANGEHUE_YELLOW		temp > 25 && temp <= 27
#define		   CHANGEHUE_ORANGE		temp > 27 && temp <= 30
#define		   CHANGEHUE_RED		temp > 30

/*#define		   CHANGEHUE_AQUA		temp <= 20 && hum <= 50
#define		   CHANGEHUE_BLUE		temp > 20 && temp <= 23 && hum <= 50
#define		   CHANGEHUE_GREEN		temp > 23 && temp <= 25 && hum > 55
#define		   CHANGEHUE_YELLOW		temp > 25 && temp <= 27 && hum >= 60
#define		   CHANGEHUE_ORANGE		temp > 27 && temp <= 30 && hum >= 70
#define		   CHANGEHUE_RED		temp > 30 && hum >= 80*/

#endif