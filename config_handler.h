/*
 * =====================================================================================
 *       Filename:  config_handler.h
 *    Description:  
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

typedef enum ConfigTags {
	e_library_path,
	e_zim_folder_path,
	e_custom_port
} ConfigTags;

/**
 * Gets the Enviroment Variables and sets them 
 * as globals variables
 * @return{void}
 **/
void get_env_variables ();

/**
 * Reads from 'XDG_CONFIG_HOME/gtk-kiwix/init.conf'
 * the user custom variables,
 * and set them as globals
 **/
void read_user_config ();

/**
 * Generates from default values and envrioment variables 
 * the user custom varialbes
 * @return{void}
 **/
void generate_user_config ();

/**
 *	first gets or generates the enviroment variables and setting them as global vars.
 *	Then checks the if exists XDG_CONFIG_HOME/gtk-kiwix/init.config
 *	to set the user custom variables to its values, if not,
 *	generate them from the env variables and default values globls paths.
 * @return{void}
 **/
void check_user_config ();

#endif
