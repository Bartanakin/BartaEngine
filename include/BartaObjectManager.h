#pragma once
#include "pch.h"
#include "ObjectManagerInterface.h"

namespace Barta{
	class BartaObjectManager : public ObjectManagerInterface{
	public:
		BartaObjectManager() noexcept;

		virtual ~BartaObjectManager();

		virtual void addNewObject( BartaObjectInterface* newObject ) override;

		virtual ObjectList getList() noexcept override;

		virtual void addDynamicsObject(DynamicsAwareInterface* dynamicsObject) override;

		virtual DynamicsAwareInterface::DynamicsAwareList& getDynamicsList() noexcept override;

        virtual void addGraphicsObject(GraphicsDataAwareInterface* dynamicsObject) override;

        virtual GraphicsDataAwareInterface::GraphicsDataAwareList& getGraphicsList() noexcept  override;
		
		virtual void reduceDeleted() override;

	private:
		ObjectList objectList;
		DynamicsAwareInterface::DynamicsAwareList dynamicsList;
        GraphicsDataAwareInterface::GraphicsDataAwareList graphicsList;
	};
}

