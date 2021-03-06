// @file           iactor.h
// @author         flow@p0cki.net
// @date           09.2021
// @brief          interface of all actors

#ifndef _ISENSOR_h
#define _ISENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/* Constants */
#define SENSORS_GRAVITY_EARTH (9.80665F) /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON (1.6F)      /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN (275.0F)     /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX                                             \
  (60.0F) /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN                                             \
  (30.0F) /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA                                           \
  (1013.25F) /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS                                                    \
  (0.017453293F) /**< Degrees/s to rad/s multiplier                            \
                  */
#define SENSORS_RADS_TO_DPS                                                    \
  (57.29577793F) /**< Rad/s to degrees/s  multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA                                            \
  (100) /**< Gauss to micro-Tesla multiplier */

/** Sensor type */
enum sensor_type
{
	SENSOR_TYP_UNDEFINED = 1,
	SENSOR_TYP_DIGITAL_IN = 2,
	SENSOR_TYP_ANALOG_IN = 3,
	SENSOR_TYP_GYROSCOPE = 4,
	SENSOR_TYP_LIGHT = 5,
	SENSOR_TYP_PRESSURE = 6,
	SENSOR_TYP_PROXIMITY = 8,
	SENSOR_TYP_GRAVITY = 9,
	SENSOR_TYP_LINEAR_ACCELERATION = 10, /**< Acceleration not including gravity */
	SENSOR_TYP_ROTATION_VECTOR = 11,
	SENSOR_TYP_RELATIVE_HUMIDITY = 12,
	SENSOR_TYP_AMBIENT_TEMPERATURE = 13,
	SENSOR_TYP_OBJECT_TEMPERATURE = 14,
	SENSOR_TYP_VOLTAGE = 15,
	SENSOR_TYP_CURRENT = 16,
	SENSOR_TYP_COLOR = 17,
	SENSOR_TYP_ACCELEROMETER = 18, /**< Gravity + linear acceleration */
	SENSOR_TYP_MAGNETIC_FIELD = 19,
	SENSOR_TYP_ORIENTATION = 20,
	SENSOR_TYP_GAS = 22,
	SENSOR_TYP_PWM_IN = 23,
	SENSOR_TYP_CAPACITY = 24,
	SENSOR_TYP_CAM = 25
};

/** Sensor subtype */
enum  sensor_subtype
{
	SENSOR_SUB_UNDEFINED = 1,
	SENSOR_SUB_DHT = 2, /**< Temperature and Humidity*/
	SENSOR_SUB_TSL2561 = 3,
	SENSOR_SUB_MANUALLY = 4
};

/** struct sensors_vec_s is used to return a vector in a common format. */
struct sensor_vec {
	union {
		float		v[3];			///< 3D vector elements
		struct {
			float	x;				///< X component of vector
			float	y;				///< Y component of vector
			float	z;				///< Z component of vector
		};							///< Struct for holding XYZ component /* Orientation sensors */
		struct {
			float	roll;			/**< Rotation around the longitudinal axis (the plane body, 'X axis'). Roll is positive and increasing when moving downward. -90 degrees <= roll <= 90 degrees */
			float	pitch;			/**< Rotation around the lateral axis (the wing span, 'Y axis'). Pitch is positive and increasing when moving upwards. -180 degrees <= pitch <= 180 degrees) */
			float	heading;		/**< Angle between the longitudinal axis (the plane body) and magnetic north, measured clockwise when viewing from the top of the device. 0-359 degrees */
		};							///< Struct for holding roll/pitch/heading
	};								///< Union that can hold 3D vector array, XYZ components or				   ///< roll/pitch/heading
	int8_t			status;			///< Status byte
	uint8_t			reserved[3];	///< Reserved
};

/** struct sensors_color_s is used to return color data in a common format. */
struct sensor_color {
	union {
		float c[3];					///< Raw 3-element data /* RGB color space */
		struct {
			float	r;				/**< Red component */
			float	g;				/**< Green component */
			float	b;				/**< Blue component */
		};							///< RGB data in floating point notation
	};								///< Union of various ways to describe RGB colorspace
	uint32_t rgba;					/**< 24-bit RGBA value */
};

/** Sensor decoder struct */
struct sensor_decoder {
	int direction;						/**< position of decoder in +/- int */
	union {
		int	longClick;					/**< long click */
		int	shortClick;					/**< short click */
	};
};

/** Sensor gas struct */
struct sensor_gas {
	int raw;							/**< raw value */
	union {
		float	co2;					/**< co2 gas */
		float	co;						/**< co gas */
	};
};

/** Sensor pins */
union sensor_pins {
	struct {
		unsigned short pin1;		/**< pin 1 */
	} eins;
	struct {
		unsigned short pin1;		/**< pin 1 */
		unsigned short pin2;		/**< pin 2 */
	} zwei;
	struct {
		unsigned short pin1;		/**< pin 1 */
		unsigned short pin2;		/**< pin 2 */
		unsigned short pin3;		/**< pin 3 */
	} drei;
};

//union sensor_pin_values {
//	struct {
//		union {
//			float			float_value_pin1;		/**< value pin 1 */
//			int				int_value_pin1;			/**< value pin 1 */
//			bool			bool_value_pin1;		/**< value pin 1 */
//		};
//	} eins;
//	struct {
//		union {
//			float			float_value_pin1;		/**< value pin 1 */
//			int				int_value_pin1;			/**< value pin 1 */
//			bool			bool_value_pin1;		/**< value pin 1 */
//		};
//		union {
//			float			float_value_pin2;		/**< value pin 1 */
//			int				int_value_pin2;			/**< value pin 1 */
//			bool			bool_value_pin2;		/**< value pin 1 */
//		};
//	} zwei;
//	struct {
//		union {
//			float			float_value_pin1;		/**< value pin 1 */
//			int				int_value_pin1;			/**< value pin 1 */
//			bool			bool_value_pin1;		/**< value pin 1 */
//		};
//		union {
//			float			float_value_pin2;		/**< value pin 1 */
//			int				int_value_pin2;			/**< value pin 1 */
//			bool			bool_value_pin2;		/**< value pin 1 */
//		};
//		union {
//			float			float_value_pin3;		/**< value pin 1 */
//			int				int_value_pin3;			/**< value pin 1 */
//			bool			bool_value_pin3;		/**< value pin 1 */
//		};
//	} drei;
//};

/* Sensor event */
/** struct sensor_event is used to provide a single sensor event in a common
 * format. */
struct sensor_event {
	unsigned int		sensorid;				/**< unique sensor identifier */
	int32_t				type;					/**< sensor type */
	int32_t				timestamp;				/**< time is in milliseconds */
	union {
		float			data[4];				///< Raw data
		sensor_vec		acceleration;			/**< acceleration values are in meter per second (m/s^2) */
		sensor_vec		magnetic;				/**< magnetic vector values are in micro-Tesla (uT) */
		sensor_vec		orientation;			/**< orientation values are in degrees */
		sensor_vec		gyro;					/**< gyroscope values are in rad/s */
		float			temperature;			/**< temperature is in degrees centigrade (Celsius) */
		float			distance;				/**< distance in centimeters */
		float			light;					/**< light in SI lux units */
		float			pressure;				/**< pressure in hectopascal (hPa) */
		float			relative_humidity;		/**< relative humidity in percent */
		float			current;				/**< current in milliamps (mA) */
		float			voltage;				/**< voltage in volts (V) */
		bool			digital;				/**< 0/1 */
		sensor_gas		gas;					/**< co or co2 and raw value */
		sensor_color	color;					/**< color in RGB component values */
		sensor_decoder	decoder;				/**< direction of direction encoder */
	};  ///< Union for the wide ranges of data we can carry
};

class ISensor
{
	public:
		virtual					~ISensor()				= default;
		virtual bool			readEvent()				= 0;
		virtual sensor_event	getEvent()				= 0;
		virtual sensor_type		getType()				= 0;
		virtual sensor_subtype	getSubtype()			= 0;
		virtual char*			getName()				= 0;
		virtual sensor_pins		getPin()				= 0;
		virtual bool			setPin(sensor_pins p)	= 0;
};

#endif