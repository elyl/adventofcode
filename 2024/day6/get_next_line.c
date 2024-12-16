#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILE_BUFFER_SIZE (1 << 10)
#define BUFFER_SIZE FILE_BUFFER_SIZE / 4
#define READ_THRESHOLD BUFFER_SIZE

char *get_next_line(int fd)
{
  static char	file_buffer[FILE_BUFFER_SIZE];
  char		buffer[BUFFER_SIZE];
  char		*output;
  static int	file_buffer_current_size = 0;
  int		line_size;
  int		read_code;
  char		*ptr;

  if (file_buffer_current_size < READ_THRESHOLD)
    {
      read_code = read(fd, buffer, BUFFER_SIZE - 1);
      if (read_code < 0 || (read_code == 0 && file_buffer_current_size == 0))
	return (NULL);
      buffer[read_code] = '\0';
      strcpy(&file_buffer[file_buffer_current_size], buffer);
      file_buffer_current_size += read_code;
    }
  ptr = strchr(file_buffer, '\n');
  if (ptr == NULL)
    return (get_next_line(fd));
  *ptr = '\0';
  line_size = strlen(file_buffer) + 1;
  output = malloc(line_size * sizeof(char));
  strcpy(output, file_buffer);
  memmove(file_buffer, ptr + 1, file_buffer_current_size - line_size);
  file_buffer_current_size -= line_size;
  return (output);
}
