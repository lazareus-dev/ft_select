/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_error.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/30 16:38:31 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 14:55:28 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		term_error(int type)
{
	if (type == TERM_NOT_SET)
		ft_putendl_fd("TERM not set", 2);
	else if (type == ACCESS_DB)
		ft_putendl_fd("Can't access termcap DB", 2);
	else if (type == TERM_NOT_FOUND)
		ft_putendl_fd("Terminal type not defined in DB", 2);
	return (-1);
}

int		disp_room_error(void)
{
	ft_putstr_fd("\e[1m\e[31m", 2);
	ft_putendl_fd("Expand!", 2);
	ft_putstr_fd(RESET, 2);
	return (-1);
}
