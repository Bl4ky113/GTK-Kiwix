/*
 * =====================================================================================
 *       Filename:  kiwix_handler.c
 *    Description:  Handler of Kiwix Serve and Kiwix Library using CommandLine Commands
 *        Version:  1.0
 *       Compiler:  gcc
 *         Author:  Martin Hernandez, 
 *   Organization:	UNAL 
 * =====================================================================================
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <consts.h>
#include <kiwix_handler.h>

int kiwix_server_port = 0;

/**
 * Gets the program (gtk-kiwix) process ID
 * @return{pid_t} Program Process ID
 **/
pid_t get_program_process_id () {
	pid_t pid;

	pid = getpid();

	return pid;
}

/**
 * Checks if there's any port avaialable in a determined range,
 * creating a socket, checking if it's available by binding it, and finaly closing it,
 * if there's any available, will change the {int *} 'port_number' by dereference to the available port number.
 * @param{int} port_min - minimum port number in the search range
 * @param{int} port_max - maximum port number in the search range
 * @param{int *} port_number - dereference available port variable, 0 if there's none
 * @return{int} boolean int, true if there's an available port, false otherwise
 **/
int check_available_ports (int port_min, int port_max, int *port_number) {
	for (int port = port_min; port <= port_max; port++) {
		struct sockaddr_in server_address;
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if (sockfd < 0) {
			continue; // Socket Error
		}

		bzero((char *) &server_address, sizeof(server_address));

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(port);

		if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
			continue; // Socket being Used
		}

		if (close(sockfd) < 0) {
			fprintf(stdin, "ERROR: did not close fd:");
			continue;
		}

		*port_number = port;
		return 1;
	}

	*port_number = 0;
	return 0;
}

/**
 *
 **/
char *generate_kiwix_library_file () {
	char library_path = (char *) malloc(sizeof(char) * 96);

	return library_path;
}

/**
 *
 **/
char *get_kiwix_library_file () {
	char *path_buffer = (char *) malloc(sizeof(char) * 96);

	path_buffer = "/home/bl4ky/.local/share/gtk-kiwix/library.xml";

	if (access(path_buffer, F_OK) == 0) {
		return path_buffer;
	}

	path_buffer = generate_kiwix_library_file();

	return path_buffer;
}

/*
 * Starts the Kiwix Server, 
 * first checks for an available port
 * second, gets the program pid in order to link 
 * the shutdown of the server with the termination of the program
 * third, gets the Kiwix Library File, or creates one if needed
 * fourth, runs the server. Enjoy!
 * @return{void}
 **/
void start_server () {
	int available_port = check_available_ports(KIWIX_SERVER_PORT_MIN, KIWIX_SERVER_PORT_MAX, &kiwix_server_port);

	if (!available_port) {
		perror("NO AVAILABLE PORTS FOR THE KIWIX SERVER. EXITING");
		exit(EXIT_FAILURE);
	}

	int program_pid = (int) get_program_process_id();

	get_kiwix_library_file();

	return;
}

/**
 * Run and executes the Kiwix Server via commandline, 
 * using the passed localhost port and 
 * @return{int} Status of the Server: 0 Fine; 1 Not Fine
 **/
int run_server (int port, int program_pid, char *library_path) {
	int status = 0;

	return status;
}

/**
 * Getter, available for other modules, 
 * for current kiwix server port
 * @return {int} current kiwix server port
 **/
int get_kiwix_server_port () {
	return kiwix_server_port;
}
