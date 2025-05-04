#pragma once

#include "MshData.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshLoader {

class MshLoaderPluginInterface {
public:
    virtual ~MshLoaderPluginInterface() = default;

    virtual void loadMshData(std::istream& in, MshData& mshData) = 0;
    virtual std::string getSectionKey() const = 0;
};

}
