/*
 * =====================================================================================
 *       Filename:  main.c
 *    Description:  Main file of GTK Implementation of Kiwix
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

/*********************************
 *
 * WARNING
 * THIS PROGRAM __WILL__ __NOT__ __RUN__ in Windows
 *
 *********************************/

// GNU Libc Libs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>
#include <time.h>

// GTK GUI Libs
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <webkit2/webkit2.h>

// Server, Net, Ports and such Libs
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <kiwix_handler.h>
#include <gtk_gui.h>

// Enviroment Global Variables
char *XDG_DATA_HOME = "";
char *XDG_CONFIG_HOME = "";
char *APP_FOLDER = "gtk-kiwix/";

/**
 * Main function of the Program. 
 * First, checks and searches for custom Config, Share and some Envars
 * Second, starts the Kiwix Server,
 * Third, inits the GTK GUI
 * @param {int} argc - number of arguments passed to the program
 * @param {char **} argv - list of strings with the args of the program
 * @returns {int}
 **/
int main (int argc, char **argv) {
	// Check User Config

	// Start Kiwix Server
	start_server();

	// Init GTK GUI
	init_gui(argc, argv);

	return 0;
}
