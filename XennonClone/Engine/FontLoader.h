#pragma once
#include <string>
#include <vector>
#include "TextureManager.h"
#include "Transform.h"

class FontText {
protected:
	TextureData FontTextureData;
	std::string font_file_path_;
	int rows_ = 12;	
	int columns_ = 8;
	std::vector<char> format_ = {' ','!','"','#','$','%','&','\'',
								'(',')','*','+',',','-','.','/',
								'0','1','2','3','4','5','6','7',
								'8','9',':',';','<','=','>','?',
								'@','A','B','C','D','E','F','G',
								'H','I','J','K','L','M','N','O',
								'P','Q','R','S','T','U','V','W',
								'X','Y','Z','[','\\',']','^','_',
								'`','a','b','c','d','e','f','g',
								'h','i','j','k','l','m','n','o',
								'p','q','r','s','t','u','v','w',
								'x','y','z','{','|','}','~','_'};
public:
	~FontText();
	void set_new_data(const TextureData& new_data);
	TextureData* get_data() { return &FontTextureData; }
	std::string get_original_path() const { return font_file_path_; }

	//Sprite location
	Vector2D get_position_index_for_char(char c) const;

	int get_rows() const { return rows_; }
	int get_columns() const { return columns_; }

	void set_format(const std::vector<char>& newFormat) { format_ = newFormat; }
	void set_rows_and_columns(int rows, int columns) { rows_ = rows; columns_ = columns; }
};

class FontLoader
{
private:
	std::vector<FontText*> loaded_fonts_;
public:

	~FontLoader();

	void init(const std::string& DefaultFontPath);

	void load_font(const std::string& newFont);
	void unload_font(const std::string& font);

	FontText* get_font(const std::string& font);

	std::vector<FontText*> get_loaded_fonts() const {
		return loaded_fonts_;
	}
};

