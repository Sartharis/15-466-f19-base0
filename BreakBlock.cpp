#include "BreakBlock.hpp"

BreakoutBlocks::BreakoutBlocks(int32_t new_width, int32_t new_height, glm::vec2 new_pos, glm::vec2 new_block_radius)
{
	broken_blocks = new bool*[new_width];
	for (int32_t i = 0; i < new_width; i++)
	{
		broken_blocks[i] = new bool[new_height];
	}
	width = new_width;
	height = new_height;
	pos = new_pos;
	block_radius = new_block_radius;
	for (int32_t i = 0 ; i< new_width; i++)
	{
		for (int32_t j = 0; j < new_height; j ++)
		{
			broken_blocks[i][j] = false;
		}
	}
}

BreakoutBlocks::~BreakoutBlocks()
{
	free(broken_blocks);
}

glm::vec2 BreakoutBlocks::get_block_pos(int32_t i, int32_t j) const
{
	return pos + get_local_block_pos(i, j);
}

glm::vec2 BreakoutBlocks::get_local_block_pos(int32_t i, int32_t j) const
{
	assert(i >= 0 && j >= 0 && i < width && j < height);
	return glm::vec2(-(2 * block_radius.x * float(height) / 2.0f) + 2 * block_radius.x * i + block_radius.x,
		-(2 * block_radius.y * float(width) / 2.0f) + 2 * block_radius.y * j + block_radius.y);
}

float BreakoutBlocks::get_y_center_offset() const
{
	return (get_blocks_top_len() - get_blocks_bottom_len()) / 2.0f;
}

float BreakoutBlocks::get_blocks_bottom_len() const
{
	float max_len = 0.0f;
	for (int32_t i = 0; i < width; i++)
	{
		for (int32_t j = 0; j < height; j++)
		{
			if (!broken_blocks[i][j])
			{
				max_len = glm::max(max_len, get_local_block_pos(i, j).y + block_radius.y);
			}
		}
	}
	return glm::abs(max_len);
}

bool BreakoutBlocks::is_fully_broken() const
{
	for (int32_t i = 0; i < width; i++)
	{
		for (int32_t j = 0; j < height; j++)
		{
			if (!broken_blocks[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

float BreakoutBlocks::get_blocks_top_len() const
{
	float min_len = 0.0f;
	for (int32_t i = 0; i < width; i++)
	{
		for (int32_t j = 0; j < height; j++)
		{
			if (!broken_blocks[i][j])
			{
				min_len = glm::min(min_len, get_local_block_pos(i, j).y - block_radius.y);
			}
		}
	}
	return glm::abs(min_len);
}

