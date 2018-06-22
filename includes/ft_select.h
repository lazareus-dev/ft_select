/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:08:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 11:39:42 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include "../libft/ft_printf/ft_printf.h"

typedef struct termios t_ermios;

typedef struct		s_win
{
	unsigned int	col;
	unsigned int	row;
}					t_win;

typedef struct		s_select
{
	char			*buff;
	t_ermios		term;
	t_ermios		orig_termios;
	t_win			win;
	t_headlst		*arglst;
}					t_select;

typedef struct		s_elem
{
	char			*name;
	int				selected;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

#endif
