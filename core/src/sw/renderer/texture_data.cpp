//
// Created by selya on 26.09.2019.
//

#include "texture_data.hpp"

#include <stdexcept>
#include <cstring>
#include <utility>

namespace sw {

static inline size_t FormatSize(TextureData::Format format) {
    switch (format) {
        case TextureData::Format::RGBA8888: return 4;
        case TextureData::Format::RGB565: return 2;
        case TextureData::Format::RGB888: return 3;
        case TextureData::Format::RGBA4444: return 2;
    }
    throw std::runtime_error("not implemented");
}

static inline void FormatSetPixel(TextureData::Format format, unsigned char *mem, float r, float g, float b, float a) {
    switch (format) {
        case TextureData::Format::RGBA8888:
            mem[0] = (unsigned char)(255 * r);
            mem[1] = (unsigned char)(255 * g);
            mem[2] = (unsigned char)(255 * b);
            mem[3] = (unsigned char)(255 * a);
            return;

        case TextureData::Format::RGB565:
            *reinterpret_cast<unsigned short *>(mem) =
                    ((unsigned int)(31 * r) << 11u) |
                    ((unsigned int)(63 * g) << 5u) |
                    (unsigned int)(31 * b);
            return;

        case TextureData::Format::RGB888:
            mem[0] = (unsigned char)(255 * r);
            mem[1] = (unsigned char)(255 * g);
            mem[2] = (unsigned char)(255 * b);
            return;

        case TextureData::Format::RGBA4444:
            *reinterpret_cast<unsigned short *>(mem) =
                    ((unsigned int)(15 * r) << 12u) |
                    ((unsigned int)(15 * g) << 8u) |
                    ((unsigned int)(15 * b) << 4u) |
                    (unsigned int)(15 * a);
            return;
    }
    throw std::runtime_error("not implemented");
}

static inline math::Vector4 FormatGetPixel(TextureData::Format format, unsigned char *mem) {
    switch (format) {
        case TextureData::Format::RGBA8888:
            return math::Vector4(
                    mem[0] / 255.0,
                    mem[1] / 255.0,
                    mem[2] / 255.0,
                    mem[3] / 255.0
            );

        case TextureData::Format::RGB565: {
            unsigned int s = *reinterpret_cast<unsigned short *>(mem);
            return math::Vector4(
                    ((s >> 11u) & 31u) / 31.0,
                    ((s >> 5u) & 63u) / 63.0,
                    (s & 31u) / 31.0,
                    1.0
            );
        }

        case TextureData::Format::RGB888:
            return math::Vector4(
                    mem[0] / 255.0,
                    mem[1] / 255.0,
                    mem[2] / 255.0,
                    1.0
            );

        case TextureData::Format::RGBA4444: {
            unsigned int s = *reinterpret_cast<unsigned short *>(mem);
            return math::Vector4(
                    ((s >> 12u) & 15u) / 15.0,
                    ((s >> 8u) & 15u) / 15.0,
                    ((s >> 4u) & 15u) / 15.0,
                    (s & 15u) / 15.0
            );
        }
    }
    throw std::runtime_error("not implemented");
}

TextureData::TextureData(int width, int height, TextureData::Format format)
    : width(width), height(height), format(format) {
    SetFormat(format);
}

TextureData::TextureData(int width, int height, const std::vector<unsigned char> &data, TextureData::Format format)
    : width(width), height(height), format(format) {
    SetData(width, height, data, format);
}

TextureData::TextureData(int width, int height, std::vector<unsigned char> &&data, TextureData::Format format)
    : width(width), height(height), format(format) {
    SetData(width, height, std::move(data), format);
}

TextureData::TextureData(const TextureData &other)
    : TextureData::TextureData(other.width, other.height, other.data, other.format) {}

TextureData::TextureData(TextureData &&other)
    : TextureData::TextureData(other.width, other.height, std::move(other.data), other.format) {}

TextureData::~TextureData() {}

TextureData &TextureData::operator=(const TextureData &other) {
    SetData(other.width, other.height, other.data, other.format);
    return *this;
}

TextureData &TextureData::operator=(TextureData &&other) {
    SetData(other.width, other.height, std::move(other.data), other.format);
    return *this;
}

int TextureData::GetWidth() const {
    return width;
}

int TextureData::GetHeight() const {
    return height;
}

void TextureData::SetWidth(int width) {
    this->width = width;
    SetFormat(format);
}

void TextureData::SetHeight(int height) {
    this->height = height;
    SetFormat(format);
}

math::Vector4 TextureData::GetPixel(int x, int y) const {
    return math::Vector4();
}

void TextureData::SetPixel(int x, int y, float r, float g, float b, float a) {
    FormatSetPixel(format, &data[FormatSize(format) * (y * width + x)], r, g, b, a);
}

void TextureData::SetPixel(int x, int y, const math::Vector4 &color) {
    SetPixel(x, y, color.x, color.y, color.z, color.w);
}

void TextureData::SetRect(int x, int y, const TextureData &r) {
    SetRect(x, y, r, 0, 0, r.width, r.height);
}

void TextureData::SetRect(int x, int y, const TextureData &r, int src_x, int src_y, int src_width, int src_height) {
    throw std::runtime_error("not implemented");
}

void TextureData::Fill(float r, float g, float b, float a) {
    size_t size = FormatSize(format);
    unsigned char *mem = data.data();
    unsigned char *mem_end = mem + data.size();
    std::vector<unsigned char> pixel(size);
    FormatSetPixel(format, pixel.data(), r, g, b, a);
    while (mem < mem_end) {
        std::memcpy(mem, pixel.data(), size);
        mem += size;
    }
}

void TextureData::Fill(const math::Vector4 &color) {
    Fill(color.x, color.y, color.z, color.w);
}

void TextureData::FlipHorizontally() {
    throw std::runtime_error("not implemented");
}

void TextureData::FlipVertically() {
    throw std::runtime_error("not implemented");
}

std::vector<unsigned char> &TextureData::GetData() const {
    return const_cast<std::vector<unsigned char> &>(data);
}

void TextureData::SetData(int width, int height, const std::vector<unsigned char> &data, TextureData::Format format) {
    this->width = width;
    this->height = height;
    this->data = data;
    this->format = format;
    SetFormat(format);
}

void TextureData::SetData(int width, int height, std::vector<unsigned char> &&data, TextureData::Format format) {
    this->width = width;
    this->height = height;
    std::swap(this->data, data);
    this->format = format;
    SetFormat(format);
}

TextureData::Format TextureData::GetFormat() const {
    return format;
}

void TextureData::SetFormat(TextureData::Format format) {
    if (this->format != format) {
        size_t dst_size = FormatSize(format);
        size_t src_size = FormatSize(this->format);
        std::vector<unsigned char> dst;
        dst.resize(dst_size * width * height);

        unsigned char *src_mem = data.data();
        unsigned char *src_mem_end = src_mem + data.size();
        unsigned char *dst_mem = dst.data();
        while (src_mem < src_mem_end) {
            auto color = FormatGetPixel(this->format, src_mem);
            FormatSetPixel(format, dst_mem, color.x, color.y, color.z, color.w);
            src_mem += src_size;
            dst_mem += dst_size;
        }

        this->data = dst;
        this->format = format;
    } else {
        if (data.size() != FormatSize(format) * width * height) {
            data.resize(FormatSize(format) * width * height);
        }
    }
}

}
