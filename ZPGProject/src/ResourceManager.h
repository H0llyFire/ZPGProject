#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "gfx/trans/TransformComponent.h"

template<typename T>
class ResourceManager
{
public:
	std::unordered_map<std::string, std::shared_ptr<T>> Resources{};

	ResourceManager() = default;


	std::shared_ptr<T> Get(const std::string& name)
	{
		auto it = Resources.find(name);
		if(it != Resources.end())
			return it->second;
		return nullptr;
	}
	
	template<typename... Args>
	std::shared_ptr<T> Add(const std::string& name, Args&&... args)
	{
		if(std::shared_ptr<T> existing = Get(name))
			return existing;

		auto res = std::make_shared<T>(std::forward<Args>(args)...);
	    Resources[name] = res;
	    return res;
	}

	template<typename Subclass, typename... Args>
	std::shared_ptr<T> Add(const std::string& name, Args&&... args)
	{
	    return Move(name, std::make_shared<Subclass>(std::forward<Args>(args)...));
	}

	std::shared_ptr<T> Move(const std::string& name, std::shared_ptr<T> resource)
	{
	    if (std::shared_ptr<T> existing = Get(name))
	        return existing;

	    Resources[name] = std::move(resource);
	    return Resources[name];
	}
};
