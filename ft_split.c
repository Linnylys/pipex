/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:08:07 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/19 21:59:56 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	nbr_cal_word(char const *s, char c)
{
	int	i;
	int	nb;

	if (s[0] == c || s[0] == '\0')
		nb = 0;
	else
		nb = 1;
	i = 0;
	while (s[i] != '\0')
	{	
		if (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c)
			nb++;
		i++;
	}
	return (nb);
}

int	*get_nb_letter_word(char const *s, char c, int nb)
{
	int	i;
	int	j;
	int	*res;

	res = malloc((nb + 1) * sizeof(int));
	if (res == NULL)
		return (NULL);
	i = 0;
	if (s[0] == c)
		j = -1;
	else
		j = 0;
	res[0] = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			j++;
			res[j] = 0;
		}
		if (s[i] != c)
			res[j] = res[j] + 1;
		i++;
	}
	return (res);
}

void	free_tab_letter(char **res, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		free(res[i]);
		i++;
	}
}

char	**affect_mem_sentence(char const *s, char c, int nb)
{
	int			i;
	int			*nb_letter_word;
	char		**res;

	i = 0;
	res = malloc((nb + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	nb_letter_word = get_nb_letter_word(s, c, nb);
	while (i < nb)
	{
		res[i] = malloc((nb_letter_word[i] + 1) * sizeof(char));
		if (res[i] == NULL)
		{
			free_tab_letter(res, i);
			return (NULL);
		}
		i++;
	}
	res[nb] = NULL;
	free(nb_letter_word);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**sentence;
	int		k;

	if (s == NULL)
		return (NULL);
	sentence = affect_mem_sentence(s, c, nbr_cal_word(s, c));
	if (sentence == NULL)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	while (s[++i] != '\0')
	{
		if ((s[i] == c && i != 0 && s[i - 1] != c) && ++j)
			k = 0;
		if (s[i] != c)
		{
			sentence[j][k] = s[i];
			sentence[j][++k] = '\0';
		}
	}
	return (sentence);
}
