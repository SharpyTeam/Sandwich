//
// Created by selya on 23.07.2019.
//

#ifndef SANDWICH_CORE_SPRITE_HPP
#define SANDWICH_CORE_SPRITE_HPP

#include <sw/object_wrap.hpp>
#include <sw/math/vector.hpp>

namespace sw {

class Sprite : public ObjectWrap {
public:
    Vector2 position;
    Vector2 scale;
    double rotation;

    Sprite() : position(0), scale(1), rotation(0) {

    }

    DECLARE_WRAP
};

}

#endif //SANDWICH_CORE_SPRITE_HPP
