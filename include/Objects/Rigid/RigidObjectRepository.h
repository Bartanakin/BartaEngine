#pragma once

#include <Graphics/Color.h>
#include <ObjectManagerInterface.h>
#include <Predefines.h>

namespace Barta {

class RigidObjectRepository {
public:
    RigidObjectRepository(ListManager& listManager, ObjectManagerInterface& objectManagerInterface) noexcept;

    RigidObjectInterface* addNewAABB(Vector size, Color color, bool infiniteMass = true);

    RigidObjectInterface* addNewCircle(PrecisionType radius, Color color);

    RigidObjectInterface* addNewOBB(Vector size, PrecisionType rotation, Color color);

private:
    ListManager& listManager;
    ObjectManagerInterface& objectManager;
};
}
