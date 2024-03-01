#pragma once
#include "pch.h"
#include "ObjectManagerInterface.h"

namespace Barta{
	class BartaObjectManager : public ObjectManagerInterface{
	public:
		BartaObjectManager() noexcept;

		virtual ~BartaObjectManager();

		virtual void addNewObject( BartaObjectInterface* const newObject ) override;

		virtual ObjectList getList() noexcept override;

		virtual void addCollidableObject(CollisionAwareInterface* const collidableObject) override;

		virtual const CollisionAwareInterface::CollidableList& getCollidableList() const noexcept override;

		virtual void addDynamicsObject(DynamicsAwareInterface* const dynamicsObject) override;

		virtual DynamicsAwareInterface::DynamicsAwareList& getDynamicsList() noexcept override;
		
		virtual void reduceDeleted() override;

	private:
		ObjectList objectList;
		CollisionAwareInterface::CollidableList collidableList;
		DynamicsAwareInterface::DynamicsAwareList dynamicsList;
	};
}

