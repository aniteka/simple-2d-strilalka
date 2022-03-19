#pragma once
#include "Engine/defines.h"

template<class _Type>
class Matrix
	: public std::vector< std::vector< _Type > >
{
	const size_t h_size;
	const size_t v_size;
public:
	using type = _Type;
	using parent_type = std::vector< std::vector< _Type > >;
	using init_list = std::initializer_list<std::vector<_Type>>;
	Matrix(
		std::initializer_list<std::vector< _Type >> init,
		size_t h_size_,
		size_t v_size_
	)
		: parent_type(init)
		, h_size(h_size_)
		, v_size(v_size_)
	{
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);
	}
	Matrix(const Matrix& mtx)
		: h_size(mtx.getHorizontalSize())
		, v_size(mtx.getVerticalSize())
	{
		for (auto i : mtx)
			this->push_back(i);
	}

	size_t getHorizontalSize() const noexcept
	{
		return h_size;
	}

	size_t getVerticalSize() const noexcept
	{
		return v_size;
	}
};

using Matrix_int = Matrix<int>;
using Matrix_float = Matrix<float>;
namespace sf { using Matrix_Vector2f = Matrix<sf::Vector2f>; }

