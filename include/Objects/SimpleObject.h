#pragma once

#include "Graphics/GraphicsDataAwareInterface.h"
#include <BartaObjectInterface.h>

namespace Barta {

class SimpleObject: public GraphicsDataAwareInterface {
public:
    SimpleObject(GraphicsData graphicsData);
    ~SimpleObject() noexcept override = default;

    bool isToBeDeleted() const override { return false; }

    GraphicsDataList getGraphicsData() override;

protected:
    GraphicsData graphicsData;
};
}
