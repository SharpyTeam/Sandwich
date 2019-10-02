//
// Created by Ilya on 05.09.2019.
//

#ifndef SANDWICH_SCENE_HPP
#define SANDWICH_SCENE_HPP

#include <sw/scene_node.hpp>

namespace sw {

class Scene : public SceneNode {
public:
    static ip::intrusive_ptr<Scene> Create();
private:
    void AttachTo(const ip::intrusive_ptr<SceneNode> &node) override;
};

}

#endif //SANDWICH_SCENE_HPP
