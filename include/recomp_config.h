#ifndef __RECOMP_CONFIG_H__
#define __RECOMP_CONFIG_H__

#include <filesystem>
#include <string_view>
#include "../ultramodern/config.hpp"

namespace recomp {
    constexpr std::u8string_view program_id = u8"Zelda64Recompiled";

    void load_config();
    void save_config();
    
    void reset_input_bindings();
    void reset_graphics_options();

    std::filesystem::path get_app_folder_path();
};

#endif 