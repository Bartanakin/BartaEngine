#pragma once
#include <ObjectManagerInterface.h>
#include <pch.h>

namespace Barta {
class BartaObjectManager: public ObjectManagerInterface {
public:
    BartaObjectManager() noexcept;

    virtual ~BartaObjectManager();

    void addNewObject(BartaObjectInterface* newObject) override;

    ObjectList getList() noexcept override;

    void addGraphicsObject(GraphicsDataAwareInterface* graphicsObject) override;

    GraphicsDataAwareInterface::GraphicsDataAwareList& getGraphicsList() noexcept override;

    void reduceDeleted() override;

private:
    ObjectList objectList;
    GraphicsDataAwareInterface::GraphicsDataAwareList graphicsList;
};
}
