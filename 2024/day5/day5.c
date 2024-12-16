#define _GNU_SOURCE	1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define TAB_SIZE	1400

typedef struct s_page
{
  int		required;
  int		target;
  struct s_page	*next;
}	t_page;

char	*get_next_line(int fd);
t_page	*parse_tab(char **tab);
t_page	*add_to_list(t_page *pages, int required, int target);
int	day5_1(char **tab, int n, t_page *pages);
int	day5_2();
int	is_page_ok(t_page *pages, int nb, int to_print[], int size);
void	free_tab(char **tab, int n);
void	free_list(t_page *list);

int main(int argc, char **argv)
{
  int		fd;
  int		i;
  char		*tab[TAB_SIZE];
  char		*ptr;
  t_page	*pages;

  fd = open(argv[1], O_RDONLY);
  ptr = get_next_line(fd);
  i = 0;
  while (ptr != NULL)
    {
      tab[i] = ptr;
      ptr = get_next_line(fd);
      ++i;
    }
  pages = parse_tab(tab);
  printf("day5-1 : %d\n", day5_1(tab, i, pages));
  return (0);
}

int day5_1(char **tab, int n, t_page *pages)
{
  int		count;
  int		i;
  int		j;
  int		k;
  int		flag;
  int		nb;
  char		*ptr;
  char		*ptr2;
  int		to_print[50];

  i = 0;
  count = 0;
  while (tab[i][0] != '\0')
    ++i;
  ++i;
  while (i < n)
    {
      ptr = tab[i];
      k = 0;
      ptr2 = tab[i];
      flag = 0;
      while (flag == 0)
	{
	  ptr2 = strchrnul(ptr, ',');
	  if (*ptr2 == '\0')
	    flag = 1;
	  *ptr2 = '\0';
	  nb = atoi(ptr);
	  to_print[k] = nb;
	  ++k;
	  ptr = ptr2 + 1;
	}
      j = 0;
      while (j < k)
	{
	  if (is_page_ok(pages, to_print[j], to_print, k) == -1)
	    break;
	  ++j;
	}
      if (j == k)
	{
	  printf("i : %d, k : %d, count : %d\n", i, k, to_print[k/2]);
	  count += to_print[k/2];
	}
      ++i;
    }
  return (count);
}

int day5_2(char **tab, int n, t_page *pages)
{
  int		count;
  int		i;
  int		j;
  int		k;
  int		flag;
  int		nb;
  char		*ptr;
  char		*ptr2;
  int		to_print[50];

  i = 0;
  count = 0;
  while (tab[i][0] != '\0')
    ++i;
  ++i;
  while (i < n)
    {
      ptr = tab[i];
      k = 0;
      ptr2 = tab[i];
      flag = 0;
      while (flag == 0)
	{
	  ptr2 = strchrnul(ptr, ',');
	  if (*ptr2 == '\0')
	    flag = 1;
	  *ptr2 = '\0';
	  nb = atoi(ptr);
	  to_print[k] = nb;
	  ++k;
	  ptr = ptr2 + 1;
	}
      j = 0;
      while (j < k)
	{
	  if (is_page_ok(pages, to_print[j], to_print, k) == -1)
	    break;
	  ++j;
	}
      if (j != k)
	{
	  order_set(pages, to_print, k);
	  count += to_print[k/2];
	}
      ++i;
    }
  return (count);
}

void order_set(t_page pages, int *to_print, int size)
{
  t_page	*first;
  int		i;

  first = pages;
  i = 0;
  while (i < size)
    {
      
    }
}

int is_page_ok(t_page *pages, int nb, int to_print[], int size)
{
  int	i;
  int	flag1; /* target number has been reached */
  int	flag2; /* required number is ok */
  
  while (pages != NULL)
    {
      flag1 = 0;
      flag2 = 0;
      if (pages->target == nb)
	{
	  i = 0;
	  while (i < size)
	    {
	      if (nb == to_print[i])
		flag1 = 1;
	      if (to_print[i] == pages->required)
		{
		  if (flag1 == 1 && flag2 == 0)
		    flag2 = -1;
		  else
		    flag2 = 1;
		}
	      ++i;
	    }
	  if (flag2 == -1)
	    return (-1);
	}
      pages = pages->next;
    }
  return (1);
}

t_page	*parse_tab(char **tab)
{
  int		i;
  char		*ptr;
  t_page	*first;
  t_page	*tmp;

  i = 0;
  first = NULL;
  while (tab[i][0] != '\0')
    {
      ptr = strchr(tab[i], '|');
      *ptr = '\0';
      tmp = add_to_list(first, atoi(tab[i]), atoi(ptr + 1));
      if (first == NULL)
	first = tmp;
      ++i;
    }
  return (first);
}

t_page	*add_to_list(t_page *list, int required, int target)
{
  t_page	*prev;

  prev = NULL;
  while (list != NULL)
    {
      prev = list;
      list = list->next;
    }
  list = malloc(sizeof(t_page));
  if (prev != NULL)
    prev->next = list;
  list->required = required;
  list->target = target;
  list->next = NULL;
  return (list);
}

void free_list(t_page *list)
{
  t_page	*prev;

  while (list != NULL)
    {
      prev = list;
      list = list->next;
      free(prev);
    }
}

void free_tab(char **tab, int n)
{
  int	i;

  i = 0;
  while (i < n)
    {
      free(tab[i]);
      ++i;
    }
  free(tab);
}
