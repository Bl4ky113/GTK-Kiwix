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
#include <kiwix_handler.h>
#include <gtk_gui.h>

WebKitWebView *webview_ptr = NULL;
char *current_url = NULL;

/**
 * Sets the WebView URI to the Kiwix URL.
 * @param{WebKitWebView *} webview - pointer of the webview instance
 **/
void set_uri_to_kiwix_server (WebKitWebView *webview) {
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
	current_url = kiwix_server_url;
	return;
}

/**
 * Callback for the load-changed
 * 
 **/
void cb_webview_url_changed (WebKitWebView *webview) {
	char *new_url = (char *) calloc(URL_BUFFER, sizeof(char));
	new_url = webkit_web_view_get_uri(webview);

	if (new_url == current_url) {
		// There's nothing to do
		return;
	}

	return;
}

/**
 * General Handling of the WebView Instance
 * @param{WebKitWebView *} webview - pointer of the webview instance
 * @return{void}
 **/
void handle_webview (WebKitWebView *webview) {
	webview_ptr = webview;

	set_uri_to_kiwix_server(webview);

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
