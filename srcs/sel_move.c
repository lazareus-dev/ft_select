/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_move.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/01 14:45:08 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 14:48:20 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"

void	move_up(void)
{
	t_select	*select;

	select = get_select();
	select->cur->cursor = 0;
	select->cur = select->cur->prev;
	select->cur->cursor = 1;
}

void	move_down(void)
{
	t_select	*select;

	select = get_select();
	select->cur->cursor = 0;
	select->cur = select->cur->next;
	select->cur->cursor = 1;
}

void	move_first(void)
{
	t_select	*select;

	select = get_select();
	select->cur->cursor = 0;
	select->cur = select->arglst->first;
	select->cur->cursor = 1;
}

void	move_last(void)
{
	t_select	*select;
	t_elem		*first;

	select = get_select();
	first = select->arglst->first;
	select->cur->cursor = 0;
	select->cur = first->prev;
	select->cur->cursor = 1;
}
