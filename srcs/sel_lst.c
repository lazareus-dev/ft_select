/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_lst.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:55:04 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 18:45:24 by tle-coza    ###    #+. /#+    ###.fr     */
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
		elem->cur = 1;
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
	elem->cur = 0;
	elem->name = name;
	return (elem);
}

int		delete_elem(void)
{
	t_select	*select;
	t_elem		*to_del;
	t_elem		*next;
	t_elem		*first;

	select = get_select();
	to_del = select->cur;
	next = to_del->next;
	first = select->arglst->first;
	if (first == to_del)
		select->arglst->first = next;
	to_del->prev->next = next;
	next->prev = to_del->prev;
	if (next->prev == next)
		return (1);
	select->cur = next;
	next->cur = 1;
	free(to_del);
	sel_refresh(select);
	return (0);
}

int		init_arglst(t_select *select, int ac, char **av)
{
	t_elem		*elem;
	t_headlst	*lst;

	lst = select->arglst;
	lst->first = NULL;
	while (--ac)
	{
		if ((elem = new_elem(*++av)) == NULL)
			return (-1);
		push_back(&lst, elem);
	}
	select->cur = lst->first;
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
		if (node->selected)
		{
			ft_putstr(node->name);
			ft_putchar(' ');
		}
		node = node->next;
	}
	if (node->selected)
		ft_putstr(node->name);
	ft_putchar('\n');
}

void	free_arglst(t_headlst *arglst)
{
	t_elem	*curr;
	t_elem	*tmp;
	t_elem	*first;

	if (!arglst)
		return ;
	first = arglst->first;
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
