#pragma once
#include "Graphics/GraphicsData.h"
#include "ReduceableList.h"
#include <BartaObjectInterface.h>

namespace Barta {

class GraphicsDataAwareInterface: public virtual BartaObjectInterface {
public:
    using GraphicsDataList = std::vector<GraphicsData*>;

    using GraphicsDataAwareList = ReducibleList<std::list<GraphicsDataAwareInterface*>>;

    virtual ~GraphicsDataAwareInterface() noexcept = default;

    virtual GraphicsDataList getGraphicsData() = 0;
};
}
