#include "woody.h"
//								  decrypt shell code len   |  key length (inc 00)
#define SHELLCODE_LEN 51 + 5 +2 + 60  +3                    +  4
#define JMP_INDEX 105 
#define KEY_INDEX 0
#define DECREL_INDEX 51
#define DECREL_DATA_INDEX 54
#define STRSIZE_INDEX 43
unsigned char shellcode[SHELLCODE_LEN] = "\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x52\x68\x2e\x2e\x2e\x0a\x48\xba\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x52\x48\x8d\x34\x24\xba\x0c\x00\x00\x00\x0f\x05\x48\x31\xd2\x48\xba\x01\x00\x00\x00\x00\x00\x00\x00\x48\x8d\x3d\xba\xbe\xba\xbe\x48\x8d\x35\x38\x00\x00\x00\x48\x31\xc9\x48\x31\xdb\x44\x8a\x0c\x1e\x00\x0c\x0f\x44\x30\x0c\x0f\x48\xff\xc3\x48\xff\xc1\x48\x39\xd1\x74\x08\x80\x3c\x1e\x00\x74\xe1\xeb\xe2\x58\x58\x5a\xE8\xEA\xCF\xFF\xFF\xb8\x3c\x00\x00\x00\xbf\x00\x00\x00\x00\x0f\x05mdr\x00";
unsigned int pad = 0;
unsigned long jmp_addr = 0;
unsigned long old_entry = 0;
unsigned long new_entry = 0;

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
			return (sect_headers[i].sh_addr + sect_headers[i].sh_size);
	}
	return (0);
}


Elf64_Shdr get_section(t_elf_file ef, char *secname)
{
	unsigned long n_sec = ef.elf64header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf64header.e_shoff;
	Elf64_Shdr sect_headers[n_sec];
	Elf64_Shdr strtab;
	Elf64_Shdr def = {0};

	if ((ef.elf64header.e_shoff+ (sizeof(Elf64_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (def);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf64_Shdr) * i), sizeof(Elf64_Shdr)); 
	strtab = sect_headers[ef.elf64header.e_shstrndx];
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if ((strtab.sh_offset + sect_headers[i].sh_name) > ef.fsize)//boundary check
			return (def);
		char *name =(char*)ef.file + strtab.sh_offset + sect_headers[i].sh_name; 
		if (!ft_strncmp(name, secname, ft_strlen(name) + 1))
			return (sect_headers[i]);
	}
	return (def);
}

int is_stripped(t_elf_file ef)
{
	unsigned long n_sec = ef.elf64header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf64header.e_shoff;
	Elf64_Shdr sect_headers[n_sec];
	Elf64_Shdr strtab;
	int ret = 1;	

	if ((ef.elf64header.e_shoff+ (sizeof(Elf64_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (1);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf64_Shdr) * i), sizeof(Elf64_Shdr)); 
	strtab = sect_headers[ef.elf64header.e_shstrndx];
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if ((strtab.sh_offset + sect_headers[i].sh_name) > ef.fsize)//boundary check
			return (1);
		char *name =(char*)ef.file + strtab.sh_offset + sect_headers[i].sh_name; 
		if (!ft_strncmp(name, ".symtab", ft_strlen(".symtab")))
			ret = 0;
	}
	return (ret);
}


int parse64elfheader(t_elf_file ef)
{
	Elf64_Ehdr new_header;

	ft_memcpy(&new_header, &ef.elf64header, sizeof(Elf64_Ehdr));
//	new_header.e_shnum = 0;
//	new_header.e_shentsize = 0;
//	new_header.e_shoff = 0;
	new_header.e_shoff = new_header.e_shoff + SHELLCODE_LEN + 8;
	old_entry = new_header.e_entry;
	if (!(new_header.e_entry = new_entryaddr(ef)))
		return (1);
	new_entry = new_header.e_entry;
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
			if (phdr.p_flags == (PF_R | PF_W))//Segment containning bss and my new section
			{
				pad = phdr.p_memsz - phdr.p_filesz;
				phdr.p_memsz += SHELLCODE_LEN;
				phdr.p_filesz = phdr.p_memsz;
			}
			phdr.p_flags = PF_X | PF_W |PF_R;
		}
		write(ef.wfd, &phdr, sizeof(Elf64_Phdr));
		i++;
	}
	return (0);
}

//mod is plain black magic 
void update_shellcode_reladdr(unsigned int op_index, unsigned int dat_index, int mod)
{
	long rel_jmp = 0;
	rel_jmp = -(new_entry + op_index - old_entry);  
	char *s = (char *)&rel_jmp;
	int j = dat_index;
	for(int i = 0; i < 4; i++)
	{
		char c = (char)s[i];
		if (i == 0 && mod)
			c -= 7;
		else if (i == 0)
			c -= 5;
		shellcode[j] = c;
		j++;
	}
}

void update_shellcode_value(unsigned int index, long val)
{
	char *s = (char *)&val;
	int j = index;
	for(int i = 0; i < 8; i++)
	{
		char c = (char)s[i];
		shellcode[j] = c;
		j++;
	}
}
int parse64elfsec(t_elf_file ef)
{
	Elf64_Off new_sect = get_section(ef, ".bss").sh_offset;
	Elf64_Shdr text_sec = get_section(ef, ".text");
	unsigned long start =  ef.elf64header.e_phoff + (sizeof(Elf64_Phdr) * ef.elf64header.e_phnum); 
	unsigned long new_start;
	char *enc_text;

	if (!(enc_text = malloc(text_sec.sh_size)))
		return (1);
	ft_memcpy(enc_text, (unsigned char *)ef.file + text_sec.sh_offset, text_sec.sh_size);
	_encrypt(enc_text, ef.key, text_sec.sh_size);//encrypt the whole .text section

	write(ef.wfd, (unsigned char *)ef.file + start, (text_sec.sh_offset - start)); //writing from PH till start of .text
	write(ef.wfd, enc_text, text_sec.sh_size); // writing .text section
	free(enc_text);
	new_start = start + (text_sec.sh_offset - start) + text_sec.sh_size;
	write(ef.wfd, (unsigned char *)ef.file + new_start, (new_sect - new_start));// writing stuff between .text and .bss
	for (unsigned int i = 0; i < pad; i++)
		write(ef.wfd, "\x00", 1); // padding 00 for what were previously "virtual memory"

	update_shellcode_reladdr(JMP_INDEX - 1, JMP_INDEX, 0);
	update_shellcode_reladdr(DECREL_INDEX, DECREL_DATA_INDEX, 1);
	update_shellcode_value(STRSIZE_INDEX, text_sec.sh_size);
	
	write(ef.wfd, shellcode, SHELLCODE_LEN); // injecting our shellcode
	write(ef.wfd, (unsigned char *)ef.file + new_sect, ef.fsize - new_sect); // remove for binary compression, it just adds the shdrs 
	return (0);	
}

int parse64elf(t_elf_file ef)
{
	if (is_stripped(ef))
		return (1);
	if (parse64elfheader(ef))
		return (1);
	parse64elfph(ef);
	parse64elfsec(ef);
	return (0);
}