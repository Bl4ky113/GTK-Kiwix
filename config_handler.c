/*
 * =====================================================================================
 *       Filename:  config_handler.c
 *    Description:	Handler for user and general XDG config, share and other file structures.
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <consts.h>
#include <config_handler.h>

char *HOME = NULL;
char *XDG_CONFIG_HOME = NULL;
char *XDG_DATA_HOME = NULL;

char *library_path = NULL;
char *zim_folder_path = NULL;
int custom_port = -1;

/**
 * Gets the Enviroment Variables and sets them 
 * as globals variables
 * @return{void}
 **/
void get_env_variables () {
	HOME = (char *) calloc(PATH_BUFFER, sizeof(char));

	HOME = getenv("HOME");
	if (HOME == NULL) {
		perror("NO HOME ENVIROMENT VARIABLE. EXIT");
		exit(EXIT_FAILURE);
	}
	strcat(HOME, "/");

	XDG_CONFIG_HOME = (char *) calloc(PATH_BUFFER, sizeof(char));
	XDG_CONFIG_HOME = getenv("XDG_CONFIG_HOME");
	if (XDG_CONFIG_HOME == NULL) {
		fprintf(stdout, "%s\t%s\t%s\n", XDG_CONFIG_HOME, HOME, XDG_CONFIG_HOME_DIR);
		/*strcat(XDG_CONFIG_HOME, HOME);*/
		/*strcat(XDG_CONFIG_HOME, XDG_CONFIG_HOME_DIR);*/
	}

	XDG_DATA_HOME = (char *) calloc(PATH_BUFFER, sizeof(char));
	XDG_DATA_HOME = getenv("XDG_DATA_HOME");
	if (XDG_DATA_HOME == NULL) {
		strcat(XDG_DATA_HOME, HOME);
		strcat(XDG_DATA_HOME, XDG_DATA_HOME_DIR);
	}

	return;
}

/**
 * Reads from 'XDG_CONFIG_HOME/gtk-kiwix/init.conf'
 * the user custom variables,
 * and set them as globals
 **/
void read_user_config () {
	FILE *config_file = NULL;

	config_file = fopen("~/.config/gtk-kiwix/init.conf", "r");

	char *tag;
	char *value; 
	while (fscanf(config_file, "%s=%s\n", &tag, &value)) {
		
	}

	return;
}

/**
 * Generates from default values and envrioment variables 
 * the user custom varialbes,
 * and set them as globals
 * @return{void}
 **/
void generate_user_config () {
	library_path = (char *) calloc(PATH_BUFFER, sizeof(char));
	strcat(library_path, XDG_DATA_HOME);
	strcat(library_path, "library.xml");

	zim_folder_path = (char *) calloc(PATH_BUFFER, sizeof(char));
	strcat(zim_folder_path, XDG_DATA_HOME);
	strcat(zim_folder_path, "zim-files/");

	// Can't Generate custom port

	return;
}

/**
 *	first gets or generates the enviroment variables and setting them as global vars.
 *	Then checks the if exists XDG_CONFIG_HOME/gtk-kiwix/init.config
 *	to set the user custom variables to its values, if not,
 *	generate them from the env variables and default values globls paths.
 * @return{void}
 **/
void check_user_config () {
	char *config_file_path = (char *) calloc(PATH_BUFFER, sizeof(char));

	get_env_variables();

	/*strcat(config_file_path, XDG_CONFIG_HOME);*/
	/*strcat(config_file_path, "init.conf");*/

	/*if (access(config_file_path, F_OK) == 0) {*/
		/*read_user_config();*/
		/*return;*/
	/*}*/

	/*generate_user_config();*/
	
	return;
}
