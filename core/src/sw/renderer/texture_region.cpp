//
// Created by selya on 27.09.2019.
//

#include "texture_region.hpp"

namespace sw {

TextureRegion::TextureRegion() : flags(0) {}

TextureRegion::TextureRegion(const std::shared_ptr<Texture> &texture)
    : TextureRegion::TextureRegion(texture, 0, 0, texture->GetWidth(), texture->GetHeight()) {}

TextureRegion::TextureRegion(const std::shared_ptr<Texture> &texture, double x, double y, double width, double height)
    : texture(texture), offset(x, y), size(width, height), flags(0) {}

TextureRegion::TextureRegion(const TextureRegion &other)
    : TextureRegion::TextureRegion(other.texture, other.offset.x, other.offset.y, other.size.x, other.size.y) {
    flags = other.flags;
}

TextureRegion::TextureRegion(TextureRegion &&other)
    : TextureRegion::TextureRegion(other.texture, other.offset.x, other.offset.y, other.size.x, other.size.y) {
    flags = other.flags;
}

TextureRegion &TextureRegion::operator=(const TextureRegion &other) {
    offset = other.offset;
    size = other.size;
    flags = other.flags;
    texture = other.texture;
    return *this;
}

TextureRegion &TextureRegion::operator=(TextureRegion &&other) {
    offset = other.offset;
    size = other.size;
    flags = other.flags;
    texture = other.texture;
    return *this;
}

void TextureRegion::SetTexture(const std::shared_ptr<Texture> &texture) {
    this->texture = texture;
}

void TextureRegion::SetX(double x) {
    offset.x = x;
}

void TextureRegion::SetY(double y) {
    offset.y = y;
}

void TextureRegion::SetWidth(double width) {
    size.x = width;
}

void TextureRegion::SetHeight(double height) {
    size.y = height;
}

void TextureRegion::SetFlipX(bool flip) {
    if (flip) flags |= 1u;
    else flags &= ~1u;
}

void TextureRegion::SetFlipY(bool flip) {
    if (flip) flags |= 2u;
    else flags &= ~2u;
}

std::shared_ptr<Texture> TextureRegion::GetTexture() const {
    return texture;
}

double TextureRegion::GetX() const {
    return offset.x;
}

double TextureRegion::GetY() const {
    return offset.y;
}

double TextureRegion::GetWidth() const {
    return size.x;
}

double TextureRegion::GetHeight() const {
    return size.y;
}

math::Vector2 TextureRegion::GetUVUpper() const {
    return (offset + size) / math::Vector2(texture->GetWidth(), texture->GetHeight());
}

math::Vector2 TextureRegion::GetUVLower() const {
    return offset / math::Vector2(texture->GetWidth(), texture->GetHeight());
}

bool TextureRegion::GetFlipX() const {
    return bool(flags & 1u);
}

bool TextureRegion::GetFlipY() const {
    return bool(flags & 2u);
}

} //namespace sw
