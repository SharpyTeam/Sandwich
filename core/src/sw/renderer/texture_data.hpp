//
// Created by selya on 26.09.2019.
//

#ifndef SANDWICH_RENDERER_TEXTURE_DATA_HPP
#define SANDWICH_RENDERER_TEXTURE_DATA_HPP

#include <sw/math/vector.hpp>

#include <vector>

namespace sw {

class TextureData final {
public:
    enum class Format {
        RGBA8888,
        RGB888,
        RGB565,
        RGBA4444
    };

    TextureData(int width, int height, Format format = Format::RGBA8888);
    TextureData(int width, int height, const std::vector<unsigned char> &data, Format format = Format::RGBA8888);
    TextureData(int width, int height, std::vector<unsigned char> &&data, Format format = Format::RGBA8888);
    TextureData(const TextureData &other);
    TextureData(TextureData &&other);

    ~TextureData();

    TextureData &operator=(const TextureData &other);
    TextureData &operator=(TextureData &&other);

    int GetWidth() const;
    int GetHeight() const;

    void SetWidth(int width);
    void SetHeight(int height);

    math::Vector4 GetPixel(int x, int y) const;

    void SetPixel(int x, int y, float r, float g, float b, float a = 1.0);
    void SetPixel(int x, int y, const math::Vector4 &color);

    void SetRect(int x, int y, const TextureData &r);
    void SetRect(int x, int y, const TextureData &r, int src_x, int src_y, int src_width, int src_height);

    void Fill(float r, float g, float b, float a);
    void Fill(const math::Vector4 &color);

    void FlipHorizontally();
    void FlipVertically();

    std::vector<unsigned char> &GetData() const;

    void SetData(int width, int height, const std::vector<unsigned char> &data, Format format = Format::RGBA8888);
    void SetData(int width, int height, std::vector<unsigned char> &&data, Format format = Format::RGBA8888);

    Format GetFormat() const;
    void SetFormat(Format format);

private:
    int width;
    int height;
    std::vector<unsigned char> data;
    Format format;
};

} // namespace sw

#endif //SANDWICH_RENDERER_TEXTURE_DATA_HPP
