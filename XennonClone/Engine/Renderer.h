#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Renderer
{
public:

	static void init();
	static void stop();

	static void begin_batch();
	static void end_batch();
	static void flush();

	static void draw_quad(const Vector2D& position, const float scaleFactor, uint32_t textureID, struct SDL_Rect* sourceRect, const Vector2D& sheetSize);

	static float screen_width, screen_height;

};

