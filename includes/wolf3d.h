/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:10:56 by maboye           ###   ########.fr       */
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

# include "../libft/libft.h"

# define    W_WIDTH     800
# define    W_HEIGHT    600
# define    SNB         18

# define    NBTHREAD    8
# define    WTHREAD     W_WIDTH / NBTHREAD
# define    HTHREAD     W_HEIGHT / NBTHREAD

# define    KA          0
# define    KE          1
# define    KZ          2
# define    KQ          3
# define    KS          4
# define    KD          5
# define    KM          6
# define    KSPC        7
# define    KNB         8

typedef struct  s_sprite
{
    SDL_Surface *img;
}               t_sprite;

typedef struct  s_object
{
    int             dead;
    int             ms;
    int             si;
    int             type;
    float           x;
    float           y;
    float           vx;
    float           vy;
    t_sprite        sprite;
    struct s_object *next;
}               t_object;

typedef struct  s_objdata
{
    int         column;
    int         si;
    uint32_t    zpixel;
    float       angle;
    float       ceiling;
    float       dst_fromplayer;
    float       eyex;
    float       eyey;
    float       floor;
    float       height;
    float       mid;
    float       ratio;
    float       vecx;
    float       vecy;
    float       samplex;
    float       sampley;
    float       width;
}               t_objdata;

typedef struct  s_player
{
    int         pos;
    float       angle;
    float       fov;
    float       ms;
    float       speed;
    float       x;
    float       y;
}               t_player;

typedef struct  s_raydata
{
    int         ceiling;
    int         floor;
    int         si;
    float       angle;
    float       bmx;
    float       bmy;
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
    float           globalgoal;
    float           localgoal;
    struct s_node   *ngbhr[4];
    struct s_node   *parent;
}               t_node;

typedef struct  s_lst
{
    t_node          *node;
    struct s_lst    *next;
}               t_lst;

typedef struct  s_pf
{
    t_node      *start;
    t_node      *end;
    t_node      *list;
    t_lst       *alst;
}               t_pf;

typedef struct  s_wolf
{
    int             fps;
    int             sdl_on;
    int             i;
    int             i_max;
    int             key[KNB];
    char            *str;
    float           etime;
    float           frame_start;
    t_map           map;
    t_pf            pfdata;
    t_player        player;
    t_raydata       raydata;
    t_objdata       objdata;
    t_object        *monster;
    t_object        *object;
    t_sprite        sprite[SNB];
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
void            sprites(t_wolf *data);
void            wolf3d(t_wolf *data);

void			get_blockside(t_wolf *data, int testx, int testy);
void            *raycasting(void *d);
void            raythread(t_wolf *data);

void            minimap(t_wolf *data);

void            clean_exit(t_wolf *data, char *str, int token);
uint32_t        get_pixel(t_wolf *data, int si, float samplex, float sampley);
void		    put_pixel(SDL_Surface *surface, int x, int y, uint32_t color);
SDL_Surface     *new_surface(int w, int h);

void            lst_free(t_object *list);
int             lst_len(t_object *list);
void            lst_pushback(t_object *list, t_object *node);

void            astar(t_wolf *data);
void            get_nodes(t_wolf *data);

void            astar_exit(t_wolf *data, char *str, int token);

void            alst_free(t_lst *list);
int             alst_len(t_lst *list);
void            alst_pushback(t_lst *list, t_node *node);
void            alst_sort(t_lst *list);

#endif
