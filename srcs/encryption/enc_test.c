#include <stdio.h>

extern void _encrypt(char *s, char *key, unsigned long);
extern void _decrypt(char *s, char *key, unsigned long);



int main()
{
	char s[] = "\xed\x31\x49\x89\xd1";
	char k[] = "mdr";

	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
	_encrypt(s, k, 5);
	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
	_decrypt(s, k, 5);
	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
}
