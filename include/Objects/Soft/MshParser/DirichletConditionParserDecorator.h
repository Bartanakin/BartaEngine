#pragma once
#include "MshDataParserInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshParser {
class DirichletConditionParserDecorator: public virtual MshDataParserInterface {
public:
    explicit DirichletConditionParserDecorator(MshDataParserInterface& decorated) noexcept;

    Mesh parse(const MshData& mshData) const override;

private:
    MshDataParserInterface& decorated;
};
}
