#include "../cub3d.h"

// Player initialization is handled in parse/validate_chars.c
// during map parsing. The function set_player_dir() sets:
// - player->pos (position in map)
// - player->dir (direction vector)
// - player->plane (camera plane for FOV)
// - player->move_speed and player->rot_speed