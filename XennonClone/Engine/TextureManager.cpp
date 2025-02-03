#include "TextureManager.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

const char* TextureManager::base_path_ = "../Assets/";

void TextureManager::remove_color(unsigned char* pixels, int width, int height,
                                unsigned char red, unsigned char green, unsigned char blue)
{
    if (!pixels) return;

    for (int i = 0; i < width * height * 3; i += 3) {
        if (pixels[i] == red && pixels[i + 1] == green && pixels[i + 2] == blue) {
            pixels[i] = pixels[i + 1] = pixels[i + 2] = 0;
        }
    }
}

std::string TextureManager::get_path_translated(const char* path)
{
    if (!path) return std::string();
    
    std::string fullPath = base_path_;
    fullPath += path;
    return fullPath;
}

TextureData TextureManager::load_texture_open_gl(const char* path)
{
    if (!path) return TextureData();

    int sheet_width = 0, sheet_height = 0;
    unsigned int internal_format = 0, data_format = 0;
    int number_channels;

    stbi_set_flip_vertically_on_load(0);
    unsigned char* texture_data = stbi_load(get_path_translated(path).c_str(), 
        &sheet_width, &sheet_height, &number_channels, 0);

    if (texture_data) {
        remove_color(texture_data, sheet_width, sheet_height, 255, 0, 255);

        internal_format = (number_channels == 3) ? GL_RGBA : GL_RGBA8;
        data_format = (number_channels == 3) ? GL_RGB : GL_RGBA;

        unsigned int texture_id;
        glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, sheet_width, sheet_height, 
                    0, data_format, GL_UNSIGNED_BYTE, texture_data);

        stbi_image_free(texture_data);
        return TextureData(texture_id, sheet_width, sheet_height);
    }

    return TextureData();
}

SDL_Texture* TextureManager::load_texture(const char* filename) //Generic Loader
{
    SDL_Renderer* const ren = GameEngine::get_instance()->get_renderer();
    if (!ren) { return nullptr; }

    SDL_Surface* tmpSurf{ load_surface(filename) };
    SDL_Texture* finaltexture{ nullptr };

    if (tmpSurf) 
    {
		SDL_SetColorKey(tmpSurf, SDL_TRUE, SDL_MapRGB(tmpSurf->format, 255, 0, 255));
        finaltexture = SDL_CreateTextureFromSurface(ren, tmpSurf);
    }

    SDL_FreeSurface(tmpSurf);
    SDL_SetTextureBlendMode(finaltexture, SDL_BLENDMODE_BLEND);

    return finaltexture;
}
void TextureManager::free_texture_data(TextureData* texture)
{
    if (texture) {
        glDeleteTextures(1, &texture->texture_id);
    }
}


SDL_Texture* TextureManager::load_texture_bmp(const char* fileName) //BMP Loader
{
    SDL_Renderer* const ren = GameEngine::get_instance()->get_renderer();

    if (!ren)return nullptr;

    SDL_Surface* surf = SDL_LoadBMP(fileName);

    if (!surf) {
        const char* error = SDL_GetError();
        return nullptr;
    }

    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    if (!text) {
        const char* error = SDL_GetError();
        return nullptr;
    }

    SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);

    return text;
}

SDL_Surface* TextureManager::load_surface(const char* filename) //Generic Surface Loader
{
    std::string path = get_path_translated(filename);
    SDL_Surface* tmpSurf = IMG_Load(path.c_str());
    if (!tmpSurf) {
        const char* error = SDL_GetError();
    }
    return tmpSurf;
}