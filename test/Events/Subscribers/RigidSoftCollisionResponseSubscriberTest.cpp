#include <pch.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Events/Subscribers/RigidSoftCollisionResponseSubscriber.h>

using namespace Barta;
using namespace Barta::Dynamics::SoftBody;

class MockSoftBodyDynamics : public Dynamics::SoftBody::SoftBodyDynamicsInterface {
public:
    MOCK_METHOD(
        StiffnessMatrixType,
        assembleTangentStiffnessMatrix,
        (const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions),
        (override)
    );

    MOCK_METHOD(
        NodalVectorType,
        calculateNodalForces,
        (const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions),
        (override)
    );
};

TEST(MappingOperatorTest, SingleContactSingleNode) {
    MockSoftBodyDynamics softBodyDynamics;
    RigidSoftCollisionResponseSubscriber calc(softBodyDynamics);

    ContactPointData contact;
    contact.normVector = {1.0, 0.0, 0.0};
    contact.convexIndexFactors2 = {{0, 2.0}};

    std::vector<ContactPointData> contacts = {contact};

    auto eta = calc.calculateMappingOperator(contacts, 3);

    ASSERT_EQ(eta.rows(), 6); // 3 * (1 + 1)
    ASSERT_EQ(eta.cols(), 1);

    Eigen::Vector3d expectedNodeBlock = -2.0 * Eigen::Vector3d(1, 0, 0);
    Eigen::Vector3d expectedAuxBlock = Eigen::Vector3d(1, 0, 0);
    ;
    EXPECT_TRUE((eta.block<3,1>(0,0).isApprox(expectedNodeBlock, 1e-6)));
    EXPECT_TRUE((eta.block<3,1>(3,0).isApprox(expectedAuxBlock, 1e-6)));
}

TEST(MappingOperatorTest, MultipleContacts) {
    MockSoftBodyDynamics softBodyDynamics;
    RigidSoftCollisionResponseSubscriber calc(softBodyDynamics);

    ContactPointData c1;
    c1.normVector = {0.5, 0.866, 0.};
    c1.convexIndexFactors2 = {{0, 0.3}, {1, 0.7}};

    ContactPointData c2;
    c2.normVector = {-0.866, 0.5, 0.};
    c2.convexIndexFactors2 = {{0, 0.75}, {1, 0.25}};

    std::vector<ContactPointData> contacts = {c1, c2};

    auto eta = calc.calculateMappingOperator(contacts, 9);

    ASSERT_EQ(eta.rows(), 12); // 3 * (2 + 2)
    ASSERT_EQ(eta.cols(), 2);

    // First contact (c1)
    EXPECT_FLOAT_EQ(eta(0,0),  -0.15);
    EXPECT_FLOAT_EQ(eta(1,0),  -0.2598);
    EXPECT_FLOAT_EQ(eta(2,0),  0.);

    EXPECT_FLOAT_EQ(eta(3,0),  -0.35);
    EXPECT_FLOAT_EQ(eta(4,0),  -0.6062);
    EXPECT_FLOAT_EQ(eta(5,0),  0.);

    EXPECT_FLOAT_EQ(eta(6,0),  0.);
    EXPECT_FLOAT_EQ(eta(7,0),  0.);
    EXPECT_FLOAT_EQ(eta(8,0),  0.);

    EXPECT_FLOAT_EQ(eta(9,0),  0.5);
    EXPECT_FLOAT_EQ(eta(10,0),  0.866);
    EXPECT_FLOAT_EQ(eta(11,0),  0.);

    // Second contact (c2)
    EXPECT_FLOAT_EQ(eta(0,1),  0.6495);
    EXPECT_FLOAT_EQ(eta(1,1),  -0.375);
    EXPECT_FLOAT_EQ(eta(2,1),  0.);

    EXPECT_FLOAT_EQ(eta(3,1),  0.2165);
    EXPECT_FLOAT_EQ(eta(4,1),  -0.125);
    EXPECT_FLOAT_EQ(eta(5,1),  0.);

    EXPECT_FLOAT_EQ(eta(6,1),  0.);
    EXPECT_FLOAT_EQ(eta(7,1),  0.);
    EXPECT_FLOAT_EQ(eta(8,1),  0.);

    EXPECT_FLOAT_EQ(eta(9,1),  -0.866);
    EXPECT_FLOAT_EQ(eta(10,1),  0.5);
    EXPECT_FLOAT_EQ(eta(11,1),  0.);
}

TEST(MappingOperatorTest, MultipleContactsWithDirichletNode) {
    MockSoftBodyDynamics softBodyDynamics;
    RigidSoftCollisionResponseSubscriber calc(softBodyDynamics);

    ContactPointData c1;
    c1.normVector = {0.0, 1.0, 0.0};
    c1.convexIndexFactors2 = {{0, 1.0}, {1, 2.0}};

    ContactPointData c2;
    c2.normVector = {0.0, 0.0, 1.0};
    c2.convexIndexFactors2 = {{2, 3.0}}; // node 2 will be Dirichlet if numberOfNodes = 2

    std::vector<ContactPointData> contacts = {c1, c2};

    auto eta = calc.calculateMappingOperator(contacts, 6);

    ASSERT_EQ(eta.rows(), 9); // 3 * (2 + 1)
    ASSERT_EQ(eta.cols(), 2);

    // First contact (c1)
    EXPECT_TRUE((eta.block<3,1>(0,0).isApprox(-1.0 * Eigen::Vector3d(0,1,0), 1e-6)));
    EXPECT_TRUE((eta.block<3,1>(3,0).isApprox(-2.0 * Eigen::Vector3d(0,1,0), 1e-6)));
    EXPECT_TRUE((eta.block<3,1>(6,0).isApprox(Eigen::Vector3d(0,1,0), 1e-6)));

    // Second contact (c2)
    EXPECT_TRUE((eta.block<3,1>(6,1).isApprox(Eigen::Vector3d(0,0,1), 1e-6)));
    EXPECT_TRUE((eta.block<3,1>(0,1).isApprox(Eigen::Vector3d(0,0,0), 1e-6))); // No effect due to Dirichlet
    EXPECT_TRUE((eta.block<3,1>(3,1).isApprox(Eigen::Vector3d(0,0,0), 1e-6)));
}

TEST(MappingOperatorTest, NoContactsReturnsZeroMatrix) {
    MockSoftBodyDynamics softBodyDynamics;
    RigidSoftCollisionResponseSubscriber calc(softBodyDynamics);
    auto eta = calc.calculateMappingOperator({}, 9);

    EXPECT_EQ(eta.rows(), 3 * (3 + 1));
    EXPECT_EQ(eta.cols(), 0);
}