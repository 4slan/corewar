/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_inst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:27:06 by amalsago          #+#    #+#             */
/*   Updated: 2020/06/14 21:30:22 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cw_inst.h"
#include "cw_op.h"

void			cw_inst_init(t_cw_inst *inst)
{
	ft_bzero(inst, sizeof(t_cw_inst));
}

int				cw_inst_fill(t_cw_inst *inst, t_cw_vm *vm, t_cw_game *game)
{
	unsigned	i;

	i = -1;
	cw_inst_init(inst);
	inst->opc = vm->arena[game->procs->pos + 0];
	if (cw_vm_is_valid_op(inst->opc))
		inst->has_coding_byte = (game->byte_codage[inst->opc - 1]) ? true : false;
	else
		return (CW_FAILURE);
	if (inst->has_coding_byte == true)
	{
		cw_inst_get_args(inst, vm->arena[game->procs->pos + 1]);
		while (++i < inst->args_count)
		{
			if (inst->args[i] == 0x01)
				inst->types[i] = T_REG;
			else if (inst->args[i] == 0x02)
				inst->types[i] = T_DIR;
			else if (inst->args[i] == 0x03)
				inst->types[i] = T_IND;
		}
	}
	return (CW_SUCCESS);
}

void			cw_inst_get_args(t_cw_inst *inst, unsigned opc)
{
	inst->args_count = 0;
	inst->args[0] = (opc >> 6) & 0x03;
	inst->args[1] = (opc >> 4) & 0x03;
	inst->args[2] = (opc >> 2) & 0x03;
	(inst->args[0]) ? inst->args_count += 1 : 0;
	(inst->args[1]) ? inst->args_count += 1 : 0;
	(inst->args[2]) ? inst->args_count += 1 : 0;
}

void			cw_inst_dump(t_cw_inst *inst)
{
	unsigned	i;
	char		*op_name;

	i = -1;
	op_name = cw_op_list()[inst->opc - 1].name;
	ft_printf("opc:           %d (%s)\n", inst->opc, op_name);
	ft_printf("has_coding_byte:  ", inst->opc);
	(inst->has_coding_byte == true) ? ft_printf("true") : ft_printf("false");
	ft_printf("\nargs_count:       %d\n", inst->args_count);
	(inst->args_count != 0) ? ft_printf("types:            ") : 0;
	while (++i < inst->args_count)
	{
		if (inst->types[i] == T_REG)
			ft_printf("T_REG");
		else if (inst->types[i] == T_DIR)
			ft_printf("T_DIR");
		else if (inst->types[i] == T_IND)
			ft_printf("T_IND");
		(i + 1 < inst->args_count) ? ft_putchar(' ') : ft_putchar('\n');
	}
}
