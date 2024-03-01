#pragma once
#include "Segment.h"
#include "BartaShapes/AABB.h"
#include "BartaShapes/Circle.h"
#include "Math/QuadraticEquation.h"

namespace Barta {
	namespace Intersections {
		auto segmentAndCircle(const Segment& I, const Circle& c) noexcept {
			auto d = I.getEnd() - I.getBeginning();
			auto m = I.getBeginning() - c.getCenter();
			auto eq = QuadraticEquation(d*d, m*d*2.f, m*m - c.getRadius()*c.getRadius());
			eq.solve();
			auto sol = eq.getSolutions();

			sol.erase(std::remove_if(sol.begin(), sol.end(), [] (float t) {
				return t < 0.f || 1.f < t;
			}), sol.end());

			return sol;
		}

		float lineAndLineRespectToFirst(const Segment& I1, const Segment& I2) noexcept {
			auto perpendicular = (I2.getEnd() - I2.getBeginning()).perpendicular();
			auto denom = (perpendicular * (I1.getEnd() - I1.getBeginning()));
			if (denom == 0.f) {
				return std::numeric_limits<float>::infinity();
			}

			return (perpendicular * (I2.getBeginning() - I1.getBeginning())) / denom;
		}

		auto segmentAndSegment(const Segment& I1, const Segment& I2) noexcept {
			std::vector<std::tuple<float, float>> result;
			auto barCoords= std::tuple<float, float>(
				lineAndLineRespectToFirst(I1, I2),
				lineAndLineRespectToFirst(I2, I1)
			);

			if (0.f <= std::get<0>(barCoords) && std::get<0>(barCoords) <= 1.f && 0.f <= std::get<1>(barCoords) && std::get<1>(barCoords) <= 1.f) {
				result.push_back(barCoords);
			}

			return result;
		}

		auto segmentAndAABB(const Segment& I, const AABB& aabb) noexcept {
			decltype(segmentAndSegment(I, I)) intersections;
			for (const auto& side : aabb.getSides()) {
				auto sideIntersections = segmentAndSegment(I, side);
				intersections.insert(intersections.end(), sideIntersections.begin(), sideIntersections.end());
			}

			std::sort(intersections.begin(), intersections.end(), [](const std::tuple<float, float>& x, const std::tuple<float, float>& y) {
				return std::get<0>(x) <= std::get<0>(y);
			});

			return intersections;
		}
	}
}