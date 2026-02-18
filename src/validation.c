#include "cub3d.h"

static int has_cub_extension(char *filename);

int validate_arguments(int argc, char **argv)
{
  int fd;

  if (argc != 2)
    return (print_error("Usage: cub3d <map_file>\n"));

  if (!has_cub_extension(argv[1]))
    return (print_error("Invalid file extension\n"));

  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    return (print_error("Cannot open file"));
  
  close(fd);
  return (0);
}

static int has_cub_extension(char *filename)
{
  int filename_len;
  
  filename_len =  ft_strlen(filename);

  if (filename_len < 5)
    return (0);

  if (ft_strncmp(&filename[filename_len - 4], ".cub", 4) != 0)
    return (0);

  return (1);
}