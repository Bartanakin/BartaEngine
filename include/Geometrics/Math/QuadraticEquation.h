#pragma once
#include "../../pch.h"
#include"EquationInterface.h"

namespace Barta{

	class QuadraticEquation : public EquationInterface{
	public:

		QuadraticEquation( float A, float B, float C ) noexcept;
		QuadraticEquation( const QuadraticEquation& ) noexcept;
		QuadraticEquation( QuadraticEquation&& ) noexcept;
		QuadraticEquation& operator=( QuadraticEquation&& ) noexcept;
		~QuadraticEquation() noexcept;

		void solve( const Method & method = Method::DEFAULT );

		State getState() const noexcept;

		std::vector<float> getSolutions() const;

	private:
		void solveLinear();

		EquationInterface::State state;

		std::vector<float> solutions;

		float A, B, C;
	};
}