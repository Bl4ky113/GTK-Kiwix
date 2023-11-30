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
 * 
 **/
int init_gui (int argc, char **argv);

/**
 * Activates the main Window of the GTK App.
 * Resizes it to 3/4ths of the monitor display, and centers it.
 * @param{GtkApplication *} app - Main App of the Program
 * @return{void}
 **/
void activate_gui (GtkApplication *app);

#endif
