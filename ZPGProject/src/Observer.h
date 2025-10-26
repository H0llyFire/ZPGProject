#pragma once

class ObservableObject;
class ObservableArgs;

class Observer
{
public:
	virtual void Notify(ObservableObject* sender, const ObservableArgs& args) = 0;
};
