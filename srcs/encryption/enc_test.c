#include <stdio.h>

extern void encryptSelmelc(char *s, char *key, unsigned long);
extern void decryptSelmelc(char *s, char *key, unsigned long);



int main()
{
	char s[] = "\x55\x48\x89\xe5";
	char k[] = "mdr";

	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
	encryptSelmelc(s, k, sizeof(s));
	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
	decryptSelmelc(s, k, sizeof(s));
	for (int i = 0; i < sizeof(s); i++)
		printf("%hhx ", s[i]);
	puts("");
}
