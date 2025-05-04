#pragma once
#include "MshLoaderPluginInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshLoader {
class EntitiesPlugin: public virtual MshLoaderPluginInterface {
public:
    void loadMshData(std::istream& in, MshData& mshData) override;

    std::string getSectionKey() const override { return "$Entities"; }
};
}
