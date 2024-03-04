#include <cmath>

#include "recomp.h"
#include "recomp_input.h"
#include "recomp_ui.h"
#include "recomp_helpers.h"
#include "../patches/input.h"
#include "../patches/graphics.h"
#include "../ultramodern/ultramodern.hpp"
#include "../ultramodern/config.hpp"

extern "C" void recomp_update_inputs(uint8_t* rdram, recomp_context* ctx) {
    recomp::poll_inputs();
}

extern "C" void recomp_puts(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) cur_str = _arg<0, PTR(char)>(rdram, ctx);
    u32 length = _arg<1, u32>(rdram, ctx);

    for (u32 i = 0; i < length; i++) {
        fputc(MEM_B(i, (gpr)cur_str), stdout);
    }
}

extern "C" void recomp_exit(uint8_t* rdram, recomp_context* ctx) {
    ultramodern::quit();
}

extern "C" void recomp_get_gyro_deltas(uint8_t* rdram, recomp_context* ctx) {
    float* x_out = _arg<0, float*>(rdram, ctx);
    float* y_out = _arg<1, float*>(rdram, ctx);

    recomp::get_gyro_deltas(x_out, y_out);
}

extern "C" void recomp_powf(uint8_t* rdram, recomp_context* ctx) {
    float a = _arg<0, float>(rdram, ctx);
    float b = ctx->f14.fl; //_arg<1, float>(rdram, ctx);

    _return(ctx, std::powf(a, b));
}

extern "C" void recomp_get_target_framerate(uint8_t* rdram, recomp_context* ctx) {
    int frame_divisor = _arg<0, u32>(rdram, ctx);

    _return(ctx, ultramodern::get_target_framerate(60 / frame_divisor));
}

extern "C" void recomp_get_aspect_ratio(uint8_t* rdram, recomp_context* ctx) {
    ultramodern::GraphicsConfig graphics_config = ultramodern::get_graphics_config();
    float original = _arg<0, float>(rdram, ctx);
    int width, height;
    recomp::get_window_size(width, height);

    switch (graphics_config.ar_option) {
        case RT64::UserConfiguration::AspectRatio::Original:
        default:
            _return(ctx, original);
            return;
        case RT64::UserConfiguration::AspectRatio::Expand:
            _return(ctx, static_cast<float>(width) / height);
            return;
    }
}

extern "C" void recomp_get_targeting_mode(uint8_t* rdram, recomp_context* ctx) {
    _return(ctx, static_cast<int>(recomp::get_targeting_mode()));
}
