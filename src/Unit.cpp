#include "Unit.hpp"

Unit::Unit()
	: status{ .is_physics = false, .is_interrupted = false, .is_drawable = false }
	, category("Unit")
	, interrupt_this{}
	, block_this{}
{
}

