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
	double count = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	std::map < std::string, StatsData> m_stats;

	void Update(SWeatherInfo const& data) override
	{
		StatsData statsData;
		for (auto statPair : data.sensors)
		{
			if (m_stats.find(statPair.first) == m_stats.end())
			{
				m_stats[statPair.first] = StatsData();
			}
			if (m_stats.at(statPair.first).min > statPair.second)
			{
				m_stats.at(statPair.first).min = statPair.second;
			}
			if (m_stats.at(statPair.first).max < statPair.second)
			{
				m_stats.at(statPair.first).max = statPair.second;
			}
			m_stats.at(statPair.first).sum += statPair.second;
			++m_stats.at(statPair.first).count;

			std::cout << "Max " << statPair.first << ": " << m_stats.at(statPair.first).max << std::endl;
			std::cout << "Min " << statPair.first << ": " << m_stats.at(statPair.first).min << std::endl;
			std::cout << "Average " << statPair.first << ": " << (m_stats.at(statPair.first).sum / m_stats.at(statPair.first).count) << std::endl;
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
		return humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		humidity = humidity;
		m_temperature = temp;
		pressure = pressure;

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
	double humidity = 0.0;	
	double pressure = 760.0;	
};
