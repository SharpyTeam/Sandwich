//
// Created by Ilya on 03.09.2019.
//

#include <vector>
#include "scene_node.hpp"

namespace sw {


void SceneNode::AttachTo(const ip::intrusive_ptr<SceneNode> &node) {
    if (!parent_node)
        return;

    if (node != this->parent_node) {
        ip::intrusive_ptr<SceneNode> this_node = this;
        if (parent_node) {
            OnDetach();
            parent_node->children.erase(parent_list_iterator);
        }
        parent_node = node;
        parent_list_iterator = parent_node->children.insert(parent_node->children.end(), this_node);
        OnAttach();
    }
}

void SceneNode::Detach() {
    for (auto &child : children) {
        child->Destroy();
    }
    // TODO: Postpone node destruction
    parent_node->children.erase(parent_list_iterator);
    parent_node = nullptr;
}

void SceneNode::OnAttach() {

}

void SceneNode::OnDetach() {

}

void SceneNode::Destroy() {
    
}

}
