//
// Created by selya on 26.09.2019.
//

#include "texture.hpp"

#include "gl.hpp"

#include <stdexcept>

namespace sw {


int Texture::GetWidth() const {
    if (IsLoaded()) return width;
    return data.GetWidth();
}

int Texture::GetHeight() const {
    if (IsLoaded()) return height;
    return data.GetHeight();
}

Texture::Filtering Texture::GetFiltering() const {
    return filtering;
}

Texture::Wrapping Texture::GetWrapping() const {
    return wrapping;
}

void Texture::SetFiltering(Texture::Filtering filtering) {
    filtering_updated = this->filtering != filtering;
    this->filtering = filtering;
}

void Texture::SetWrapping(Texture::Wrapping wrapping) {
    wrapping_updated = this->wrapping != wrapping;
    this->wrapping = wrapping;
}

TextureData &Texture::GetData() const {
    return const_cast<TextureData &>(data);
}

void Texture::SetData(const TextureData &data) {
    this->data = data;
}

void Texture::SetData(TextureData &&data) {
    this->data = std::move(data);
}

bool Texture::HaveMipmap() const {
    return mipmap;
}

void Texture::GenMipmap() {
    Bind();
    glGenerateMipmap(GL_TEXTURE_2D);
    mipmap = true;
}

bool Texture::IsLoaded() const {
    return loaded;
}

void Texture::Load() {
    if (IsLoaded()) return;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    if (data.GetFormat() != TextureData::Format::RGBA8888 && data.GetFormat() != TextureData::Format::RGB888) {
        throw std::runtime_error("Non-compatible TextureData format for loading");
    }

    glTexImage2D(GL_TEXTURE_2D, 0,
            data.GetFormat() == TextureData::Format::RGB888 ? GL_RGB : GL_RGBA,
            GetWidth(), GetHeight(), 0,
            data.GetFormat() == TextureData::Format::RGB888 ? GL_RGB : GL_RGBA,
            GL_UNSIGNED_BYTE, data.GetData().data());

    width = GetWidth();
    height = GetHeight();

    loaded = true;
}

void Texture::Unload() {
    if (!IsLoaded()) return;
    glDeleteTextures(1, &handle);
    loaded = false;
}

void Texture::Reload() {
    Unload();
    Load();
}

std::shared_ptr<Texture> Texture::Create(const TextureData &data) {
    return std::shared_ptr<Texture>(new Texture(data));
}

std::shared_ptr<Texture> Texture::Create(TextureData &&data) {
    return std::shared_ptr<Texture>(new Texture(std::move(data)));
}

Texture::Texture(const TextureData &data) : Texture::Texture(TextureData(data)) {}

Texture::Texture(TextureData &&data)
    : filtering(Filtering::LINEAR), wrapping(Wrapping::EDGE),
    filtering_updated(true), wrapping_updated(true),
    data(data), mipmap(false), loaded(false) {}

Texture::~Texture() {
    if (IsLoaded()) Unload();
}

void Texture::Bind() {
    Load();
    glBindTexture(GL_TEXTURE_2D, handle);
    if (filtering_updated) {
        GLint f;
        switch (filtering) {
            case Filtering::NEAREST: f = GL_NEAREST; break;
            case Filtering::LINEAR: f = GL_LINEAR; break;
            case Filtering::TRILINEAR: f = GL_LINEAR_MIPMAP_LINEAR; break;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
        filtering_updated = false;
    }
    if (wrapping_updated) {
        GLint w;
        switch (wrapping) {
            case Wrapping::EDGE: w = GL_CLAMP_TO_EDGE; break;
            case Wrapping::MIRROR: w = GL_MIRRORED_REPEAT; break;
            case Wrapping::REPEAT: w = GL_REPEAT; break;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, w);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, w);
        wrapping_updated = false;
    }
}

} // namespace sw
