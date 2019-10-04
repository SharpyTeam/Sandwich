//
// Created by selya on 26.09.2019.
//

#ifndef SANDWICH_RENDERER_TEXTURE_REGION_HPP
#define SANDWICH_RENDERER_TEXTURE_REGION_HPP

#include "texture.hpp"

namespace sw {

class TextureRegion final {
public:
    TextureRegion();
    TextureRegion(const std::shared_ptr<Texture> &texture);
    TextureRegion(const std::shared_ptr<Texture> &texture, double x, double y, double width, double height);
    TextureRegion(const TextureRegion &other);
    TextureRegion(TextureRegion &&other);

    TextureRegion &operator=(const TextureRegion &other);
    TextureRegion &operator=(TextureRegion &&other);

    void SetTexture(const std::shared_ptr<Texture> &texture);
    void SetX(double x);
    void SetY(double y);
    void SetWidth(double width);
    void SetHeight(double height);
    void SetFlipX(bool flip);
    void SetFlipY(bool flip);

    std::shared_ptr<Texture> GetTexture() const;
    double GetX() const;
    double GetY() const;
    double GetWidth() const;
    double GetHeight() const;
    math::Vector2 GetUVUpper() const;
    math::Vector2 GetUVLower() const;
    bool GetFlipX() const;
    bool GetFlipY() const;

private:
    std::shared_ptr<Texture> texture;
    math::Vector2 offset;
    math::Vector2 size;

    // 7
    // 6
    // 5
    // 4
    // 3
    // 2
    // 1 - y flip flag
    // 0 - x flip flag
    unsigned char flags;
};

} // namespace sw

#endif //SANDWICH_RENDERER_TEXTURE_REGION_HPP
