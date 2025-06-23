#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include "Collisions/CollisionTestResult/CollisionTestResultBuilder.h"
#include "pch.h"
#include <Geometrics/ConvexFactor.h>
#include <Geometrics/Intersections.h>
#include <Geometrics/Segment.h>

namespace Barta {
CircleAABBCheckCollisionVisitor::CircleAABBCheckCollisionVisitor(
    const Circle& circle,
    const AABB& aabb
):
    circle(circle),
    aabb(aabb),
    expandedAABB(AABB( // TODO third dimention
        this->aabb.getLeftTop() - Vector(this->circle.getRadius(), this->circle.getRadius()),
        this->aabb.getWidthHeight() + 2.f * Vector(this->circle.getRadius(), this->circle.getRadius())
    )) {}

CircleAABBCheckCollisionVisitor::~CircleAABBCheckCollisionVisitor() {}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Point CircleAABBCheckCollisionVisitor::calculateCollisionPoint() const {
    Point collisionPoint = Point::Zero();
    float min = std::numeric_limits<float>::max();
    for (const auto& side: this->expandedAABB.getSides()) {
        auto perpVector = (side.getEnd() - side.getBeginning()).perp(this->circle.getCenter() - side.getBeginning());
        auto distance = perpVector.squaredNorm();
        if (distance < min) {
            min = distance;
            collisionPoint = this->circle.getCenter() - 0.5 * perpVector;
        }
    }

    return collisionPoint;
}

CollisionTestResult CircleAABBCheckCollisionVisitor::checkStaticCollision(
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    auto collisionTestResultBuilder = CollisionTestResultBuilder();
    std::stringstream ss;
    ss << "circle " << this->circle << " aabb: " << this->aabb;

    collisionTestResultBuilder.setStaticCollision(true)->setCollisionDetected(false)->setObjectsDebugInfo(ss.str())->setTimePassed(0.f);
    if (!this->expandedAABB.isWithin(this->circle.getCenter())) {
        return collisionTestResultBuilder.setDebugInfo("Circle - AABB static, center not in expanded")->build();
    }

    auto regionMask = this->aabb.findVoronoiRegionType(this->circle.getCenter());
    if (regionMask == AABB::VoronoiRegion::TOP || regionMask == AABB::VoronoiRegion::RIGHT || regionMask == AABB::VoronoiRegion::BOTTOM
        || regionMask == AABB::VoronoiRegion::LEFT || regionMask == AABB::VoronoiRegion::INSIDE) {
        collisionTestResultBuilder.setNormVector(this->calculateNormVectorForStatic());
        collisionTestResultBuilder.setCollisionDetected(true);
        collisionTestResultBuilder.setCollisionPoint(this->calculateCollisionPoint());

        return collisionTestResultBuilder.setDebugInfo("Circle - AABB static, in expanded, in base")->build();
    }

    auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
    if (cornerCircle.isWithin(this->circle.getCenter())) {
        return collisionTestResultBuilder.setCollisionDetected(true)
            ->setCollisionPoint(this->calculateCollisionPoint())
            ->setNormVector(this->calculateNormVectorForStatic())
            ->setDebugInfo("Circle - AABB static, in expanded, NOT in base, in corners")
            ->build();
    }

    return collisionTestResultBuilder.setDebugInfo("Circle - AABB static, in expanded, NOT in base, NOT in corners")->build();
}

#pragma GCC diagnostic pop

CollisionTestResult CircleAABBCheckCollisionVisitor::checkDynamicCollision(
    const PrecisionType delta_time,
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    auto collisionTestResultBuilder = CollisionTestResultBuilder();

    collisionTestResultBuilder.setStaticCollision(false)->setTimePassed(delta_time);
    Point A = this->circle.getCenter();
    Point B = A
              + (dynamicsOfFirstObject[DynamicsDTOIteration::CURRENT].velocity - dynamicsOfSecondObject[DynamicsDTOIteration::CURRENT].velocity)
                    * delta_time;
    Segment L = Segment(A, B);
    auto tContainer = Intersections::segmentAndAABB(L, this->expandedAABB);
    if (!this->expandedAABB.isWithin(circle.getCenter()) && tContainer.empty()) {
        return collisionTestResultBuilder.setDebugInfo("Circle - AABB dynamic, NOT in expanded")->build();
    }

    Point P;
    auto t = 0.f;
    if (!tContainer.empty()) {
        t = std::get<0>(tContainer[0]);
        P = ConvexFactor::convexCombination({
            {1.f - t, A},
            {t,       B}
        });
    } else {
        P = this->circle.getCenter();
    }

    auto regionMask = this->aabb.findVoronoiRegionType(P);
    auto normVector = this->calculateNormVector(dynamicsOfFirstObject[DynamicsDTOIteration::CURRENT].velocity - dynamicsOfSecondObject[DynamicsDTOIteration::CURRENT].velocity);
    if (normVector == Vector::Zero()) {
        throw "Incorrect normal vector found";
    }

    collisionTestResultBuilder.setNormVector(std::move(normVector));
    if (regionMask == AABB::VoronoiRegion::TOP || regionMask == AABB::VoronoiRegion::RIGHT || regionMask == AABB::VoronoiRegion::BOTTOM
        || regionMask == AABB::VoronoiRegion::LEFT || regionMask == AABB::VoronoiRegion::INSIDE) {
        collisionTestResultBuilder.setTimePassed(t * delta_time)
            ->setDebugInfo("Circle - AABB dynamic, in expanded, in base")
            ->setCollisionDetected(true);

        return collisionTestResultBuilder.build();
    }

    auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
    auto circleIntersections = Intersections::segmentAndCircle(L, cornerCircle);
    if (circleIntersections.empty()) {
        return collisionTestResultBuilder.setDebugInfo("Circle - AABB dynamic, in expanded, NOT in base, NOT in corners")->build();
    }

    return collisionTestResultBuilder.setTimePassed(circleIntersections[0] * delta_time)
        ->setDebugInfo("Circle - AABB dynamic, in expanded, NOT in base, in corners")
        ->setCollisionDetected(true)
        ->build();
}

Point CircleAABBCheckCollisionVisitor::matchCornerCenter(
    AABB::VoronoiRegion regionMask,
    const AABB& aabb
) const {
    switch (regionMask) {
    case AABB::VoronoiRegion::LEFT_TOP: return aabb.getLeftTop();
    case AABB::VoronoiRegion::RIGTH_TOP: return aabb.getRightTop();
    case AABB::VoronoiRegion::RIGTH_BOTTOM: return aabb.getRightBottom();
    case AABB::VoronoiRegion::LEFT_BOTTOM: return aabb.getLeftBottom();
    default: throw std::runtime_error("Invalid regionMask supplied");
    }
}

Vector CircleAABBCheckCollisionVisitor::calculateNormVector(
    const Vector& velocity
) const {
    std::vector<Vector> possibleNormalVectors = {
        {0.f,  -1.f},
        {1.f,  0.f },
        {0.f,  1.f },
        {-1.f, 0.f }
    };
    auto vertices = this->expandedAABB.getVertices();
    for (decltype(vertices)::size_type i = 0; i < 4; i++) {
        auto seg = Segment(
            this->circle.getCenter(),
            this->circle.getCenter() + velocity
        );
        if (seg.calculateRelationToPoint(vertices[i]) == Segment::Relation::RIGHT) {
            auto relationToNext = seg.calculateRelationToPoint(vertices[(i + 1) % 4]);
            if (relationToNext == Segment::Relation::LEFT || relationToNext == Segment::Relation::COLINEAR) {
                return possibleNormalVectors[i];
            }
        }
    }

    return {};
}

Vector CircleAABBCheckCollisionVisitor::calculateNormVectorForStatic() const {
    auto middle = this->aabb.getLeftTop() + 0.5f * this->aabb.getWidthHeight();
    std::vector<Vector> possibleNormalVectors = {
        {0.f,  -1.f},
        {1.f,  0.f },
        {0.f,  1.f },
        {-1.f, 0.f }
    };
    auto vertices = this->aabb.getVertices();
    for (decltype(possibleNormalVectors)::size_type i = 0; i < 4; i++) {
        auto seg = Segment(middle, vertices[i]);
        if (seg.calculateRelationToPoint(this->circle.getCenter()) == Segment::Relation::RIGHT) {
            auto nextSeg = Segment(middle, vertices[(i + 1) % 4]);
            auto relationToNext = nextSeg.calculateRelationToPoint(this->circle.getCenter());
            if (relationToNext == Segment::Relation::LEFT || relationToNext == Segment::Relation::COLINEAR) {
                return possibleNormalVectors[i];
            }
        }
    }

    return {};
}
}
