#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "gfx/trans/Transform.h"


template<typename T>
class ResourceManager
{
	std::unordered_map<std::string, std::shared_ptr<T>> _resources{};
public:
	ResourceManager() = default;


	std::shared_ptr<T> Get(const std::string& name)
	{
		auto it = _resources.find(name);
		if(it != _resources.end())
			return it->second;
		return nullptr;
	}
	
	template<typename... Args>
	std::shared_ptr<T> Add(const std::string& name, Args&&... args)
	{
		if(std::shared_ptr<T> existing = Get(name))
			return existing;

		auto res = std::make_shared<T>(std::forward<Args>(args)...);
        _resources[name] = res;
        return res;
	}

	template<typename Subclass, typename... Args>
	std::shared_ptr<Transform> Add(const std::string& name, Args&&... args)
	{
	    return Add(name, std::make_shared<Subclass>(std::forward<Args>(args)...));
	}

	std::shared_ptr<T> Add(const std::string& name, std::shared_ptr<T> resource)
    {
        if (std::shared_ptr<T> existing = Get(name))
            return existing;

        _resources[name] = std::move(resource);
        return _resources[name];
    }
};
