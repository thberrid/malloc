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

t_metadata	*g_memroot[3] = {NULL, NULL, NULL};

void	*castto_void(t_chunkdata *chunk)
{
	return ((void *)(chunk + sizeof(t_chunkdata)));
}

int		chunk_hasspace(t_chunkdata **chunk, size_t size)
{
	while (*chunk)
	{
		if (*chunk->len >= size)
			return (1);
		*chunk = *chunk->next;
	}
	return (0);
}

int		mfind(t_metadata **block, t_chunkdata **chunk, size_t size)
{
	if (size > SMALL_MAX || !(*block))
		return (0);
	while (*block)
	{
		*chunk = block->free;
		if (chunk_hasspace(chunk, size))
			return (1);
		*block = *block->next;
	}
	return (0);
}

void	mcreate(void **addr, int fit, size_t size)
{
	void	*addr;

	addr = mmap(NULL, get_pagesize(fit),
		PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!addr)
		return (0);
	
	return (1);
}

void	*malloc(size_t size)
{
	t_metadata		*block;
	t_chunkdata		*chunk;

	if (size > MALLOC_MAX_SIZE)
		return (NULL);
	chunk = NULL;
	block = g_mroot[get_fitname(size)];
	if (!mfind(&block, &chunk, size))
		if (!mcreate(&block, &chunk, size))
			return (NULL);	
	mupdate(&block, &chunk, size);
	return (castto_void(chunk));
}