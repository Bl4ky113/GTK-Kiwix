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
 * 
 **/
void start_server ();

/**
 * Run and executes the Kiwix Server via commandline, 
 * using the passed localhost port and 
 * @return{int} Status of the Server: 0 Fine; 1 Not Fine
 **/
int run_server (int port, int program_pid, char *library_path);

/**
 * Getter, available for other modules, 
 * for current kiwix server port
 * @return {int} current kiwix server port
 **/
int get_kiwix_server_port();

#endif
