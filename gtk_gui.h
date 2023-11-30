/*
 * =====================================================================================
 *       Filename:  gtk_gui.h
 *    Description: 	Header File of the GTK Graphical User Interface
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef GTK_GUI_H
#define GTK_GUI_H

/**
 * Callback for 'button_prev'
 * Takes WebViewer to the previous url 
 * in the urls list if available
 * @return{void}
 **/
void cb_get_prev_url ();

/**
 * Callback for 'button_next'
 * Takes WebViewer to the next url 
 * in the urls list if available
 * @return{void}
 **/
void cb_get_next_url ();

/**
 * Callback to any dialog destroy or restard app button.
 * It justs destroys the dialog and the main window
 * @param{GtkWidget *} dialog - dialog where the call came from
 * @return{void}
 **/
void cb_destroy_window (GtkWidget *dialog);

/**
 * Callback to refresh library button.
 * Deletes the current kiwix library file 
 * so when the application is restarted, it will 
 * create a new one with or without changes.
 * @return{void}
 **/
void cb_refresh_library ();

/**
 * Callback for 'button_fullscreen'.
 * Makes the app window fullscreen
 * @return{void}
 **/
void cb_make_window_fullscreen ();

/**
 * Adds to the GUI the main attraction
 * the WebViewer, from the lib Webkit2GTK-4.1!!!,
 * to the notebook or the right section of the GUI.
 * @param{GtkWidget *} notebook - pointer of the right section wrapper, or notebook, widget
 * @return{void}
 **/
void add_webview_to_notebook (GtkWidget *notebook);

/**
 * Adds the GUI content of the upper section
 * buttons for actions and general buttons
 * @param{GtkWidget *} wrapper - pointer of the upper section wrapper widget
 * @return{void}
 **/
void add_content_upper_section (GtkWidget *wrapper);

/**
 * Adds the main layout to the main window
 * @param{GtkWidget *} main_window - main window widget pointer
 * @return{void}
 **/
void add_layout_gui (GtkWidget *main_window);

/**
 * Activates the main Window of the GTK App.
 * Resizes it to 3/4ths of the monitor display, and centers it.
 * @param{GtkApplication *} app - Main App of the Program
 * @return{void}
 **/
void activate_gui (GtkApplication *app);

/**
 * Inits the GTK Application and GUI, 
 * once activated, activates the rest of the GUI
 * @param{int} argc - number of arguments passed to the program
 * @param{char **} argv - vector of the arguments passed to the program
 * @return {int} GTK Application Status
 **/
int init_gui (int argc, char **argv);

/**
 * Getter of the main window, in the GUI, pointer
 * @return{GtkWidget *} ptr of the main window
 **/
GtkWidget *get_window_ptr ();

#endif
