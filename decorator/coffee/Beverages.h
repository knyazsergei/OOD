#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string & description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(unsigned quantity = 1):CCoffee("Capuccino"), m_quantity(quantity)
	{}

	double GetCost() const override 
	{
		switch (m_quantity) {
		case 1:
			return 80;
		case 2:
			return 120;
		default:
			return 80;
		}
	}
private:
	unsigned m_quantity = 1;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(unsigned quantity = 1):CCoffee("Latte"), m_quantity(quantity)
	{}

	double GetCost() const override 
	{
		switch (m_quantity) {
		case 1:
			return 90;
		case 2:
			return 130;
		default:
			return 90;
		} 
	}
private:
	unsigned m_quantity = 1;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class СFireweed : public CTea//Иван чай
{
public:
	СFireweed() :CTea("Fireweed tea")
	{}

	double GetCost() const override
	{
		return 45;
	}
};


class СPuerh : public CTea//Пу-эр
{
public:
	СPuerh() :CTea("Pu-erh tea")
	{}

	double GetCost() const override
	{
		return 35;
	}
};

class СGoldenTea : public CTea//Золотой чай
{
public:
	СGoldenTea() :CTea("Golden tea")
	{}

	double GetCost() const override
	{
		return 60;
	}
};

class СGreenTea : public CTea//Зеленый чай
{
public:
	СGreenTea() :CTea("Green tea")
	{}

	double GetCost() const override
	{
		return 20;
	}
};	

enum class SizeOfCoctale
{
	small = 1,
	normal = 2,
	big = 3
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(SizeOfCoctale size = SizeOfCoctale::small)
		:CBeverage("Milkshake"), m_size(static_cast<unsigned>(size))
	{}

	double GetCost() const override 
	{ 
		switch (m_size)
		{
		case 1:
			return 50;
		case 2:
			return 60;
		case 3:
			return 80;
		default:
			return 50;
			break;
		}
	}
protected:
	unsigned m_size = 1;
};
