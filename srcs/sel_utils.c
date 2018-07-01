/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/30 21:09:19 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 14:38:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"

size_t	max_len(t_headlst *head)
{
	t_elem	*elem;
	size_t	len;

	if (!head || !head->first)
		return (0);
	len = 0;
	elem = (t_elem*)(head->first);
	while (elem->next != (t_elem*)(head->first))
	{
		if (ft_strlen(elem->name) > len)
			len = ft_strlen(elem->name);
		elem = elem->next;
	}
	if (ft_strlen(elem->name) > len)
		len = ft_strlen(elem->name);
	return (len);
}

void	echo_result(void)
{
	t_select	*select;
	t_elem		*node;
	t_elem		*first;
	int			output;

	output = 0;
	select = get_select();
	node = select->arglst->first;
	first = select->arglst->first;
	while (node != first->prev)
	{
		if (node->selected)
		{
			output ? ft_putchar(' ') : 0;
			ft_putstr(node->name);
			output = 1;
		}
		node = node->next;
	}
	if (node->selected)
	{
		output ? ft_putchar(' ') : 0;
		ft_putstr(node->name);
	}
}
