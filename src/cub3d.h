#ifndef CUB3D_H
# define CUB3D_H

# include "../helper_function/libft/libft.h"
# include "../helper_function/get_next_line/get_next_line.h"
# include "../helper_function/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <string.h>

# define KEY_MAX	70000	// Maximum tuş sayısı
# define RD_CHUNK	4096	// Dosya okuma buffer boyutu

typedef struct	s_v2		// 2D vektör (konum/yön için)
{
	double	x;				// X koordinatı
	double	y;				// Y koordinatı
}	t_v2;

typedef struct	s_color		// RGB renk yapısı
{
	int	r;					// Red (0-255)
	int	g;					// Green (0-255)
	int	b;					// Blue (0-255)
}	t_color;

typedef struct	s_img		// MLX image yapısı
{
	void	*img;			// MLX image pointer
	char	*addr;			// Pixel data adresi
	int		bpp;			// Bits per pixel
	int		line_len;		// Line length in bytes
	int		end;			// Endian (byte order)
	int		w;				// Image genişliği
	int		h;				// Image yüksekliği
}	t_img;

typedef struct	s_tex		// Texture yapısı (4 yön)
{
	t_img	no;				// North texture
	t_img	so;				// South texture
	t_img	we;				// West texture
	t_img	ea;				// East texture
}	t_tex;

typedef struct	s_f			// Flood fill yapısı (harita doğrulama için)
{
	int	*qx;				// Queue X koordinatları
	int	*qy;				// Queue Y koordinatları
	int dx[4];				// X yönleri (4 komşu: sağ, sol, yukarı, aşağı)
	int	dy[4];				// Y yönleri
	int	head;				// Queue başlangıcı
	int	tail;				// Queue sonu
	int	w_2;				// Genişlik * 2 (queue boyutu)
	int	h_2;				// Yükseklik * 2
	int	nx;					// Yeni X koordinatı
	int	ny;					// Yeni Y koordinatı
	int	cx;					// Mevcut X koordinatı
	int	cy;					// Mevcut Y koordinatı
}	t_f;

typedef struct	s_map		// Harita yapısı
{
	char	**grid;			// 2D harita grid'i (char array)
	int		w;				// Harita genişliği
	int		h;				// Harita yüksekliği
	t_f		f;				// Flood fill helper
}	t_map;

typedef struct	s_player	// Oyuncu yapısı
{
	t_v2	pos;			// Oyuncu pozisyonu (x, y)
	t_v2	dir;			// Bakış yönü vektörü
	t_v2	plane;			// Kamera düzlemi vektörü (FOV için)
	double	move_speed;		// Hareket hızı
	double	rot_speed;		// Dönme hızı
}	t_player;

typedef struct	s_keys		// Klavye input yapısı
{
	unsigned char	held[KEY_MAX];	// Basılı tutulan tuşlar (1=basılı, 0=değil)
}	t_keys;

typedef struct	s_cfg		// Config dosyası bilgileri
{
	char	*no;			// North texture path
	char	*so;			// South texture path
	char	*we;			// West texture path
	char	*ea;			// East texture path
	t_color	ceil;			// Tavan rengi (RGB)
	t_color	floor;			// Zemin rengi (RGB)
	char	**map_lines;	// Ham harita satırları
	int		map_w;			// Harita genişliği
	int		map_h;			// Harita yüksekliği
}	t_cfg;

typedef enum	e_side		// Ray'in hangi yönde duvara çarptığı
{
	SIDE_X = 0,				// Dikey duvar (X ekseni)
	SIDE_Y = 1				// Yatay duvar (Y ekseni)
}	t_side;

typedef struct	s_rayhit	// Ray casting çarpma bilgisi
{
	int		hit;			// Duvara çarptı mı? (1=evet, 0=hayır)
	t_side	side;			// Hangi yönde çarptı (X veya Y)
	double	perp_dist;		// Duvara dik uzaklık (fish-eye düzeltmeli)
	double	wall_x;			// Duvarda çarpma noktası (0.0-1.0)
	int		map_x;			// Haritada X koordinatı
	int		map_y;			// Haritada Y koordinatı
	int		step_x;			// X yönünde adım (-1 veya 1)
	int		step_y;			// Y yönünde adım (-1 veya 1)
	t_v2	ray_dir;		// Ray yönü vektörü
	t_v2	delta_dist;		// Delta mesafe vektörü
}	t_rayhit;

typedef struct s_draw_info
{
	int	line_h;
	int	draw_start;
	int	draw_end;
}	t_draw_info;

typedef struct	s_cub		// Ana program yapısı
{
	void		*mlx;		// MLX instance pointer
	void		*win;		// MLX window pointer
	int			screen_w;	// Ekran genişliği (pixel)
	int			screen_h;	// Ekran yüksekliği (pixel)
	t_img		frame;		// Render edilecek frame image
	t_tex		tex;		// Yüklü texture'lar
	long		last_frame_time;	// Son frame zamanı (microseconds)
	int			ceil_color_int;	// Precomputed ceiling color
	int			floor_color_int;	// Precomputed floor color
	int			pixel_stride;	// Precomputed frame.line_len / sizeof(int)
	double		screen_w_recip;	// Precomputed 2.0 / screen_w
	double		cos_rot;	// Cached cos(rot_speed)
	double		sin_rot;	// Cached sin(rot_speed)
	t_map		map;		// Harita grid
	t_player	player;		// Oyuncu bilgileri
	t_keys		keys;		// Tuş durumları
	t_cfg		cfg;		// Config dosyasından okunan bilgiler
	t_rayhit	hit;		// Current ray hit info
	t_draw_info	draw;		// Current draw info
}	t_cub;

int		ft_strcmp(char *s1, char *s2);
int		is_allowed_char(char c);
void	free_double(char **str);
int		in_range(int v);
int		set_tex_color_lines(t_cfg *cfg, int	fd);
int		validate_chars_and_player(t_map *map, t_player *player);
int		set_map_parse(t_cub *cfg, int fd);
int		is_line_blank(char *s);
void	trim_newline(char *s);
int		collect_map_lines(int fd, char ***lines, int *h);
int		check_closed_by_walls(t_map *map);
void	ft_error(char *str);

void 	create_cub(t_cub *cub);
void	setup_hooks(t_cub *cub);
void	raycast(t_cub *cub);
void	handle_input(t_cub *cub);
void	move_forward_back(t_cub *cub);
void	move_strafe(t_cub *cub);
void	rotate_camera(t_cub *cub);
void	perform_dda(t_cub *cub);
void	draw_ceiling(t_cub *cub, int *dst);
void	draw_wall(t_cub *cub, int *dst);
void	free_cub(t_cub *cub);
#endif
