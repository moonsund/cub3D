#include "cub3d.h"

void initialize_map(t_map* map);
int count_lines_in_file(const char* file_path, size_t* lines_count);
char* trim_if_needed(char* str);
int set_texture(char** target, char* str);
int validate_texture_arg(char* path);
void free_split(char** arr);
bool is_texture_identifier(char* str);
bool is_color_identifier(char* str);
void free_file_data(char** file_data, int i);
int set_colour(const char* str, int* dst);
int validate_colour_args(char** arr);

void initialize_map(t_map* map)
{
    map->lines_count = 0;
    map->file_data = NULL;
    map->tex_N = NULL;
    map->tex_E = NULL;
    map->tex_S = NULL;
    map->tex_W = NULL;
    map->ceiling_color = -1;
    map->floor_color = -1;
    map->grid = NULL;
    map->map_height = 0;
    map->map_width = 0;
    map->player_dir = ' ';
    map->player_x = -1;
    map->player_y = -1;
}

int count_lines_in_file(const char* file_path, size_t* lines_count)
{
    int fd;
    int i;
    char* line;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (error_errno("count_lines"));

    line = get_next_line(fd);
    if (!line)
        return (close(fd), error_exit_msg("count_lines: The file is empty.\n"));

    i = 0;
    while (line)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }

    *lines_count = i;
    close(fd);
    return (0);
}

char* trim_if_needed(char* str)
{
    size_t i;

    if (!str)
        return (NULL);

    i = 0;
    while (str[i] == ' ')
        i++;

    if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E' ||
        str[i] == 'F' || str[i] == 'C')
        return (ft_strtrim(str, " \n\t"));

    return (ft_strdup(str));
}

int set_texture(char** dst, char* str)
{
    if (*dst != NULL)
        return (error_exit_msg("set_texture: duplicated texture id\n"));
    if (validate_texture_arg(str))
        return (1);

    *dst = ft_strdup(str);
    if (*dst == NULL)
        return (error_errno("set_texture"));
    return (0);
}

int validate_texture_arg(char* path)
{
    int fd;
    int path_len;

    path_len = ft_strlen(path);

    if (path_len < 5)
        return (error_exit_msg("validate_texture_arg: invalid file path\n"));

    if (ft_strncmp(&path[path_len - 4], ".xpm", 4) != 0)
        return (
            error_exit_msg("validate_texture_arg: invalid file extension\n"));

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (error_errno("validate_texture_arg"));
    close(fd);

    return (0);
}

void free_split(char** arr)
{
    size_t i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

bool is_texture_identifier(char* str)
{
    return (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) ||
            !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2));
}

bool is_color_identifier(char* str)
{
    return (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1));
}

void free_file_data(char** file_data, int i)
{
    (void)file_data;
    (void)i;
}

int set_colour(const char* str, int* dst)
{
    char** tmp;

    if (*dst != -1)
        return (error_exit_msg("set_colours: duplicated colour id"));

    tmp = ft_split(str, ',');
    if (!tmp)
        return (error_errno("set_colours: split"));

    if (validate_colour_args(tmp))
    {
        free_split(tmp);
        return (1);
    }

    *dst = (ft_atoi(tmp[0]) << 16) | (ft_atoi(tmp[1]) << 8) | ft_atoi(tmp[2]);
    free_split(tmp);
    return (0);
}

int validate_colour_args(char** arr)
{
    int i;
    int j;

    i = 0;
    if (!arr[0] || !arr[1] || !arr[2] || arr[3])
        return (error_exit_msg("set_colours: invalid colour line format"));

    while (i < 3)
    {
        if (arr[i][0] == '\0')
            return (error_exit_msg("validate_colour_args: empty component"));
        j = 0;
        while (arr[i][j])
        {
            if (!ft_isdigit(arr[i][j]))
                return (error_exit_msg("validate_colour_args: is not digit"));
            j++;
        }
        if (ft_atoi(arr[i]) < 0 || ft_atoi(arr[i]) > 255)
            return (error_exit_msg("validate_colour_args: out of range"));
        i++;
    }
    return (0);
}
