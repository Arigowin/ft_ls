#include "ft_ls.h"
#include <stdlib.h>

void	ft_init_t_ft_ls(t_ft_ls *data)
{
	data->path = NULL;
	data->op_recu = 0;
	data->op_a = 0;
	data->op_l = 0;
	data->op_r = 0;
	data->op_t = 0;
	data->nb_path = 0;
}

void	ft_init_t_elem(t_elem *elem)
{
	elem->name = NULL;
	elem->droit = NULL;
	elem->nlink = NULL;
	elem->uid = NULL;
	elem->grp = NULL;
	elem->size = NULL;
	elem->date = NULL;
	elem->sec_date = NULL;
	elem->rdevmineur = NULL;
	elem->rdevmajeur = NULL;
	elem->link = NULL;
	elem->type = 0;
	elem->nbelem = 0;
}
