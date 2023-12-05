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
 * WHY? This program is heavily dependant in WebKit2GTK, exactly with the WebView Widget,
 * widget which IS NOT AVAILABLE FOR THE GTK VERSION OF WINDOWS
 *
 *********************************/

// GNU Libc Libs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

// GTK GUI Libs
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <webkit2/webkit2.h>

// Server, Net, Ports and such Libs
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <config_handler.h>
#include <kiwix_handler.h>
#include <gtk_gui.h>

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
	fprintf(stdout, "START LOAD/CHECK USER CONFIG\n");
	/*check_user_config();*/
	fprintf(stdout, "DONE LOAD/CHECK USER CONFIG\n");

	// Start Kiwix Server
	fprintf(stdout, "SERVER SERVER CONFIG/START\n");
	start_server();
	fprintf(stdout, "DONE SERVER CONFIG/START\n");

	// Init GTK GUI
	fprintf(stdout, "STARTING GUI\n");
	init_gui(argc, argv);
	fprintf(stdout, "DONE STARTING GUI. NOW CLOSING GUI\n\n");
	fprintf(stdout, "BYE BYE <3\n");

	return 0;
}
