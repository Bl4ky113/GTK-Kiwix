/*
 * =====================================================================================
 *       Filename:  webview_handler.c
 *    Description:  Handler of the WebView Widget of WebKit2GTK 
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <webkit2/webkit2.h>

#include <stdio.h>
#include <string.h>

#include <webview_handler.h>

#include <consts.h>
#include <double_linked_list.h>
#include <kiwix_handler.h>
#include <gtk_gui.h>

WebKitWebView *webview_ptr = NULL;
Node *head_urls_list = NULL;
char *current_url = NULL;

/**
 * Starts a dobule linkedlist to use in the GUI
 * @param{char *} url - url starting the linked list
 * @return{void}
 **/
void init_url_double_linked_list (char *url) {
	head_urls_list = (Node *) malloc(sizeof(Node));

	head_urls_list = create_list_node(
		0,
		url,
		NULL,
		NULL
	);

	return;
}

/**
 * Set WebView URI to passed URL
 * @param{char *} url - url to change
 * @return {void}
 **/
void set_url (char *url) {
	webkit_web_view_load_uri(webview_ptr, url);
	current_url = url;

	return;
}

/**
 * Sets the WebView URI to the Kiwix URL.
 * @param{WebKitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void set_url_to_kiwix_server (WebKitWebView *webview) {
	char *kiwix_server_url = (char *) calloc(URL_BUFFER, sizeof(char));
	char port_str[INT_STRING_BUFFER];
	int port = 0;

	port = get_kiwix_server_port();
	sprintf(port_str, "%d", port);

	strcat(kiwix_server_url, SERVER_METHOD);
	strcat(kiwix_server_url, HOSTNAME);
	strcat(kiwix_server_url, ":");
	strcat(kiwix_server_url, port_str);
	strcat(kiwix_server_url, "/");

	webkit_web_view_load_uri(webview, kiwix_server_url);
	init_url_double_linked_list(kiwix_server_url);
	current_url = kiwix_server_url;
	return;
}

/**
 * Returns the WebView 1 url in the linkedlist
 * @return{void}
 **/
int change_url_to_previous_url () {
	if (head_urls_list->prev == NULL) {
		return 1;
	}

	Node *prev_node = head_urls_list->prev;

	head_urls_list = prev_node;
	set_url(head_urls_list->url);

	return 0;
}

/**
 * Fowards the WebView 1 url in the linkedlist
 * @return{void}
 **/
int change_url_to_next_url () {
	if (head_urls_list->next == NULL) {
		return 1;
	}

	Node *next_node = head_urls_list->next;

	head_urls_list = next_node;
	set_url(head_urls_list->url);

	return 0;
}

/**
 * Callback for the load-changed event, 
 * which is whenever the webview changes or loads someting.
 * This is used to see if the 'current_url' and the webview uri 
 * are different, then process them
 * @param{WebkitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void cb_webview_url_changed (WebKitWebView *webview) {
	char *new_url = (char *) calloc(URL_BUFFER, sizeof(char));
	new_url = webkit_web_view_get_uri(webview);

	if (strcmp(new_url, current_url) == 0) {
		// There's nothing to do
		return;
	}

	if (head_urls_list->next != NULL) {
		Node *deleted_node = NULL;
		deleted_node = head_urls_list->next;
		
		head_urls_list->next = NULL;

		free(deleted_node);
	}

	Node *new_node = add_list_node(head_urls_list, new_url);

	current_url = new_url;
	head_urls_list = new_node;
	return;
}

/**
 * General Handling of the WebView Instance
 * @param{WebKitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void handle_webview (WebKitWebView *webview) {
	webview_ptr = webview;

	set_url_to_kiwix_server(webview);

	g_signal_connect(webview, "load-changed", G_CALLBACK(cb_webview_url_changed), webview);

	return;
}

/**
 * Getter of the webview pointer
 * @return{WebKitWebView *} ptr of the webview instance
 **/
WebKitWebView *get_webview_ptr () {
	return webview_ptr;
}
