#include <glm/glm.hpp>

struct BreakoutBlocks
{
public:
	BreakoutBlocks(int32_t new_width, int32_t new_height, glm::vec2 new_pos, glm::vec2 new_block_radius);
	~BreakoutBlocks();
	glm::vec2 get_block_pos(int32_t i, int32_t j) const;
	glm::vec2 get_local_block_pos(int32_t i, int32_t j) const;
	float get_y_center_offset() const;
	float get_blocks_top_len() const;
	float get_blocks_bottom_len() const;
	bool is_fully_broken() const;
	
	glm::vec2 pos = glm::vec2(0.0f, 0.0f);
	int32_t width = 0;
	int32_t height = 0;
	glm::vec2 block_radius = glm::vec2(0.0f, 0.0f);
	bool **broken_blocks = nullptr;
};