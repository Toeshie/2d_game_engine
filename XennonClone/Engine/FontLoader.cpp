#include "FontLoader.h"
#include "TextureManager.h"
#include "MathHelper.h"

FontLoader::~FontLoader()
{
	for (auto font : loaded_fonts_) {
		delete font;
	}
	loaded_fonts_.clear();
}

void FontLoader::init(const std::string& DefaultFontPath)
{
	
}

void FontLoader::load_font(const std::string& newFont)
{
	
}

void FontLoader::unload_font(const std::string& font)
{
	
}

FontText* FontLoader::get_font(const std::string& font)
{
	for (auto fontPtr : loaded_fonts_) {
		if (fontPtr->get_original_path() == font) {
			return fontPtr;
		}
	}
	TextureData newData = TextureManager::load_texture_open_gl(font.c_str());

	FontText* newFont = new FontText();
	newFont->set_new_data(newData);

	loaded_fonts_.push_back(newFont);

	return newFont;
}

FontText::~FontText()
{
	TextureManager::free_texture_data(&FontTextureData);
}

void FontText::set_new_data(const TextureData& new_data)
{
	if (new_data.texture_id != FontTextureData.texture_id) {
		TextureManager::free_texture_data(&FontTextureData);
		FontTextureData = new_data;
	}
}

Vector2D FontText::get_position_index_for_char(char c) const
{
	int y = 0;
	int x = 0;
	for (size_t i = 0; i < format_.size(); ++i) {
		if (c == format_[i]) {
			return Vector2D(x, y);
		}
		++x;
		if (x >= columns_) {
			x = 0;
			++y;
		}
	}
	return Vector2D::zero();
}
