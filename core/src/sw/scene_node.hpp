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
#include <sw/renderer/sprite_batch.hpp>

namespace sw {

class SceneNode : public ip::ref_counter {
public:
    std::shared_ptr<math::Vector2> position;
    std::shared_ptr<math::Vector2> local_position;
    std::shared_ptr<math::Vector2> scale;
    double rotation;
    double local_rotation;

protected:
    //TODO add getters and setters for this fields
    ip::intrusive_ptr<SceneNode> parent;
    std::list<ip::intrusive_ptr<SceneNode>> children;
    std::list<ip::intrusive_ptr<SceneNode>>::const_iterator parent_list_iterator;
    SceneNode();

public:
    REMOVE_DEFAULTS(SceneNode)
    ~SceneNode() override;

    virtual void AttachTo(const ip::intrusive_ptr<SceneNode> &new_parent);
    virtual void Destroy();

    virtual void OnAttach();
    virtual void OnDetach();

    virtual void Update(double delta);
    virtual void Draw(SpriteBatch &batch);

    static ip::intrusive_ptr<SceneNode> Create();
};


}


#endif //SANDWICH_SCENE_NODE_HPP
