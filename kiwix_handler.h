/*
 * =====================================================================================
 *       Filename:  kiwix_handler.h
 *    Description:  Header File of the Kiwix Serve and General ZIM Handling
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:  UNAL
 * =====================================================================================
 */

#ifndef KIWIX_HANDLER_H
#define KIWIX_HANDLER_H

/**
 * Checks if there's any port avaialable in a determined range,
 * creating a socket, checking if it's available by binding it, and finaly closing it,
 * if there's any available, will change the {int *} 'port_number' by dereference to the available port number.
 * @param{int} port_min - minimum port number in the search range
 * @param{int} port_max - maximum port number in the search range
 * @param{int *} port_number - dereference available port variable, 0 if there's none
 * @return{int} boolean int, true if there's an available port, false otherwise
 **/
int check_available_ports (int port_min, int port_max, int *port_number);


/**
 * Gets the program (gtk-kiwix) process ID
 * @return{pid_t} Program Process ID
 **/
pid_t get_program_process_id ();

/**
 * Get the zim files names in a given folder path,
 * then returning the array of the names with the first value being 
 * the length of the array
 * @param{char *} folder_path - path of directory where the zim files are
 * @return{char **} array with the names of the zim files
 **/
char **get_zim_files (char *folder_path);

/**
 * Generate a Kiwix Library File from a list of zim files 
 * in the 'zim_file_folder' path
 * @return{char *} path of the generated Kiwix Library File
 **/
char *generate_kiwix_library_file ();

/**
 * Gets the Kiwix Library File, 
 * which is a list of all the available ZIM files.
 * If the file is not available in 'XDG_DATA_HOME' as 'library.xml', 
 * it will generate a new library file with the ZIM files 
 * available in 'XDG_DATA_HOME/zim-files/'
 * @return{char *} char allocated pointer of the library file path
 **/
char *get_kiwix_library_file ();

/**
 * Starts the Kiwix Server, 
 * first checks for an available port
 * second, gets the program pid in order to link 
 * the shutdown of the server with the termination of the program
 * third, gets the Kiwix Library File, or creates one if needed
 * fourth, runs the server. Enjoy!
 * @return{void}
 **/
void start_server ();

/**
 * Run and executes the Kiwix Server via commandline, 
 * using the passed localhost port and 
 * @return{int} Status of the Server: 0 Fine; 1 Not Fine
 **/
int run_server (int port, int program_pid, char *library_path);

/**
 * Method that refreshes the 'kiwix library file' from the GUI,
 * checks if there's a file size change and then returns according to the result
 * @return{int} 0 if there's any change in zim file count. 1 if there's none
 **/
int refresh_kiwix_library_file ();

/**
 * Getter, available for other modules, 
 * for current kiwix server port
 * @return {int} current kiwix server port
 **/
int get_kiwix_server_port();

#endif
