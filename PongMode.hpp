#include "ColorTextureProgram.hpp"

#include "Mode.hpp"
#include "GL.hpp"

#include <vector>
#include <deque>
#include "BreakBlock.hpp"

/*
 * PongMode is a game mode that implements a single-player game of Pong.
 */

struct PongMode : Mode {
	PongMode();
	virtual ~PongMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	glm::vec2 court_radius = glm::vec2(7.0f, 5.0f);
	glm::vec2 block_radius = glm::vec2(0.2f, 0.5f);
	glm::vec2 trail_radius = glm::vec2(0.2f, 0.2f);
	glm::vec2 ball_radius = glm::vec2(0.3f, 0.3f);
	float target_height = 0.0f;
	glm::vec2 ball_squish = glm::vec2(0.0f);

	int32_t blocks_width = 5;
	int32_t blocks_height = 5;
	BreakoutBlocks left_blocks = BreakoutBlocks(blocks_width, blocks_height, 
		glm::vec2(-court_radius.x + float(blocks_width) * block_radius.x, 0.0f), block_radius);
	BreakoutBlocks right_blocks = BreakoutBlocks(blocks_width, blocks_height,
		glm::vec2(court_radius.x - float(blocks_width) * block_radius.x, 0.0f), block_radius);

	glm::vec2 ball = glm::vec2(0.0f, 0.0f);
	glm::vec2 ball_velocity = glm::vec2(-3.0f, 0.0f);

	uint32_t left_score = 0;
	uint32_t right_score = 0;

	float speed_multiplier;
	float ai_offset = 0.0f;
	float ai_offset_update = 0.0f;
	float screen_shake = 0.0f;

	//----- pretty rainbow trails -----

	float trail_length = 0.7f;
	std::deque< glm::vec3 > ball_trail; //stores (x,y,age), oldest elements first

	//----- opengl assets / helpers ------

	//draw functions will work on vectors of vertices, defined as follows:
	struct Vertex {
		Vertex(glm::vec3 const &Position_, glm::u8vec4 const &Color_, glm::vec2 const &TexCoord_) :
			Position(Position_), Color(Color_), TexCoord(TexCoord_) { }
		glm::vec3 Position;
		glm::u8vec4 Color;
		glm::vec2 TexCoord;
	};
	static_assert(sizeof(Vertex) == 4*3 + 1*4 + 4*2, "PongMode::Vertex should be packed");

	//Shader program that draws transformed, vertices tinted with vertex colors:
	ColorTextureProgram color_texture_program;

	//Buffer used to hold vertex data during drawing:
	GLuint vertex_buffer = 0;

	//Vertex Array Object that maps buffer locations to color_texture_program attribute locations:
	GLuint vertex_buffer_for_color_texture_program = 0;

	//Solid white texture:
	GLuint white_tex = 0;

	//matrix that maps from clip coordinates to court-space coordinates:
	glm::mat3x2 clip_to_court = glm::mat3x2(1.0f);
	// computed in draw() as the inverse of OBJECT_TO_CLIP
	// (stored here so that the mouse handling code can use it to position the paddle)

};
