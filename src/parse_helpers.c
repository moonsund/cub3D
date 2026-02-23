#include "cub3d.h"


int count_lines_in_file(const char *file_path, size_t *lines_count)
{
    int fd;
    int i;
    char *line;

    fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (error_errno("count_lines"));

    line = get_next_line(fd);
	if (!line)
		return (close(fd), error_msg("count_lines: The file is empty.\n"));
    
    i = 0;
    while(line)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }

    *lines_count = i;
    close(fd);
    return (0);
}

char *trim_if_needed(char *str)
{
    size_t  i;

    if (!str)
        return (NULL);

    i = 0;
    while (str[i] == ' ')
        i++;

    if (str[i] == 'N' || str[i] == 'S'
        || str[i] == 'W' || str[i] == 'E'
        || str[i] == 'F' || str[i] == 'C')
        return (ft_strtrim(str, " \n\t"));

    return (ft_strdup(str));
}



		



void free_file_data(char **file_data, int i)
{
    (void)file_data;
    (void)i;

}

