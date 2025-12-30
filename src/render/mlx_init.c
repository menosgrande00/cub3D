#include "../cub3d.h"
#include <sys/time.h>
#include <stdio.h>

//silinecek fps için
void	display_fps(t_cub *cub)
{
    static int			frame_count = 0;
    static int			fps = 0;
    static struct timeval	last_time = {0, 0};
    struct timeval		current_time;
    double			elapsed;
    char			fps_str[32];

    frame_count++;
    gettimeofday(&current_time, NULL);
    if (last_time.tv_sec == 0)
        last_time = current_time;
    elapsed = (current_time.tv_sec - last_time.tv_sec)
        + (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
    if (elapsed >= 1.0)
    {
        fps = frame_count;
        frame_count = 0;
        last_time = current_time;
    }
    snprintf(fps_str, sizeof(fps_str), "FPS: %d", fps);
    mlx_string_put(cub->mlx, cub->win, 10, 20, 0x00FF00, fps_str);
}
static void set_texture_pixel(t_cub *cub)
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

static void set_frame_buffer(t_cub *cub)
{
	cub->frame.img = mlx_new_image(cub->mlx, cub->screen_w, cub->screen_h);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp, &cub->frame.line_len, &cub->frame.end);
	cub->frame.w = cub->screen_w;
    cub->frame.h = cub->screen_h;
}

static int render_frame(t_cub *cub)
{
	struct timeval	current_time;
	long			current_us;
	long			elapsed_us;

	gettimeofday(&current_time, NULL);
	current_us = current_time.tv_sec * 1000000 + current_time.tv_usec;
	elapsed_us = current_us - cub->last_frame_time;
	
	// 10ms = 10000 microseconds kontrolü
	//if (elapsed_us < 10000)
	//	return (0);
	
	cub->last_frame_time = current_us;
	handle_input(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	display_fps(cub);
	return (0);
}


void create_cub(t_cub *cub)
{
	struct timeval	start_time;

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
	// Başlangıç zamanını ayarla
	gettimeofday(&start_time, NULL);
	cub->last_frame_time = start_time.tv_sec * 1000000 + start_time.tv_usec;
	set_texture_pixel(cub); // pixel verileri;
	set_frame_buffer(cub); // frame buffer verileri;
	// Tüm precomputed değerler (bir arada - cache friendly)
	cub->ceil_color_int = (cub->cfg.ceil.r << 16) | (cub->cfg.ceil.g << 8)
		| cub->cfg.ceil.b;
	cub->floor_color_int = (cub->cfg.floor.r << 16) | (cub->cfg.floor.g << 8)
		| cub->cfg.floor.b;
	cub->pixel_stride = cub->frame.line_len / sizeof(int);
	cub->screen_w_recip = 2.0 / (double)cub->screen_w;
	cub->cos_rot = cos(cub->player.rot_speed);
	cub->sin_rot = sin(cub->player.rot_speed);
	setup_hooks(cub);
	// Loop hook: her frame'de render_frame çağır
	mlx_loop_hook(cub->mlx, render_frame, cub); // şuan en başta tavan ve yeri basıyor bunu raycast kısmı yapılınca yer ve tavan pixel verisine göre yapılıp arasına duvar basılacak
	// Loop başlat
	mlx_loop(cub->mlx);
}
