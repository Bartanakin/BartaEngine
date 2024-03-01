#pragma once
#include "Vector2f.h"

namespace Barta {

	class Segment {
		public:
		Segment(Vector2f beg, Vector2f end): beg(beg), end(end) {}

		enum class Relation {
			LEFT = -1,
			COLINEAR = 0,
			RIGHT = 1
		};

		inline Vector2f getBeginning() const noexcept { return this->beg; }

		inline Vector2f getEnd() const noexcept { return this->end; }

		inline float squareOfDistance() const noexcept { return beg.squareOfDistance(end); }

		Relation calculateRelationToPoint(const Vector2f& point) const noexcept;

		private:

		const Vector2f beg;
		const Vector2f end;
	};

	inline std::ostream& operator << (std::ostream& stream, const Segment& I) noexcept {
		return stream << "(" << I.getBeginning() << ", " << I.getEnd() << ")";
	}
}
