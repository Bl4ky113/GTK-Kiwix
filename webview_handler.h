/*
 * =====================================================================================
 *       Filename:  webview_handler.h
 *    Description: Header file of the WebView general Handling 
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef WEBVIEW_HANDLER_H
#define WEBVIEW_HANDLER_H

/**
 * Starts a dobule linkedlist to use in the GUI
 * @param{char *} url - url starting the linked list
 * @return{void}
 **/
void init_url_double_linked_list (char *url);

/**
 * Sets the WebView URI to the Kiwix URL.
 * @param{WebKitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void set_url_to_kiwix_server (WebKitWebView *webview);

/**
 * Returns the WebView 1 url in the linkedlist
 * @return{void}
 **/
int change_url_to_previous_url ();

/**
 * Fowards the WebView 1 url in the linkedlist
 * @return{void}
 **/
int change_url_to_next_url ();

/**
 * Callback for the load-changed event, 
 * which is whenever the webview changes or loads someting.
 * This is used to see if the 'current_url' and the webview uri 
 * are different, then process them
 * @param{WebkitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void cb_webview_url_changed (WebKitWebView *webview);

/**
 * General Handling of the WebView Instance
 * @param{WebKitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void handle_webview (WebKitWebView *webview);

/**
 * Getter of the webview pointer
 * @return{WebKitWebView *} ptr of the webview instance
 **/
WebKitWebView *get_webview_ptr ();

#endif
