/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:58:01 by thberrid          #+#    #+#             */
/*   Updated: 2020/10/01 22:58:07 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_arenadata	*g_memroot[3];

int		rfind(t_arenadata **arena, t_chunkdata **chunk,\
	t_chunkdata *adjacents, size_t size)
{
	
}

void	*realloc(void *ptr, size_t size)
{
	/*
		/!\ 	new size < original size

		if (!ptr)
			just malloc
		if (!size)
			just free
		find if adjecent part
			if enough make copy
		else
			malloc
			then copy
	*/
}