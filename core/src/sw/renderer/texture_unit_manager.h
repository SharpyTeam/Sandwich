//
// Created by selya on 22.10.2019.
//

#ifndef SANDWICH_RENDERER_TEXTURE_BINDER_H
#define SANDWICH_RENDERER_TEXTURE_BINDER_H

#include "texture.hpp"

#include <queue>
#include <vector>
#include <map>

namespace sw {

class TextureUnitManager final {
    friend class Texture;

    struct TextureUnit {
        const int index;
        int bound_texture_handle;

        TextureUnit(int index);
    };

public:
    TextureUnitManager() = delete;

    static void SetActiveUnit(int index);
    static int GetActiveUnit();

private:
    static bool Initialize();
    static int PickAndActiveUnit(Texture *texture);

    static std::vector<TextureUnit> units;
    static std::queue<TextureUnit *> units_queue;
    static std::map<int, TextureUnit *> handle_to_unit;
    static int active_unit;
};

} //namespace sw

#endif //SANDWICH_RENDERER_TEXTURE_BINDER_H
