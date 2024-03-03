#pragma once
#include "../../pch.h"
#include "../../Geometrics/Vector2f.h"

namespace Barta {

	struct CollisionTestResult {
		bool collisionDetected;
		float timePassed;
		bool staticCollision;
		Vector2f normVector;
        std::string debugInfo;

        CollisionTestResult() noexcept
			: collisionDetected(false),
			timePassed(0.f),
			staticCollision(true),
			normVector(Vector2f()),
            debugInfo("")
		{}
	
		CollisionTestResult(
			bool collisionDetected,
			float timePassed,
			bool staticCollision,
			Vector2f normVector,
            std::string debugInfo = ""
		) noexcept
			: collisionDetected(collisionDetected),
			timePassed(timePassed),
			staticCollision(staticCollision),
			normVector(normVector),
            debugInfo(debugInfo)
		{}

        bool operator==(const CollisionTestResult& second) const {
            return (this->collisionDetected == second.collisionDetected) &&
                (static_cast<float>(std::abs(this->timePassed - second.timePassed)) <= 1e-6f) &&
                (this->staticCollision == second.staticCollision) &&
                (this->normVector == second.normVector);
        }
	};

}