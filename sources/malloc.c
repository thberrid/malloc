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

void	mem_insert(void **addr, int fit, size_t size)
{
	
}

void	*mem_find(int fit, size_t size)
{
	if (!g_memroot[fit])
		return (NULL);
	return (0x1);
}

void	*malloc(size_t size)
{
	void	*addr;
	int		fit;

	addr = NULL;
	fit = get_fitname(size);
	if (!mem_find(fit, size))
		mem_create(&addr, fit, size); 
	else
		mem_insert(&addr, fit, size);
	mem_update(addr, fit);
	return (addr);
}