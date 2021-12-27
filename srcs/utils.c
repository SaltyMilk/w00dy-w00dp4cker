#include "woody.h"

unsigned int smallest_len(char *s1, char *s2)
{
	unsigned int l1 = ft_strlen(s1);
	unsigned int l2 = ft_strlen(s2);
	if (l1 < l2)
		return (l1);
	else
		return (l2);
}

int str_is_nullterm(t_elf_file ef, unsigned int offset)
{

	while (offset < ef.fsize)
	{
		if (!*((char *)ef.file + offset))
			return (1);
		offset++;
	}
	return (0);
}

unsigned int sp_len(char **sp)
{
	unsigned int i = 0;

	while (sp[i])
		i++;
	return (i);
}

void free_sp(char **sp)
{
	for (unsigned int i = 0; sp[i]; i++)
		free(sp[i]);
	free(sp);
}

char **copy_sp(char **sp)
{
	unsigned int i = 0;
	char **cpy;

	if (!(cpy = malloc(sizeof(char *) * (sp_len(sp) + 1))))
		return (NULL);
	while (sp[i])
	{
		if (!(cpy[i] = ft_strdup(sp[i])))
			return (NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

char	*ft_strnjoin(char const *s1, size_t n, char const *s2)
{
	char	*jstr;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(jstr = malloc((n + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (i < n)
	{
		jstr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		jstr[i] = *s2;
		s2++;
		i++;
	}
	jstr[i] = '\0';
	return (jstr);
}