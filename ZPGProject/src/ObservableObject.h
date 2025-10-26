#pragma once
#include <list>
#include <memory>

class ObservableArgs;
class Observer;

class ObservableObject
{
private:
    std::list<std::weak_ptr<Observer>> _observers;
public:
	virtual ~ObservableObject() = default;

	void Attach(const std::shared_ptr<Observer>& observer);
	void Detach(const std::shared_ptr<Observer>& observer);

	void NotifyAll(const ObservableArgs& args);
};
