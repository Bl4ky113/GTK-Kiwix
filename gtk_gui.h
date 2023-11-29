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
 *
 **/
void activate_gui (GtkApplication *app);

#endif
