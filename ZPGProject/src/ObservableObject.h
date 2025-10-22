#pragma once
#include <list>
#include <memory>

#include "Observer.h"

class ObservableObject
{
private:
    std::list<std::weak_ptr<Observer>> _observers;
public:
	void Attach(const std::shared_ptr<Observer>& observer);
	void Detach(const std::shared_ptr<Observer>& observer);

	void NotifyAll();
};
