#include "pch.h"
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <Geometrics/Segment.h>
#include <Geometrics/Intersections.h>

Barta::CircleAABBCheckCollisionVisitor::CircleAABBCheckCollisionVisitor(
	const Circle& circle,
	const AABB& aabb,
	const DynamicsDTO& dynamicsDifference
) : 
	circle( circle ),
	aabb( aabb ),
	dynamicsDifference( dynamicsDifference ),
	expandedAABB(
        // Write your code here ---->
        AABB(
            this->aabb.getLeftTop(),
            this->aabb.getWidthHeight()
	    )
        // <----
    )
{}

Barta::CircleAABBCheckCollisionVisitor::~CircleAABBCheckCollisionVisitor(){}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
Barta::CollisionTestResult Barta::CircleAABBCheckCollisionVisitor::checkStaticCollision(
	const MathLibraryInterface& mathLib,
	CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "circle " << this->circle << " aabb: " << this->aabb << " velocity: " << this->dynamicsDifference.velocity;

	collisionTestResultBuilder
		.setStaticCollision(true)
		->setCollisionDetected(false)
        ->setObjectsDebugInfo(ss.str())
		->setTimePassed(0.f);

    // Write your code here ---->
    // Use Barta::AABB::isWithin(Barta::Vector2f)
	if (false) {
    // <----
		 return collisionTestResultBuilder
            .setDebugInfo("Circle - AABB static, center not in expanded")
            ->build();
	}

	auto regionMask = this->aabb.findVoronoiRegionType(this->circle.getCenter());
    // Write your code here ---->
	if (false) {
    // <----
		collisionTestResultBuilder.setCollisionDetected(true);

		return collisionTestResultBuilder
            .setDebugInfo("Circle - AABB static, in expanded, in base")
            ->build();
	}

	auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
    // Write your code here ---->
    // Use Barta::Circle::isWithin(Barta::Vector2f)
	if (false) {
    // <----
		return collisionTestResultBuilder
            .setCollisionDetected(true)
            ->setDebugInfo("Circle - AABB static, in expanded, NOT in base, in corners")
            ->build();
	}

	return collisionTestResultBuilder
        .setDebugInfo("Circle - AABB static, in expanded, NOT in base, NOT in corners")
        ->build();
}
#pragma GCC diagnostic pop

Barta::CollisionTestResult Barta::CircleAABBCheckCollisionVisitor::checkDynamicCollision(
	const MathLibraryInterface& mathLib,
	const float delta_time,
	CollisionTestResultBuilder& collisionTestResultBuilder
) const {
	auto staticResult = this->checkStaticCollision(mathLib, collisionTestResultBuilder);
	if (staticResult.collisionDetected) {
		return staticResult;
	}

	collisionTestResultBuilder.setStaticCollision(false)->setTimePassed(delta_time);
    // Write your code here ---->
	Vector2f A = {};
	Vector2f B = {};
	// <----
    Segment L = Segment(A, B);
    // What are the results of the following function?
	auto tContainer = Intersections::segmentAndAABB(L, this->expandedAABB);
    // Write your code here ---->
    // Use Barta::AABB::isWithin(Barta::Vector2f) - be careful of an edge case!
	if (false) {
    // <----
		 return collisionTestResultBuilder
            .setDebugInfo("Circle - AABB dynamic, NOT in expanded")
            ->build();
	}

	Vector2f P;
	auto t = 0.f;
	if (!tContainer.empty()) {
        // Write your code here ---->
		t = 0.f;
		P = {};
        // <----
	} else {
		P = this->circle.getCenter();
	}

	auto regionMask = this->aabb.findVoronoiRegionType(P);
	auto normVector = this->calculateNormVector(delta_time);
	if (normVector == Vector2f()) {
//		throw "Incorrect normal vector found";
	}

	collisionTestResultBuilder.setNormVector(std::move(normVector));
    // Write your code here ---->
	if (false) {
    // <----
		collisionTestResultBuilder
			.setTimePassed(t * delta_time)
            ->setDebugInfo("Circle - AABB dynamic, in expanded, in base")
			->setCollisionDetected(true);

		return collisionTestResultBuilder.build();
	}

	auto cornerCircle = Circle(this->circle.getRadius(), this->matchCornerCenter(regionMask, this->aabb));
	auto circleIntersections = Intersections::segmentAndCircle(L, cornerCircle);
    // Write your code here ---->
	if (true) {
    // <----
		return collisionTestResultBuilder
            .setDebugInfo("Circle - AABB dynamic, in expanded, NOT in base, NOT in corners")
            ->build();
	}

	return collisionTestResultBuilder
		.setTimePassed(circleIntersections[0] * delta_time)
        ->setDebugInfo("Circle - AABB dynamic, in expanded, NOT in base, in corners")
		->setCollisionDetected(true)
        ->build();
}

Barta::Vector2f Barta::CircleAABBCheckCollisionVisitor::matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const {
	switch (regionMask) {
	case AABB::VoronoiRegion::LEFT_TOP:
		return aabb.getLeftTop();
	case AABB::VoronoiRegion::RIGTH_TOP:
		return aabb.getRightTop();
	case AABB::VoronoiRegion::RIGTH_BOTTOM:
		return aabb.getRightBottom();
	case AABB::VoronoiRegion::LEFT_BOTTOM:
		return aabb.getLeftBottom();
	default:
        return {};
//		throw std::runtime_error("Invalid regionMask supplied");
	}
}

Barta::Vector2f Barta::CircleAABBCheckCollisionVisitor::calculateNormVector(const float delta_time) const {
	std::vector<Vector2f> possibleNormalVectors = {{0.f, -1.f}, {1.f, 0.f}, {0.f, 1.f}, {-1.f, 0.f}};
	auto vertices = this->expandedAABB.getVertices();
	for (decltype(vertices)::size_type i = 0; i < 4; i++) {
		auto seg = Segment(
			this->circle.getCenter(),
			this->circle.getCenter() + this->dynamicsDifference.velocity + 0.5f * this->dynamicsDifference.acceleration * delta_time
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
