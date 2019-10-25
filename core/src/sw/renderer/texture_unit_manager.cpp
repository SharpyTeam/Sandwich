//
// Created by selya on 22.10.2019.
//

#include "texture_unit_manager.hpp"

#include "gl.hpp"

namespace sw {

std::vector<TextureUnitManager::TextureUnit> TextureUnitManager::units;
std::list<TextureUnitManager::TextureUnit *> TextureUnitManager::units_queue;
std::unordered_map<unsigned int, TextureUnitManager::TextureUnit *> TextureUnitManager::handle_to_unit;
TextureUnitManager::TextureUnit *TextureUnitManager::active_unit = nullptr;

TextureUnitManager::TextureUnit::TextureUnit(int index)
    : index(index), texture_handle(0), in_use(false) {}

bool TextureUnitManager::TextureUnit::InUse() const {
    return in_use;
}

void TextureUnitManager::TextureUnit::Free() {
    if (!in_use) return;
    in_use = false;
    TextureUnitManager::units_queue.erase(iter_in_queue);
    iter_in_queue = TextureUnitManager::units_queue.emplace(TextureUnitManager::units_queue.begin(), this);
    TextureUnitManager::handle_to_unit.erase(texture_handle);
}

bool TextureUnitManager::TextureUnit::Claim(unsigned int texture_handle_, bool force_free) {
    if (in_use) {
        if (!force_free) {
            return false;
        } else if (texture_handle == texture_handle_) {
            return true;
        }
        TextureUnitManager::handle_to_unit.erase(texture_handle);
    }
    texture_handle = texture_handle_;
    in_use = true;
    TextureUnitManager::units_queue.erase(iter_in_queue);
    iter_in_queue = TextureUnitManager::units_queue.emplace(TextureUnitManager::units_queue.end(), this);
    TextureUnitManager::handle_to_unit[texture_handle] = this;
    return true;
}

TextureUnitManager::TextureUnit *TextureUnitManager::GetUnit(int index) {
    if (index < 0 || index >= units.size()) return nullptr;
    return &units[index];
}

TextureUnitManager::TextureUnit *TextureUnitManager::SetActiveUnit(int index) {
    if (index < 0 || index >= units.size()) return nullptr;
    if (!active_unit || active_unit->index != index) {
        glActiveTexture(GLenum(GL_TEXTURE0 + index));
        active_unit = &units[index];
    }
    return active_unit;
}

TextureUnitManager::TextureUnit *TextureUnitManager::GetActiveUnit() {
    return active_unit;
}

bool TextureUnitManager::Initialize() {
    int units_count;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &units_count);

    units.reserve(units_count);
    for (int i = 0; i < units_count; ++i) {
        units.emplace_back(i);
        units[i].iter_in_queue = units_queue.emplace(units_queue.end(), &units[i]);
    }

    return true;
}

TextureUnitManager::TextureUnit *TextureUnitManager::Bind(Texture *texture) {
    static bool initialized = Initialize();

    auto unit = units_queue.front();

    auto it = handle_to_unit.find(texture->handle);
    if (it != handle_to_unit.end()) {
        unit = it->second;
    }

    unit->Claim(texture->handle, true);
    SetActiveUnit(unit->index);
    texture->BindToGL();

    return unit;
}

void TextureUnitManager::Unbind(Texture *texture) {
    auto it = handle_to_unit.find(texture->handle);
    if (it != handle_to_unit.end()) {
        it->second->Free();
    }
}

} //namespace sw
