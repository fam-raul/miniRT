/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 21:01:08 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Counts whitespace-separated words in one line. */
static int	count_words(const char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line)
	{
		if (ft_isspace(*line))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		line++;
	}
	return (count);
}

/* Fills token array from input line after count_words allocation. */
static int	fill_words(const char *line, char **arr, int count)
{
	size_t	start;
	int		i;

	i = 0;
	while (i < count)
	{
		while (*line && ft_isspace(*line))
			line++;
		start = 0;
		while (line[start] && !ft_isspace(line[start]))
			start++;
		arr[i] = ft_substr(line, 0, start);
		if (!arr[i])
			return (1);
		line += start;
		i++;
	}
	return (0);
}

/* Extracts each space-delimited token into a newly allocated array. */
char	**split_spaces(const char *line, int *count)
{
	char	**arr;
	int		i;

	*count = count_words(line);
	arr = (char **)malloc(sizeof(char *) * (*count + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i <= *count)
		arr[i] = NULL;
	if (fill_words(line, arr, *count))
		return (free_split(arr), NULL);
	return (arr);
}

/* Frees a NULL-terminated array of strings. */
void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
