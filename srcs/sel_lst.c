/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_lst.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:55:04 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 14:55:10 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../libft/ft_printf/ft_printf.h"

void	push_back(t_headlst **head, t_elem *elem)
{
	t_elem   *run;

	if ((*head)->first == NULL)
	{
		(*head)->first = elem;
		elem->next = elem;
		elem->prev = elem;
	}
	else
	{
		run = (*head)->first;
		elem->prev = run->prev;
		run->prev = elem;
		elem->prev->next = elem;
		elem->next = run;
	}
}

t_elem	*new_elem(char *name)
{
	t_elem	*elem;

	if (!(elem = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	elem->prev = NULL;
	elem->next = NULL;
	elem->selected = 0;
	elem->name = name;
	return (elem);
}

int		init_arglst(t_headlst *lst, int ac, char **av)
{
	t_elem	*elem;

	lst->first = NULL;
	while (--ac)
	{
		if ((elem = new_elem(*++av)) == NULL)
			return (-1);
		push_back(&lst, elem);
	}
	return (0);
}

void	echo_result()
{
	t_select	*select;
	t_elem		*node;
	t_elem		*first;

	select = get_select();
	node = select->arglst->first;
	first = select->arglst->first;
	while (node != first->prev)
	{
		ft_putstr(node->name);
		ft_putchar(' ');
		node = node->next;
	}
	ft_putstr(node->name);
}

void	free_arglst(t_headlst *arglst)
{
	t_elem	*curr;
	t_elem	*tmp;
	t_elem	*first;

	if (!arglst)
		return ;
	first = (arglst)->first;
	curr = first->next;
	while (curr != first)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	free(first);
	free(arglst);
}
