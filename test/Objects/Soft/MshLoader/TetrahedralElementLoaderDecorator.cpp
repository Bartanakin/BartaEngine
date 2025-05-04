#include <Objects/Soft/MshParser/TetrahedralElementLoaderDecorator.h>
#include "MshDataParserMock.h"
#include <pch.h>

using namespace Barta;
using namespace Barta::Objects::Soft;
using namespace Barta::Objects::Soft::MshParser;
using ::testing::Return;

TEST(
    TetrahedralElementLoaderDecoratorTest,
    ParsesTetrahedralElementsCorrectly
) {
    testing::NiceMock<MshDataParserMock> mockParser;

    // Prepare MshData with one tetrahedral element
    MshData mshData;
    mshData.tetrahedralElements.push_back({
        .nodeTags = {4, 3, 1, 2}
    });

    // Prepare corresponding mesh from the base parser
    Mesh mesh;
    Node node;
    node.isZeroDirichlet = false;

    node.tag = 1;
    node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT].massCenter = {0, 0, 0};
    mesh.nodes.push_back(node);

    node.tag = 1;
    node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT].massCenter = {1, 0, 0};
    mesh.nodes.push_back(node);

    node.tag = 2;
    node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT].massCenter = {0, 1, 0};
    mesh.nodes.push_back(node);

    node.tag = 3;
    node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT].massCenter = {0, 0, 1};
    mesh.nodes.push_back(node);

    EXPECT_CALL(mockParser, parse(::testing::_)).WillOnce(testing::Return(mesh));

    TetrahedralElementLoaderDecorator decorator(mockParser);

    Mesh result = decorator.parse(mshData);

    // Assert mesh has one tetrahedral element
    ASSERT_EQ(result.elements.size(), 1);

    const auto& element = result.elements[0];
    EXPECT_EQ(element.getNodeIndices().size(), 4);
    EXPECT_THAT(element.getNodeIndices(), ::testing::UnorderedElementsAre(3, 2, 0, 1));
}
