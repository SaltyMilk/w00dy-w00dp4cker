#include "woody.h"

Elf64_Addr new_entryaddr(t_elf_file ef)
{
	unsigned long n_sec = ef.elf64header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf64header.e_shoff;
	Elf64_Shdr sect_headers[n_sec];
	Elf64_Shdr strtab;

	if ((ef.elf64header.e_shoff+ (sizeof(Elf64_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (0);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf64_Shdr) * i), sizeof(Elf64_Shdr)); 
	strtab = sect_headers[ef.elf64header.e_shstrndx];
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if ((strtab.sh_offset + sect_headers[i].sh_name) > ef.fsize)//boundary check
			return (0);
		char *name =(char*)ef.file + strtab.sh_offset + sect_headers[i].sh_name; 
		if (!ft_strncmp(name, ".bss", ft_strlen(name) + 1))
			return (sect_headers[i].sh_addr + sect_headers[i].sh_size + sect_headers[i].sh_entsize);
	}
	return (0);
}

int parse64elfheader(t_elf_file ef)
{
	Elf64_Ehdr new_header;

	ft_memcpy(&new_header, &ef.elf64header, sizeof(Elf64_Ehdr));
	new_header.e_shnum = 0;
	new_header.e_shentsize = 0;
	new_header.e_shoff = 0;

//	if (!(new_header.e_entry = new_entryaddr(ef)))
//		return (1);
	write(ef.wfd, &new_header, sizeof(Elf64_Ehdr));
	return (0);
}

int parse64elfph(t_elf_file ef)
{
	Elf64_Phdr phdr;
	unsigned char *ptr = (unsigned char *)ef.file  + ef.elf64header.e_phoff;
	unsigned int i = 0;

	while (i < ef.elf64header.e_phnum)
	{
		ft_memcpy(&phdr, ptr, sizeof(Elf64_Phdr));
		ptr += sizeof(Elf64_Phdr);
		if (phdr.p_type == PT_LOAD)
		{
			phdr.p_flags = PF_X | PF_W |PF_R;
		}
		write(ef.wfd, &phdr, sizeof(Elf64_Phdr));
		i++;
	}
	return (0);
}

int parse64elfsec(t_elf_file ef)
{
	Elf64_Shdr shdr;
	unsigned char *ptr = (unsigned char *)ef.file  + ef.elf64header.e_shoff;
	unsigned int i = 0;

	while (i < ef.elf64header.e_shnum)
	{
		ft_memcpy(&shdr, ptr, sizeof(Elf64_Shdr));
		ptr += sizeof(Elf64_Shdr);
		if (shdr.sh_type != SHT_NOBITS)
		{
			write(ef.wfd, (unsigned char *)ef.file + shdr.sh_offset, shdr.sh_size);
		}
		i++;
	}
	return (0);	
}

void lulz(t_elf_file ef)
{
	Elf64_Shdr shdr;
	unsigned char *ptr = (unsigned char *)ef.file  + ef.elf64header.e_shoff;
	unsigned int i = 0;

	while (i < ef.elf64header.e_shnum)
	{
		ft_memcpy(&shdr, ptr, sizeof(Elf64_Shdr));
		ptr += sizeof(Elf64_Shdr);
		write(ef.wfd, &shdr, sizeof(Elf64_Shdr));
		i++;
	}
}

int parse64elf(t_elf_file ef)
{
	if (parse64elfheader(ef))
		return (1);
	parse64elfph(ef);
	//int n = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * ef.elf64header.e_phnum;
	//write(ef.wfd, (unsigned char *)ef.file + n, ef.fsize - n - ( ef.fsize -ef.elf64header.e_shoff));
	parse64elfsec(ef);
	//lulz(ef);
	return (0);
}