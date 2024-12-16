#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

#define TAB_SIZE	50

#define ABS(x) (((x) > 0) ? (x) : -(x))

enum nodes { ANTINODE, NONE };

typedef struct s_pos
{
  int		x;
  int		y;
  struct s_pos	*next;
}	t_pos;

typedef struct s_antena
{
  char			c;
  t_pos			*pos;
  struct s_antena	*next;
}	t_antena;

void		create_antinodes(int **antigrid, int size, t_antena *antenas);
void		print_antigrid(int **antigrid, int size);
char		*get_next_line(int fd);
char		**get_grid(int fd);
int		**init_antigrid(int size);
int		day8_1(char **grid);
int		day8_2(char **grid);
int		count_antinodes(int **antigrid, int size);
t_antena	*parse_grid(char **grid, int size);
t_antena	*add_antena(t_antena *list, int x, int y, char c);
t_pos		*add_pos(t_pos *list, int x, int y);

int main(int argc, char **argv)
{
  int	fd;
  char	**grid;
  
  if (argc < 2)
    return (-1);
  fd = open(argv[1], O_RDONLY);
  grid = get_grid(fd);
  printf("day8 - 1 : %d\n", day8_1(grid));
  return (0);
}

int day8_1(char **grid)
{
  int		size;
  int		**antigrid;
  t_antena	*antenas;

  size = 0;
  while (grid[size] != NULL)
    ++size;
  antigrid = init_antigrid(size);
  antenas = parse_grid(grid, size);
  create_antinodes(antigrid, size, antenas);
  print_antigrid(antigrid, size);
  return (count_antinodes(antigrid, size));
}

void create_antinodes(int **antigrid, int size, t_antena *antenas)
{
  t_pos	*pos1;
  t_pos	*pos2;
  int	deltax;
  int	deltay;

  while (antenas != NULL)
    {
      pos1 = antenas->pos;
      while (pos1 != NULL)
	{
	  pos2 = pos1->next;
	  while (pos2 != NULL)
	    {
	      deltax = ABS(pos1->x - pos2->x);
	      deltay = ABS(pos1->y - pos2->y);
	      printf("Antena : %c\n", antenas->c);
	      printf("pos 1 ; x : %d ; y : %d\n", pos1->x, pos1->y);
	      printf("pos 2 ; x : %d ; y : %d\n", pos2->x, pos2->y);
	      printf("deltax : %d; deltay : %d\n", deltax, deltay);
	      if (pos2->y - deltay >= 0)
		{
		  if (pos2->x >= pos1->x && pos2->x + deltax < size)
		    antigrid[pos2->y - deltay][pos2->x + deltax] = ANTINODE;
		  else if (pos2->x < pos1->x && pos2->x - deltax >= 0)
		    antigrid[pos2->y - deltay][pos2->x - deltax] = ANTINODE;
		}
	      if (pos1->y + deltay < size)
		{
		  if (pos1->x >= pos2->x && pos1->x + deltax < size)
		    antigrid[pos1->y + deltay][pos1->x + deltax] = ANTINODE;
		  else if (pos1->x < pos2->x && pos1->x - deltax >= 0)
		    antigrid[pos1->y + deltay][pos1->x - deltax] = ANTINODE;
		}
	      pos2 = pos2->next;
	    }
	  pos1 = pos1->next;
	}
      antenas = antenas->next;
    }
}

int **init_antigrid(int size)
{
  int	**antigrid;
  int	i;
  int	j;

  antigrid = malloc(size * sizeof(int*));
  i = 0;
  while (i < size)
    {
      antigrid[i] = malloc(size * sizeof(int));
      j = 0;
      while (j < size)
	{
	  antigrid[i][j] = NONE;
	  ++j;
	}
      ++i;
    }
  return (antigrid);
}

t_antena *parse_grid(char **grid, int size)
{
  int		i;
  int		j;
  char		c;
  t_antena	*list;

  i = 0;
  list = NULL;
  while (i < size)
    {
      j = 0;
      while (j < size)
	{
	  c = grid[i][j];
	  if (isalpha(c) || isdigit(c))
	    list = add_antena(list, j, i, c);
	  ++j;
	}
      ++i;
    }
  return (list);
}

t_antena *add_antena(t_antena *list, int x, int y, char c)
{
  t_antena	*first;

  if (list == NULL)
    {
      list = malloc(sizeof(t_antena));
      list->next = NULL;
      list->c = 0;
      list->pos = NULL;
    }
  first = list;
  while (list->next != NULL && list->c != c)
    list = list->next;
  if (list->c != c)
    {
      list->next = malloc(sizeof(t_antena));
      list = list->next;
      list->next = NULL;
      list->pos = NULL;
    }
  list->pos = add_pos(list->pos, x, y);
  list->c = c;
  return (first);
}

t_pos *add_pos(t_pos *list, int x, int y)
{
  t_pos	*new_pos;
  t_pos *first;

  first = list;
  while (list != NULL)
    {
      if (list->x == x && list->y == y)
	return (first);
      list = list->next;
    }
  new_pos = malloc(sizeof(t_pos));
  new_pos->next = first;
  new_pos->x = x;
  new_pos->y = y;
  return (new_pos);
}

int count_antinodes(int **antigrid, int size)
{
  int	count;
  int	i;
  int	j;

  count = 0;
  i = 0;
  while (i < size)
    {
      j = 0;
      while (j < size)
	{
	  if (antigrid[i][j] == ANTINODE)
	    {
	      printf("count : x : %d, y : %d\n", j, i);
	      ++count;
	    }
	  ++j;
	}
      ++i;
    }
  return (count);
}

char **get_grid(int fd)
{
  int	i;
  char	*buffer;
  char	**grid;

  grid = malloc((TAB_SIZE + 1) * sizeof(char*));
  buffer = get_next_line(fd);
  i = 0;
  while (buffer != NULL)
    {
      grid[i] = buffer;
      buffer = get_next_line(fd);
      ++i;
    }
  grid[i] = NULL;
  return (grid);
}

void print_antigrid(int **antigrid, int size)
{
  int	i;
  int	j;

  i = 0;
  while (i < size)
    {
      j = 0;
      while (j < size)
	{
	  if (antigrid[i][j] == ANTINODE)
	    printf("#");
	  else
	    printf(".");
	  ++j;
	}
      printf("\n");
      ++i;
    }
}
