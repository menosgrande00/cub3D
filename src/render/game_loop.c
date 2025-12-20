/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:40:06 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/20 17:57:32 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Ana input handler - her frame'de çağrılır
void	handle_input(t_cub *cub)
{
	move_forward_back(cub);
	move_strafe(cub);
	rotate_camera(cub);
}
