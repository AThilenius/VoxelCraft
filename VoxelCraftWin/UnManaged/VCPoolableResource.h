//
//  VCPoolableResource.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/4/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

struct ResourceLifespan
{
	enum Value
	{
		DEFAULT				= 1,
		USAGE               = 1,
		LEVEL               = 2,
		APPLICATION         = 3
	};
};

template<typename T, typename TParam>
class VCPoolableResource
{
public:
	static std::shared_ptr<T> Get (std::string path, TParam params = TParam(),  ResourceLifespan::Value lifespan = ResourceLifespan::DEFAULT);
	
public:
	std::weak_ptr<T> WeakPtr;

private:
	static std::unordered_map<std::string, std::weak_ptr<T>> m_resourceMap;
	static std::vector<std::shared_ptr<T>> m_applicationLifespanObjects;
};

template<class T, typename TParam>
std::shared_ptr<T> VCPoolableResource<T, TParam>::Get( std::string path, TParam params, ResourceLifespan::Value lifespan )
{
	auto iter = T::m_resourceMap.find(path);
	if (iter != T::m_resourceMap.end())
	{
		std::shared_ptr<VCTexture> tlock = iter->second.lock();
		if (tlock)
			return tlock;
	}

	// Allocate / ReAllocate
	T* tex = T::Create(path, params);
	std::shared_ptr<T> ptr (tex);
	tex->WeakPtr = ptr;

	// Hold a weak reference in map
	T::m_resourceMap[path] = ptr;

	// If Application-Level, hold a strict reference so object is never freed
	if (lifespan == ResourceLifespan::APPLICATION)
		T::m_applicationLifespanObjects.push_back(ptr);

	return ptr;
}
