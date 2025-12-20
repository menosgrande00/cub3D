#include "../cub3d.h"
#include <sys/time.h>
#include <stdio.h>

//silinecek fps için
//void	display_fps(t_cub *cub)
//{
//    static int			frame_count = 0;
//    static int			fps = 0;
//    static struct timeval	last_time = {0, 0};
//    struct timeval		current_time;
//    double			elapsed;
//    char			fps_str[32];

//    frame_count++;
//    gettimeofday(&current_time, NULL);
//    if (last_time.tv_sec == 0)
//        last_time = current_time;
//    elapsed = (current_time.tv_sec - last_time.tv_sec)
//        + (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
//    if (elapsed >= 1.0)
//    {
//        fps = frame_count;
//        frame_count = 0;
//        last_time = current_time;
//    }
//    snprintf(fps_str, sizeof(fps_str), "FPS: %d", fps);
//    mlx_string_put(cub->mlx, cub->win, 10, 20, 0x00FF00, fps_str);
//}
static void set_texture_pixel(t_cub *cub)
{
	cub->tex.no.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.no,&cub->tex.no.w,&cub->tex.no.h);
	cub->tex.so.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.so,&cub->tex.so.w,&cub->tex.so.h);
	cub->tex.we.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.we,&cub->tex.we.w,&cub->tex.we.h);
	cub->tex.ea.img = mlx_xpm_file_to_image(cub->mlx,cub->cfg.ea,&cub->tex.ea.w,&cub->tex.ea.h);

	cub->tex.no.addr = mlx_get_data_addr(cub->tex.no.img, &cub->tex.no.bpp, &cub->tex.no.line_len, &cub->tex.no.end);
	//printf(" north ımage = %p , north bpp = %d , north line = %d ,  north end = %d \n" , cub->tex.no.img, cub->tex.no.bpp, cub->tex.no.line_len, cub->tex.no.end);
	cub->tex.so.addr = mlx_get_data_addr(cub->tex.so.img, &cub->tex.so.bpp, &cub->tex.so.line_len, &cub->tex.so.end);
	//printf(" south ımage = %p , south bpp = %d , south line = %d ,  south end = %d \n" , cub->tex.so.img, cub->tex.so.bpp, cub->tex.so.line_len, cub->tex.so.end);
	cub->tex.we.addr = mlx_get_data_addr(cub->tex.we.img, &cub->tex.we.bpp, &cub->tex.we.line_len, &cub->tex.we.end);
	//printf(" west ımage = %p , west bpp = %d , west line = %d ,  west end = %d \n" , cub->tex.we.img, cub->tex.we.bpp, cub->tex.we.line_len, cub->tex.we.end);
	cub->tex.ea.addr = mlx_get_data_addr(cub->tex.ea.img, &cub->tex.ea.bpp, &cub->tex.ea.line_len, &cub->tex.ea.end);
	//printf(" east ımage = %p , east bpp = %d , east line = %d ,  east end = %d \n" , cub->tex.ea.img, cub->tex.ea.bpp, cub->tex.ea.line_len, cub->tex.ea.end);

	/*	north ımage = 0x14e1a2f0 , north bpp = 32 , north line = 256 ,  north end = 0 
		south ımage = 0x14e1a5a0 , south bpp = 32 , south line = 256 ,  south end = 0 
		west ımage = 0x14e1a690 , wesr bpp = 32 , wesr line = 256 ,  wesr end = 0 
		east ımage = 0x14e1a780 , east bpp = 32 , east line = 256 ,  east end = 0 ; line 256 olma sebebi 64 * 4 byte  sadece bir line uzunluğu yani toplam texture boyutu 64 * 64 * 4 byte */  
}

static void set_frame_buffer(t_cub *cub)
{
	cub->frame.img = mlx_new_image(cub->mlx, cub->screen_w, cub->screen_h);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp, &cub->frame.line_len, &cub->frame.end);
	//printf(" frame ımage = %p , frame bpp = %d , frame line = %d ,  frame end = %d \n" , cub->frame.img, cub->frame.bpp, cub->frame.line_len, cub->frame.end);
	cub->frame.w = cub->screen_w;
    cub->frame.h = cub->screen_h;

	//frame ımage = 0x14e1a870 , frame bpp = 32 , frame line = 7680 ,  frame end = 0 ; frame line 7680 olma sebebi 1920 * 4 byte sadece bir line uzunluğu yani toplam texture boyutu 1080 * 1920 * 4 byte;
}

static int render_frame(t_cub *cub)
{
	// Input işle (hareket ve rotasyon)
	handle_input(cub);

	// Raycasting - duvarlar, tavan ve zemini çizer
	raycast(cub);

	// Frame'i ekrana çiz
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	//display_fps(cub);  // FPS göster
	return (0);
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
	set_texture_pixel(cub); // pixel verileri;
	set_frame_buffer(cub); // frame buffer verileri;
	setup_hooks(cub);
	// Loop hook: her frame'de render_frame çağır
	mlx_loop_hook(cub->mlx, render_frame, cub); // şuan en başta tavan ve yeri basıyor bunu raycast kısmı yapılınca yer ve tavan pixel verisine göre yapılıp arasına duvar basılacak

	// Loop başlat
	mlx_loop(cub->mlx);
}
