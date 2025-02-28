//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include <Geometrics/BartaShapes/OBB.h>
#include <Graphics/Color.h>
#include <Graphics/GraphicsData.h>

namespace Barta {

class GraphicsDataTransformer {
public:
    GraphicsDataTransformer(Color color1) noexcept;

    GraphicsData fromOBB(const OBB& obb) const;

private:
    Color color1;
};

}
