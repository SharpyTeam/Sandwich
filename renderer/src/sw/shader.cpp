//
// Created by selya on 31.08.2019.
//

#include <sw/shader.hpp>

#include <sw/gl.hpp>

#include <stdexcept>
#include <vector>

namespace sw {

Shader *Shader::bound_shader = nullptr;

void Shader::Uniform::Set(float v) {
    switch (type) {
        case ValueType::FLOAT:
            glUniform1f(location, (float)v);
            break;

        case ValueType::INT:
            glUniform1i(location, (int)v);
            break;

        case ValueType::UNSIGNED_INT:
#if RENDERER_GL
            glUniform1ui(location, (unsigned int)v);
#else
            glUniform1i(location, (int)v);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(double v) {
    switch (type) {
        case ValueType::FLOAT:
            glUniform1f(location, (float)v);
            break;

        case ValueType::INT:
            glUniform1i(location, (int)v);
            break;

        case ValueType::UNSIGNED_INT:
#if RENDERER_GL
            glUniform1ui(location, (unsigned int)v);
#else
            glUniform1i(location, (int)v);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(int v) {
    switch (type) {
        case ValueType::FLOAT:
            glUniform1f(location, (float)v);
            break;

        case ValueType::TEXTURE_UNIT:
        case ValueType::INT:
            glUniform1i(location, (int)v);
            break;

        case ValueType::UNSIGNED_INT:
#if RENDERER_GL
            glUniform1ui(location, (unsigned int)v);
#else
            glUniform1i(location, v);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(unsigned int v) {
    switch (type) {
        case ValueType::FLOAT:
            glUniform1f(location, (float)v);
            break;

        case ValueType::TEXTURE_UNIT:
        case ValueType::INT:
            glUniform1i(location, (int)v);
            break;

        case ValueType::UNSIGNED_INT:
#if RENDERER_GL
            glUniform1ui(location, (unsigned int)v);
#else
            glUniform1i(location, v);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(const Vector2 &vec) {
    switch (type) {
        case ValueType::VECTOR_2_FLOAT:
            glUniform2f(location, (float)vec.x, (float)vec.y);
            break;

        case ValueType::VECTOR_2_INT:
            glUniform2i(location, (int)vec.x, (int)vec.y);
            break;

        case ValueType::VECTOR_2_UNSIGNED_INT:
#if RENDERER_GL
            glUniform2ui(location, (unsigned int)vec.x, (unsigned int)vec.y);
#else
            glUniform2i(location, (int)vec.x, (int)vec.y);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(const Vector3 &vec) {
    switch (type) {
        case ValueType::VECTOR_3_FLOAT:
            glUniform3f(location, (float)vec.x, (float)vec.y, (float)vec.z);
            break;

        case ValueType::VECTOR_3_INT:
            glUniform3i(location, (int)vec.x, (int)vec.y, (int)vec.z);
            break;

        case ValueType::VECTOR_3_UNSIGNED_INT:
#if RENDERER_GL
            glUniform3ui(location, (unsigned int)vec.x, (unsigned int)vec.y, (unsigned int)vec.z);
#else
            glUniform3i(location, (int)vec.x, (int)vec.y, (int)vec.z);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(const Vector4 &vec) {
    switch (type) {
        case ValueType::VECTOR_4_FLOAT:
            glUniform4f(location, (float)vec.x, (float)vec.y, (float)vec.z, (float)vec.w);
            break;

        case ValueType::VECTOR_4_INT:
            glUniform4i(location, (int)vec.x, (int)vec.y, (int)vec.z, (int)vec.w);
            break;

        case ValueType::VECTOR_4_UNSIGNED_INT:
#if RENDERER_GL
            glUniform4ui(location, (unsigned int)vec.x, (unsigned int)vec.y, (unsigned int)vec.z, (unsigned)vec.w);
#else
            glUniform4i(location, (int)vec.x, (int)vec.y, (int)vec.z, (int)vec.w);
#endif
            break;

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

void Shader::Uniform::Set(const Matrix4 &mat) {
    switch (type) {
        case ValueType::MATRIX_4_FLOAT: {
            auto p = mat[0];
            float f[16] {
                (float)p[0], (float)p[1], (float)p[2], (float)p[3],
                (float)p[4], (float)p[5], (float)p[6], (float)p[7],
                (float)p[8], (float)p[9], (float)p[10], (float)p[11],
                (float)p[12], (float)p[13], (float)p[14], (float)p[15]
            };
            glUniformMatrix4fv(location, 1, GL_FALSE, f);
        }

        default:
            throw std::runtime_error("Uniform is not of required type");
    }
}

Shader::Shader(unsigned int program_id) : program_id(program_id) {}

Shader::Uniform *Shader::GetUniform(const std::string &name) const {
    auto u = uniforms.find(name);
    if (u != uniforms.end()) return const_cast<Uniform *>(&u->second);
    return nullptr;
}

const std::map<std::string, Shader::Uniform> &Shader::GetUniforms() const {
    return uniforms;
}

Shader::Attribute *Shader::GetAttribute(const std::string &name) const {
    auto u = attributes.find(name);
    if (u != attributes.end()) return const_cast<Attribute *>(&u->second);
    return nullptr;
}

const std::map<std::string, Shader::Attribute> &Shader::GetAttributes() const {
    return attributes;
}

void Shader::Bind() {
    if (bound_shader == this) return;
    glUseProgram(program_id);
    bound_shader = this;
}

Shader::~Shader() {
    glDeleteProgram(program_id);
}

std::shared_ptr<Shader> Shader::FromSource(const std::map<Stage, std::string> &sources) {
    return FromSpirv(glslcross::SourceToSpirv(sources));
}

std::shared_ptr<Shader> Shader::FromSpirv(const std::map<Stage, std::vector<uint32_t>> &spirv) {
    int version;
    bool es = false;

    std::string gl_version = (char *)glGetString(GL_VERSION);
    std::string glsl_version = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
    if (gl_version.find("OpenGL ES") == 0) {
        es = true;
        std::string prefix = "OpenGL ES GLSL ES ";
        glsl_version = glsl_version.substr(prefix.size());
    }
    int v_major = std::stoi(glsl_version);
    glsl_version = glsl_version.substr(glsl_version.find('.') + 1);
    int v_minor = std::stoi(glsl_version);
    version = v_major * 100;
    if (v_minor < 10) v_minor *= 10;
    version += v_minor;

    return FromSourceInternal(glslcross::SpirvToSource(spirv, version, es));
}




static GLuint CompileShader(const std::string &text, GLenum type) {
    GLuint shader_id = glCreateShader(type);

    const char *str = text.c_str();
    glShaderSource(shader_id, 1, &str, nullptr);
    glCompileShader(shader_id);

    GLint is_compiled = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);

    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);
        std::string err;
        if (max_length > 0) {
            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);
            err = &*info_log.begin();
        }
        glDeleteShader(shader_id);
        throw std::runtime_error("Can't compile shader:\n" + err);
    }

    return shader_id;
}

static GLuint CompileProgram(const std::vector<int> &shader_ids) {
    GLuint program_id = glCreateProgram();
    for (auto id : shader_ids) {
        glAttachShader(program_id, id);
    }
    glLinkProgram(program_id);
    GLint is_linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);

    if (is_linked == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);
        std::string err;
        if (max_length > 0) {
            std::vector<GLchar> info_log(max_length);
            glGetProgramInfoLog(program_id, max_length, &max_length, &info_log[0]);
            err = &*info_log.begin();
        }
        for (auto id : shader_ids) {
            glDeleteShader(id);
        }
        glDeleteProgram(program_id);
        throw std::runtime_error("Can't link shader:\n" + err);
    }

    for (auto id : shader_ids) {
        glDetachShader(program_id, id);
        glDeleteShader(id);
    }

    return program_id;
}

static GLenum StageToGLenum(Shader::Stage stage) {
    switch (stage) {
        case Shader::Stage::Vertex: return GL_VERTEX_SHADER;
        case Shader::Stage::Fragment: return GL_FRAGMENT_SHADER;
        case Shader::Stage::Geometry: return GL_GEOMETRY_SHADER;
    }
    throw std::runtime_error("Unsupported stage");
}

static Shader::ValueType GLenumToValueType(GLenum type) {
    switch (type) {
        case GL_FLOAT: return Shader::ValueType::FLOAT;
        case GL_INT: return Shader::ValueType::INT;
        case GL_UNSIGNED_INT: return Shader::ValueType::UNSIGNED_INT;
        case GL_FLOAT_MAT3: return Shader::ValueType::MATRIX_3_FLOAT;
        case GL_FLOAT_MAT4: return Shader::ValueType::MATRIX_4_FLOAT;
        case GL_FLOAT_VEC2: return Shader::ValueType::VECTOR_2_FLOAT;
        case GL_FLOAT_VEC3: return Shader::ValueType::VECTOR_3_FLOAT;
        case GL_FLOAT_VEC4: return Shader::ValueType::VECTOR_4_FLOAT;
        case GL_INT_VEC2: return Shader::ValueType::VECTOR_2_INT;
        case GL_INT_VEC3: return Shader::ValueType::VECTOR_3_INT;
        case GL_INT_VEC4: return Shader::ValueType::VECTOR_4_INT;
#if RENDERER_GL
        case GL_UNSIGNED_INT_VEC2: return Shader::ValueType::VECTOR_2_UNSIGNED_INT;
        case GL_UNSIGNED_INT_VEC3: return Shader::ValueType::VECTOR_3_UNSIGNED_INT;
        case GL_UNSIGNED_INT_VEC4: return Shader::ValueType::VECTOR_4_UNSIGNED_INT;
#endif
        case GL_SAMPLER_2D: return Shader::ValueType::TEXTURE_UNIT;
        default: return Shader::ValueType::UNSUPPORTED;
    }
}

std::shared_ptr<Shader> Shader::FromSourceInternal(const std::map<Stage, std::string> &sources) {
    std::vector<int> ids;
    for (auto &s : sources) {
        ids.push_back(CompileShader(s.second, StageToGLenum(s.first)));
    }
    auto shader = std::shared_ptr<Shader>(new Shader(CompileProgram(ids)));

    GLint max_uniform_name_length = 0;
    glGetProgramiv(shader->program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_uniform_name_length);
    GLint max_attribute_name_length = 0;
    glGetProgramiv(shader->program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_attribute_name_length);

    std::vector<GLchar> name_data(max_uniform_name_length > max_attribute_name_length
                                  ? max_uniform_name_length : max_attribute_name_length);

    GLsizei length;
    GLint size;
    GLenum type;

    GLint uniforms_count;
    glGetProgramiv(shader->program_id, GL_ACTIVE_UNIFORMS, &uniforms_count);
    for (GLuint i = 0; (int)i < uniforms_count; i++) {
        glGetActiveUniform(shader->program_id, i, name_data.size(), &length, &size, &type, &name_data[0]);
        shader->uniforms.emplace(
                &name_data[0],
                Uniform {
                        &name_data[0],
                        GLenumToValueType(type),
                        (unsigned int)glGetUniformLocation(shader->program_id, &name_data[0])
                }
        );
    }

    GLint attributes_count;
    glGetProgramiv(shader->program_id, GL_ACTIVE_ATTRIBUTES, &attributes_count);
    for (GLuint i = 0; (int)i < attributes_count; i++) {
        glGetActiveAttrib(shader->program_id, i, name_data.size(), &length, &size, &type, &name_data[0]);
        shader->attributes.emplace(
                &name_data[0],
                Attribute {
                        &name_data[0],
                        GLenumToValueType(type),
                        (unsigned int)glGetAttribLocation(shader->program_id, &name_data[0])
                }
        );
    }

    return shader;
}

} // namespace sw
