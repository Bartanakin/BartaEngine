//
// Created by barta on 02/03/2024.
//

#include <Objects/SimpleObject.h>

Barta::SimpleObject::SimpleObject(
    GraphicsData graphicsData
):
    graphicsData(std::move(graphicsData)) {}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::SimpleObject::getGraphicsData() {
    return {&this->graphicsData};
}
