#include "simple_shell.h"
/**
 * unique_inc_node -A function that inserts a node to the
 * beginning of a linked list
 * @add: head node's pointer address
 * @st: field string of the new node
 * @in: Numeric index related to the history node.
 * Return: linked list size after insertion
 */
unique_list_t *unique_inc_node(unique_list_t **add, const char *st, int in)
{
unique_list_t *new_add;
if (!add)
return (NULL);
new_add = malloc(sizeof(unique_list_t));
if (!new_add)
return (NULL);
custom_shell_memset((void *)new_add, 0, sizeof(unique_list_t));
new_add->in = in;
if (st)
{
new_add->st = custom_gen_strdup(st);
if (!new_add->st)
{
free(new_add);
return (NULL);
}
}
new_add->next = *add;
*add = new_add;
return (new_add);
}
/**
 * unique_inc_node_fin - A function that appends
 * a node to the very end of a linked list
 * @add: head node's pointer address
 * @st: field cstring of the new node
 * @in: Numeric index related to the history node
 * Return:  The Size of the linked list after appending
 */
unique_list_t *unique_inc_node_fin(unique_list_t **add, const char *st, int in)
{
unique_list_t *inc_node, *node;
if (!add)
return (NULL);
node = *add;
inc_node = malloc(sizeof(unique_list_t));
if (!inc_node)
return (NULL);
custom_shell_memset((void *)inc_node, 0, sizeof(unique_list_t));
inc_node->in = in;
if (st)
{
inc_node->st = custom_gen_strdup(st);
if (!inc_node->st)
{
free(inc_node);
return (NULL);
}
}
if (node)
{
while (node->next)
{
node = node->next;
}
node->next = inc_node;
}
else
{
*add = inc_node;
}
return (inc_node);
}
/**
 * custom_disp_ls_beg - A function that displays only the string element of
 * a list_t linked list
 * @p: Points to the first node
 * Return: Size of the linked list
 */
size_t custom_disp_ls_beg(const unique_list_t *p)
{
size_t x = 0;
while (p)
{
custom_gen_puts(p->str ? p->str : "(nil)");
custom_gen_puts("\n");
p = p->next;
x++;
}
return (x);
}
/**
 * custom_rem_node - A function that removes node
 * @add: The address of the pointer to first node
 * @in: Index of node that's to be deleted
 * Return: 1 if successful and  0 if it fails
 */
int custom_rem_node(unique_list_t **add, unsigned int in)
{
unique_list_t *node, *node_bef;
unsigned int x;
if (!add || !*add)
return (0);
if (!in)
{
node = *add;
*add = (*add)->next;
free(node->str);
free(node);
return (1);
}
node = *add;
for (x = 0; node; node = node->next, x++)
{
if (x == in)
{
node_bef->next = node->next;
free(node->str);
free(node);
return (1);
}
node_bef = node;
}
return (0);
}
/**
 * custom_rel_lst - A function that releases the entire nodes of a linked list
 * @add: The head node's pointer address
 * Return: void
 */
void custom_rel_lst(unique_list_t **add)
{
unique_list_t *node, *node_aft, *ab;
if (!add || !*add)
return;
ab = *add;
node = ab;
for (; node; node = node_aft)
{
node_aft = node->next;
free(node->str);
free(node);
}
*add = NULL;
}
