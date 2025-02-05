/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 06:05:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/03 06:05:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quoted(char c, char *q)
{
	char	prev;

	prev = *q;
	if (c == '\'' || c == '\"')
	{
		if (!*q)
			*q = c;
		else if (c == *q)
			*q = 0;
	}
	return (prev != *q);
}

static char	**ft_split_quotes_word(char *str, t_norm *s)
{
	s->j = 0;
	while (str && str[s->i] && (str[s->i] != ' ' || s->q))
	{
		if (!quoted(str[s->i], &s->q))
			s->split[s->k][s->j++] = str[s->i];
		s->i++;
		s->split[s->k][s->j] = 0;
		if (s->j + 1 == (int)s->cap)
			s->split[s->k] = ft_realloc
				(s->split[s->k], s->j, s->cap * 2, &s->cap);
		if (!s->split[s->k])
			return (ft_split_free(s->split));
	}
	s->split[++s->k] = NULL;
	return (s->split);
}

static char	**ft_split_quotes_norm(char *str, t_norm *s)
{
	while (str && str[s->i])
	{
		while (str[s->i] == ' ')
			s->i++;
		s->cap = DEFAULT_CAP;
		if (str[s->i])
			s->split[s->k] = (char *)ft_malloc(s->cap * sizeof(char));
		if (!s->split[s->k])
			return (ft_split_free(s->split));
		ft_split_quotes_word(str, s);
		if (s->k + 1 == (int)s->cap2 && s->split)
			s->split = ft_split_realloc(s->split, s->cap2 * 2, &s->cap2);
		if (!s->split)
			return (NULL);
	}
	return (s->split);
}

char	**ft_split_quotes(char *str)
{
	t_norm	s;

	s.i = 0;
	s.k = 0;
	s.cap2 = DEFAULT_CAP;
	s.q = 0;
	s.split = (char **)ft_malloc(s.cap2 * sizeof(char *));
	if (!s.split)
		return (NULL);
	return (ft_split_quotes_norm(str, &s));
}

/*
char	**ft_split_quotes(const char *str, char d)
{
	char	**ret;
	//int		i[6];
	int	i = 0;//i[0]
	int	j = 0;//i[1]
	int	k = 0;//i[2]
	int	q = 0;//i[3]
	int	cap;//i[4]
	int	cap2;//i[5]

	//ft_bzero(i, sizeof(i));
	cap2 = DEFAULT_CAP;
	ret = (char **)ft_malloc(cap2 * sizeof(char *));
	if (!ret)
		return (NULL);
	while (str && str[i])
	{
		while (str[i] == ' ' || str[i] == d)
			i++;
		cap = DEFAULT_CAP;
		if (str[i])
			ret[k] = (char *)ft_malloc(cap * sizeof(char));
		if (!ret[k])
			return (ft_split_free(ret));
		ret[k] = ft_splitword();
		if (!ret)
			return (NULL);
	}
	return (ret);
}


str[i]
ret[k][j]
k, cap2
j, cap


typedef struct s_norm
{
	char	**split;
	char	*word;
	char	c;
	char	q;
	int		i;
	int		j;
	int		k;
	size_t	cap;
	size_t	cap2;
}	t_norm;


static char	**ft_split_quotes_norm(char *str, t_norm *s)
{
	while (str && str[s->i])
	{
		while (str[s->i] == ' ')
			s->i++;
		s->cap = DEFAULT_CAP;
		if (str[s->i])
			s->split[s->k] = (char *)ft_malloc(s->cap * sizeof(char));
		if (!s->split[s->k])
			return (ft_split_free(s->split));
		ft_split_quotes_word(str, s);
		if (s->k + 1 == (int)s->cap2 && s->split)
			s->split = ft_split_realloc(s->split, s->cap2 * 2, &s->cap2);
		if (!s->split)
			return (NULL);
	}
	return (s->split);
}

char	**ft_split_quotes(char *str, char d)
{
	t_norm	s;

	s.i = 0;
	s.k = 0;
	s.cap2 = DEFAULT_CAP;
	s.q = 0;
	s.split = (char **)ft_malloc(s.cap2 * sizeof(char *));
	if (!s.split)
		return (NULL);
	return (ft_split_quotes_norm(str, &s));
}*/