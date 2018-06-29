/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_refresh.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 14:53:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 15:19:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_display.h"
#include <termcap.h>
#include <sys/ioctl.h>

int		set_winsize(t_select *select)
{
	if (!select)
		select = get_select();
	ioctl(0, TIOCGWINSZ, &(select->win));
	return (0);
}

void	sel_refresh(t_select *select)
{
	if (!select)
		select = get_select();
	tputs(tgetstr("cl", NULL), 0, ft_putchar_term);
	set_winsize(select);
	display_list(select->arglst);
}
