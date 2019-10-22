//
// Created by selya on 22.10.2019.
//

#include "texture_unit_manager.h"

#include "gl.hpp"

namespace sw {

std::vector<TextureUnitManager::TextureUnit> TextureUnitManager::units;
std::queue<TextureUnitManager::TextureUnit *> TextureUnitManager::units_queue;
std::map<int, TextureUnitManager::TextureUnit *> TextureUnitManager::handle_to_unit;
int TextureUnitManager::active_unit = 0;

TextureUnitManager::TextureUnit::TextureUnit(int index) : index(index), bound_texture_handle(-1) {}

void TextureUnitManager::SetActiveUnit(int index) {
    if (active_unit == index) return;
    glActiveTexture(GLenum(GL_TEXTURE0 + index));
    active_unit = index;
}

int TextureUnitManager::GetActiveUnit() {
    return active_unit;
}

bool TextureUnitManager::Initialize() {
    int units_count;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &units_count);

    units.reserve(units_count);
    for (int i = 0; i < units_count; ++i) {
        units.emplace_back(i);
        units_queue.emplace(&units[i]);
    }

    return true;
}

int TextureUnitManager::PickAndActiveUnit(Texture *texture) {
    static bool initialized = Initialize();

    auto it = handle_to_unit.find(texture->handle);
    if (it != handle_to_unit.end()) {
        return it->second->index;
    }

    auto unit = units_queue.front();
    SetActiveUnit(unit->index);

    if (unit->bound_texture_handle != -1) {
        handle_to_unit.erase(unit->bound_texture_handle);
    }

    handle_to_unit[texture->handle] = unit;
    unit->bound_texture_handle = texture->handle;

    units_queue.pop();
    units_queue.emplace(unit);

    return unit->index;
}

} //namespace sw
