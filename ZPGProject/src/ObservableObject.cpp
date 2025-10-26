#include "ObservableObject.h"

#include "Observer.h"
#include "ObserverableArgs.h"

void ObservableObject::Attach(const std::shared_ptr<Observer>& observer)
{
	if(observer == nullptr)
		return;
	for(auto it = _observers.begin(); it != _observers.end(); )
	{
		std::shared_ptr<Observer> sharedPtr = it->lock();

		if(sharedPtr == observer)
			return;
		if(sharedPtr != nullptr)
			++it;
		else
			it = _observers.erase(it);
	}

	_observers.push_back(observer);
	observer->Notify(this, {});
}

void ObservableObject::Detach(const std::shared_ptr<Observer>& observer)
{
	for(auto it = _observers.begin(); it != _observers.end(); )
	{
		std::shared_ptr<Observer> sharedPtr = it->lock();

		if(sharedPtr == nullptr || sharedPtr == observer)
			it = _observers.erase(it);
		else
			++it;
	}
}

void ObservableObject::NotifyAll(const ObservableArgs& args)
{
	for(auto it = _observers.begin(); it != _observers.end(); )
	{
		if(const std::shared_ptr<Observer> obsPtr = it->lock())
		{
			obsPtr->Notify(this, args);
			++it;
		}
		else
			it = _observers.erase(it);
	}
}
