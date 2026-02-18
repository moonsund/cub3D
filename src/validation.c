#include "cub3d"

int validate_cli_args(int argc, char *file_name)
{
  if (argc != 2)
    {
        printf("Usage: %s <map_file>\n");
        return (1);
    }

    // argc == 2
    // расширение .cub
    // файл существует / открывается
    // это не директория
    // (иногда) можно прочитать
  
  return (0);
}