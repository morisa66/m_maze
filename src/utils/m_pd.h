#ifndef  __M_PD_H__
#define  __M_PD_H__

#include "../_morisa.h"

MORISA_NAMESPACE_BEGIN


enum m_direction
{
	forward,
	right,
	backward,
	left
};

struct m_position
{
	int x{ 0 };
	int y{ 0 };

	m_position() noexcept {}

	m_position(int x, int y)noexcept :x(x), y(y) {}

	m_position operator+ (const m_position& other) noexcept
	{
		return m_position(x + other.x, y + other.y);
	}

	m_position operator- (const m_position& other) noexcept
	{
		return m_position(x - other.x, y - other.y);
	}

	void operator = (const m_position& other)noexcept
	{
		x = other.x;
		y = other.y;
	}

	bool operator ==(const m_position& other)noexcept
	{
		return x == other.x && y == other.y;
	}
};

struct m_type
{
	m_position pos;
	m_direction dir;

	m_type(m_position _pos, m_direction _dir)noexcept :pos(_pos), dir(_dir) {}

	// for remove and erase.
	bool operator ==(const m_type& other)noexcept
	{
		return pos == other.pos && dir == other.dir;
	}
};

MORISA_NAMESPACE_END

#endif