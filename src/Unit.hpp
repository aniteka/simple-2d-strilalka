#pragma once
#include "defines.h"


class Unit  
{
	struct Status
	{
		bool is_physics;
		bool is_interrupted;
		bool is_drawable;
	} status;
	
	std::string category;
	std::vector<std::string> interrupt_this;
	std::vector<std::string> block_this;
public:
	Unit()
		: status							{.is_physics = false, .is_interrupted = false, .is_drawable = false}	
		, category							("Unit")
		, interrupt_this					{}
		, block_this						{}
	{}

	void setPhysicsStatus(bool stat)	{ status.is_physics = stat; }
	void setInterruptStatus(bool stat)	{ status.is_interrupted = stat; }
	void setDrawStatus(bool stat)		{ status.is_drawable = stat; }

	Status getStatus() const			{ return status; }
};