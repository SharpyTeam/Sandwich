//
// Created by selya on 31.08.2019.
//

#ifndef SANDWICH_RENDERER_SHADER_HPP
#define SANDWICH_RENDERER_SHADER_HPP

#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>

#include <glslcross.hpp>

#include <memory>
#include <map>
#include <vector>
#include <string>


namespace sw {

class Shader final {
public:
    using Stage = glslcross::Stage;

    enum class ValueType {
        FLOAT = 1,
        INT,
        UNSIGNED_INT,
        MATRIX_3_FLOAT,
        MATRIX_4_FLOAT,
        VECTOR_2_FLOAT,
        VECTOR_3_FLOAT,
        VECTOR_4_FLOAT,
        VECTOR_2_INT,
        VECTOR_3_INT,
        VECTOR_4_INT,
        VECTOR_2_UNSIGNED_INT,
        VECTOR_3_UNSIGNED_INT,
        VECTOR_4_UNSIGNED_INT,
        TEXTURE_UNIT,
        UNSUPPORTED
    };

    struct Attribute {
        const std::string name;
        const ValueType type;
        const unsigned int location;
    };

    struct Uniform {
        const std::string name;
        const ValueType type;
        const unsigned int location;

        void Set(float v);
        void Set(double v);
        void Set(int v);
        void Set(unsigned int v);
        void Set(const Vector2 &vec);
        void Set(const Vector3 &vec);
        void Set(const Vector4 &vec);
        void Set(const Matrix4 &mat);
    };

    Uniform *GetUniform(const std::string &name) const;
    const std::map<std::string, Uniform> &GetUniforms() const;

    Attribute *GetAttribute(const std::string &name) const;
    const std::map<std::string, Attribute> &GetAttributes() const;

    void Bind();

    ~Shader();
private:
    unsigned int program_id;

    std::map<std::string, Uniform> uniforms;
    std::map<std::string, Attribute> attributes;

    static Shader *bound_shader;

    explicit Shader(unsigned int program_id);

public:
    static std::shared_ptr<Shader> FromSpirv(
            const std::map<Stage, std::vector<uint32_t>> &spirv);

    static std::shared_ptr<Shader> FromSource(const std::map<Stage, std::string> &sources);

private:
    static std::shared_ptr<Shader> FromSourceInternal(const std::map<Stage, std::string> &sources);
};

}

#endif //SANDWICH_RENDERER_SHADER_HPP
