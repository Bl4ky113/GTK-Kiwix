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
 * Sets the WebView URI to the Kiwix URL.
 * @param{WebKitWebView *} webview - pointer of the webview instance
 **/
void set_uri_to_kiwix_server (WebKitWebView *webview);

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
