#include "woody.h"

void	*open_file(char **argv, unsigned int *fsize)
{
	int			fd;
	void		*f;
	off_t		start;
	off_t		size;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("woody_woodpacker: '%s': No such file\n", argv[1]);
		return (NULL);
	}
	start = lseek(fd, (size_t)0, SEEK_CUR);
	size = lseek(fd, (size_t)0, SEEK_END);//get file size
	lseek(fd, start, SEEK_SET); //set cursor back at the beg
	f = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	*fsize = size;
	return (f == MAP_FAILED ? NULL : f);
}

int parse_magic(t_elf_file ef)
{
	if (sizeof(Elf32_Addr) > ef.fsize)
	{
		ft_printf("woody_woodpacker: %s: file format not recognized\n", ef.fname);
		return (0);
	}
	ft_memcpy(&ef.elf32header, ef.file, sizeof(Elf32_Ehdr));
	if (ef.elf32header.e_ident[EI_MAG0] != ELFMAG0  ||
		ef.elf32header.e_ident[EI_MAG1] != ELFMAG1  ||
		ef.elf32header.e_ident[EI_MAG2] != ELFMAG2  ||
		ef.elf32header.e_ident[EI_MAG3] != ELFMAG3  ||
	 	ef.elf32header.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_printf("woody_woodpacker: %s: file format not recognized\n", ef.fname);
		return (0);
	}
	if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS32)
	{
//		if (parse32elf(ef))
		//	ft_printf("woody_woodpacker: File corrupted\n");
	}
	else if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS64)
	{
		ft_memcpy(&ef.elf64header, ef.file, sizeof(Elf64_Ehdr));
		if (parse64elf(ef))
			ft_printf("woody_woodpacker: File corrupted\n");
	}
	return (0);
}

int open_wfile()
{
	int fd;

	if ((fd = open("woody", O_RDWR | O_CREAT | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG)) < 0)
	{
		printf("woody_woodpacker: could not create new binary\n");
	}
	return (fd);
}

int ft_woody(void *file, char *fname, unsigned int fsize)
{
	t_elf_file	ef;
	ef.fname = fname;
	ef.file = file;
	ef.fsize = fsize;
	ef.key = strdup("mdr");
	if ((ef.wfd = open_wfile()) < 0)
		return (1);
	if (parse_magic(ef))
		return (1);	
	free(ef.key);
	return (0);
}


int		main(int argc, char **argv)
{
	void			*file;
	unsigned int	fsize;

	char **arg_cpy;

	if (!(arg_cpy = copy_sp(argv)))
		return (1);
	if (argc < 2)
	{
		free_sp(arg_cpy);
		if (!(arg_cpy = malloc(sizeof(char *) * 3)))
			return (1);
		if (!(arg_cpy[0] = ft_strdup(argv[0])))
		{
			free(arg_cpy);
			return (1);
		}
		if (!(arg_cpy[1] = ft_strdup("a.out")))
		{
			free(arg_cpy);
			free(arg_cpy[0]);
			return (1);
		}
		arg_cpy[2] = NULL;
		argc = 2;
	}
	if (argc == 2)
	{
		if ( ft_strnstr(arg_cpy[1], "woody", ft_strlen(arg_cpy[1])) )
			printf("woody_woodpacker: You devil hacker you used the forbiden word gtfo of here\n");
		else if ((file = open_file(arg_cpy, &fsize)))
		{
			if (ft_woody(file, arg_cpy[1], fsize))
			{
				free_sp(arg_cpy);
				return (1);
			}
		}
	}
	free_sp(arg_cpy);
	return (0);
}