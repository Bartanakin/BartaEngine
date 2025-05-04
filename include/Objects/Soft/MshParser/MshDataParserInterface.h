#pragma once
#include <Objects/Soft/Mesh.h>
#include <Objects/Soft/MshLoader/MshData.h>
#include <pch.h>

namespace Barta::Objects::Soft::MshParser {
using MshLoader::MshData;

class MshDataParserInterface {
public:
    MshDataParserInterface() = default;
    virtual ~MshDataParserInterface() = default;

    virtual Mesh parse(const MshLoader::MshData& mshData) const = 0;
};
}
