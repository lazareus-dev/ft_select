/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_loop.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:48:51 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:12:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_lst.h"
#include "../includes/sel_move.h"
#include "../includes/sel_refresh.h"
#include "../includes/sel_select.h"
#include <termcap.h>

static void	toggle_selected(void)
{
	t_select	*select;

	select = get_select();
	select->cur->selected = !select->cur->selected;
	if (select->cur->selected)
	{
		select->cur->cursor = 0;
		select->cur->next->cursor = 1;
		select->cur = select->cur->next;
	}
}

static void	exit_clear(int code)
{
	(void)code;
	restore_term(NULL);
	clear_select();
	exit(0);
}

static void	keys(char buffer[])
{
	if (buffer[2] == 'A')
		move_up();
	else if (buffer[2] == 'B')
		move_down();
	else if (buffer[2] == 'C')
		move_down();
	else if (buffer[2] == 'D')
		move_up();
	else if (buffer[2] == 'H')
		move_first();
	else if (buffer[2] == 'F')
		move_last();
	else if (buffer[1] == 0)
		exit_clear(0);
}

int			sel_loop(void)
{
	char	buffer[4];

	while (101)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 3);
		if (buffer[0] == 127 || (buffer[0] == 27 && buffer[2] == '3'))
		{
			if (delete_elem())
				exit_clear(0);
		}
		else if (buffer[0] == 27)
			keys(buffer);
		else if (buffer[0] == '\n')
			return (0);
		else if (buffer[0] == ' ')
			toggle_selected();
		sel_refresh(NULL);
	}
	return (0);
}
