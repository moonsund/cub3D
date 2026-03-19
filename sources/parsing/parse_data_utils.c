#include "cub3d.h"

int set_texture(char **dst, char *str)
{
    if (*dst != NULL)
        return (error_msg("set_texture: duplicated texture id\n"));
    if (validate_texture_arg(str))
        return (1);

    *dst = ft_strdup(str);
    if (*dst == NULL)
        return (error_errno("set_texture"));
    return (0);
}

int validate_texture_arg(char *path)
{
    int fd;
    int path_len;

    path_len = ft_strlen(path);

    if (path_len < 5)
        return (error_msg("validate_texture_arg: invalid file path\n"));

    if (ft_strncmp(&path[path_len - 4], ".xpm", 4) != 0)
        return (
            error_msg("validate_texture_arg: invalid file extension\n"));

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (error_errno("validate_texture_arg"));
    close(fd);

    return (0);
}

int set_colour(const char *str, int *dst)
{
    char **tmp;

    if (*dst != -1)
        return (error_msg("set_colours: duplicated colour id"));

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

int validate_colour_args(char **arr)
{
    int i;
    int j;

    i = 0;
    if (!arr[0] || !arr[1] || !arr[2] || arr[3])
        return (error_msg("set_colours: invalid colour line format"));

    while (i < 3)
    {
        if (arr[i][0] == '\0')
            return (error_msg("validate_colour_args: empty component"));
        j = 0;
        while (arr[i][j])
        {
            if (!ft_isdigit(arr[i][j]))
                return (error_msg("validate_colour_args: is not digit"));
            j++;
        }
        if (ft_atoi(arr[i]) < 0 || ft_atoi(arr[i]) > 255)
            return (error_msg("validate_colour_args: out of range"));
        i++;
    }
    return (0);
}

void free_split(char **arr)
{
    size_t i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}