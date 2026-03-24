#include "cub3d.h"

void skip_empty_lines(char **lines, int *i)
{
    while (lines[*i])
    {
        if (line_is_empty(lines[*i]))
            (*i)++;
        else
            break;
    }
}

bool line_is_empty(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

void get_map_dimensions(char **lines, int *height, int *width, int i)
{
    int line_len;

    *height = 0;
    *width = 0;
    while (lines[i])
    {
        if (line_is_empty(lines[i]))
            break;
        line_len = ft_map_line_length(lines[i]);
		if (line_len > *width)
            *width = line_len;
        (*height)++;
        i++;
    }
}

int	ft_map_line_length(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n') 
		i++;
	return (i);
}

int check_trailing_content(char **lines, int i)
{
    while (lines[i])
    {
        if (!line_is_empty(lines[i]))
            return (error_msg("check_trailing_content: unexpected content after map"));
        i++;
    }
    return (SUCCESS);
}

int	validate_map_chars(char **lines, int i)
{
	int	j;

	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!(lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W'
				|| lines[i][j] == '0' || lines[i][j] == '1'
				|| lines[i][j] == ' ' || lines[i][j] == '\n'))
				return (error_msg("validate_map_chars: map contains forbidden character"));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
