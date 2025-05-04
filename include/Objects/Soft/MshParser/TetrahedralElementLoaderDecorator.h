#pragma once
#include "MshDataParserInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshParser {
class TetrahedralElementLoaderDecorator: public virtual MshDataParserInterface {
public:
    TetrahedralElementLoaderDecorator(MshDataParserInterface& decorated) noexcept;

    Mesh parse(const MshData& mshData) const override;

private:
    MshDataParserInterface& decorated;
};
}
