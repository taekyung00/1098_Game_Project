/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 19, 2025
*/

#include "Texture.h"
#include "Engine.h"

CS230::Texture::Texture() {}

CS230::Texture::Texture(const std::filesystem::path& file_name){
    Load(file_name);
}

CS230::Texture::~Texture() {
    UnloadTexture(texture);
}

CS230::Texture::Texture(Texture&& temporary) noexcept : texture(temporary.texture) {
    temporary.texture.id = 0;
    temporary.texture.width = 0;
    temporary.texture.height = 0;
    temporary.texture.mipmaps = 0;
    temporary.texture.format = 0;
}

CS230::Texture& CS230::Texture::operator=(Texture&& temporary) noexcept {
    std::swap(texture.id, temporary.texture.id);
    std::swap(texture.width, temporary.texture.width);
    std::swap(texture.height, temporary.texture.height);
    std::swap(texture.mipmaps, temporary.texture.mipmaps);
    std::swap(texture.format, temporary.texture.format);
    return *this;
}


void CS230::Texture::Load(const std::filesystem::path& file_name) {
    texture = LoadTexture(file_name.string().c_str());
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
}

Math::ivec2 CS230::Texture::GetSize() const {
    return { texture.width, texture.height };
}

void CS230::Texture::Draw(Math::vec2 location) {
    location.y *= -1;
    location.y += Engine::GetWindow().GetSize().y - texture.height;
    DrawTexture(texture, int(location.x), int(location.y), WHITE);
}

void CS230::Texture::Draw(Math::vec2 location, Rectangle rect)
{
    //Rectangle draw_rect = { rect.bottom_left.x,rect.bottom_left.y,rect.top_right.x - rect.bottom_left.x ,rect.top_right.y - rect.bottom_left.y };
    /*location.y *= -1;
    location.y += Engine::GetWindow().GetSize().y - texture.height;*/
    /*draw_rect.y *= -1;
    draw_rect.y += Engine::GetWindow().GetSize().y - draw_rect.height;*/
    DrawTexturePro(texture, rect, Rectangle{ float(location.x),float(location.y),rect.width,rect.height }, { 0,0 }, 0.f,WHITE);
}
