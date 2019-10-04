//
// Created by Ilya on 03.09.2019.
//

#include <sw/sprite.hpp>
#include <sw/scene.hpp>

namespace sw {

ip::intrusive_ptr <Sprite> sw::Sprite::Create() {
    auto s = new Sprite;
    s->AttachTo(Scene::scene);
    return s;
}

}