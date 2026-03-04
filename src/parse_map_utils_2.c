#include "cub3d.h"

bool	ft_tabs_check(t_map *map, int i)
{
	char	*line;

	while (map->file_data[i])
	{
		line = map->file_data[i];
		//printf("linecheck passed i= [%d]\n", i);
		if (ft_strchr(line, '\t') != NULL)
			return (false);
		i++;
	}
	return (true);
}
