#pragma once
#include "Objects/Soft/MshParser/MshDataParserInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Barta::Objects::Soft::MshParser;

class MshDataParserMock: public MshDataParserInterface {
public:
    MOCK_METHOD(Barta::Objects::Soft::Mesh, parse, (const MshData&), (const, override));
};
