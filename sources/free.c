/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:57:14 by thberrid          #+#    #+#             */
/*   Updated: 2020/10/01 22:57:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_arenadata	*g_memroot[3];

void	fupdate(t_arenadata **arena, t_chunkdata **chunk)
{
	return ;
}

int		ffind(t_arenadata **arena, t_chunkdata **chunk)
{
	int			fit_id;

	fit_id = 0;
	while (fit_id < 3)
	{
		(*arena) = g_memroot[fit_id];
		printf("%s : %p\n", fit_getname(fit_id), (*arena));
		while ((*arena))
		{
			(*chunk) = (*arena)->chunk;
			while (this_(*chunk))
			{
				printf("%p - %p : %d octets\n", (*chunk) + sizeof(t_(*chunk)data),\
					(*chunk) + (*chunk)->len + sizeof(t_(*chunk)data), (*chunk)->len);
				total += (*chunk)->len;
				(*chunk) = (*chunk)->next;
			}
			(*arena) = (*arena)->next;
		}
		fit_id += 1;
	}
	return (0);
}

void	free(void *ptr)
{
	t_arenadata		*arena;
	t_chunkdata		*chunk;

	arena = NULL;
	chunk = NULL;
	if (ffind(&arena, &chunk))
	{
		fupdate(&arena, &chunk);
		return ;
	}
	if (M_DEBUG)
		ft_putendl("unknow ptr");
}