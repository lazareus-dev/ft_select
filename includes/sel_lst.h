/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_lst.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/21 16:21:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 16:57:42 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SEL_LST_H
# define SEL_LST_H

int		init_arglst(t_headlst *lst, int ac, char **av);
void	echo_result();
void	free_arglst(t_headlst *lst);

#endif
