#pragma once
#include <Objects/Soft/Mesh.h>
#include <Objects/Soft/MeshLoader/MshData.h>
#include <pch.h>

namespace Barta::Objects::Soft::MeshLoader {
class MshDataParserInterface {
public:
    MshDataParserInterface() = default;
    virtual ~MshDataParserInterface() = default;

    virtual Mesh parse(const MshData& mshData) const = 0;
};
}
