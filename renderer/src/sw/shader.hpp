//
// Created by selya on 31.08.2019.
//

#ifndef SANDWICH_CORE_SHADER_HPP
#define SANDWICH_CORE_SHADER_HPP

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
    typedef glslcross::ShaderProgram::Stage Stage;

    enum ValueType {
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
        // OpenGL location in shader
        const unsigned int location;
    };

    struct Uniform {
        const std::string name;
        const ValueType type;
        // OpenGL location in shader
        const unsigned int location;

        void Set(double v);
        void Set(int v);
        void Set(const Vector2 &vec);
        void Set(const Vector3 &vec);
        void Set(const Vector4 &vec);
        void Set(const Matrix4 &mat);
    };

    Uniform *GetUniform(const std::string &name) const;
    const std::map<std::string, Uniform> &GetUniforms() const;

    Attribute *GetAttribute(const std::string &name) const;
    const std::map<std::string, Attribute> &GetAttributes() const;

    void Bind() {}

private:
    // OpenGL program id
    unsigned int program_id;

    std::map<std::string, Uniform> uniforms;
    std::map<std::string, Attribute> attributes;

    explicit Shader(unsigned int program_id) : program_id(program_id) {}
    ~Shader() {
        // TODO OpenGL shader program destruction here
    }

public:

    static std::shared_ptr<Shader> FromSource(const std::map<Stage, std::string> &sources,
                                              int target_version, bool es) {
        glslcross::ShaderProgram program;
        for (auto &p : sources) {
            auto stage = p.first;
            program.GetShaderData((glslcross::ShaderProgram::Stage)stage).source = p.second;
        }
        if (!program.Crosscompile(target_version, es)) {
            // TODO remove with logging
            std::cout << program.GetInfoLog() << std::endl;
            return nullptr;
        }
        std::map<Stage, std::string> crosscompiled_sources;
        for (auto &p : sources) {
            auto stage = p.first;
            crosscompiled_sources[stage] =
                    program.GetShaderData((glslcross::ShaderProgram::Stage)stage).GetCrosscompiledSource();
        }
        return FromSource(crosscompiled_sources);
    }

    static std::shared_ptr<Shader> FromSpirV(const std::map<Stage, std::vector<uint32_t>> &spirv,
                                             int target_version, bool es) {
        glslcross::ShaderProgram program;
        for (auto &p : spirv) {
            auto stage = p.first;
            program.GetShaderData((glslcross::ShaderProgram::Stage)stage).spirv = p.second;
        }
        if (!program.Crosscompile(target_version, es)) {
            // TODO remove with logging
            std::cout << program.GetInfoLog() << std::endl;
            return nullptr;
        }
        std::map<Stage, std::string> crosscompiled_sources;
        for (auto &p : spirv) {
            auto stage = p.first;
            crosscompiled_sources[stage] =
                    program.GetShaderData((glslcross::ShaderProgram::Stage)stage).GetCrosscompiledSource();
        }
        return FromSource(crosscompiled_sources);
    }

    static std::shared_ptr<Shader> FromSource(const std::map<Stage, std::string> &sources) {
        // TODO actual OpenGL compiling here
        return nullptr;
    }
};

}

#endif //SANDWICH_CORE_SHADER_HPP
