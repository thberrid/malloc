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

# define M_DEBUG	1

# define TINY_ID	0
# define SMALL_ID	1
# define LARGE_ID	2
# define TINY_NAME	"TINY"
# define SMALL_NAME	"SMALL"
# define LARGE_NAME	"LARGE"
# define TINY_SIZE	512
# define SMALL_SIZE	2048

# define MALLOC_MAX_SIZE 	1000000000000000

typedef struct		s_chunkdata
{
	size_t				len;
	struct s_chunkdata	*prev;
	struct s_chunkdata	*next;
}					t_chunkdata;

typedef struct		s_arenadata
{
	size_t				len;
	struct s_metadata	*next;
	struct s_chunkdata	*free;
	struct s_chunkdata	*chunk;
}					t_arenadata;
/*
typedef struct		s_meach
{
	int		(*begin)(t_arena *, t_chunk *, void *);
	int		(*fit)(t_arena *, t_chunk *, void *);
	int		(*arena)(t_arena *, t_chunk *, void *);
	int		(*chunk)(t_arena *, t_chunk *, void *);
	int		(*end)(t_arena *, t_chunk *, void *);
}					t_meach;
*/
extern t_arenadata	*g_mroot[3];

void			*malloc(size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);

int		arena_create(t_arenadata **arena, t_chunkdata **chunk, int fitid);
int		mfind(t_arenadata **arena, t_chunkdata **chunk, size_t size);


/*
void	*realloc(void *ptr, size_t size);
	

*		block large
			next->
			prev->
			len

		block small
			next->
			prev->
			list free
			list locked

*			list
				next
				prev
				len
		
		block tiny
			next->
			prev->
			bitmap
		
		/!\ still need len ! nor one size allowed ?

		have a struct with fn in it ? dispatcher fn with pointer ?

		udpdate adding (newAlloc*)
			add newAlloc to firrst locked
				order by adress
			remove newAlloc from freed list
				go through until free == newAlloc
				update prev with (newalloc + len)
					coalesc ?
					ordering ?

		
		find
			go to correct segreg fit
+				while list block next
+					while free list
						has enough space ?
							return struct
								> free adress
								> block adress
			return false
		
		create
			mmap
+			insert among blocks


		update insertion
			remove from free
				> basic list remove
			add in locked
+?				while locked next
					adress ordering
+					basic list insertion

		

		init // several for required fns // (fit)
			init update : while fit != index
				struct->update = (*p)[index]
			etc
		
		struct s_minterface
		>	find()
		>	update_alloc()

		free
			while segregfit [array]
+				while list block (can skip by calculing size)
+					while list memdata
						if this == addr
							free update

		free update 
+			basic list locked remover
+			basic list insertion (first ? or by size ?)

		realloc

		create tests
			> on list lol

+		show allocs
			while segregfit [array]
+				while list block
+					while list memdata
						display
*/



#endif
