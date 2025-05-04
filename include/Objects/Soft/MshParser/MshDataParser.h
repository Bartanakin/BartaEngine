#pragma once
#include <Objects/Soft/MshParser/MshDataParserInterface.h>
#include <pch.h>

namespace Barta::Objects::Soft::MshParser {
class MshDataParser: public MshDataParserInterface {
public:
    MshDataParser() = default;
    Mesh parse(const MshData& mshData) const override;
};
}
