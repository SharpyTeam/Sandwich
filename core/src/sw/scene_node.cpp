//
// Created by Ilya on 03.09.2019.
//

#include <sw/scene_node.hpp>

#include <vector>

namespace sw {

SceneNode::SceneNode()
    : position(new Vector2),
    local_position(new Vector2),
    scale(new Vector2(1)),
    rotation(0.0),
    local_rotation(0.0) {}

SceneNode::~SceneNode() = default;

void SceneNode::OnAttach() {}

void SceneNode::OnDetach() {}

void SceneNode::AttachTo(const ip::intrusive_ptr<SceneNode> &new_parent) {
    if (!new_parent)
        return;

    if (new_parent == parent) {
        return;
    }

    ip::intrusive_ptr<SceneNode> this_node = this;
    if (parent) {
        OnDetach();
        parent->children.erase(parent_list_iterator);
    }
    parent = new_parent;
    parent_list_iterator = parent->children.insert(parent->children.end(), this_node);
    OnAttach();
}

void SceneNode::Destroy() {
    for (auto &c : children) {
        c->Destroy();
    }
    if (!parent) return;
    parent->children.erase(parent_list_iterator);
    parent = nullptr;
}

ip::intrusive_ptr<SceneNode> SceneNode::Create() {
    return new SceneNode;
}

void SceneNode::Update(double delta) {
    for (auto &c : children) {
        c->Update(delta);
    }
    // TODO: Default node update code
}

void SceneNode::Draw(SpriteBatch &batch) {
    for (auto &c : children) {
        c->Draw(batch);
    }
}

}
