#pragma once

#include <set>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iterator>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned priority) override
	{
		m_observers.push_back({ &observer, priority });
	
		sort(m_observers.begin(), m_observers.end(), [](const auto & left, const auto & right) {
			return left.second < right.second;
		});
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto & observer : m_observers)
		{
			observer.first->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = find_if(m_observers.begin(), m_observers.end(), [&observer](const auto & element)
		{
			return element.first == &observer;
		}
		);
		m_observers.erase(it);
	}

protected:
	bool pairCompare(const std::pair<ObserverType *, unsigned> & firstElem, const std::pair<ObserverType *, unsigned> & secondElem) {
		return firstElem.second < secondElem.second;
	}
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::vector<std::pair<ObserverType *, unsigned>> m_observers;
};
