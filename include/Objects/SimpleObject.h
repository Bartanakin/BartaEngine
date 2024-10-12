#pragma once

#include <BartaObjectInterface.h>
#include "Graphics/GraphicsDataAwareInterface.h"

namespace Barta {

    class SimpleObject :
        public GraphicsDataAwareInterface {
    public:
        SimpleObject(
            GraphicsData graphicsData
        );
        ~SimpleObject() noexcept = default;

        bool isToBeDeleted() const override { return false; };

        GraphicsDataList getGraphicsData() override;

        void move(Vector2f shift);

    protected:
        GraphicsData graphicsData;
    };
}