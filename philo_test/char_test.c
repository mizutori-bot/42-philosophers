/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:19:40 by sho               #+#    #+#             */
/*   Updated: 2022/10/11 20:07:18 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

size_t	ft_strlen(const char *s)
{	
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	count_s;
	char	*s2;
	size_t	i;

	count_s = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * count_s + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < count_s)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int main(void)
{
	char	*msg;

	msg = "shobobo";
	printf("%s\n", msg);
	/* char *msg;

	msg = ft_strdup("shobobobobo");
	char *msg = ;
	printf("%s\n", msg);
	free(msg);
	msg = (char *)malloc(sizeof(char) * 12);
	msg = "shabibi";
	printf("%s\n", msg);
	free(msg); 
 */
}