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

// GTK GUI
#define MAIN_TITLE "GTK Implementation of Kiwix"

// Kiwix Server Handler
#define HOSTNAME "localhost"
#define KIWIX_SERVER_PORT_MIN 1024
#define KIWIX_SERVER_PORT_MAX 10000 // Linux max is 65.535, but yeah...
															
// XDG, INI, Config, Share and MORE Handler
#define XDG_DATA_HOME ".local/share/gtk-kiwix"
#define XDG_CONFIG_HOME ".config/gtk-kiwix"

#endif
