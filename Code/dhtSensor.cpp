// 
// 
// 

#include "DHT.h"
#include "dhtSensor.h"
#include "logger.h"

dhtSensor::dhtSensor(String n, int p)
	:sensor(t_sensor_type::DHT_sens, n, p)
{
	dht.begin();
}

dhtSensor::~dhtSensor()
= default;

float dhtSensor::getTempValue(logger &log)
{
	temp = dht.readTemperature();
	log.writeLog("Temperature = " + String(temp) + "C", sensordata);
	return temp;
}

float dhtSensor::getHumValue(logger &log)
{
	hum = dht.readHumidity();
	log.writeLog("Humidity = " + String(hum) + "%", sensordata);
	return hum;
}

float dhtSensor::getTempValueOnlyIfChanged(logger &log)
{
	temp = dht.readTemperature();
	if (temp != savetemp)
	{
		log.writeLog("Temperature = " + String(temp) + "C", sensordata);
		savetemp = temp;
	}
	return temp;
}

float dhtSensor::getHumValueOnlyIfChanged(logger &log)
{
	hum = dht.readHumidity();
	if (hum != savehum)
	{
		log.writeLog("Humidity = " + String(hum) + "%", sensordata);
		savehum = hum;
	}
	return hum;
}