#pragma once
#include "../head.h"

enum class NcursesKey
{
    alt_or_esc = 27,
    number_0   = 48,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9,
    upper_a = 65,
    upper_b,
    upper_c,
    upper_d,
    upper_e,
    upper_f,
    upper_g,
    upper_h,
    upper_i,
    upper_j,
    upper_k,
    upper_l,
    upper_m,
    upper_n,
    upper_o,
    upper_p,
    upper_q,
    upper_r,
    upper_s,
    upper_t,
    upper_u,
    upper_v,
    upper_w,
    upper_x,
    upper_y,
    upper_z,
    lower_a = 97,
    lower_b,
    lower_c,
    lower_d,
    lower_e,
    lower_f,
    lower_g,
    lower_h,
    lower_i,
    lower_j,
    lower_k,
    lower_l,
    lower_m,
    lower_n,
    lower_o,
    lower_p,
    lower_q,
    lower_r,
    lower_s,
    lower_t,
    lower_u,
    lower_v,
    lower_w,
    lower_x,
    lower_y,
    lower_z,

};

struct ProcessedKeyInput
{
    enum class Modifier
    {
        none,
        alt,
        ctrl,
        shift,
        alt_shift
    };

    char     key;
    Modifier modifier;
};
