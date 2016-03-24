#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <climits>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	std::map < std::string, double > sensors;
	SWeatherInfo()
	{
		sensors["temperature"] = 0;
		sensors["humidity"] = 0;
		sensors["pressure"] = 0;
	}
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Display:" << std::endl;
		std::cout << "Current Temp " << data.sensors.at("temperature") << std::endl;
		std::cout << "Current Hum " << data.sensors.at("humidity") << std::endl;
		std::cout << "Current Pressure " << data.sensors.at("pressure") << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

struct StatsData{
	double max = -std::numeric_limits<double>::infinity();
	double min = std::numeric_limits<double>::infinity();
	double sum = 0;
	double average = 0;
	unsigned count = 0;
	
	void update(const double & value)
	{
		++count;

		if (min > value)
		{
			min = value;
		}
		if (max < value)
		{
			max = value;
		}
		sum += value;
		average = sum / count;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	std::map < const std::string, StatsData> m_stats;

	void Update(SWeatherInfo const& data) override
	{
		cout << "Stats:" << std::endl;
		for (auto & statPair : data.sensors)
		{
			//для лучшей читабельности
			StatsData & statsData = m_stats[statPair.first];
			const std::string & sensorTypeName = statPair.first;
			
			statsData.update(statPair.second);

			std::cout << "Max " << sensorTypeName << ": " << statsData.max << std::endl;
			std::cout << "Min " << sensorTypeName << ": " << statsData.min << std::endl;
			std::cout << "Average " << sensorTypeName << ": " << statsData.average << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.sensors.at("temperature") = GetTemperature();
		info.sensors.at("humidity") = GetHumidity();
		info.sensors.at("pressure") = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
};
