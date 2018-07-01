/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_display.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:35:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:35:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_error.h"
#include <termcap.h>

/*
** Calculate the best ratio rows/columns for the display
*/

static int	rows_and_cols(t_select *select)
{
	int	max_col;

	if (!(max_col = select->disp.width / select->disp.max_len))
		return (-1);
	select->disp.nb_col = max_col;
	select->disp.nb_row = select->arglst->nb_node / max_col;
	if (select->disp.nb_row > select->disp.height - 2)
		return (-1);
	return (0);
}

static void	put_elem(t_elem *elem)
{
	if (ft_is_lnk(elem->name))
		ft_putstr_fd(PURP, 2);
	else if (ft_is_dir(elem->name))
		ft_putstr_fd(BLUE, 0);
	else
		ft_putstr_fd(GREEN, 0);
	ft_putstr_fd(BOLD, 0);
	if (elem->cursor)
		tputs(tgetstr("us", NULL), 1, ft_putchar_term);
	if (elem->selected)
		tputs(tgetstr("mr", NULL), 1, ft_putchar_term);
	ft_putendl_fd(elem->name, 0);
	if (elem->selected)
		tputs(tgetstr("se", NULL), 1, ft_putchar_term);
	if (elem->cursor)
		tputs(tgetstr("ue", NULL), 1, ft_putchar_term);
	ft_putstr_fd(RESET, 0);
}

static int	sel_dispatch(t_elem *elem, t_select *select, int i, int j)
{
	tputs(tgoto(tgetstr("cm", NULL), (j * select->disp.max_len), i),
			1, ft_putchar_term);
	i += 1;
	put_elem(elem);
	return (0);
}

int			display_list(t_select *select)
{
	t_elem		*elem;
	int			nb;
	int			i;
	int			j;

	if (!select->arglst || !(elem = (t_elem*)(select->arglst->first)))
		return (0);
	i = 0;
	j = 0;
	nb = select->arglst->nb_node;
	while (nb--)
	{
		if (rows_and_cols(select))
			return (disp_room_error());
		sel_dispatch(elem, select, i++, j);
		elem = elem->next;
		if (elem == (t_elem*)(select->arglst->first))
			break ;
		if (i > select->disp.nb_row)
		{
			i = 0;
			j++;
		}
	}
	return (0);
}
