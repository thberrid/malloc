/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:28:43 by thberrid          #+#    #+#             */
/*   Updated: 2020/10/01 22:28:46 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <libft.h>
# include <sys/mman.h>
# include <sys/resource.h>

# define BITMAP_LEN	1024

# define TINY		0
# define SMALL		1
# define LARGE		2

#

typedef struct	s_metadata {
	size_t				len;
	struct s_metadata	*prev;
	struct s_metadata	*next;
}				t_metadata;

typedef struct	s_tinydata {
	size_t				len;
	unsigned char		bitmap[BITMAP_LEN];
	struct s_tinydata 	*prev;
	struct s_tinydata 	*next;
}				t_tinydata;

extern void		*g_memroot[3];

void			*malloc(size_t size);

int				get_fitname(size_t size);

void			mem_insert(void **addr, int fit, size_t size);
void			mem_create(void **addr, int fit, size_t size);
void			*mem_find(int fit, size_t size);

/*
void	free(void *ptr);

void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();
*/



#endif
