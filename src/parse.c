#include "cub3d.h"

static int read_file(const char* file_path, t_map* map);
static int procces_data_read(t_map* map);
static int parse_texture_line(t_map* map, char* str);
static int parse_colour_line(t_map* map, char* str);
static int get_map_data(t_map* map, int i);

int fill_map(const char* file_path, t_map* map)
{
    initialize_map(map);

    if (count_lines_in_file(file_path, &map->lines_count) != 0)
        return (1);

    map->file_data = malloc(sizeof(char*) * (map->lines_count + 1));
    if (!map->file_data)
        return (error_errno("fill_map"));

    if (read_file(file_path, map) != 0)
        return (1);

    if (procces_data_read(map) != 0)
        return (1);

    // if (!validate_data(map));
    // 	return (1);
    return (0);
}

static int read_file(const char* file_path, t_map* map)
{
    int fd;
    char* line;
    size_t i;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (error_errno("read_file"));
    i = 0;
    while (i < map->lines_count)
    {
        line = get_next_line(fd);
        map->file_data[i] = trim_if_needed(line);
        free(line);
        if (!map->file_data[i])
            return (close(fd), free_file_data(map->file_data, i),
                    error_errno("read_file"));
        i++;
    }
    map->file_data[i] = NULL;
    close(fd);
    return (0);
}

static int procces_data_read(t_map* map)
{
    size_t i;
    int params;
    char* line;

    i = 0;
    params = 0;
    while (map->file_data[i] && params < 6)
    {
        line = map->file_data[i];

        if (line[0] == '\n' || line[0] == '\0')
        {
            i++;
            continue;
        }

        if (is_texture_identifier(line))
        {
            if (parse_texture_line(map, line) != 0)
                return (1);
            params++;
        }
        else if (is_color_identifier(line))
        {
            if (parse_colour_line(map, line) != 0)
                return (1);
            params++;
        }
        else
            return (error_exit_msg("procces_data_read: data corrupted"));
        i++;
    }

    if (params < 6)
        return (error_exit_msg("procces_data_read: missing data"));

    get_map_data(map, i);
    return (0);
}

static int parse_texture_line(t_map* map, char* str)
{
    char** tmp;
    int return_code;

    tmp = ft_split(str, ' ');
    if (!tmp)
        return (error_errno("parse_texture_line: split"));

    if (!tmp[0] || !tmp[1] || tmp[2])
    {
        free_split(tmp);
        return (error_exit_msg("invalid texture line format"));
    }

    return_code = 0;
    if (ft_strncmp(tmp[0], "NO", 3) == 0)
        return_code = set_texture(&map->tex_N, tmp[1]);
    else if (ft_strncmp(tmp[0], "SO", 3) == 0)
        return_code = set_texture(&map->tex_S, tmp[1]);
    else if (ft_strncmp(tmp[0], "EA", 3) == 0)
        return_code = set_texture(&map->tex_E, tmp[1]);
    else if (ft_strncmp(tmp[0], "WE", 3) == 0)
        return_code = set_texture(&map->tex_W, tmp[1]);
    else
        return_code = error_exit_msg("unknown texture id");

    free_split(tmp);
    return (return_code);
}

static int parse_colour_line(t_map* map, char* str)
{
    char** tmp;
    int return_code;

    tmp = ft_split(str, ' ');
    if (!tmp)
        return (error_errno("get_colours_data: split"));

    if (!tmp[0] || !tmp[1] || tmp[2])
    {
        free_split(tmp);
        return (error_exit_msg("invalid colour line format"));
    }

    return_code = 0;
    if (tmp[0][0] == 'F' && tmp[0][1] == '\0')
        return_code = set_colour(tmp[1], &map->floor_color);
    else if (tmp[0][0] == 'C' && tmp[0][1] == '\0')
        return_code = set_colour(tmp[1], &map->ceiling_color);
    else
        return_code = error_exit_msg("unknown colour id");

    free_split(tmp);
    return (return_code);
}

static int get_map_data(t_map* map, int start_index)
{
    (void)map;
    (void)start_index;

    return (0);
}