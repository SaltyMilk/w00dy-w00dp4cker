#include "woody.h"
//					 print decrypt call/jmp
#define SHELLCODE_LEN 49 + 59      + 5 + 13
#define JMP_INDEX 100 
#define DECREL_DATA_INDEX 62
#define STRSIZE_INDEX 39
#define RELCALL_INDEX 43 
unsigned char shellcode32[SHELLCODE_LEN] = "\xb8\x04\x00\x00\x00\xbb\x01\x00\x00\x00\x52\x68\x2e\x2e\x2e\x0a\x68\x4f\x4f\x44\x59\x68\x2e\x2e\x2e\x57\x8d\x0c\x24\xba\x0c\x00\x00\x00\xcd\x80\x31\xd2\xba\x41\x42\x43\x44\xe8\x00\x00\x00\x00\x58\x05\x46\x00\x00\x00\x89\xc6\x2d\x46\x00\x00\x00\x05\x41\x42\x43\x44\x89\xc7\x31\xc9\x31\xdb\x8a\x04\x1e\x00\x0c\x0f\x30\x04\x0f\x43\x41\x39\xd1\x74\x08\x80\x3c\x1e\x00\x74\xe9\xeb\xe9\x58\x58\x58\x5a\xe8\xBA\xBE\xBA\xBE\x31\xdb\xb8\x01\x00\x00\x00\xcd\x80\x41\x42\x43\x44\x45\x46\x47\x48\x49\x50\x51\x52\x53";
unsigned int pad32 = 0;
unsigned long jmp_addr32 = 0;
unsigned long old_entry32 = 0;
unsigned long new_entry32 = 0;

Elf32_Addr new_entryaddr32(t_elf_file ef)
{
	unsigned long n_sec = ef.elf32header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf32header.e_shoff;
	Elf32_Shdr sect_headers[n_sec];
	Elf32_Shdr strtab;

	if ((ef.elf32header.e_shoff+ (sizeof(Elf32_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (0);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf32_Shdr) * i), sizeof(Elf32_Shdr)); 
	strtab = sect_headers[ef.elf32header.e_shstrndx];
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


Elf32_Shdr get_section32(t_elf_file ef, char *secname)
{
	unsigned long n_sec = ef.elf32header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf32header.e_shoff;
	Elf32_Shdr sect_headers[n_sec];
	Elf32_Shdr strtab;
	Elf32_Shdr def = {0};

	if ((ef.elf32header.e_shoff+ (sizeof(Elf32_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (def);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf32_Shdr) * i), sizeof(Elf32_Shdr)); 
	strtab = sect_headers[ef.elf32header.e_shstrndx];
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

int is_stripped32(t_elf_file ef)
{
	unsigned long n_sec = ef.elf32header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf32header.e_shoff;
	Elf32_Shdr sect_headers[n_sec];
	Elf32_Shdr strtab;
	int ret = 1;	

	if ((ef.elf32header.e_shoff+ (sizeof(Elf32_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (1);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf32_Shdr) * i), sizeof(Elf32_Shdr)); 
	strtab = sect_headers[ef.elf32header.e_shstrndx];
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


int parse32elfheader(t_elf_file ef)
{
	Elf32_Ehdr new_header;

	ft_memcpy(&new_header, &ef.elf32header, sizeof(Elf32_Ehdr));
/*	new_header.e_shnum = 0;
	new_header.e_shentsize = 0;
	new_header.e_shoff = 0;*/
	new_header.e_shoff = new_header.e_shoff + ft_strlen(ef.key) + 1 + SHELLCODE_LEN + pad32;
	old_entry32 = new_header.e_entry;
	if (!(new_header.e_entry = new_entryaddr32(ef)))
		return (1);
	new_entry32 = new_header.e_entry;
	write(ef.wfd, &new_header, sizeof(Elf32_Ehdr));
	return (0);
}

int parse32elfph(t_elf_file ef)
{
	Elf32_Phdr phdr;
	unsigned char *ptr = (unsigned char *)ef.file  + ef.elf32header.e_phoff;
	unsigned int i = 0;

	while (i < ef.elf32header.e_phnum)
	{
		ft_memcpy(&phdr, ptr, sizeof(Elf32_Phdr));
		ptr += sizeof(Elf32_Phdr);
		if (phdr.p_type == PT_LOAD)
		{
			if (phdr.p_flags == (PF_R | PF_W))//Segment containning bss and my new section
			{
				printf("size=%u\n", phdr.p_memsz);
				printf("size=%u\n", phdr.p_filesz);
				pad32 = phdr.p_memsz - phdr.p_filesz;
				phdr.p_memsz += SHELLCODE_LEN + ft_strlen(ef.key);
				phdr.p_filesz = phdr.p_memsz;
			}
			phdr.p_flags = PF_X | PF_W |PF_R;
		}
		write(ef.wfd, &phdr, sizeof(Elf32_Phdr));
		i++;
	}
	return (0);
}

//mod is plain black magic 
void update_shellcode32_reladdr(unsigned int op_index, unsigned int dat_index, int mod)
{
	long rel_jmp = 0;
	rel_jmp = -(new_entry32 + op_index - old_entry32);  
	char *s = (char *)&rel_jmp;
	int j = dat_index;
	(void) mod;
	for(int i = 0; i < 4; i++)
	{
		char c = (char)s[i];
	/*	if (i == 0 && mod)
			c -= 7;
		else */if (i == 0 && !mod)
					c -= 5;
		shellcode32[j] = c;
		j++;
	}
}

void update_shellcode32_value(unsigned int index, int val)
{
	char *s = (char *)&val;
	int j = index;
	for(int i = 0; i < 4; i++)
	{
		char c = (char)s[i];
		shellcode32[j] = c;
		j++;
	}
}

char *update_shellcode32_key(char *key)
{
	return (ft_strnjoin((char *)shellcode32, SHELLCODE_LEN, key));
}

int parse32elfsec(t_elf_file ef)
{
	Elf32_Off new_sect = get_section32(ef, ".bss").sh_offset;
	Elf32_Shdr text_sec = get_section32(ef, ".text");
	unsigned long start =  ef.elf32header.e_phoff + (sizeof(Elf32_Phdr) * ef.elf32header.e_phnum); 
	unsigned long new_start;
	char *enc_text;

	if (!(enc_text = malloc(text_sec.sh_size)))
		return (1);
	ft_memcpy(enc_text, (unsigned char *)ef.file + text_sec.sh_offset, text_sec.sh_size);
	_encryptSelmelc(enc_text, ef.key, text_sec.sh_size);//encrypt the whole .text section

	write(ef.wfd, (unsigned char *)ef.file + start, (text_sec.sh_offset - start)); //writing from PH till start of .text
	write(ef.wfd, enc_text, text_sec.sh_size); // writing .text section
	free(enc_text);
	new_start = start + (text_sec.sh_offset - start) + text_sec.sh_size;
	write(ef.wfd, (unsigned char *)ef.file + new_start, (new_sect - new_start));// writing stuff between .text and .bss
	for (unsigned int i = 0; i < pad32; i++)
		write(ef.wfd, "\x00", 1); // padding 00 for what were previously "virtual memory"
	printf("textsize=%u\n", text_sec.sh_size);
	update_shellcode32_reladdr(JMP_INDEX - 1, JMP_INDEX, 0);
//	update_shellcode32_reladdr(DECREL_INDEX, DECREL_DATA_INDEX, 1);
	update_shellcode32_reladdr(RELCALL_INDEX, DECREL_DATA_INDEX, 1);
	update_shellcode32_value(STRSIZE_INDEX, text_sec.sh_size);

	char *new_sc = update_shellcode32_key(ef.key);
	write(ef.wfd, new_sc, SHELLCODE_LEN + ft_strlen(ef.key) + 1); // injecting our shellcode
	write(ef.wfd, (unsigned char *)ef.file + new_sect + 4, ef.fsize - new_sect); // remove for binary compression, it just adds the shdrs 
	free(new_sc);
	return (0);	
}

int parse32elf(t_elf_file ef)
{
	if (is_stripped32(ef))
		return (1);
	if (parse32elfheader(ef))
		return (1);
	parse32elfph(ef);
	parse32elfsec(ef);
	return (0);
}