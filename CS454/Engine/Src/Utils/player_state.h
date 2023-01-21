#pragma once
#ifndef PLAYER_STATE_INCLUDE
#define PLAYER_STATE_INCLUDE

#include <iostream>

enum class p_state {
    idle_left,
    idle_right,
    move_left,
    move_right,
    crouch_left,
    crouch_right,
    jump_left,
    jump_right,
    land_left,
    land_right,
    atck_left,
    atck_right,
    crouch_atck_left,
    crouch_atck_right,
    take_dmg_left,
    take_dmg_right,
    pull_exclbr_left,
    pull_exclbr_right,
    grab_exclbr_left,
    grab_exclbr_right,
    raise_exclbr_left,
    raise_exclbr_right,
    victory_pose

};

std::string p_stateToStr(p_state state);

#endif