#ifndef MACH_WOODY_H
#define MACH_WOODY_H

# include "libft/libft.h"
# include <mach-o/loader.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <ar.h>
# include <stdio.h>

#define DEFAULT_KEY_LEN 16
typedef struct mach_header t_mach_header;
typedef struct mach_header_64 t_mach_header_64;
typedef struct load_command t_load_command; 
typedef struct segment_command_64 t_segment_command_64;
typedef struct section_64 t_section;
typedef struct entry_point_command t_entry_point_command;

typedef struct s_mf
{
	void			*file;
	char			*fname;
	t_mach_header		mach32header;
	t_mach_header_64		mach64header;
	int				wfd;
	unsigned int	fsize;
	char			*key;
}				t_mf;

//macho64
int parse64macho(t_mf mf);
//Utils
unsigned int sp_len(char **sp);
void free_sp(char **sp);
char **copy_sp(char **sp);
unsigned int smallest_len(char *s1, char *s2);
char	*ft_strnjoin(char const *s1, size_t n, char const *s2);

extern void encryptSelmelc(char *s, char *key, unsigned long);

#endif