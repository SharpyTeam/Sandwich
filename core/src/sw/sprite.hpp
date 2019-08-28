//
// Created by selya on 23.07.2019.
//

#ifndef SANDWICH_CORE_SPRITE_HPP
#define SANDWICH_CORE_SPRITE_HPP

#include <vector.hpp>

namespace sw {

class Sprite {
public:
    Vector2 position;
    Vector2 scale;
    double rotation;

    Sprite() : position(0), scale(1), rotation(0) {

    }

};

}

#endif //SANDWICH_CORE_SPRITE_HPP
