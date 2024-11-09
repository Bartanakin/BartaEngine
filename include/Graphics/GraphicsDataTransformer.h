//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "Color.h"
#include "GraphicsData.h"

namespace Barta {

class GraphicsDataTransformer {
public:
    GraphicsDataTransformer(Color color1) noexcept;

    Barta::GraphicsData fromOBB(const OBB& obb) const;

private:
    Color color1;
};

}
