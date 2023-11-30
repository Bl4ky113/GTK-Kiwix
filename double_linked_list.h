/*
 * =====================================================================================
 *       Filename:  double_linked_list.h
 *    Description:  Header file of the data structure Double LinkedList
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct Node {
	int index;
	char *url;
	struct Node *next;
	struct Node *prev;
} Node;


/**
 * Add a node in a list of nodes
 * @param{Node *} head - head or top of the linked list
 * @param{char *} url - url string to store
 * @return{Node *} ptr of the added node
 **/
Node *add_list_node (Node *head, char *url);

/**
 * Creates a simple node for a Double Linked List
 * @param{int} index - index of the current node
 * @param{char *} url - url of the current node
 * @param{Node *} next - next node in the list
 * @param(Node *) prev - previous node in the list
 * @return{Node *} pointer of the Node of a double linkedlist Created
 **/
struct Node*create_list_node (int index, char *url, struct Node*next, struct Node*prev);

#endif
