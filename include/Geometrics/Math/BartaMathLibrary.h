#pragma once
#include "../../pch.h"
#include"MathLibraryInterface.h"

namespace Barta{

	class BartaMathLibrary : public MathLibraryInterface{
	public:

		std::unique_ptr<EquationInterface> createQuadraticEquation( float A, float B, float C ) const override;
	};
}