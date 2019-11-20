/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/11/19 17:42:14 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# include <SDL2/SDL.h>
# include <SDL_ttf.h>

# include "../libft/libft.h"

# define    W_WIDTH     800
# define    W_HEIGHT    600
# define    SNB         29

# define    NBTHREAD    8
# define    WTHREAD     W_WIDTH / NBTHREAD
# define    HTHREAD     W_HEIGHT / NBTHREAD

# define    KA          0
# define    KE          1
# define    KW          2
# define    KQ          3
# define    KS          4
# define    KD          5
# define    KM          6
# define    KSPC        7
# define    WNB         4
# define	KB			8
# define    KN         	9
# define    KP         	10
# define    KZ         	11
# define    KNB         12

typedef struct  s_sprite
{
    SDL_Surface *img;
}               t_sprite;

typedef struct  s_mouse 
{
    uint8_t     mouse;
    int         x;
    int         y;
}               t_mouse;

typedef struct  s_objdata
{
    int         column;
    uint32_t    zpixel;
    float       angle;
    float       mid;
    float       ratio;
    float       dst_fromplayer;
    float       ceiling;
    float       floor;
    float       eyex;
    float       eyey;
    float       height;
    float       width;
    float       samplex;
    float       sampley;
}               t_objdata;

typedef struct  s_object
{
    int             dead;
    int             hp;
    int             hp_max;
    int             delay;
    int             si;
    int             type;
    float           speed;
    float           x;
    float           y;
    float           vx;
    float           vy;
    t_sprite        sprite;
    t_objdata       data;
    struct s_object *next;
}               t_object;

typedef struct  s_wdata
{
    int         si;
    int         column;
    int         damage;
    int         delay;
    int         range;
    uint32_t    zpixel;
    float       height;
    float       width;
    float       ratio;
}               t_wdata;

typedef struct  s_player
{
    int         health;
    int         health_max;
    int         pos;
    int         weapon;
    float       angle;
    float       fov;
    float       ms;
    float       speed;
    float       x;
    float       y;
    t_wdata     wdata[WNB];
}               t_player;

typedef struct  s_raydata
{
    int         ceiling;
    int         floor;
    int         si;
    float       angle;
    float       bmx;
    float       bmy;
    float       cdst;
    float       dst_towall;
    float       eyex;
    float       eyey;
    float       ray_step;
    float       samplex;
    float       sampley;
    float       testangle;
    float       testx;
    float       testy;
}               t_raydata;

typedef struct  s_map
{
    int         len;
    int         height;
    int         width;
    int         *map;
    float       depth;
    float       depth_buffer[W_WIDTH];
	int			sc_x;
}               t_map;

typedef struct  s_point
{
    int         i;
    int         x;
    int         y;
}               t_point;

typedef struct  s_node
{
    int             bobstacle;
    int             bvisited;
    int             i;
    int             x;
    int             y;
    int             wall;
    float           globalgoal;
    float           localgoal;
    struct s_node   *ngbhr[4];
    struct s_node   *parent;
}               t_node;

typedef struct  s_alst
{
    t_node          *node;
    struct s_alst   *next;
}               t_alst;

typedef struct  s_pf
{
    t_node      *start;
    t_node      *end;
    t_node      *list;
    t_alst      *alst;
}               t_pf;

typedef struct  s_wolf
{
    int             kill_score;
    int             fire_delay;
    int             shoot;
    int             fps;
    int             sdl_on;
    int             i;
    int             i_max;
    int             key[KNB];
    char            *str;
    float           etime;
    float           frame_start;
	TTF_Font		*police;
	TTF_Font		*police2;
	TTF_Font		*police3;
	t_map           map;
    t_pf            pfdata;
    t_player        player;
    t_raydata       raydata;
    t_object        *monster;
    t_object        *object;
    t_sprite        sprite[SNB];
    t_mouse         mouse;
    SDL_Event       event;
    SDL_Renderer    *renderer;
    SDL_Surface     *screen;
    SDL_Texture     *bgc;
    SDL_Texture     *bgf;
    SDL_Texture     *window;
    SDL_Window	    *pWindow;
}               t_wolf;

void            display(t_wolf *data);
void            events(t_wolf *data);
void            load_datagame(t_wolf *data);
void            monsters(t_wolf *data);
void            mouse_events(t_wolf *data);
void            objects(t_wolf *data, t_object *list);
void            shoot(t_wolf *data);
void            spawner(t_wolf *data);
void            sprites(t_wolf *data);
void            weapons(t_wolf *data);
void            wolf3d(t_wolf *data);

void			get_blockside(t_wolf *data, int testx, int testy);
void            *raycasting(void *d);
void            raythread(t_wolf *data);

void            minimap(t_wolf *data);

void            clean_exit(t_wolf *data, char *str, int token);
uint32_t        get_pixel(t_wolf *data, int si, float samplex, float sampley);
SDL_Surface     *new_surface(int w, int h);
void		    put_pixel(SDL_Surface *surface, int x, int y, uint32_t color);

float           distance(float x1, float y1, float x2, float y2);
float			Q_sqrt(float number);
void            lst_free(t_object *list);
int             lst_len(t_object *list);
void            lst_pushback(t_object *list, t_object *node);

void            astar(t_wolf *data);
void            get_nodes(t_wolf *data);

void            alst_free(t_alst *list);
int             alst_len(t_alst *list);
void            alst_pushback(t_alst *list, t_node *node);
void            alst_sort(t_alst *list);
void			w_pause(t_wolf *data);
void			set_write_to_screen(t_wolf *data, SDL_Rect rect, int color, char *str, TTF_Font *pl);

#endif
