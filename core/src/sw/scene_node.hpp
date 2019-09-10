//
// Created by Ilya on 03.09.2019.
//

#ifndef SANDWICH_SCENE_NODE_HPP
#define SANDWICH_SCENE_NODE_HPP

#include <sw/math/vector.hpp>
#include <list>
#include <memory>
#include <sw/core/sw_macros.hpp>
#include <ip/intrusive_ptr.hpp>

namespace sw {

class SceneNode : public ip::ref_counter {
public:
    REMOVE_DEFAULTS(SceneNode)

    SceneNode() : position(new Vector2),
                  local_position(new Vector2),
                  scale(new Vector2),
                  rotation(0.0),
                  local_rotation(0.0) {}

    virtual void AttachTo(const ip::intrusive_ptr<SceneNode> &node);
    virtual void Detach();
    virtual void Destroy();

    virtual void OnAttach();
    virtual void OnDetach();

    static ip::intrusive_ptr<SceneNode> Create() {
        ip::intrusive_ptr<SceneNode> node = new SceneNode;
        return node;
    }

    std::shared_ptr<Vector2> position;
    std::shared_ptr<Vector2> local_position;
    std::shared_ptr<Vector2> scale;
    double rotation;
    double local_rotation;

    ip::intrusive_ptr<SceneNode> parent_node;
    std::list<ip::intrusive_ptr<SceneNode>> children;
    std::list<ip::intrusive_ptr<SceneNode>>::const_iterator parent_list_iterator;
};


}


#endif //SANDWICH_SCENE_NODE_HPP
