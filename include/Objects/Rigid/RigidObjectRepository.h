#pragma once


#include <Objects/Rigid/RigidObject.h>
#include <Graphics/Color.h>
#include <Predefines.h>
#include <ObjectManagerInterface.h>

namespace Barta {

    class RigidObjectRepository {
    public:
        RigidObjectRepository(
            Barta::ListManager& listManager,
            Barta::ObjectManagerInterface& objectManagerInterface
        ) noexcept;

        Barta::RigidObjectInterface* addNewAABB(Barta::Vector2f size, Barta::Color color, bool infiniteMass = true);
        Barta::RigidObjectInterface* addNewCircle(float radius, Barta::Color color);

    private:
        Barta::ListManager& listManager;
        Barta::ObjectManagerInterface& objectManager;
    };
}
