#include <pch.h>
#include <Geometrics/Math/QuadraticEquation.h>

Barta::QuadraticEquation::QuadraticEquation( float A, float B, float C ) noexcept :
	state( EquationInterface::State::UNSOLVED ),
    solutions({}),
	A( A ),
	B( B ),
	C( C )
{}

Barta::QuadraticEquation::QuadraticEquation( const QuadraticEquation& second ) noexcept :
	state( second.state ),
	solutions( second.solutions ),
	A( second.A ),
	B( second.B ),
	C( second.C )
{}

Barta::QuadraticEquation::QuadraticEquation( QuadraticEquation&& second ) noexcept :
	state( second.state ),
	solutions( std::move( second.solutions ) ),
	A( second.A ),
	B( second.B ),
	C( second.C )
{}

Barta::QuadraticEquation& Barta::QuadraticEquation::operator=( QuadraticEquation&& second ) noexcept{
	this->solutions = std::move( second.solutions );
	this->state = second.state;
	this->A = second.A;
	this->B = second.B;
	this->C = second.C;

	return *this;
}

Barta::QuadraticEquation::~QuadraticEquation() noexcept{}

void Barta::QuadraticEquation::solve( const Method& method ){
    if (method != Method::DEFAULT) {
        return;
    }

	if( this->state != EquationInterface::State::UNSOLVED ){
		return;
	}

	if( this->A == 0.f ){
		this->solveLinear();

		return;
	}

	auto p = - this->B / this->A * 0.5f;
	auto q = this->C / this->A;
	auto delta = p * p - q;
	if( delta < 0.f ){
		this->state = EquationInterface::State::NO_SOLUTIONS;

		return;
	}

	this->solutions.resize( 2 );
	this->state = EquationInterface::State::FINITE_NO_SOLTIONS;
	delta = sqrt( delta );
	if( p >= 0.f ){
		this->solutions[ 1 ] = p + delta;
		this->solutions[ 0 ] = q / this->solutions[ 1 ];
	}
	else{
		this->solutions[ 0 ] = p - delta;
		this->solutions[ 1 ] = q / this->solutions[ 0 ];
	}
}

Barta::EquationInterface::State Barta::QuadraticEquation::getState() const noexcept{
	return this->state;
}

std::vector<float> Barta::QuadraticEquation::getSolutions() const{
	return this->solutions;
}

void Barta::QuadraticEquation::solveLinear(){
	if( this->B == 0.f ){
		if( this->C != 0.f ){
			this->state = EquationInterface::State::NO_SOLUTIONS;
		}
		else{
			this->state = EquationInterface::State::INFINITE_NO_SOLUTIONS;
		}
	}
	else{
		this->solutions.resize( 1 );
		this->solutions[ 0 ] = - this->C / this->B;
		this->state = EquationInterface::State::FINITE_NO_SOLTIONS;
	}
}




