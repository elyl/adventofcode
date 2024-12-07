#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 1024
#define COLS 50

char *get_next_line(int fd);
int day2(int **tab, int size, int max_err);
int number_validation(int direction, int n1, int n2);

int main()
{
  int	fd;
  int	i;
  int	**tab;
  int	current_col;
  int	current_elements;
  char	*ptr2;
  char	*ptr;
  char	*buffer;

  fd = open("sample", O_RDONLY);
  tab = malloc(ROWS * sizeof(int*));
  for (i = 0; i < ROWS; ++i)
    tab[i] = malloc(COLS * sizeof(int));
  current_elements = 0;
  buffer = get_next_line(fd);
  while (buffer)
    {
      current_col = 1;
      ptr = buffer;
      while (1)
	{
	  ptr2 = strchr(ptr, ' ');
	  if (ptr2 == NULL)
	    {
	      tab[current_elements][current_col] = atoi(ptr);
	      break;
	    }
	  *ptr2 = '\0';
	  tab[current_elements][current_col] = atoi(ptr);
	  ++ptr2;
	  ptr = ptr2;
	  ++current_col;
	}
      tab[current_elements][0] = current_col + 1;
      current_elements++;
      free(buffer);
      buffer = get_next_line(fd);
    }
  free(buffer);
  /*printf("day2 - 1 : %d\n", day2(tab, current_elements, 0));*/
  printf("day2 - 2 : %d\n", day2(tab, current_elements, 1)); /* More than 352 */ /* not 355 */ /* not 359 */
  return (0);
}

int day2(int **tab, int size, int max_err)
{
  int	total;
  int	i;
  int	j;
  int	size2;
  int	direction;
  int	errors;

  total = 0;
  i = 0;
  while (i < size)
    {
      j = 2;
      direction =  (tab[i][1] <= tab[i][2]) ? 1 : -1;
      size2 = tab[i][0];
      errors = 0;
      while (j < size2)
	{
	  if (number_validation(direction, tab[i][j - 1], tab[i][j]) == -1)
	    {
	      /*	      printf("%d - j : %d ; Direction %d, N : %d, N-1 ; %d\n", i + 1, j, direction, tab[i][j], tab[i][j - 1]);*/
	      if (j > 3)
		tab[i][j] = tab[i][j - 1];
	      else if (j == 3)
		{
		  if (number_validation(direction, tab[i][j - 2], tab[i][j]) == 0)
		    {
		      errors = 0;
		    }
		  else if (number_validation(direction * -1, tab[i][j - 2], tab[i][j]) == 0 || number_validation(direction * -1, tab[i][j- 1], tab[i][j]) == 0)
		    {
		      errors = 0;
		      direction *= - 1;
		    }
		  else
		    tab[i][j] = tab[i][j - 1];
		}
	      ++errors;
	    }
	  ++j;
	}
      if (errors <= max_err)
	{
	  printf("safe, errors : %d\n", errors);
	  ++total;
	}
      else
	printf("unsafe\n");
      ++i;
    }
  return (total);
}

int number_validation(int direction, int n1, int n2)
{
  /*printf("direction : %d, n1 : %d, n2 : %d\n", direction, n1, n2);*/
  if (direction == 1 && (n2 <= n1 || n2 - 3 > n1))
    return (-1);
  if (direction == -1 && (n2 >= n1 || n2 + 3 < n1))
    return (-1);
  return (0);
}
