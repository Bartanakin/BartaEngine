#pragma once
#include <Objects/Soft/MeshLoader/MshDataParserInterface.h>
#include <pch.h>

namespace Barta::Objects::Soft::MeshLoader {
class MshDataParser: public MshDataParserInterface {
public:
    MshDataParser() = default;
    Mesh parse(const MshData& mshData) const override;
};
}
