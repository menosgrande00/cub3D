#include "../cub3d.h"

static void set_texture(t_cub *cub)
{
	cub->tex.no.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.no,&cub->tex.no.w,&cub->tex.no.h);
	cub->tex.so.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.so,&cub->tex.so.w,&cub->tex.so.h);
	cub->tex.we.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.we,&cub->tex.we.w,&cub->tex.we.h);
	cub->tex.ea.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.ea,&cub->tex.ea.w,&cub->tex.ea.h);

	cub->tex.no.addr = mlx_get_data_addr(cub->tex.no.img, &cub->tex.no.bpp, &cub->tex.no.line_len, &cub->tex.no.end);
	cub->tex.so.addr = mlx_get_data_addr(cub->tex.so.img, &cub->tex.so.bpp, &cub->tex.so.line_len, &cub->tex.so.end);
	cub->tex.we.addr = mlx_get_data_addr(cub->tex.we.img, &cub->tex.we.bpp, &cub->tex.we.line_len, &cub->tex.we.end);
	cub->tex.ea.addr = mlx_get_data_addr(cub->tex.ea.img, &cub->tex.ea.bpp, &cub->tex.ea.line_len, &cub->tex.ea.end);
}

void create_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if(!cub->mlx)
	{
		//return veya exit free;
	}
	cub->win = mlx_new_window(cub->mlx, cub->screen_w, cub->screen_h, "cub3D");
	if(!cub->win)
	{
		//return veya exit free;
	}
	set_texture(cub);

}