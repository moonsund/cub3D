#include "cub3d.h"


int count_lines_in_file(const char *file_path, int *lines_count)
{
    int fd;
    int i;
    char *line;

    fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("count_lines: Could not open the file.\n"));

    line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("count_lines: The file is empty.\n"));
    
    i = 1;
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

void free_file_data(char **file_data, int i)
{
    (void)file_data;
    (void)i;

}