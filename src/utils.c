#include "cub3d.h"

static void print_error_marker(void);

int error_errno(const char *context)
{
    print_error_marker();
    perror(context);
    return (1);
}

int error_exit_msg(const char *error_message)
{
    print_error_marker();
    if (error_message)
        write(2, error_message, ft_strlen(error_message));
    return (1);
}


void cleanup_game(t_game *game)
{
  (void)game;


}



void free_map(t_map *map)
{
    (void)map;



}

static void print_error_marker(void)
{
    write(2, "Error\n", 6);
}