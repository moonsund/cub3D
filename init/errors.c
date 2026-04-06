/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:01:19 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:44:30 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_errno(const char *context)
{
	print_error_marker();
	perror(context);
	return (FAILURE);
}

int	error_msg(const char *error_message)
{
	print_error_marker();
	if (error_message)
		write(2, error_message, ft_strlen(error_message));
	return (FAILURE);
}

void	print_error_marker(void)
{
	write(2, "Error\n", 6);
}
