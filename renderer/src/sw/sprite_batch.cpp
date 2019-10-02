//
// Created by selya on 27.09.2019.
//

#include <sw/sprite_batch.hpp>

#include <sw/gl.hpp>

#include <stdexcept>

namespace sw {

const int SpriteBatch::max_quads = 2048;
const int SpriteBatch::floats_per_quad = 40;

SpriteBatch::SpriteBatch() : batch_pos(0), color(1.0) {
    std::vector<unsigned int> indices(max_quads * 6);
    for (unsigned int i = 0; (size_t)i < indices.size(); i += 6) {
        indices[i + 0] = i * 4 + 0u;
        indices[i + 1] = i * 4 + 1u;
        indices[i + 2] = i * 4 + 2u;
        indices[i + 3] = i * 4 + 0u;
        indices[i + 4] = i * 4 + 2u;
        indices[i + 5] = i * 4 + 3u;
    }

    glGenBuffers(1, &buffer_handle);
    glGenBuffers(1, &indices_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, max_quads * sizeof(float) * floats_per_quad, nullptr, GL_DYNAMIC_DRAW);

    shader = GetDefaultShader();
    batch.resize(max_quads * floats_per_quad);
}

SpriteBatch::~SpriteBatch() {
    glDeleteBuffers(1, &buffer_handle);
    glDeleteBuffers(1, &indices_buffer_handle);
}

void SpriteBatch::Begin() {
    batch_pos = 0;
}

void SpriteBatch::Flush() {
    if (!batch_pos || !shader) return;

    shader->Bind();
    texture->Bind();
    auto texture_uniform = shader->GetUniform("main_texture");
    if (texture_uniform) texture_uniform->Set(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch_pos * sizeof(float), batch.data());

    auto p = shader->GetAttribute("position");
    auto uv = shader->GetAttribute("uv");
    auto color = shader->GetAttribute("color");

    if (p) {
        glEnableVertexAttribArray(p->location);
        glVertexAttribPointer(p->location, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void *)nullptr);
    }

    if (uv) {
        glEnableVertexAttribArray(uv->location);
        glVertexAttribPointer(uv->location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void *)(sizeof(float) * 4));
    }

    if (color) {
        glEnableVertexAttribArray(color->location);
        glVertexAttribPointer(color->location, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void *)(sizeof(float) * 6));
    }

    glDrawElements(GL_TRIANGLES, batch_pos / floats_per_quad * 6, GL_UNSIGNED_INT, nullptr);

    if (p) glDisableVertexAttribArray(p->location);
    if (uv) glDisableVertexAttribArray(uv->location);
    if (color) glDisableVertexAttribArray(color->location);

    batch_pos = 0;
}

void SpriteBatch::End() {
    Flush();
}

void SpriteBatch::Draw(const std::shared_ptr<Texture> &texture, double x, double y, double rotation,
        double origin_x, double origin_y, double scale_x, double scale_y, bool flip_x, bool flip_y) {
    Draw(TextureRegion(texture), x, y, rotation, origin_x, origin_y, scale_x, scale_y, flip_x, flip_y);
}

void SpriteBatch::Draw(const TextureRegion &region, double x, double y, double rotation,
        double origin_x, double origin_y, double scale_x, double scale_y, bool flip_x, bool flip_y) {
    if (!shader || !region.GetTexture()) return;

    if (batch.size() - batch_pos < floats_per_quad) {
        Flush();
    }

    SetTexture(region.GetTexture());

    Vector2 origin(region.GetWidth() * origin_x, region.GetHeight() * origin_y);
    auto uv_lower = region.GetUVLower();
    auto uv_upper = region.GetUVUpper();

    transform_matrix.Identity().Translate(x, y, 0.0).Rotate(rotation, 0, 0, -1).Scale(scale_x, scale_y, 1.0);
    transform_matrix = view_projection_matrix * transform_matrix;

    Vector4 p = transform_matrix * Vector4(-origin.x, -origin.y, 0.0, 1.0);
    batch[batch_pos++] = p.x;
    batch[batch_pos++] = p.y;
    batch[batch_pos++] = p.z;
    batch[batch_pos++] = p.w;
    batch[batch_pos++] = uv_lower.x;
    batch[batch_pos++] = uv_lower.y;
    batch[batch_pos++] = color.x;
    batch[batch_pos++] = color.y;
    batch[batch_pos++] = color.z;
    batch[batch_pos++] = color.w;

    p = transform_matrix * Vector4(region.GetWidth() - origin.x, -origin.y, 0.0, 1.0);
    batch[batch_pos++] = p.x;
    batch[batch_pos++] = p.y;
    batch[batch_pos++] = p.z;
    batch[batch_pos++] = p.w;
    batch[batch_pos++] = uv_upper.x;
    batch[batch_pos++] = uv_lower.y;
    batch[batch_pos++] = color.x;
    batch[batch_pos++] = color.y;
    batch[batch_pos++] = color.z;
    batch[batch_pos++] = color.w;

    p = transform_matrix * Vector4(region.GetWidth() - origin.x, region.GetHeight() - origin.y, 0.0, 1.0);
    batch[batch_pos++] = p.x;
    batch[batch_pos++] = p.y;
    batch[batch_pos++] = p.z;
    batch[batch_pos++] = p.w;
    batch[batch_pos++] = uv_upper.x;
    batch[batch_pos++] = uv_upper.y;
    batch[batch_pos++] = color.x;
    batch[batch_pos++] = color.y;
    batch[batch_pos++] = color.z;
    batch[batch_pos++] = color.w;

    p = transform_matrix * Vector4(-origin.x, region.GetHeight() - origin.y, 0.0, 1.0);
    batch[batch_pos++] = p.x;
    batch[batch_pos++] = p.y;
    batch[batch_pos++] = p.z;
    batch[batch_pos++] = p.w;
    batch[batch_pos++] = uv_lower.x;
    batch[batch_pos++] = uv_upper.y;
    batch[batch_pos++] = color.x;
    batch[batch_pos++] = color.y;
    batch[batch_pos++] = color.z;
    batch[batch_pos++] = color.w;
}

void SpriteBatch::SetColor(const Vector4 &color) {
    this->color = color;
}

void SpriteBatch::SetShader(const std::shared_ptr<Shader> &shader) {
    if (shader == this->shader) return;
    Flush();
    this->shader = shader;
}

void SpriteBatch::SetViewMatrix(const Matrix4 &view_matrix) {
    this->view_matrix = view_matrix;
    this->view_projection_matrix = projection_matrix * view_matrix;
}

void SpriteBatch::SetProjectionMatrix(const Matrix4 &projection_matrix) {
    this->projection_matrix = projection_matrix;
    this->view_projection_matrix = projection_matrix * view_matrix;
}

Vector4 SpriteBatch::GetColor() const {
    return color;
}

std::shared_ptr<Shader> SpriteBatch::GetShader() const {
    return shader;
}

const Matrix4 &SpriteBatch::GetViewMatrix() const {
    return view_matrix;
}

const Matrix4 &SpriteBatch::GetProjectionMatrix() const {
    return projection_matrix;
}

void SpriteBatch::SetTexture(const std::shared_ptr<Texture> &texture) {
    if (texture == this->texture) return;
    Flush();
    this->texture = texture;
}

std::shared_ptr<Shader> SpriteBatch::GetDefaultShader() {
    static auto shader = Shader::FromSource(
        std::map<Shader::Stage, std::string> {
            { Shader::Stage::Vertex,
R"(#version 330 core

in vec4 position;
in vec2 uv;
in vec4 color;

out vec2 uv_;
out vec4 color_;

void main() {
    uv_ = uv;
    color_ = color;
    gl_Position = position;
})"
             },
            { Shader::Stage::Fragment,
R"(#version 330 core

in vec2 uv_;
in vec4 color_;

out vec4 fragment_color;

uniform sampler2D main_texture;

void main() {
    fragment_color = texture(main_texture, uv_) * color_;
})"
              },
        }
    );
    return shader;
}

} //namespace sw
