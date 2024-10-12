#pragma once

#include <Graphics/Color.h>
#include <ObjectManagerInterface.h>
#include <Predefines.h>

namespace Barta {

class RigidObjectRepository {
public:
    RigidObjectRepository(ListManager& listManager, ObjectManagerInterface& objectManagerInterface) noexcept;

    RigidObjectInterface* addNewAABB(Vector2f size, Color color, bool infiniteMass = true);

    RigidObjectInterface* addNewCircle(float radius, Color color);

private:
    ListManager& listManager;
    ObjectManagerInterface& objectManager;
};
}
