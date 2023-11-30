/*
 * =====================================================================================
 *       Filename:  gtk_gui.h
 *    Description:	Implementation of the GTK Graphical User Interface
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez
 *   Organization:  UNAL
 * =====================================================================================
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <webkit2/webkit2.h>

#include <consts.h>
#include <gtk_gui.h>

#include <kiwix_handler.h>

/**
 * Activates the main Window of the GTK App.
 * Resizes it to 3/4ths of the monitor display, and centers it.
 * @param{GtkApplication *} app - Main App of the Program
 * @return{void}
 **/
void activate_gui (GtkApplication *app) {
	GtkWidget *window = NULL;

	GdkDisplay *display = NULL;
	GdkMonitor *monitor = NULL;
	GdkRectangle *geometry;
	int window_width = 0;
	int window_height = 0;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), MAIN_TITLE);

	// Transform Window initial size to 3/4 of the screen's width and height.
	display = gdk_display_get_default();
	monitor = gdk_display_get_monitor(display, 0);

	gdk_monitor_get_geometry(monitor, geometry);

	window_width = 3 * (geometry->width / 4);
	window_height = 3 * (geometry->height / 4);

	gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_window_present(GTK_WINDOW(window));
	return;
}

/**
 * Inits the GTK Application and GUI, 
 * once activated, activates the rest of the GUI
 * @param{int} argc - number of arguments passed to the program
 * @param{char **} argv - vector of the arguments passed to the program
 * @return {int} GTK Application Status
 **/
int init_gui (int argc, char **argv) {
	GtkApplication *app = NULL;
	int status = 0;

	app = gtk_application_new("gui.main", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate_gui), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
