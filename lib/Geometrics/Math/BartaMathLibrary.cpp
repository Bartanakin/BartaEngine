#include <pch.h>
#include <Geometrics/Math/BartaMathLibrary.h>

std::unique_ptr<Barta::EquationInterface> Barta::BartaMathLibrary::createQuadraticEquation( float A, float B, float C ) const{
	return std::unique_ptr<EquationInterface>( new QuadraticEquation( A, B, C ) );
}
