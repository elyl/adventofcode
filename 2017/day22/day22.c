#include <stdio.h>

#define TARGET_X 770
#define TARGET_Y 7

void main()
{
  unsigned long	long cave[TARGET_X + 1][TARGET_Y + 1];
  unsigned long	long erosion[TARGET_X + 1][TARGET_Y + 1];
  int	depth = 10647;
  //  int	depth = 510;
  int	risk;
  int	x;
  int	y;

  risk = 0;
  x = 0;
  while (x <= TARGET_X)
    {
      y = 0;
      while (y <= TARGET_Y)
	{
	  if (x == 0 || y == 0)
	    cave[x][y] = x * 48271 + y * 16807;
	  else if (x == TARGET_X && y == TARGET_Y)
	    cave[x][y] = 0;
	  else
	    cave[x][y] = erosion[x - 1][y] * erosion[x][y - 1];
	  erosion[x][y] = (cave[x][y] + depth) % 20183;
	  risk += erosion[x][y] % 3;
	  ++y;
	}
      ++x;
    }
  printf("%d\n", risk);
}
