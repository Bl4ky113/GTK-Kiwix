/*
 * =====================================================================================
 *       Filename:  double_linked_list.c
 *    Description:	File of the data structure: Double-LinkedList
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#include <double_linked_list.h>

#include <stdlib.h>

/**
 * Creates a simple node for a Double Linked List
 * @param{int} index - index of the current node
 * @param{char *} url - url of the current node
 * @param{Node *} next - next node in the list
 * @param(Node *) prev - previous node in the list
 * @return{Node *} pointer of the Node of a double linkedlist Created
 **/
Node *create_list_node (int index, char *url, Node *next, Node *prev) {
	Node *new_node = (Node*) malloc(sizeof(Node));

	new_node->index = index;
	new_node->url = url;
	new_node->next = next;
	new_node->prev = prev;

	return new_node;
}

/**
 * Add a node in a list of nodes
 * @param{Node *} head - head or top of the linked list
 * @param{char *} url - url string to store
 * @return{Node *} ptr of the added node
 **/
Node *add_list_node (Node *head, char *url) {
	Node *new_node = create_list_node(
		head->index + 1,
		url,
		head->next,
		head
	);

	head->next = new_node;
	return new_node;
}
