//#include "../cub3d.h"

//void	print_v2(t_v2 *v, char *name)
//{
//    printf("=== %s (t_v2) ===\n", name);
//    printf("  x: %.2f\n", v->x);
//    printf("  y: %.2f\n", v->y);
//    printf("\n");
//}

//void	print_color(t_color *color, char *name)
//{
//    printf("=== %s (t_color) ===\n", name);
//    printf("  r: %d\n", color->r);
//    printf("  g: %d\n", color->g);
//    printf("  b: %d\n", color->b);
//    printf("\n");
//}

//void	print_img(t_img *img, char *name)
//{
//    printf("=== %s (t_img) ===\n", name);
//    printf("  img: %p\n", img->img);
//    printf("  addr: %p\n", img->addr);
//    printf("  bpp: %d\n", img->bpp);
//    printf("  line_len: %d\n", img->line_len);
//    printf("  end: %d\n", img->end);
//    printf("  w: %d\n", img->w);
//    printf("  h: %d\n", img->h);
//    printf("\n");
//}

//void	print_tex(t_tex *tex)
//{
//    printf("=== TEXTURES (t_tex) ===\n");
//    print_img(&tex->no, "North");
//    print_img(&tex->so, "South");
//    print_img(&tex->we, "West");
//    print_img(&tex->ea, "East");
//}

//void	print_map(t_map *map)
//{
//    int	i;

//    printf("=== MAP (t_map) ===\n");
//    printf("  Width: %d\n", map->w);
//    printf("  Height: %d\n", map->h);
//    printf("  Grid:\n");
//    i = 0;
//    while (i < map->h)
//    {
//        printf("    [%d]: %s\n", i, map->grid[i]);
//        i++;
//    }
//    printf("\n");
//}

//void	print_player(t_player *player)
//{
//    printf("=== PLAYER (t_player) ===\n");
//    printf("  Position:\n");
//    printf("    x: %.2f\n", player->pos.x);
//    printf("    y: %.2f\n", player->pos.y);
//    printf("  Direction:\n");
//    printf("    x: %.2f\n", player->dir.x);
//    printf("    y: %.2f\n", player->dir.y);
//    printf("  Plane:\n");
//    printf("    x: %.2f\n", player->plane.x);
//    printf("    y: %.2f\n", player->plane.y);
//    printf("  Move speed: %.2f\n", player->move_speed);
//    printf("  Rotation speed: %.2f\n", player->rot_speed);
//    printf("\n");
//}

//void	print_cfg(t_cfg *cfg)
//{
//    printf("=== CONFIG (t_cfg) ===\n");
//    printf("  Textures:\n");
//    printf("    NO: %s\n", cfg->no ? cfg->no : "NULL");
//    printf("    SO: %s\n", cfg->so ? cfg->so : "NULL");
//    printf("    WE: %s\n", cfg->we ? cfg->we : "NULL");
//    printf("    EA: %s\n", cfg->ea ? cfg->ea : "NULL");
//    print_color(&cfg->ceil, "Ceiling");
//    print_color(&cfg->floor, "Floor");
//    printf("\n");
//}

//void	print_rayhit(t_rayhit *hit)
//{
//    printf("=== RAYHIT (t_rayhit) ===\n");
//    printf("  hit: %d\n", hit->hit);
//    printf("  side: %s\n", hit->side == SIDE_X ? "SIDE_X" : "SIDE_Y");
//    printf("  perp_dist: %.2f\n", hit->perp_dist);
//    printf("  wall_x: %.2f\n", hit->wall_x);
//    printf("  map_x: %d\n", hit->map_x);
//    printf("  map_y: %d\n", hit->map_y);
//    printf("\n");
//}

//void	print_cub(t_cub *cub)
//{
//    printf("\n");
//    printf("╔════════════════════════════════════════╗\n");
//    printf("║      CUB3D STRUCTURE DEBUG INFO        ║\n");
//    printf("╚════════════════════════════════════════╝\n\n");

//    printf("=== MAIN (t_cub) ===\n");
//    printf("  mlx: %p\n", cub->mlx);
//    printf("  win: %p\n", cub->win);
//    printf("  screen_w: %d\n", cub->screen_w);
//    printf("  screen_h: %d\n\n", cub->screen_h);

//    print_cfg(&cub->cfg);
//    print_map(&cub->map);
//    print_player(&cub->player);
//    print_img(&cub->frame, "Frame");
//    print_tex(&cub->tex);

//    printf("════════════════════════════════════════\n\n");
//}