#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 18000

int	is_num(char c);
int	get_num(char *buffer);
int	day3_1(char *buffer);
int	day3_2(char *buffer);

int main(int argc, char **argv)
{
  int	fd;
  int	n;
  char	buffer[BUFFER_SIZE];
  
  fd = open(argv[1], O_RDONLY);
  n = read(fd, buffer, BUFFER_SIZE - 1);
  buffer[n] = '\0';
  printf("Day3 - 1 : %d\n", day3_1(buffer));
  printf("Day3 - 2 : %d\n", day3_2(buffer));
  return (0);
}

int is_num(char c)
{
  if (c >= '0' && c <= '9')
    return (0);
  else
    return (-1);
}

/* Less than 179942518 */ 
int day3_1(char *buffer)
{
  int	n1;
  int	n2;
  int	count;
  char	*ptr;

  count = 0;
  while (1)
    {
      ptr = strstr(buffer, "mul(");
      if (ptr == NULL)
	break;
      ptr += 4;
      buffer = ptr;
      n1 = get_num(ptr);
      if (n1 == -1)
	continue;
      ptr = strchr(buffer, ',');
      if (ptr - buffer > 3)
	continue;
      ptr += 1;
      buffer = ptr;
      n2 = get_num(ptr);
      if (n2 == -1)
	continue;
      ptr = strchr(buffer, ')');
      if (ptr - buffer > 3)
	continue;
      count += n1 * n2;
    }
  return (count);
}

int day3_2(char *buffer)
{
  int	n1;
  int	n2;
  int	count;
  char	*ptr;
  char	*ptr2;
  int	enabled;

  enabled = 1;
  count = 0;
  while (1)
    {
      if (enabled == 0)
	{
	  ptr = strstr(buffer, "do()");
	  enabled = 1;
	  buffer = ptr;
	  if (ptr != NULL)
	    continue;
	  else
	    break;
	}
      ptr = strstr(buffer, "mul(");
      if (ptr == NULL)
	break;
      ptr2 = strstr(buffer, "don't()");
      printf("ptr : %x; ptr2: %x\n", ptr, ptr2);
      if (ptr2 != NULL && ptr2 < ptr)
	{
	  enabled = 0;
	  continue;
	}
      ptr += 4;
      buffer = ptr;
      n1 = get_num(ptr);
      if (n1 == -1)
	continue;
      ptr = strchr(buffer, ',');
      if (ptr - buffer > 3)
	continue;
      ptr += 1;
      buffer = ptr;
      n2 = get_num(ptr);
      if (n2 == -1)
	continue;
      ptr = strchr(buffer, ')');
      if (ptr - buffer > 3)
	continue;
      count += n1 * n2;
    }
  return (count);
}

int get_num(char *buffer)
{
  int	i;
  char	tmp[4];

  i = 0;
  while (i < 3)
    {
      if (buffer[i] == ',' || buffer[i] == ')')
	break;
      if (is_num(buffer[i]) == -1)
	return (-1);
      ++i;
    }
  strncpy(tmp, buffer, i);
  tmp[i] = '\0';
  return (atoi(tmp));
}
