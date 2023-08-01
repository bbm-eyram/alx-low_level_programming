#include "lists.h"

/**
 * print_listint - Prints all  elements of a linked list
 * @head: Pointer to the head of the linked list
 *
 * Return: Number of nodes of linked list
 */
size_t print_listint(const listint_t *head)
{
	size_t num = 0;

	while (head)
	{
		printf("%d\n", head->n);
		num++;
		head = head->next;
	}

	return (num);
}

