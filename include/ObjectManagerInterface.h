#pragma once
#include "pch.h"
#include "BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"

namespace Barta{

	class ObjectManagerInterface{
	public:
		using ObjectList = std::list<BartaObjectInterface*>;

		virtual ~ObjectManagerInterface() = default;

		virtual void addNewObject( BartaObjectInterface* const newObject ) = 0;

		virtual ObjectList getList() noexcept = 0;

		virtual void addCollidableObject(CollisionAwareInterface* const collidableObject) = 0;

		virtual const CollisionAwareInterface::CollidableList& getCollidableList() const noexcept = 0;

		virtual void addDynamicsObject(DynamicsAwareInterface* const dynamicsObject) = 0;

		virtual DynamicsAwareInterface::DynamicsAwareList& getDynamicsList() noexcept = 0;

		virtual void reduceDeleted() = 0;
	};
}

