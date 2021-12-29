#include "macho_woody.h"
//								  decrypt shell code len  
#define SHELLCODE_LEN 51 + 5 +2 + 60  +3                     
#define JMP_INDEX 105 
#define KEY_INDEX 0
#define DECREL_INDEX 51
#define DECREL_DATA_INDEX 54
#define STRSIZE_INDEX 43
unsigned char shellcode[SHELLCODE_LEN] = "\xb8\x04\x00\x00\x02\xbf\x01\x00\x00\x00\x52\x68\x2e\x2e\x2e\x0a\x48\xba\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x52\x48\x8d\x34\x24\xba\x0c\x00\x00\x00\x0f\x05\x48\x31\xd2\x48\xba\x01\x00\x00\x00\x00\x00\x00\x00\x48\x8d\x3d\xba\xbe\xba\xbe\x48\x8d\x35\x38\x00\x00\x00\x48\x31\xc9\x48\x31\xdb\x44\x8a\x0c\x1e\x00\x0c\x0f\x44\x30\x0c\x0f\x48\xff\xc3\x48\xff\xc1\x48\x39\xd1\x74\x08\x80\x3c\x1e\x00\x74\xe1\xeb\xe2\x58\x58\x5a\xE8\xEA\xCF\xFF\xFF\xb8\x01\x00\x00\x02\xbf\x00\x00\x00\x00\x0f\x05";
unsigned int pad = 0;
unsigned long lc_tot_size = 0;
t_section text_sec;
t_segment_command_64 text_seg;
unsigned long old_entry = 0;
unsigned long new_entry = 0;
unsigned long entry_off = 0;

/*
int is_stripped(t_mf mf)
{
	unsigned long n_sec = mf.elf64header.e_shnum;
	unsigned char *ptr = (unsigned char *)mf.file + mf.elf64header.e_shoff;
	Elf64_Shdr sect_headers[n_sec];
	Elf64_Shdr strtab;
	int ret = 1;	

	if ((mf.elf64header.e_shoff+ (sizeof(Elf64_Shdr) * n_sec)) > mf.fsize)//boundary check
		return (1);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf64_Shdr) * i), sizeof(Elf64_Shdr)); 
	strtab = sect_headers[mf.elf64header.e_shstrndx];
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if ((strtab.sh_offset + sect_headers[i].sh_name) > mf.fsize)//boundary check
			return (1);
		char *name =(char*)mf.file + strtab.sh_offset + sect_headers[i].sh_name; 
		if (!ft_strncmp(name, ".symtab", ft_strlen(".symtab")))
			ret = 0;
	}
	return (ret);
}

*/
int parse64machheader(t_mf mf)
{
	t_mach_header_64 new_header;

	ft_memcpy(&new_header, &mf.mach64header, sizeof(t_mach_header_64));
	write(mf.wfd, &new_header, sizeof(t_mach_header_64));
	return (0);
}

void handle_entry(t_mf mf, t_entry_point_command *lcmd)
{
	t_entry_point_command epc;

	ft_memcpy(&epc, lcmd, sizeof(t_entry_point_command));
	old_entry = epc.entryoff;
	printf("oldentry=%lu\n", old_entry);
	epc.entryoff = new_entry;
	write(mf.wfd, &epc, lcmd->cmdsize);
}
void handle_segment(t_mf mf, t_segment_command_64 *lcmd)
{
	t_segment_command_64 newseg;
	ft_memcpy(&newseg, lcmd, sizeof(t_segment_command_64));
	newseg.initprot = VM_PROT_ALL;
	newseg.maxprot = VM_PROT_ALL;
	if (!ft_strncmp(newseg.segname, SEG_LINKEDIT,ft_strlen(SEG_LINKEDIT)))
	{
		pad = newseg.vmsize - newseg.filesize;
		newseg.vmsize += SHELLCODE_LEN + ft_strlen(mf.key);
		newseg.filesize = newseg.vmsize;
		write(mf.wfd, &newseg, sizeof(t_segment_command_64));
	}
	else
		write(mf.wfd,(unsigned char*)lcmd, lcmd->cmdsize);
}

unsigned long find_new_entry(t_segment_command_64 *lcmd)
{
	t_segment_command_64 newseg;
	ft_memcpy(&newseg, lcmd, sizeof(t_segment_command_64));

	if (!ft_strncmp(newseg.segname, SEG_TEXT, ft_strlen(SEG_TEXT)))//Find all the info on __text
	{
		ft_memcpy(&text_seg, &newseg, sizeof(t_segment_command_64));
		void * section = ((unsigned char *)lcmd) + sizeof(t_segment_command_64);
		for (uint32_t i = 0; i < newseg.nsects; i++)
		{
			t_section new_section;
			ft_memcpy(&new_section, section, sizeof(t_section));
			if (!ft_strncmp(new_section.sectname, SECT_TEXT, ft_strlen(SECT_TEXT)))
			{
				ft_memcpy(&text_sec, &new_section, sizeof(t_section));
			}
			section += sizeof(t_section);
		}
	}
	if (!ft_strncmp(newseg.segname, SEG_LINKEDIT,ft_strlen(SEG_LINKEDIT)))
	{
		entry_off = newseg.fileoff + newseg.filesize;
		return ((newseg.vmaddr - text_seg.vmaddr) + newseg.vmsize);
	}
	return (0);
}

int parse64machloadcmd(t_mf mf)
{
	t_load_command lcmd;
	unsigned char *ptr = (unsigned char *)mf.file  + sizeof(t_mach_header_64);
	unsigned int i = 0;
	unsigned long tmp;
	//first we need to find our new entry
	while (i < mf.mach64header.ncmds)
	{
		ft_memcpy(&lcmd, ptr, sizeof(t_load_command));
		if (lcmd.cmd == LC_SEGMENT_64)
			if ((tmp = find_new_entry((t_segment_command_64 *)ptr)))
				new_entry = tmp; //entry found
		ptr += lcmd.cmdsize;
		i++;
	}
	printf("entry=%lu\n", new_entry);
	ptr = (unsigned char *)mf.file  + sizeof(t_mach_header_64); 
	i = 0;
	while (i < mf.mach64header.ncmds)
	{
		ft_memcpy(&lcmd, ptr, sizeof(t_load_command));
		if (lcmd.cmd == LC_MAIN)
			handle_entry(mf, (t_entry_point_command *)ptr);
		else if (lcmd.cmd == LC_SEGMENT_64)
			handle_segment(mf, (t_segment_command_64 *)ptr);
		else
			write(mf.wfd, ptr, lcmd.cmdsize);
		ptr += lcmd.cmdsize;
		lc_tot_size += lcmd.cmdsize;
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

char *update_shellcode_key(char *key)
{
	return (ft_strnjoin((char *)shellcode, SHELLCODE_LEN, key));
}
int hock(t_mf mf)
{
	unsigned long start  = sizeof(t_mach_header_64) + lc_tot_size;
	write(mf.wfd, (unsigned char *)mf.file + start, (mf.fsize - start) );
	return(0);
}

int hack(t_mf mf)
{
	unsigned long start  = sizeof(t_mach_header_64) + lc_tot_size;
	unsigned long new_start;
	char *enc_text;

	if (!(enc_text = malloc(text_sec.size)))
		return (1);
	ft_memcpy(enc_text, (unsigned char *)mf.file + text_sec.offset, text_sec.size);
	encryptSelmelc(enc_text, mf.key, text_sec.size);
	write(mf.wfd, (unsigned char *)mf.file + start, (text_sec.offset - start)); //writing from LCMDS till start of __text
	write(mf.wfd, enc_text, text_sec.size); // writing __text section
	free(enc_text);
	new_start = start +(text_sec.offset - start)+ text_sec.size;
	write(mf.wfd, (unsigned char *)mf.file + new_start, (entry_off - new_start));// writing stuff between __text and last __data
	for (unsigned int i = 0; i < pad; i++)
		write(mf.wfd, "\x00", 1); // padding 00 for what were previously "virtual memory"

	update_shellcode_reladdr(JMP_INDEX - 1, JMP_INDEX, 0);
	update_shellcode_reladdr(DECREL_INDEX, DECREL_DATA_INDEX, 1);
	update_shellcode_value(STRSIZE_INDEX, text_sec.size);
	printf("sizetext=%llu\n", text_sec.size);
	char *new_sc = update_shellcode_key(mf.key);
	write(mf.wfd, new_sc, SHELLCODE_LEN + ft_strlen(mf.key)); // injecting our shellcode
//	write(mf.wfd, (unsigned char *)mf.file + new_entry, mf.fsize - new_entry);  
	free(new_sc);
	return (0);
}
/*
int parse64elfsec(t_mf mf)
{
	Elf64_Off new_sect = get_section(mf, ".bss").sh_offset;
	Elf64_Shdr text_sec = get_section(mf, ".text");
	unsigned long start =  mf.elf64header.e_phoff + (sizeof(Elf64_Phdr) * mf.elf64header.e_phnum); 
	unsigned long new_start;
	char *enc_text;

	if (!(enc_text = malloc(text_sec.sh_size)))
		return (1);
	ft_memcpy(enc_text, (unsigned char *)mf.file + text_sec.sh_offset, text_sec.sh_size);
	_encrypt(enc_text, mf.key, text_sec.sh_size);//encrypt the whole .text section

	write(mf.wfd, (unsigned char *)mf.file + start, (text_sec.sh_offset - start)); //writing from PH till start of .text
	write(mf.wfd, enc_text, text_sec.sh_size); // writing .text section
	free(enc_text);
	new_start = start + (text_sec.sh_offset - start) + text_sec.sh_size;
	write(mf.wfd, (unsigned char *)mf.file + new_start, (new_sect - new_start));// writing stuff between .text and .bss
	for (unsigned int i = 0; i < pad; i++)
		write(mf.wfd, "\x00", 1); // padding 00 for what were previously "virtual memory"

	update_shellcode_reladdr(JMP_INDEX - 1, JMP_INDEX, 0);
	update_shellcode_reladdr(DECREL_INDEX, DECREL_DATA_INDEX, 1);
	update_shellcode_value(STRSIZE_INDEX, text_sec.sh_size);

	char *new_sc = update_shellcode_key(mf.key);
	write(mf.wfd, new_sc, SHELLCODE_LEN + ft_strlen(mf.key)); // injecting our shellcode
//	write(mf.wfd, (unsigned char *)mf.file + new_sect, mf.fsize - new_sect); // remove for binary compression, it just adds the shdrs 
	free(new_sc);
	return (0);	
}
*/
int parse64macho(t_mf mf)
{
	//if (is_stripped(mf))
	//	return (1);
	if (parse64machheader(mf))
		return (1);
	parse64machloadcmd(mf);
	if (hack(mf))
		return (1);
	printf("pad=%u\n", pad);
	return (0);
}