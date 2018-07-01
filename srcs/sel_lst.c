/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_lst.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:55:04 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:33:02 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_refresh.h"
#include "../includes/sel_utils.h"

static void		push_back(t_headlst **head, t_elem *elem)
{
	t_elem	*run;

	if ((*head)->first == NULL)
	{
		(*head)->first = elem;
		elem->next = elem;
		elem->prev = elem;
		elem->cursor = 1;
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

static t_elem	*new_elem(char *name)
{
	t_elem	*elem;

	if (!(elem = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	elem->prev = NULL;
	elem->next = NULL;
	elem->selected = 0;
	elem->cursor = 0;
	elem->name = name;
	return (elem);
}

int				delete_elem(void)
{
	t_select	*select;
	t_elem		*first;
	t_elem		*to_del;
	t_elem		*next;
	t_elem		*prev;

	select = get_select();
	first = select->arglst->first;
	to_del = select->cur;
	next = to_del->next;
	prev = to_del->prev;
	if (to_del == next)
		return (1);
	if (first == to_del)
		select->arglst->first = next;
	prev->next = next;
	next->prev = prev;
	next->cursor = 1;
	select->cur = next;
	free(to_del);
	select->arglst->nb_node -= 1;
	select->disp.max_len = max_len(select->arglst) + 2;
	sel_refresh(select);
	return (0);
}

int				init_arglst(t_select *select, int ac, char **av)
{
	t_elem		*elem;
	t_headlst	*lst;

	lst = select->arglst;
	select->arglst->nb_node = 0;
	lst->first = NULL;
	while (--ac)
	{
		if ((elem = new_elem(*++av)) == NULL)
			return (-1);
		push_back(&lst, elem);
		select->arglst->nb_node += 1;
	}
	select->cur = lst->first;
	select->disp.max_len = max_len(lst) + 2;
	return (0);
}

void			free_arglst(t_headlst *arglst)
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
