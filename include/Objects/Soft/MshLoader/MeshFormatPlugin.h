#pragma once
#include "MshLoaderPluginInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshLoader {
class MeshFormatPlugin: public virtual MshLoaderPluginInterface {
public:
    void loadMshData(std::istream& in, MshData& mshData) override;

    std::string getSectionKey() const override { return "$MeshFormat"; }

private:
    static constexpr std::array<std::string, 1> ALLOWED_VERSIONS = {"4.1"};
};
}
