#ifndef __M_MAZE_H__
#define __M_MAZE_H__

#include <vector>
#include <stack>

#include "../_morisa.h"
#include "../utils/m_pd.h"


MORISA_NAMESPACE_BEGIN

class m_maze
{
public:
	m_maze(size_t _size) :maze_size(_size)
	{
		wall.reserve(maze_size * maze_size << 2);
		is_visted.resize(maze_size * maze_size);

		init_wall();

		generate_maze();

		set_enter_exit();
	}


	const std::vector<m_type>& operator*()noexcept
	{
		return wall;
	}

	inline const size_t size() const  noexcept
	{
		return maze_size;
	}

	inline const std::vector<m_type> get_wall() const noexcept
	{
		return wall;
	}

private:
	size_t maze_size;
	std::vector<m_type> wall;
	std::vector<bool> is_visted;
	std::vector<m_direction> neighbors;
	std::stack<m_position> way;

	const m_position dir_to_pos[4] =
	{
		m_position(0, 1),	//forward,
		m_position(1, 0),	//right,
		m_position(0, -1),	//backward,
		m_position(-1, 0)	//left
	};


	void init_wall()
	{
		for (int y = 0; y < maze_size; ++y)
		{
			for (int x = 0; x < maze_size; ++x)
			{
				for (m_direction i = forward; i <= left; i = (m_direction)(i + 1))
				{
					wall.emplace_back(m_type{ m_position(x, y), i });
				}
			}
		}
		;
	}

	void erase_single_face(m_type _val)
	{
		using std::remove;
		wall.erase(remove(wall.begin(), wall.end(), _val), wall.end());
	}

	void erase_single_all(m_position _pos)
	{
		using std::remove;
		for (m_direction i = forward; i <= left; i = (m_direction)(i + 1))
		{
			erase_single_face(m_type{ _pos , i });
		}
	}

	void erase_between_face(m_position _cur, m_position _next)
	{
		if (_cur.x > _next.x)
		{
			erase_single_face(m_type{ _cur, left });
			erase_single_face(m_type{ _next, right });
		}

		if (_cur.x < _next.x)
		{
			erase_single_face(m_type{ _cur, right });
			erase_single_face(m_type{ _next, left });
		}

		if (_cur.y > _next.y)
		{
			erase_single_face(m_type{ _cur, backward });
			erase_single_face(m_type{ _next, forward });
		}

		if (_cur.y < _next.y)
		{
			erase_single_face(m_type{ _cur, forward });
			erase_single_face(m_type{ _next, backward });
		}
	}

	void flash_neighbors(m_position _pos)
	{
		auto is_visted_fun = [&](m_position _pos_)->bool
		{
			if (_pos_.x < maze_size && _pos_.x >= 0 && _pos_.y < maze_size && _pos_.y >= 0)
			{
				return !is_visted[_pos_.y * maze_size + _pos_.x];
			}
			return false;
		};

		neighbors.clear();
		for (m_direction i = forward; i <= left; i = (m_direction)(i + 1))
		{
			if (is_visted_fun(_pos + dir_to_pos[i]))
			{
				neighbors.emplace_back(i);
			}
		}
	}

	void generate_maze()
	{
		srand((unsigned)time(NULL));

		m_position cur{ 0,0 };
		m_position next{ 0,0 };
		is_visted[0] = true;
		size_t visted_cnt = 1;

		while (visted_cnt < maze_size * maze_size)
		{
			flash_neighbors(cur);
			if (!neighbors.empty())
			{
				next = cur + dir_to_pos[neighbors[rand() % neighbors.size()]];
				is_visted[next.y * maze_size + next.x] = true;
				way.push(cur);
				erase_between_face(cur, next);
				cur = next;
				++visted_cnt;
			}
			else
			{
				if (!way.empty())
				{
					cur = way.top();
					way.pop();
				}
			}
		}

	}

	void set_enter_exit()
	{
		erase_single_all(m_position{ 0,0 });
		erase_single_all(m_position{ (int)maze_size - 1, (int)maze_size - 1 });
	}

};


MORISA_NAMESPACE_END

#endif