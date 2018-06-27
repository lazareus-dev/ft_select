/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_display.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:35:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 14:52:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_lst.h"

void	put_elem(t_elem *elem)
{
	if (elem->selected)
		ft_putstr(UNDERL);
	ft_putendl(elem->name);
}

void	display_list(t_headlst *head)
{
	t_elem	*elem;

	if (!head || !head->first)
		return ;
	elem = (t_elem*)(head->first);
	while (elem->next != (t_elem*)(head->first))
	{
		put_elem(elem);
		elem = elem->next;
	}
	put_elem(elem);
}
