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

        Barta::RigidObject* addNewAABB(Barta::Vector2f size, Barta::Color color, bool infiniteMass = true);
        Barta::RigidObject* addNewCircle(float radius, Barta::Color color);

    private:
        Barta::ListManager& listManager;
        Barta::ObjectManagerInterface& objectManager;
    };
}
