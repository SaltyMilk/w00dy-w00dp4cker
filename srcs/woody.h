#ifndef WOODY_H
#define WOODY_H

# include "libft/libft.h"
# include <elf.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <ar.h>
# include <stdio.h>

typedef struct s_elf_file
{
	void			*file;
	char			*fname;
	Elf32_Ehdr		elf32header;
	Elf64_Ehdr		elf64header;
	int				endian;
	int				wfd;
	unsigned int	fsize;
	char			*key;
}				t_elf_file;

//elf64
int parse64elf(t_elf_file ef);
//Utils
unsigned int sp_len(char **sp);
void free_sp(char **sp);
char **copy_sp(char **sp);
unsigned int smallest_len(char *s1, char *s2);
int str_is_nullterm(t_elf_file ef, unsigned int offset);

extern void _encrypt(char *s, char *key, unsigned long);

#endif