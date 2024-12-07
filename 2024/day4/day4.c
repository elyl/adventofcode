#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define LINE_COUNT 150

char	*get_next_line(int fd);
int	day4_1(char **tab, int n);
int	day4_2(char **tab, int n);
int	count_word_line(char **tab, int n, char *word);
int	count_word_col(char **tab, int n, char *word);
int	count_word_diag(char **tab, int n, char *word);
int	count_x_mas(char **tab, int n, char *w1, char *w2);
void	free_tab(char **tab, int n);

int main(int argc, char **argv)
{
  int	fd;
  int	n1;
  char	**tab;
  char	*buffer;
  
  fd = open(argv[1], O_RDONLY);
  tab = malloc(LINE_COUNT * sizeof(char*));
  n1 = 0;
  while (1)
    {
      buffer = get_next_line(fd);
      if (buffer == NULL)
	break;
      tab[n1] = malloc(strlen(buffer) * sizeof(char));
      tab[n1] = buffer;
      ++n1;
    }
  printf("day4 - 1 : %d\n", day4_1(tab, n1));
  printf("day4 - 2 : %d\n", day4_2(tab, n1));
  free_tab(tab, n1);
  return (0);
}

int day4_1(char **tab, int n)
{
  int	count;

  count = 0;
  count = count_word_line(tab, n, "XMAS");
  count += count_word_line(tab, n, "SAMX");
  count += count_word_col(tab, n, "XMAS");
  count += count_word_col(tab, n, "SAMX");
  count += count_word_diag(tab, n, "XMAS");
  count += count_word_diag(tab, n, "SAMX");
  return (count);
}

/* More than 1867 */
int day4_2(char **tab, int n)
{
  int	count;

  count = 0;
  count += count_x_mas(tab, n, "MAS", "MAS");
  count += count_x_mas(tab, n, "SAM", "SAM");
  count += count_x_mas(tab, n, "MAS", "SAM");
  count += count_x_mas(tab, n, "SAM", "MAS");
  return (count);
}

int count_x_mas(char **tab, int n, char *w1, char *w2)
{
  int	count;
  int	i;
  int	j;
  int	k;
  int	len;
  int	line_len;

  i = 0;
  count = 0;
  len = strlen(w1);
  line_len = strlen(tab[0]);
  while (i <= n - len)
    {
      j = 0;
      while (j + len <= line_len)
	{
	  if (tab[i][j] == w1[0] && tab[i][j + 2] == w2[0])
	    {
	      k = 1;
	      while (k < len)
		{
		  if (tab[i + k][j + k] != w1[k] || tab[i + k][j - k + 2] != w2[k])
		    break;
		  ++k;
		}
	      if (k == len)
		{
		  /*printf("i : %d ; j : %d : c : %c\n", i, j, tab[i][j]);*/
		  ++count;
		}
	    }
	  ++j;
	}
      ++i;
    }
  return (count);
}

int count_word_line(char **tab, int n, char *word)
{
  int	i;
  char	*ptr;
  int	count;

  i = 0;
  count = 0;
  while (i < n)
    {
      ptr = tab[i++];
      while (1)
	{
	  ptr = strstr(ptr, word);
	  if (ptr == NULL)
	    break;
	  ++ptr;
	  ++count;
	}
    }
  return (count);
}

int count_word_col(char **tab, int n, char *word)
{
  int	count;
  int	i;
  int	j;
  int	k;
  int	len;

  len = strlen(word);
  count = 0;
  i = 0;
  while (i <= n - len)
    {
      j = 0;
      while (tab[i][j] != '\0')
	{
	  if (tab[i][j] == word[0])
	    {
	      k = 1;
	      while (k < len)
		{
		  if (tab[i + k][j] != word[k])
		    break;
		  ++k;
		}
	      if (k == len)
		++count;
	    }
	  ++j;
	}
      ++i;
    }
  return (count);
}

int count_word_diag(char **tab, int n, char *word)
{
  int	count;
  int	i;
  int	j;
  int	k;
  int	len;
  int	line_len;

  count = 0;
  i = 0;
  len = strlen(word);
  line_len = strlen(tab[0]);
  while (i <= n - len)
    {
      j = 0;
      while (tab[i][j] != '\0')
	{
	  if (tab[i][j] == word[0])
	    {
	      k = 1;
	      while (k < len)
		{
		  if (!(j + k < line_len && tab[i + k][j + k] == word[k]))
		    break;
		  ++k;
		}
	      if (k == len)
		++count;
	      k = 1;
	      while (k < len)
		{
		  if (!(j - k >= 0 && tab[i + k][j - k] == word[k]))
		    break;
		  ++k;
		}
	      if (k == len)
		++count;
	    }
	  ++j;
	}
      ++i;
    }
  return (count);
}

void free_tab(char **tab, int n)
{
  int	i;

  i = 0;
  while (i < n)
    free(tab[i++]);
  free(tab);
}
