//
// Created by selya on 27.09.2019.
//

#ifndef SANDWICH_RENDERER_SPRITE_BATCH_HPP
#define SANDWICH_RENDERER_SPRITE_BATCH_HPP

#include "shader.hpp"
#include "texture.hpp"
#include "texture_region.hpp"
#include <sw/math/matrix.hpp>
#include <sw/math/vector.hpp>

#include <memory>
#include <vector>

namespace sw {

class SpriteBatch {
public:
    SpriteBatch();
    ~SpriteBatch();

    void Begin();
    void Flush();
    void End();

    void Draw(const std::shared_ptr<Texture> &texture, const math::Vector2 &position, double rotation = 0.0,
            const math::Vector2 &origin = math::Vector2(0.0), const math::Vector2 &scale = math::Vector2(1.0),
            bool flip_x = false, bool flip_y = false);

    void Draw(const std::shared_ptr<Texture> &texture, double x, double y, double rotation = 0.0,
            double origin_x = 0.0, double origin_y = 0.0, double scale_x = 1.0, double scale_y = 1.0,
            bool flip_x = false, bool flip_y = false);

    void Draw(const TextureRegion &region, const math::Vector2 &position, double rotation = 0.0,
              const math::Vector2 &origin = math::Vector2(0.0), const math::Vector2 &scale = math::Vector2(1.0),
              bool flip_x = false, bool flip_y = false);

    void Draw(const TextureRegion &region, double x, double y, double rotation = 0.0,
              double origin_x = 0.0, double origin_y = 0.0, double scale_x = 1.0, double scale_y = 1.0,
              bool flip_x = false, bool flip_y = false);

    void SetColor(const math::Vector4 &color);
    void SetShader(const std::shared_ptr<Shader> &shader);
    void SetViewMatrix(const math::Matrix4 &view_matrix);
    void SetProjectionMatrix(const math::Matrix4 &projection_matrix);

    math::Vector4 GetColor() const;
    std::shared_ptr<Shader> GetShader() const;
    const math::Matrix4 &GetViewMatrix() const;
    const math::Matrix4 &GetProjectionMatrix() const;

private:
    void SetTexture(const std::shared_ptr<Texture> &texture);

    static std::shared_ptr<Shader> GetDefaultShader();

    static const int max_quads;
    static const int floats_per_quad;

    unsigned int buffer_handle;
    unsigned int indices_buffer_handle;

    std::vector<float> batch;
    int batch_pos;

    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;

    math::Vector4 color;

    math::Matrix4 view_matrix;
    math::Matrix4 projection_matrix;
    math::Matrix4 view_projection_matrix;
    math::Matrix4 transform_matrix;
};

} //namespace sw

#endif //SANDWICH_SPRITE_BATCH_HPP
