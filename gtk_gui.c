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

#include <gtk_gui.h>

#include <consts.h>
#include <kiwix_handler.h>
#include <webview_handler.h>

GtkWidget *window_ptr = NULL;

int fullscreen = 0;

/**
 * Adds to the GUI the main attraction
 * the WebViewer, from the lib Webkit2GTK-4.1!!!,
 * to the notebook or the right section of the GUI.
 * @param{GtkWidget *} notebook - pointer of the right section wrapper, or notebook, widget
 * @return{void}
 **/
void add_webview_to_notebook (GtkWidget *notebook) {
	WebKitWebView *webview = NULL; 
	WebKitSettings *webview_settings = NULL;
	GtkWidget *label_new_page = NULL;
	int notebook_new_page_index = 0;

	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

	handle_webview(webview);

	label_new_page = gtk_label_new("Home");

	notebook_new_page_index = gtk_notebook_append_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(webview), label_new_page);
	return;
}

/**
 * Callback to any dialog destroy or restard app button.
 * It justs destroys the dialog and the main window
 * @param{GtkWidget *} dialog - dialog where the call came from
 * @return{void}
 **/
void cb_destroy_window (GtkWidget *dialog) {
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(window_ptr);
	return;
}

/**
 * Callback to refresh library button.
 * Deletes the current kiwix library file 
 * so when the application is restarted, it will 
 * create a new one with or without changes.
 * @return{void}
 **/
void cb_refresh_library () {
	GtkWidget *dialog = NULL;
	GtkWidget *dialog_content = NULL;
	GtkWidget *dialog_wrapper = NULL;
	GtkWidget *label = NULL;
	GtkWidget *dialog_button = NULL;

	if (window_ptr == NULL) {
		return;
	}

	refresh_kiwix_library_file();

	dialog = gtk_dialog_new();
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	dialog_wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
	label = gtk_label_new("The Kiwix Library has changed, please restart the application.");
	dialog_button = gtk_button_new_with_label("Restart Application");

	gtk_box_pack_start(GTK_BOX(dialog_wrapper), label, TRUE, TRUE, 4);
	gtk_box_pack_end(GTK_BOX(dialog_wrapper), dialog_button, TRUE, TRUE, 4);

	g_signal_connect(dialog_button, "clicked", G_CALLBACK(cb_destroy_window), dialog);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_wrapper);
	gtk_widget_show_all(dialog);
	return;
}

/**
 * Callback for 'button_fullscreen'.
 * Makes the app window fullscreen
 * @return{void}
 **/
void cb_make_window_fullscreen () {
	if (window_ptr == NULL) {
		return;
	}
	
	if (!fullscreen) {
		gtk_window_fullscreen(GTK_WINDOW(window_ptr));
	} else {
		gtk_window_unfullscreen(GTK_WINDOW(window_ptr));
	}

	fullscreen = ~fullscreen;
	return;
}

/**
 * Adds the GUI content of the upper section
 * buttons for actions and general buttons
 * @param{GtkWidget *} wrapper - pointer of the upper section wrapper widget
 * @return{void}
 **/
void add_content_upper_section (GtkWidget *wrapper) {
	GtkWidget *buttons_left_wrapper = NULL;
	GtkWidget *buttons_right_wrapper = NULL;
	GtkWidget *button_prev = NULL;
	GtkWidget *button_next = NULL;
	GtkWidget *button_menu = NULL;
	GtkWidget *button_fullscreen = NULL;
	GtkWidget *button_refresh = NULL;

	buttons_left_wrapper = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	button_prev = gtk_button_new_from_icon_name("gtk-go-back", GTK_ICON_SIZE_LARGE_TOOLBAR);
	button_next = gtk_button_new_from_icon_name("gtk-go-forward", GTK_ICON_SIZE_LARGE_TOOLBAR);

	buttons_right_wrapper = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	button_menu = gtk_button_new_from_icon_name("gtk-properties", GTK_ICON_SIZE_LARGE_TOOLBAR);
	button_fullscreen = gtk_button_new_from_icon_name("gtk-fullscreen", GTK_ICON_SIZE_LARGE_TOOLBAR);
	button_refresh = gtk_button_new_from_icon_name("gtk-refresh", GTK_ICON_SIZE_LARGE_TOOLBAR);

	g_signal_connect(button_fullscreen, "clicked", G_CALLBACK(cb_make_window_fullscreen), NULL);
	g_signal_connect(button_refresh, "clicked", G_CALLBACK(cb_refresh_library), NULL);

	gtk_box_pack_start(GTK_BOX(buttons_left_wrapper), button_prev, TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(buttons_left_wrapper), button_next, TRUE, TRUE, 2);

	gtk_box_pack_end(GTK_BOX(buttons_right_wrapper), button_menu, TRUE, TRUE, 2);
	gtk_box_pack_end(GTK_BOX(buttons_right_wrapper), button_fullscreen, TRUE, TRUE, 2);
	gtk_box_pack_end(GTK_BOX(buttons_right_wrapper), button_refresh, TRUE, TRUE, 2);
	
	gtk_box_pack_start(GTK_BOX(wrapper), buttons_left_wrapper, FALSE, TRUE, 4);
	gtk_box_pack_end(GTK_BOX(wrapper), buttons_right_wrapper, FALSE, TRUE, 4);
	return;
}

/**
 * Adds the main layout to the main window
 * @param{GtkWidget *} main_window - main window widget pointer
 * @return{void}
 **/
void add_layout_gui (GtkWidget *main_window) {
	GtkWidget *main_wrapper = NULL;
	GtkWidget *upper_wrapper = NULL;
	GtkWidget *bottom_wrapper = NULL;
	GtkWidget *left_wrapper = NULL;
	GtkWidget *right_wrapper = NULL;

	main_wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
	upper_wrapper = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	bottom_wrapper = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
	left_wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	right_wrapper = gtk_notebook_new();

	add_content_upper_section(upper_wrapper);
	add_webview_to_notebook(right_wrapper);

	gtk_box_pack_start(GTK_BOX(bottom_wrapper), left_wrapper, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(bottom_wrapper), right_wrapper, TRUE, TRUE, 4);

	gtk_box_pack_start(GTK_BOX(main_wrapper), upper_wrapper, FALSE, TRUE, 8);
	gtk_box_pack_start(GTK_BOX(main_wrapper), bottom_wrapper, TRUE, TRUE, 8);

	gtk_container_add(GTK_CONTAINER(main_window), main_wrapper);
	return;
}

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
	window_ptr = window;
	gtk_window_set_title(GTK_WINDOW(window), MAIN_TITLE);

	// Transform Window initial size to 3/4 of the screen's width and height.
	display = gdk_display_get_default();
	monitor = gdk_display_get_monitor(display, 0);

	gdk_monitor_get_geometry(monitor, geometry);

	window_width = 3 * (geometry->width / 4);
	window_height = 3 * (geometry->height / 4);

	add_layout_gui(window);

	gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_widget_show_all(window);
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

/**
 * Getter of the main window, in the GUI, pointer
 * @return{GtkWidget *} ptr of the main window
 **/
GtkWidget *get_window_ptr () {
	return window_ptr;
}
