//
// Created by Ilya on 05.09.2019.
//

#include <sw/scene.hpp>

#include <stdexcept>

namespace sw {

void Scene::AttachTo(const ip::intrusive_ptr<SceneNode> &node) {
    throw std::runtime_error("Should not be called");
}

ip::intrusive_ptr<Scene> Scene::Create() {
    return new Scene();
}

}
