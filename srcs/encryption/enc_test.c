#include <stdio.h>

extern void _encrypt(char *s, char *key);
extern void _decrypt(char *s, char *key);



int main()
{
	char s[] = "\xff\x00\x42";
	char k[] = "ab";
	_encrypt(s, k);
	_decrypt(s, k);
}