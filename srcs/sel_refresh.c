/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_refresh.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 14:53:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 14:37:50 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_display.h"
#include <termcap.h>
#include <sys/ioctl.h>

void	clear_screen(t_select *select)
{
	int	i;

	i = 0;
	while (i < select->disp.height)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, i), 1, ft_putchar_term);
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
		i++;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
}

int		set_winsize(t_select *select)
{
	struct winsize win;

	if (!select)
		select = get_select();
	ioctl(0, TIOCGWINSZ, &win);
	select->disp.width = win.ws_col;
	select->disp.height = win.ws_row;
	return (0);
}

void	sel_refresh(t_select *select)
{
	if (!select)
		select = get_select();
	clear_screen(select);
	set_winsize(select);
	display_list(select);
}
