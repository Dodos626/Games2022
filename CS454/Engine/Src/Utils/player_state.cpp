#include "player_state.h"

std::string p_stateToStr(p_state state) {
    switch (state) {
    case p_state::idle_left: return "idle_left";
    case p_state::idle_right: return "idle_right";
    case p_state::move_left: return "move_left";
    case p_state::move_right: return "move_right";
    case p_state::crouch_left: return "crouch_left";
    case p_state::crouch_right: return "crouch_right";
    case p_state::jump_left: return "jump_left";
    case p_state::jump_right: return "jump_right";
    case p_state::land_left: return "land_left";
    case p_state::land_right: return "land_right";
    case p_state::atck_left: return "atck_left";
    case p_state::atck_right: return "atck_right";
    case p_state::crouch_atck_left: return "crouch_atck_left";
    case p_state::crouch_atck_right: return "crouch_atck_right";
    case p_state::take_dmg_left: return "take_dmg_left";
    case p_state::take_dmg_right: return "take_dmg_right";
    case p_state::pull_exclbr_left: return "pull_exclbr_left";
    case p_state::pull_exclbr_right: return "pull_exclbr_right";
    case p_state::grab_exclbr_left: return "grab_exclbr_left";
    case p_state::grab_exclbr_right: return "grab_exclbr_right";
    case p_state::raise_exclbr_left: return "raise_exclbr_left";
    case p_state::raise_exclbr_right: return "raise_exclbr_right";
    case p_state::victory_pose: return "victory_pose";
    default: return "Invalid p_state";
    }
}