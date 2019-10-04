//
// Created by Ilya on 03.09.2019.
//

#ifndef SANDWICH_CORE_SPRITE_HPP
#define SANDWICH_CORE_SPRITE_HPP

#include <sw/scene_node.hpp>

#include <sw/renderer/texture_region.hpp>

namespace sw {

class Sprite : public SceneNode {
public:
    // TODO change to texture region
    std::shared_ptr<sw::Texture> texture;
    std::shared_ptr<math::Vector2> origin;

    void Draw(SpriteBatch &batch) override {
        batch.Draw(texture, position->x, position->y, rotation, origin->x, origin->y, scale->x, scale->y);
        SceneNode::Draw(batch);
    }

    static ip::intrusive_ptr<Sprite> Create();
};

}


#endif //SANDWICH_CORE_SPRITE_HPP
