#pragma once
#include "BartaObjectInterface.h"
#include "Collisions/CollisionAwareInterface.h"
#include "Graphics/GraphicsDataAwareInterface.h"
#include "pch.h"

namespace Barta {

class ObjectManagerInterface {
public:
    using ObjectList = std::list<BartaObjectInterface*>;

    virtual ~ObjectManagerInterface() = default;

    virtual void addNewObject(BartaObjectInterface* newObject) = 0;

    virtual ObjectList getList() noexcept = 0;

    virtual void addDynamicsObject(DynamicsAwareInterface* dynamicsObject) = 0;

    virtual DynamicsAwareInterface::DynamicsAwareList& getDynamicsList() noexcept = 0;

    virtual void addGraphicsObject(GraphicsDataAwareInterface* dynamicsObject) = 0;

    virtual GraphicsDataAwareInterface::GraphicsDataAwareList& getGraphicsList() noexcept = 0;

    virtual void reduceDeleted() = 0;
};
}
