#include <Objects/Soft/MshParser/DirichletConditionParserDecorator.h>
#include "MshDataParserMock.h"

using namespace Barta::Objects::Soft::MshParser;

TEST(
    DirichletConditionParserDecoratorTest,
    MarksNodesWithDirichletCondition
) {
    MshDataParserMock mockParser;

    MshData mshData;

    mshData.physicalGroups = {
        {1, 2, "\"SomeOtherCondition\""},
        {2, 2, "\"DirichletCondition\""}
    };

    mshData.entities[MshData::EntityDimension::SURFACE] = {
        {.tag = 101, .physicalGroupTags = {2}},
        {.tag = 102, .physicalGroupTags = {1}},
    };

    mshData.triangleElements = {
        {.entityTag = 101, .nodeTags = {10, 11, 12}},
        {.entityTag = 102, .nodeTags = {13, 14, 15}}
    };

    Barta::Objects::Soft::Mesh initialMesh;
    Barta::Objects::Soft::Node node;
    node.isZeroDirichlet = false;

    node.tag = 10;
    initialMesh.nodes.push_back(node);
    node.tag = 11;
    initialMesh.nodes.push_back(node);
    node.tag = 12;
    initialMesh.nodes.push_back(node);
    node.tag = 13;
    initialMesh.nodes.push_back(node);
    node.tag = 14;
    initialMesh.nodes.push_back(node);
    node.tag = 15;
    initialMesh.nodes.push_back(node);
    node.tag = 16;
    initialMesh.nodes.push_back(node);

    EXPECT_CALL(mockParser, parse(testing::_)).WillOnce(testing::Return(initialMesh));

    DirichletConditionParserDecorator decorator(mockParser);

    Barta::Objects::Soft::Mesh finalMesh = decorator.parse(mshData);

    bool dirichletStarted = false;
    for (const auto& node: finalMesh.nodes) {
        if (node.tag == 10 || node.tag == 11 || node.tag == 12) {
            EXPECT_TRUE(node.isZeroDirichlet) << "Node " << node.tag << " should be marked as Dirichlet.";
            dirichletStarted = true;
        } else {
            EXPECT_FALSE(node.isZeroDirichlet) << "Node " << node.tag << " should not be marked as Dirichlet.";
            EXPECT_FALSE(dirichletStarted) << "Dirichlet node should be in the back of the vector.";
        }
    }
}
