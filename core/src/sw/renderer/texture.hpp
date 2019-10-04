//
// Created by selya on 26.09.2019.
//

#ifndef SANDWICH_RENDERER_TEXTURE_HPP
#define SANDWICH_RENDERER_TEXTURE_HPP

#include "texture_data.hpp"

#include <memory>

namespace sw {

class Texture final {
public:
    enum class Filtering {
        NEAREST,
        LINEAR,
        TRILINEAR
    };

    enum class Wrapping {
        EDGE,
        REPEAT,
        MIRROR
    };

    int GetWidth() const;
    int GetHeight() const;

    Filtering GetFiltering() const;
    Wrapping GetWrapping() const;

    void SetFiltering(Filtering filtering);
    void SetWrapping(Wrapping wrapping);

    TextureData &GetData() const;
    void SetData(const TextureData &data);
    void SetData(TextureData &&data);

    bool HaveMipmap() const;
    void GenMipmap();

    bool IsLoaded() const;
    void Load();
    void Unload();
    void Reload();

    void Bind();

    static std::shared_ptr<Texture> Create(const TextureData &data);
    static std::shared_ptr<Texture> Create(TextureData &&data);

    ~Texture();

private:
    Texture(const TextureData &data);
    Texture(TextureData &&data);

    int width;
    int height;
    unsigned int handle;
    Filtering filtering;
    Wrapping wrapping;
    bool filtering_updated;
    bool wrapping_updated;
    TextureData data;
    bool mipmap;
    bool loaded;
};

} // namespace sw

#endif //SANDWICH_RENDERER_TEXTURE_HPP
