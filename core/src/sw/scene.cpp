//
// Created by Ilya on 05.09.2019.
//

#include <sw/scene.hpp>

#include <stdexcept>

namespace sw {

void Scene::AttachTo(const ip::intrusive_ptr<SceneNode> &node) {}

ip::intrusive_ptr<Scene> Scene::Create() {
    return new Scene;
}

}
