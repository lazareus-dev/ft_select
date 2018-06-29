/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_keys.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 15:06:51 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 15:14:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
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

void    keys(char buffer[])
{
	if (buffer[2] == 'A')
		ft_putstr("^");
	else if (buffer[2] == 'B')
		ft_putstr("v");
	else if (buffer[2] == 'C')
		move_right();
	else if (buffer[2] == 'D')
		move_left();
	else if (buffer[2] == '3')
		ft_putendl("Delete");
	else if (buffer[2] == 'H')
		ft_putendl("Home");
	else if (buffer[2] == 'F')
		ft_putendl("End");
	else
		ft_putstr(&buffer[1]);
}

int     voir_touche()
{
	char	buffer[4];

	while (1)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 4);
		if (buffer[0] == 27)
			keys(buffer);
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
		else if (buffer[0] == '\n')
			return (0);
		else if (buffer[0] == ' ')
			ft_putendl("Select");
		else if (buffer[0] == 127)
			ft_putendl("Delete");
	}
	return (0);
}
