#include <stdio.h>

extern void _encrypt(char *s, char *key, unsigned long);
extern void _decrypt(char *s, char *key, unsigned long);



int main()
{
	char s[] = "hello";
	char k[] = "ab";
	printf("%s\n", s);
	_encrypt(s, k, 5);
	printf("%s\n", s);
	_decrypt(s, k, 5);
	printf("%s\n", s);
}
