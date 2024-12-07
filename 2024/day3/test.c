#include <stdio.h>
#include <string.h>

void main()
{
  char s1[] = "Je suis une loutre";
  char s2[] = "loutre";
  char s3[] = "suis";
  char s4[] = "poney";

  printf("%x, %x, %x\n", strstr(s1, s2), strstr(s1, s3), strstr(s1, s4));
}
