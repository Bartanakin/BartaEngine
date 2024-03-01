#pragma once
#include "../../pch.h"
#include"QuadraticEquation.h"

namespace Barta{

	class MathLibraryInterface{
	public:
        virtual ~MathLibraryInterface() noexcept = default;  
		/*
			Ax^2 + Bx + C = 0
		*/
		virtual std::unique_ptr<EquationInterface> createQuadraticEquation( float A, float B, float C ) const = 0;
	};
}