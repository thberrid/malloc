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

extern t_arenadata	*g_memroot[3];

int		ffind(t_arenadata **arena, t_chunkdata **chunk, void *ptr)
{
	int			fit_id;

	fit_id = 0;
	while (fit_id < 3)
	{
		(*arena) = g_memroot[fit_id];
		while ((*arena))
		{
			(*chunk) = (*arena)->chunk;
			while (*chunk)
			{
				if (*chunk + sizeof(t_chunkdata) == ptr)
					return (1);
				(*chunk) = (*chunk)->next;
			}
			(*arena) = (*arena)->next;
		}
		fit_id += 1;
	}
	return (0);
}

void	chunk_setfree(t_arenadata **arena, t_chunkdata **chunk)
{
	(*chunk)->prev = (*chunk)->next;
	(*chunk)->next = (*arena)->free;
	(*arena)->free = (*chunk);
}

int		arena_isempty(t_arenadata *arena)
{
	if (!arena->chunk)
		return (1);
	return (0);
}

size_t	arena_getsize(size_t len)
{
	if (len < TINY_SIZE)
		return TINY_SIZE;
	if (len < SMALL_SIZE)
		return SMALL_SIZE;
	return (len + sizeof(t_arenadata) + sizeof(t_chunkdata)); 
}

void	arena_unmap(t_arena **arena, size_t arena_size)
{
	if (!(*arena)->prev)
		(*arena)->prev = (*arena)->next;
	else
		((*arena)->prev)->next = (*arena)->next;
	munmap(*arena, arena_getsize((*chunk)->len));
}

void	fupdate(t_arenadata **arena, t_chunkdata **chunk)
{
	chunk_setfree(arena, chunk);
	if (arena_isempty(*arena))
		arena_unmap(arena, arena_getsize((*chunk)->len));
}

void	free(void *ptr)
{
	t_arenadata		*arena;
	t_chunkdata		*chunk;

	arena = NULL;
	chunk = NULL;
	if (ffind(&arena, &chunk, ptr))
	{
		fupdate(&arena, &chunk);
		/* insert coalescing somewhere here */
		return ;
	}
	if (M_DEBUG)
		ft_putendl("unknown ptr");
}