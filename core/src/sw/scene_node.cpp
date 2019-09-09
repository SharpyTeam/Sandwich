//
// Created by Ilya on 03.09.2019.
//

#include <vector>
#include "scene_node.hpp"

namespace sw {


void SceneNode::AttachTo(const std::shared_ptr<SceneNode> &node) {
    if (!parent_node)
        return;

    if (node != this->parent_node) {
        std::shared_ptr<SceneNode> this_node(this);
        if (this_node->parent_node) {
            this_node->parent_node->OnDetach();
            this_node->parent_node->children.erase(parent_list_iterator);
        }
        this_node->parent_node = node;
        this_node->parent_list_iterator = this_node->parent_node->children.insert(this_node->parent_node->children.end(), this_node);
    }
}

void SceneNode::Detach() {

}

void SceneNode::OnAttach() {

}

void SceneNode::OnDetach() {

}

void SceneNode::Destroy() {
    
}

}
