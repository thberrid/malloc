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

void	*g_memroot[3] = {NULL, NULL, NULL};

void	mem_create(void **addr, int fit, size_t size)
{
	addr = mmap(NULL, get_pagesize(fit),
		PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!addr)
		return ;
}

void	*malloc(size_t size)
{
	if (size > MALLOC_MAX_SIZE)
		return (NULL);
	/* 	minit_alloc(&struct)
			int		fitname;
			fitname = get_fitname(size);
			init this lol
		if (struct.find())
			struct.create()
		? struct.insert()
		struct.update()
		return struct.new_alloc	
	*/
	return (new_alloc);
}