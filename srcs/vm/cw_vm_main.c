/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vm_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:04:40 by jthierce          #+#    #+#             */
/*   Updated: 2020/06/04 23:54:39 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cw_vm.h"

int			main(int argc, char **argv)
{
	t_cw_data data;
	if (argc < 2)
		return (cw_vm_usage());
	cw_vm_parsing(argc - 1 , argv + 1, &data);
	return (CW_SUCCESS);
}
