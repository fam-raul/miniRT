/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/24 15:05:18 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	rt_error(const char *msg, int line_no)
{
	write(2, "Error\n", 6);
	if (line_no >= 0)
		printf("line %d: %s\n", line_no, msg);
	else
		printf("%s\n", msg);
	return (1);
}

static int	has_rt_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strcmp(path + len - 3, ".rt"));
}

static int	parse_content(t_scene *scene, char *content)
{
	size_t	start;
	size_t	i;
	int		line_no;
	char	*line;

	start = 0;
	i = 0;
	line_no = 1;
	while (1)
	{
		if (content[i] == '\n' || content[i] == '\0')
		{
			line = ft_substr(content, start, i - start);
			if (!line || parse_line(scene, line, line_no))
				return (free(line), 1);
			free(line);
			if (content[i] == '\0')
				break ;
			start = ++i;
			line_no++;
		}
		else
			i++;
	}
	return (0);
}

int	parse_scene(t_scene *scene, const char *path)
{
	char	*content;

	if (!has_rt_extension(path))
		return (rt_error("scene file extension must be .rt", -1));
	content = read_entire_file(path);
	if (!content)
		return (1);
	if (parse_content(scene, content))
		return (free(content), 1);
	free(content);
	return (0);
}
