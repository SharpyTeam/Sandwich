//
// Created by selya on 22.10.2019.
//

#ifndef SANDWICH_RENDERER_TEXTURE_BINDER_H
#define SANDWICH_RENDERER_TEXTURE_BINDER_H

#include "texture.hpp"

#include <list>
#include <vector>
#include <unordered_map>

namespace sw {

class TextureUnitManager final {
    friend class Texture;
    friend class TextureUnit;

public:
    class TextureUnit {
        friend class TextureUnitManager;

    public:
        const int index;

    private:
        unsigned int texture_handle;
        bool in_use;
        std::list<TextureUnit *>::const_iterator iter_in_queue;

    public:
        explicit TextureUnit(int index);

        bool InUse() const;

        void Free();
        bool Claim(unsigned int texture_handle, bool force_free = false);
    };

    TextureUnitManager() = delete;

    static TextureUnit *GetUnit(int index);
    static TextureUnit *SetActiveUnit(int index);
    static TextureUnit *GetActiveUnit();

private:
    static bool Initialize();
    static TextureUnit *Bind(Texture *texture);
    static void Unbind(Texture *texture);

    static std::vector<TextureUnit> units;
    static std::list<TextureUnit *> units_queue;
    static std::unordered_map<unsigned int, TextureUnit *> handle_to_unit;
    static TextureUnit *active_unit;
};

} //namespace sw

#endif //SANDWICH_RENDERER_TEXTURE_BINDER_H
