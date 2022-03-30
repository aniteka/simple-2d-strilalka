#pragma once
#include "../Engine/defines.h"

template<class _Type>
class Matrix
	: public std::vector< std::vector< _Type > >
{
protected:
	size_t h_size;
	size_t v_size;
public:
	using type = _Type;
	using parent_type = std::vector< std::vector< _Type > >;
	using init_list = std::initializer_list<std::vector<_Type>>;
	Matrix(std::initializer_list<std::vector< _Type >> init,
		size_t h_size_,
		size_t v_size_)
		: parent_type(init)
		, h_size(h_size_)
		, v_size(v_size_)
	{
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);
	}
	Matrix(const Matrix& mtx)
		: h_size(mtx.h_size)
		, v_size(mtx.v_size)
	{
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);

		for (size_t y = 0; y < v_size; ++y)
			for (size_t x = 0; x < h_size; ++x)
			{
				this->at(y).at(x) = mtx[y][x];
			}
	}
	Matrix(Matrix&& mtx)
		: h_size(mtx.h_size)
		, v_size(mtx.v_size)
	{
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);

		for (size_t y = 0; y < v_size; ++y)
			for (size_t x = 0; x < h_size; ++x)
			{
				this->at(y).at(x) = std::move(mtx[y][x]);
			}

		mtx.h_size = 0;
		mtx.v_size = 0;
		mtx.clear();
	}

	Matrix& operator=(const Matrix& mtx)
	{
		this->h_size = mtx.h_size;
		this->v_size = mtx.v_size;

		this->clear();
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);

		for (size_t y = 0; y < v_size; ++y)
			for (size_t x = 0; x < h_size; ++x)
			{
				this->at(y).at(x) = mtx[y][x];
			}

		return *this;
	}
	Matrix& operator=(Matrix&& mtx)
	{
		this->h_size = mtx.h_size;
		this->v_size = mtx.v_size;

		this->clear();
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);

		for (size_t y = 0; y < v_size; ++y)
			for (size_t x = 0; x < h_size; ++x)
			{
				this->at(y).at(x) = std::move(mtx[y][x]);
			}

		mtx.h_size = 0;
		mtx.v_size = 0;
		mtx.clear();

		return *this;
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

