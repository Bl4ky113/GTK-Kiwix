/*
 * =====================================================================================
 *       Filename:  consts.h
 *    Description:  Constant Values in Gtk-Kiwix
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef CONSTNS_H
#define CONSTNS_H

#define DYNAMIC_ARRAY_BUFFER 16
#define INT_STRING_BUFFER 10
#define REGEX_BUFFER 32
#define TIME_BUFFER 26
#define TIME_FORMAT "%Y-%m-%d %H:%M:%S"

// GTK GUI
#define MAIN_TITLE "GTK Implementation of Kiwix"

// Kiwix Server Handler
#define HOSTNAME "localhost"
// Linux max port is 65.535, but yeah...
#define KIWIX_SERVER_PORT_MIN 1024
#define KIWIX_SERVER_PORT_MAX 10000 
#define PIPE_BUFFER 256
															
// XDG, INI, Config, Share and MORE Handler
#define XDG_DATA_HOME ".local/share/gtk-kiwix"
#define XDG_CONFIG_HOME ".config/gtk-kiwix"
#define KIWIX_MANAGE_PATH "/usr/bin/kiwix-manage "
#define KIWIX_SERVE_PATH "/usr/bin/kiwix-serve "
#define PATH_BUFFER 96

#endif
