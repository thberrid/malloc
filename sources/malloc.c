/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:57:43 by thberrid          #+#    #+#             */
/*   Updated: 2020/10/01 22:57:55 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdio.h>

t_arenadata	*g_memroot[3] = {NULL, NULL, NULL};

void	*castto_void(t_chunkdata *chunk)
{
	return ((void *)(chunk + sizeof(t_chunkdata)));
}

void	chunk_inserthere(t_chunkdata **chunk_list, t_chunkdata *chunk_new)
{
	chunk_new->next = *chunk_list;				
	*chunk_list = chunk_new;
}

void	chunk_insertordered(t_arenadata **arena, t_chunkdata *chunk_new)
{
	t_chunkdata		*chunk_list;

	chunk_list = (*arena)->chunk;
	while (chunk_list)
	{	
		if (chunk_list > chunk_new)
		{
			chunk_inserthere(&chunk_list, chunk_new);
			return ;
		}
		chunk_list = chunk_list->next;
	}
	chunk_inserthere(&chunk_list, *chunk_new);
	return ;
}

void	mupdate(t_arenadata **arena, t_chunkdata **chunk, size_t size)
{
	t_chunkdata		*free_new;

	free_new = (*chunk)->next;
	if (!free_new)
	{
		free_new = (*chunk) + size + sizeof(t_chunkdata);
		free_new->len = (*chunk)->len - (size + sizeof(t_chunkdata));
		free_new->next = NULL;
	}
	(*arena)->free = free_new;
	(*chunk)->len = size;
	chunk_insertordered(arena, *chunk);
}

int		chunk_hasspace(t_chunkdata **chunk, size_t size)
{
	while (*chunk)
	{
		if ((*chunk)->len >= size + sizeof(t_chunkdata))
			return (1);
		*chunk = (*chunk)->next;
	}
	return (0);
}

int		mfind(t_arenadata **arena, t_chunkdata **chunk, size_t size)
{
	if (size > SMALL_MAX || !(*arena))
		return (0);
	while (*arena)
	{
		*chunk = (*arena)->free;
		if (chunk_hasspace(chunk, size))
			return (1);
		*arena = (*arena)->next;
	}
	return (0);
}

char	*fit_getname(int ft_id)
{
	if (ft_id == 0)
		return (TINY_NAME);
	if (ft_id == 1)
		return (SMALL_NAME);
	return (LARGE_NAME);
}

/*
TINY : 0xA0000
0xA0020 - 0xA004A : 42 octets
...
Total : 52698 octets
*/
/*
t_meach_fns		*meach_setfn_show()
{
	static t_meach_fns fns[5] = {
		begin = 
	}
	return (fns);
}

void			miter_init(t_meach *meach, t_meach_fns *fns)
{
	meach->begin = fns[0];
	meach->fit = fns[1];
	meach->arena = fns[2];
	meach->chunk = fns[3];
	meach->end = fns[4];
}

int				miter(t_arenadata **arena, t_chunkdata **chunk, t_meach *meach, void *ptr)
{
	int			fit_id;

	fit_id = 0;
	meach->begin();
	while (fit_id < 3)
	{
		(*arena) = g_memroot[fit_id];
		meach->fit(*arena, *chunk, ptr);
		while ((*arena))
		{
			(*chunk) = (*arena)->chunk;
			meach->arena(*arena, *chunk, ptr);
			while (*chunk)
			{
				if (meach->chunk(*arena, *chunk, ptr)
					return (1);
				(*chunk) = (*chunk)->next;
			}
			(*arena) = (*arena)->next;
		}
		fit_id += 1;
	}
	meach->end();
	return (0);
}
*/
void			show_alloc_mem(void)
{
	char		*fitname;
	int			fit_id;
	size_t		total;
	t_arenadata	*this_arena;
	t_chunkdata	*this_chunk;

	fit_id = 0;
	total = 0;
	while (fit_id < 3)
	{
		this_arena = g_memroot[fit_id];
		printf("%s : %p\n", fit_getname(fit_id), this_arena);
		while (this_arena)
		{
			this_chunk = this_arena->chunk;
			while (this_chunk)
			{
				printf("%p - %p : %d octets\n", this_chunk + sizeof(t_chunkdata), this_chunk + this_chunk->len + sizeof(t_chunkdata), this_chunk->len);
				total += this_chunk->len;
				this_chunk = this_chunk->next;
			}
			this_arena = this_arena->next;
		}
		fit_id += 1;
	}
	printf("Total : %d octets\n");
}

int		arena_create(t_arenadata **arena, t_chunkdata **chunk, int fitid)
{
	size_t	arenasize;
	size_t	datalen;

	arenasize = arena_getsize(fitid);
	datalen = sizeof(t_arenadata) + sizeof(t_chunkdata);
	*arena = (t_arenadata *)mmap(NULL, arenasize,
		PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!(*arena))
		return (0);
	ft_bzero(*arena, datalen);
	*chunk = (t_chunkdata)((*arena) + sizeof(t_chunkdata));
	(*chunk)->len = arenasize - datalen;
	(*arena)->free = *chunk;
	return (1);
}

void	*malloc(size_t size)
{
	t_arenadata		*arena;
	t_chunkdata		*chunk;
	int				fitid;

	if (size > MALLOC_MAX_SIZE)
		return (NULL);
	fitid = fit_getid(size);
	chunk = NULL;
	arena = g_mroot[fitid];
	if (!mfind(&arena, &chunk, size))
		if (!arena_create(&arena, &chunk, fitid))
			return (NULL);	
	mupdate(&arena, &chunk, size);
	return (castto_void(chunk));
}