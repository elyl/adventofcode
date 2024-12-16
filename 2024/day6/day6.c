#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define TAB_SIZE 1200
#define MAX_TRY	10000

enum direction { FORWARD, LEFT, RIGHT, BACKWARD };

typedef struct s_pos
{
  int			x;
  int			y;
  enum direction	direction;
}	t_pos;

char	*get_next_line(int fd);
int	get_tab(int fd, char **grid);
int	day6_1(char **grid, int height);
int	day6_2(char **grid, int height);
int	move(char **grid, int width, int height, t_pos *pos, int try);
int	move_backward(char **grid, int width, int height, t_pos *pos, int try);
int	move_forward(char **grid, int width, int height, t_pos *pos, int try);
int	move_right(char **grid, int width, int height, t_pos *pos, int try);
int	move_left(char **grid, int width, int height, t_pos *pos, int try);
t_pos	get_starting_pos(char **grid, int size, int height);
void	display_grid(char **grid, int width, int height, t_pos *pos);
char	**reset_grid(char **grid, int width, int height, t_pos *pos);

int main(int argc, char **argv)
{
  int	fd;
  int	size;
  char	**tab;

  fd = open(argv[1], O_RDONLY);
  tab = malloc(TAB_SIZE * sizeof(char*));
  size = get_tab(fd, tab);
  /*printf("day6 - 1 : %d\n", day6_1(tab, size));*/
  printf("day6 - 2 : %d\n", day6_2(tab, size));
  return (1);
}

int day6_1(char **grid, int height)
{
  int	width;
  int	count;
  t_pos	pos;
  int	movement;

  count = 0;
  width = strlen(grid[0]);
  pos = get_starting_pos(grid, width, height);
  movement = 0;
  while (movement != -1)
    {
      movement = move(grid, width, height, &pos, 0);
      if (movement != 0)
	++count;
    }
  return (count);
}

int day6_2(char **grid, int height)
{
  int	width;
  int	count;
  t_pos	pos;
  t_pos	starting_pos;
  int	movement;
  int	i;
  int	j;
  int	moves;
  char	previous;

  width = strlen(grid[0]);
  starting_pos = get_starting_pos(grid, width, height);
  count = 0;
  i = 0;
  while (i < height)
    {
      j = 0;
      while (j < width)
	{
	  previous = grid[i][j];
	  printf("Trying i : %d, j : %d\n", i, j);
	  if (starting_pos.x == j && starting_pos.y == i)
	    {
	      ++j;
	      continue;
	    }
	  pos.x = starting_pos.x;
	  pos.y = starting_pos.y;
	  pos.direction = starting_pos.direction;
	  reset_grid(grid, width, height, &starting_pos);
	  grid[i][j] = '#';
	  movement = 0;
	  moves = 0;
	  while (movement >= 0 && moves < MAX_TRY)
	    {
	      ++moves;
	      /*display_grid(grid, width, height, &pos);*/
	      movement = move(grid, width, height, &pos, 0);
	      if (movement == -2 || moves == MAX_TRY)
		++count;
	    }
	  grid[i][j] = previous;
	  ++j;
	}
      ++i;
    }
  return (count);
      
}

char **reset_grid(char **grid, int width, int height, t_pos *starting_pos)
{
  int	i;
  int	j;

  i = 0;
  while (i < height)
    {
      j = 0;
      while (j < width)
	{
	  if (i == starting_pos->y && j == starting_pos->x)
	    {
	      grid[i][j] = '^';
	    }
	  else if (grid[i][j] == 'X')
	    grid[i][j] = '.';
	  ++j;
	}
      ++i;
    }
  return (grid);
}

int move(char **grid, int width, int height, t_pos *pos, int try)
{
  if (++try > MAX_TRY)
    return (-2);
  switch (pos->direction)
    {
    case FORWARD: 
      return (move_forward(grid, width, height, pos, try));
    case LEFT:
      return (move_left(grid, width, height, pos, try));
    case RIGHT:
      return (move_right(grid, width, height, pos, try));
    case BACKWARD:
      return (move_backward(grid, width, height, pos, try));
    }
  return (0);
}

int move_backward(char **grid, int width, int height, t_pos *pos, int try)
{
  if (pos->y + 1 >= height)
    return (-1);
  else if (grid[pos->y + 1][pos->x] == '#')
    {
      pos->direction = LEFT;
      return (move(grid, width, height, pos, try));
    }
  else if (grid[pos->y + 1][pos->x] == 'X')
    {
      grid[pos->y][pos->x] = 'X';
      ++pos->y;
      return (0);
    }
  grid[pos->y][pos->x] = 'X';
  ++pos->y;
  return (1);
}

int move_right(char **grid, int width, int height, t_pos *pos, int try)
{
  if (pos->x + 1 >= width)
    return (-1);
  else if (grid[pos->y][pos->x + 1] == '#')
    {
      pos->direction = BACKWARD;
      return (move(grid, width, height, pos, try));
    }
  else if (grid[pos->y][pos->x + 1] == 'X')
    {
      grid[pos->y][pos->x] = 'X';
      ++pos->x;
      return (0);
    }
  grid[pos->y][pos->x] = 'X';
  ++pos->x;
  return (1);
}

int move_left(char **grid, int width, int height, t_pos *pos, int try)
{
  if (pos->x - 1 < 0)
    return (-1);
  else if (grid[pos->y][pos->x - 1] == '#')
    {
      pos->direction = FORWARD;
      return (move(grid, width, height, pos, try));
    }
  else if (grid[pos->y][pos->x - 1] == 'X')
    {
      grid[pos->y][pos->x] = 'X';
      --pos->x;
      return (0);
    }
  grid[pos->y][pos->x] = 'X';
  --pos->x;
  return (1);
}

int move_forward(char **grid, int width, int height, t_pos *pos, int try)
{
  if (pos->y - 1 < 0)
    return (-1);
  else if (grid[pos->y - 1][pos->x] == '#')
    {
      pos->direction = RIGHT;
      return (move(grid, width, height, pos, try));
    }
  else if (grid[pos->y - 1][pos->x] == 'X')
    {
      grid[pos->y][pos->x] = 'X';
      --pos->y;
      return (0);
    }
  grid[pos->y][pos->x] = 'X';
  --pos->y;
  return (1);
}

t_pos get_starting_pos(char **grid, int width, int height)
{
  t_pos	pos;

  pos.x = 0;
  pos.y = 0;
  pos.direction = FORWARD;
  while (pos.y < height)
    {
      pos.x = 0;
      while (pos.x < width)
	{
	  if (grid[pos.y][pos.x] == '^')
	    return (pos);
	  ++pos.x;
	}
      ++pos.y;
    }
}

int get_tab(int fd, char **grid)
{
  char	*buffer;
  int	i;
  
  i = 0;
  buffer = get_next_line(fd);
  while (buffer != NULL)
    {
      grid[i] = buffer;
      buffer = get_next_line(fd);
      ++i;
    }
  return (i);
}

void display_grid(char **grid, int width, int height, t_pos *pos)
{
  int	i;
  int	j;
  
  printf("Direction : ");
  switch (pos->direction)
    {
    case FORWARD:
      printf("Forward");
      break;
    case BACKWARD:
      printf("Backward");
      break;
    case RIGHT:
      printf("Right");
      break;
    case LEFT:
      printf("Left");
      break;
    }
  printf("\n");
  i = 0;
  while (i < height)
    {
      j = 0;
      while (j < width)
	{
	  if (pos->x == j && pos->y == i)
	    printf("^");
	  else
	    printf("%c", grid[i][j]);
	  ++j;
	}
      printf("\n");
      ++i;
    }
}
