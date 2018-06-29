/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_loop.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:48:51 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 18:45:25 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_refresh.h"
#include "../includes/sel_lst.h"
#include <termcap.h>

void    move_right(void)
{
	t_select	*select;
	char		*move;

	select = get_select();
	move = tgetstr("nd", NULL);
	tputs(move, 0, ft_putchar_term);
}

void    move_left(void)
{
	t_select	*select;
	char		*move;

	select = get_select();
	move = tgetstr("le", NULL);
	tputs(move, 0, ft_putchar_term);
}

void	move_up(void)
{
	t_select	*select;

	select = get_select();
	select->cur->cur = 0;
	select->cur = select->cur->prev;
	select->cur->cur = 1;
	sel_refresh(select);
}

void	move_down(void)
{
	t_select	*select;

	select = get_select();
	select->cur->cur = 0;
	select->cur = select->cur->next;
	select->cur->cur = 1;
	sel_refresh(select);
}

void	toggle_selected(void)
{
	t_select	*select;

	select = get_select();
	select->cur->selected = !select->cur->selected;
	sel_refresh(select);
}

void    keys(char buffer[])
{
	if (buffer[2] == 'A')
		move_up();
	else if (buffer[2] == 'B')
		move_down();
	else if (buffer[2] == 'C')
		move_right();
	else if (buffer[2] == 'D')
		move_left();
	else if (buffer[2] == '3')
		delete_elem();
	else if (buffer[2] == 'H')
		ft_putendl("Home");
	else if (buffer[2] == 'F')
		ft_putendl("End");
	else
		ft_putstr(&buffer[1]);
}

int     sel_loop()
{
	char	buffer[4];

	while (101)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 4);
		if (buffer[0] == 27)
			keys(buffer);
		else if (buffer[0] == '\n')
			return (0);
		else if (buffer[0] == ' ')
			toggle_selected();
		else if (buffer[0] == 127)
		{
			if (delete_elem())
				exit (0);
		}
	}
	return (0);
}
