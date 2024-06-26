/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_vis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:48:51 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 20:51:24 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * the minimap will display only a fixed square size 128*128 pixels.
 * It will show only certain part of the map, where the player is seen
 * in the center of the square.
 */

void	render_minimap(t_cub3d *cub3d, t_vec start, t_vec p)
{
	if (start.x < 0 || start.y < 0 || start.x >= cub3d->minimap->w_pixels
		|| start.y >= cub3d->minimap->h_pixels)
		mlx_put_pixel(cub3d->buf, p.x, p.y, BLACK);
	else
	{
		if (cub3d->minimap->map[(int)start.y / MINIMAP_SCALE][(int)start.x
			/ MINIMAP_SCALE] > 0)
			mlx_put_pixel(cub3d->buf, p.x, p.y, GREEN);
		else
			mlx_put_pixel(cub3d->buf, p.x, p.y, WHITE);
	}
}

void	draw_minimap_vis(t_cub3d *cub3d)
{
	t_vec	start;
	t_vec	end;
	t_vec	pixpos;
	double	mt;

	mt = (MINIMAP_SCALE / TILE_SIZE);
	start = vec_sub(vec_scal_m(cub3d->p->pos, mt), (t_vec){.x = 64, .y = 64});
	end = vec_add(vec_scal_m(cub3d->p->pos, mt), (t_vec){.x = 64, .y = 64});
	pixpos = (t_vec){.x = 0, .y = 0};
	while (start.y < end.y)
	{
		while (start.x < end.x)
		{
			render_minimap(cub3d, start, pixpos);
			pixpos.x++;
			start.x++;
		}
		start.x = cub3d->p->pos.x * (MINIMAP_SCALE / TILE_SIZE) - 64;
		pixpos.x = 0;
		start.y++;
		pixpos.y++;
	}
}

void	draw_player_vis(t_cub3d *cub3d)
{
	t_vec_int	delta;
	t_vec_int	p;
	double		half_ps;

	half_ps = PLAYER_SIZE / 2;
	delta = (t_vec_int){.x = -half_ps, .y = -half_ps};
	while (delta.x <= half_ps)
	{
		p.x = delta.x + 64;
		while (delta.y <= half_ps)
		{
			if (delta.x * delta.x + delta.y * delta.y <= half_ps * half_ps + 1)
			{
				p.y = delta.y + 64;
				mlx_put_pixel(cub3d->buf, p.x, p.y, PLAYER_COLOR);
			}
			delta.y++;
		}
		delta.y = -half_ps;
		delta.x++;
	}
}

void	draw_player_direction_vis(t_cub3d *cub3d)
{
	t_vec	p1;
	t_vec	p2;

	p1 = (t_vec){.x = 64, .y = 64};
	p2 = vec_add(p1, vec_scal_m(cub3d->p->dir, 16));
	draw_line_vis(cub3d->buf, p1, p2, PLAYER_COLOR);
}

void	draw_map_vis(void *ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)ptr;
	draw_minimap_vis(cub3d);
	draw_player_vis(cub3d);
	draw_player_direction_vis(cub3d);
}
