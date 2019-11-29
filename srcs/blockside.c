/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blockside.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/28 12:33:41 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		getside(t_wolf *data, int testx, int testy)
{
	if (data->raydata.testangle >= -3.14159 * 0.25
			&& data->raydata.testangle < 3.14159 * 0.25)
	{
		data->raydata.samplex = (float)testy - data->raydata.testy;
		data->raydata.si = 16;
	}
	else if (data->raydata.testangle >= 3.14159 * 0.25
			&& data->raydata.testangle < 3.14159 * 0.75)
	{
		data->raydata.samplex = data->raydata.testx - (float)testx;
		data->raydata.si = 17;
	}
	else if (data->raydata.testangle < -3.14159 * 0.25
			&& data->raydata.testangle >= -3.14159 * 0.75)
	{
		data->raydata.samplex = (float)testx - data->raydata.testx;
		data->raydata.si = 18;
	}
	else if (data->raydata.testangle >= -3.14159 * 0.75
			|| data->raydata.testangle < -3.14159 * 0.75)
	{
		data->raydata.samplex = data->raydata.testy - (float)testy;
		data->raydata.si = 19;
	}
}

void			get_blockside(t_wolf *data, int testx, int testy)
{
	data->raydata.bmx = (float)testx + 0.5;
	data->raydata.bmy = (float)testy + 0.5;
	data->raydata.testx = data->player.x
		+ data->raydata.eyex * data->raydata.dst_towall;
	data->raydata.testy = data->player.y
		+ data->raydata.eyey * data->raydata.dst_towall;
	data->raydata.testangle = atan2f((data->raydata.testy - data->raydata.bmy),
			(data->raydata.testx - data->raydata.bmx));
	getside(data, testx, testy);
}
