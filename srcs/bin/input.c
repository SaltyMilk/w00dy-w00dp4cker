#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
int main()
{
	int i = 0;
	char s[64];
	bzero(s, 64);
	printf("Enter your name: ");
	fgets(s, 63, stdin);

	while (s[i] && s[i] != '\n')
		i++;
	s[i] = 0;
	printf("Welcome %s !\n", s);
}
