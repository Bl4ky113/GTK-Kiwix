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

// Std and Libc Libs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// GTK Libs
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <webkit2/webkit2.h>

#include <gtk_gui.h>

// Enviroment Global Variables
char *XDG_DATA_HOME = "";
char *APP_FOLDER = "gtk-kiwix/";

// Kiwix Server Global Variables
int kiwix_server_port = 1024;

/**
 * @param {int} argc - number of arguments passed to the program
 * @param {char **} argv - list of strings with the args of the program
 * @returns {int}
 **/
int main (int argc, char **argv) {

	// Init GTK GUI
	init_gui(argc, argv);

	return 0;
}
