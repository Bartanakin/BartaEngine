#pragma once
#include "../Events/BartaEventLoggerInterface.h"
#include "../Geometrics/Vector2f.h"
#include "../pch.h"
#include "GraphicsDataAwareInterface.h"

namespace Barta {
class BartaGraphicsBridgeInterface {
public:
    BartaGraphicsBridgeInterface() = default;
    virtual ~BartaGraphicsBridgeInterface() = default;

    virtual void createWindow(Vector2f size, std::string title) = 0;
    virtual void drawObjects(std::list<GraphicsDataAwareInterface*>& objects) = 0;
    virtual bool logEvents(BartaEventLoggerInterface& eventLogger) = 0;
};
}
