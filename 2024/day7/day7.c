#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

/* 6123715 too low */
/* 1914119917 too low */
/* 2050753933 too low */

#define TAB_SIZE 851

enum operator { ADD, MULT };

typedef struct s_operande
{
  int			number;
  enum operator		op;
  struct s_operande	*next;
}	t_operande;

typedef struct s_operation
{
  unsigned long int	result;
  t_operande		*list;
}	t_operation;

void		reset_operations(t_operande *list);
void		add_mul(t_operande *list, int count_mult, int *offsets);
void		init_offsets(int *offsets, int count_mult);
void		inc_offsets(int *offsets, int count_mult, int list_sie);
void		print_ops(t_operande *list);
char		*get_next_line(int fd);
int		get_tab(int fd, char **tab);
unsigned long int		day7_1(char **tab, int height);
int		strcount(char *str, char c);
int		ratoi(char *str, char **ptr);
int		get_list_size(t_operande *list);
int		try_mul(t_operation *ope);
unsigned long int		solve(t_operande *list);
t_operation	parse_line(char *tab);
t_operande	*add_to_list(t_operande *ope, int number, enum operator op);

int main(int argc, char **argv)
{
  int	fd;
  int	height;
  char	**tab;

  if (argc < 2)
    return (-1);
  fd = open(argv[1], O_RDONLY);
  tab = malloc(TAB_SIZE * sizeof(char*));
  height = get_tab(fd, tab);
  printf("Day7 - 1 : %ld\n", day7_1(tab, height));
  return (0);
}

unsigned long int day7_1(char **tab, int height)
{
  int				i;
  unsigned long int	count;
  t_operation			ope;

  count = 0;
  i = 0;
  while (i < height)
    {
      ope = parse_line(tab[i]);
      if (try_mul(&ope) == 1)
	{
	  count += ope.result;
	  printf("%ld\n", ope.result);
	}
      ++i;
    }
  return (count);
}

int try_mul(t_operation *ope)
{
  int	count_mult;
  int	list_size;
  int	*offsets;
  
  count_mult = 1;
  list_size = get_list_size(ope->list);
  while (count_mult < list_size)
    {
      if (ope->result == solve(ope->list))
	return (1);
      offsets = malloc(count_mult * sizeof(int));
      init_offsets(offsets, count_mult);
      while (offsets[count_mult - 1] < list_size)
	{
	  add_mul(ope->list, count_mult, offsets);
	  if (ope->result == solve(ope->list))
	    return (1);
	  /*print_ops(ope->list);*/
	  reset_operations(ope->list);
	  inc_offsets(offsets, count_mult, list_size);
	}
      free(offsets);
      ++count_mult;
    }
  return (-1);
}

void init_offsets(int *offsets, int count_mult)
{
  int	i;

  i = 0;
  while (i < count_mult)
    {
      offsets[i] = i + 1;
      ++i;
    }
}

void inc_offsets(int *offsets, int count_mult, int list_size)
{
  if (count_mult == 0)
    return;
  offsets[count_mult - 1] += 1;
  if (offsets[count_mult - 1] >= list_size)
    {
      inc_offsets(offsets, count_mult - 1, list_size - 1);
      if (count_mult > 1)
	offsets[count_mult - 1] = offsets[count_mult - 2] + 1;
    }
}

void print_ops(t_operande *list)
{
  while (list != NULL)
    {
      printf("Number  : %d ; op : ", list->number);
      if (list->op == ADD)
	printf("ADD");
      else
	printf("MULT");
      printf("\n");
      list = list->next;
    }
  printf("_____________________\n");
}

void add_mul(t_operande *list, int count_mult, int *offsets)
{
  int	i;
  int	j;
  t_operande *first;

  first = list;
  j = 0;
  while (j < count_mult)
    {
      i = 0;
      list = first;
      while (i < offsets[j] && list != NULL)
	{
	  list = list->next;
	  ++i;
	}
      if (list != NULL)
	list->op = MULT;
      ++j;
    }
}

void reset_operations(t_operande *list)
{
  while (list != NULL)
    {
      list->op = ADD;
      list = list->next;
    }
}

int get_list_size(t_operande *list)
{
  int	size;

  size = 0;
  while (list != NULL)
    {
      list = list->next;
      ++size;
    }
  return (size);
}

unsigned long int solve(t_operande *ope)
{
  unsigned long int	result;

  result = ope->number;
  ope = ope->next;
  while (ope != NULL)
    {
      if (ope->op == ADD)
	result += ope->number;
      else if (ope->op == MULT)
	result *= ope->number;
      ope = ope->next;
    }
  return (result);
}

t_operation parse_line(char *line)
{
  int		i;
  int		count;
  t_operation	operation;
  char		*ptr;

  i = 0;
  operation.list = NULL;
  count = strcount(line, ' ');
  ptr = line;
  while (i < count + 1)
    {
      if (i == 1)
	operation.list = add_to_list(NULL, ratoi(ptr, &ptr), ADD);
      else if (i != 0)
	add_to_list(operation.list, ratoi(ptr, &ptr), ADD);
      else
	{
	  operation.result = ratoi(ptr, &ptr);
	  ++ptr;
	}
      ++i;
    }
  return (operation);
}

int ratoi(char *str, char **ptr)
{
  int	i;
  char	tmp[255];

  i = 0;
  while (isdigit(str[i]) > 0)
    ++i;
  *ptr = &str[i];
  *ptr = *ptr + 1;
  strncpy(tmp, str, i);
  tmp[i] = '\0';
  return (atoi(tmp));
}

int strcount(char *str, char c)
{
  char	*ptr;
  int	count;

  ptr = str;
  count = 0;
  while (1)
    {
      ptr = strchr(ptr, c);
      ++count;
      if (ptr == NULL)
	break;
      ++ptr;
    }
  return (count);
}

int get_tab(int fd, char **tab)
{
  int	size;
  char	*buffer;

  size = 0;
  buffer = get_next_line(fd);
  while (buffer != NULL)
    {
      tab[size] = buffer;
      buffer = get_next_line(fd);
      ++size;
    }
  return (size);
}

t_operande *add_to_list(t_operande *ope, int number, enum operator op)
{
  t_operande	*new_ope;
  
  new_ope = malloc(sizeof(t_operande));
  if (ope != NULL)
    {
      while (ope->next != NULL)
	ope = ope->next;
      ope->next = new_ope;
    }
  new_ope->next = NULL;
  new_ope->number = number;
  new_ope->op = op;
  return (new_ope);
}
