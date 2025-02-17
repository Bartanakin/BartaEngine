//
// Created by barta on 02/03/2024.
//

#include <Objects/SimpleObject.h>

Barta::SimpleObject::SimpleObject(
    GraphicsData graphicsData
):
    graphicsData(std::move(graphicsData)) {}

void Barta::SimpleObject::move(
    const Vector& shift
) {
    this->graphicsData.transformation = Transformation::translation(shift) * this->graphicsData.transformation;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::SimpleObject::getGraphicsData() {
    return {&this->graphicsData};
}
