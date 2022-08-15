#pragma once

#include <iostream>
#include<vector>
#include <memory>
#include<algorithm>
#include<bitset>
#include<array>

class Component; 
class Entity;
class Manager;

using ComponentID = std::size_t;   //component id is size_t
using Group = std::size_t;


//generating component ID to give ID for each components like.. physics, position, input handelling

inline ComponentID getNewComponentTypeID()  
{
	//the static component id keeps its value even among several calls to the function getNewComponentTypeID
	static ComponentID lastID = 0u;
	std::cout << " Created Component ID: " << lastID << std::endl;
	return lastID++; //new static value is returned
	//first time we call the function we get 1 , second time we run the function we get 2 and so on
}

//creating the template for grtcomponent to get the component ID of the type that is being passed into template (i.e the lastIDfor the component type passed in component ID )
//suppose physics last id 1, position lastid 2 etc
template <typename T> 
inline ComponentID getComponentTypeID() noexcept  //return componentID calling it getComponentID
{
	//generates new componentID for each getComponentID called
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}


//to tell if an entity has a component attached
constexpr std::size_t maxComponents = 32; //componets entity is able to hold
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset <maxComponents>;  //if an entity has selection of components ,to be able to compare weather it has required component or not
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents > ;


//base class of component
class Component
{
public:
	Entity* entity;  //entity pointer |reference to its owner
	virtual void init(){}//virtual :inorder to override them
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};

class Entity
{
private:
	Manager& manager; // manager reference
	bool active = true;//keep track if the entity is active else we remove them
	std::vector < std::unique_ptr<Component>> components; //list of all the component the entity is holding..|vector is dynamic memory allocation

	GroupBitset groupBitset;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:

	Entity(Manager& mManager):manager(mManager){}
	void update()
	{
		for (auto& c : components) c->update(); //loop through all its components and update and draw
		
	}
	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() const 
	{
		return active;
	}
	void destroy()  //when any of the components of the entity calls for destroy, the manager class will loop through and remove any inactive components
	{
		active = false; 
	}

	bool hasGroup(Group mGroup)  
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}


	//template for has component
	template <typename T>
	bool hasComponent() const //return a boolean called as hasComponent
	{
		return componentBitSet[getComponentTypeID<T>()];//return componentBitset and see if it matches getcomponentid |we ask is we have the component and ths function 
		//will return boolean weather we have it or not
	}


	//Tamplete for add component
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...)); //forwars rvalue or lvalue to c, depending on TArgs 
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;//ensure that the component type will always be put in the same position in the array
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T>          //tamplete for get component
	T& getComponent()const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager             //to keep list of all our entities
{
private:
	std::vector<std::unique_ptr<Entity >> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update()
	{
		for (auto & e : entities)
			e->update();
	}
	void draw()
	{
		for (auto& e : entities)
			e->draw();
	}
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}
			), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)  //remove the entities that are not active
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };  //initializing uprt to e
		entities.emplace_back(std::move(uPtr));  //adding the entity to our entity list
		return *e;
	}
};

