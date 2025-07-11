#pragma once
#include "MshDataParserInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshParser {
class SurfaceFacesMshParserDecorator: public MshDataParserInterface {
public:
    SurfaceFacesMshParserDecorator(MshDataParserInterface& decorated) noexcept;

    Mesh parse(const MshData& mshData) const override;

private:
    MshDataParserInterface& decorated;
};
}
