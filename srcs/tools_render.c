#include "wolf3d.h"

int mouse_rect(t_wolf *data, SDL_Rect rect)
{
	if ((data->event.motion.x >= rect.x && data->event.motion.x <= rect.x + rect.w)
		   && (data->event.motion.y	>= rect.y && data->event.motion.y <= (rect.y + rect.h)))
				return (1);
	else
		return (0);
}

void	set_write_to_screen(t_wolf *data, SDL_Rect rect, int color, char *str, TTF_Font *pl)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0);
	surface = TTF_RenderText_Solid(pl, str, ft_hex_to_rgb(color));
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	SDL_QueryTexture(texture, 0, 0, &(rect.w), &(rect.h));
	SDL_RenderCopy(data->renderer, texture, NULL, &rect);
}

void set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int color)
{
	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 100);
	SDL_RenderFillRect(data->renderer, rect);
}
