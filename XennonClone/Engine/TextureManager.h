#pragma once
#include "SDL.h"
#include <map>
#include <vector>
#include <string>

struct TextureData
{
	unsigned int texture_id;
	int sheet_width = 1;
	int sheet_height = 1;
	TextureData() = default;
	TextureData(unsigned int textureID, int sheetWidth, int sheetHeight) : texture_id{ textureID }, sheet_width{ sheetWidth }, sheet_height{ sheetHeight } {};
};

class TextureManager {
public:
	// Delete default constructor and assignment operators since this is a static-only class
	TextureManager() = delete;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static std::string get_path_translated(const char* path);

	static TextureData load_texture_open_gl(const char* path);
	static SDL_Texture* load_texture(const char* filename);

	static void free_texture_data(TextureData* texture);

	static SDL_Texture* load_texture_bmp(const char* filename);

	static SDL_Surface* load_surface(const char* filename);

protected:
	static const char* base_path_;

	static void remove_color(unsigned char* pixels, int width, int height, unsigned char red, unsigned char green, unsigned char blue);
};