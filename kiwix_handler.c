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
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#include <kiwix_handler.h>

#include <consts.h>

int kiwix_server_port = 0;
int number_zim_files = 0;

/**
 * Function that takes multiple strings as arguments, then adds them in a single string
 * the function stops adding stings until a NULL argument is passed
 * *This function is more optimal than using multiple strcat, or strcat at all
 * @param{char *str ...} Strings to concat, multiple args can be passed. LAST ARG MUST BE NULL
 * @return{char *} Concated passed Strings
 **/
char *concat (const char *string, ... ) {
	char *str_result = NULL;
	size_t str_mem_allocated = 32;

	str_result = (char *) malloc(str_mem_allocated);
	memset(str_result, 0, str_mem_allocated);

	if (str_result == NULL) {
		fprintf(stderr, "Concat String Memory allocation failed");
		return NULL;
	}

	va_list str_params;
	size_t str_result_size = 0;
	char *str_ptr = NULL;

	va_start(str_params, string);
	
	for (const char *str = string; str != NULL; str = va_arg(str_params, const char *)) {
		size_t str_len = strlen(str);

		if (str_result_size + str_len + 1 > str_mem_allocated) {
			str_mem_allocated += str_len;
			str_ptr = reallocarray(str_result, str_mem_allocated, 2);
			str_mem_allocated *= 2;

			if (str_ptr == NULL) {
				free(str_result);

				fprintf(stderr, "String Ptr Memory allocation failed");
				return NULL;
			}

			str_result = str_ptr;
		}

		memcpy(str_result + str_result_size, str, str_len);

		str_result_size += str_len;
	}

	str_result[str_result_size++] = '\0';
	str_ptr = realloc(str_result, str_result_size);

	if (str_ptr == NULL) {
		fprintf(stderr, "String Ptr Memory Reallocation Failed");
		return NULL;
	}

	str_result = str_ptr;

	va_end(str_params);
	return str_result;
}

/**
 * Gets the program (gtk-kiwix) process ID
 * @return{pid_t} Program Process ID
 **/
pid_t get_program_process_id () {
	// I swear to god, that I thought that this would have been more complex.
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
int check_available_ports (const int port_min, const int port_max, int *port_number) {
	fprintf(stdout, "CHECKING FOR AVAILABLE PORTS IN %s", HOSTNAME);
	
	for (int port = port_min; port <= port_max; port++) {
		struct sockaddr_in server_address;
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if (sockfd < 0) {
			fprintf(stderr, "ERROR socket NOT ASIGNED");
			continue; // Socket Error
		}

		bzero((char *) &server_address, sizeof(server_address));

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(port);

		if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
			// Socket being Used
			continue; 
		}

		if (close(sockfd) < 0) {
			// Socket didn't close, check for the next one
			fprintf(stderr, "ERROR socket DIDN'T CLOSE PROPERLY");
			continue;
		}

		*port_number = port;
		return 1;
	}

	*port_number = 0;
	return 0;
}

/**
 * Get the zim files names in a given folder path,
 * then returning the array of the names with the first value being 
 * the length of the array
 * @param{char *} folder_path - path of directory where the zim files are
 * @return{char **} array with the names of the zim files
 **/
char **get_zim_files (const char *folder_path) {
	char **zim_files_names = (char **) malloc(sizeof(char*) * DYNAMIC_ARRAY_BUFFER);
	char zim_file_counter_str[INT_STRING_BUFFER]; 
	struct dirent *folder_content = NULL;
	DIR *zim_folder = NULL;
	int zim_file_index = 0;
	int zim_file_counter = 1;

	fprintf(stdout, "GETTING zim file names IN %s FOLDER\n", folder_path);

	sprintf(zim_file_counter_str, "%d", zim_file_counter);
	zim_files_names[zim_file_index++] = zim_file_counter_str;

	zim_folder = opendir(folder_path);

	if (!zim_folder) {
		fprintf(stderr, "THERE'S NO zim files FOLDER. EXIT\n");
		exit(EXIT_FAILURE);
	}

	while ((folder_content = readdir(zim_folder)) != NULL) {
		if (
				(strcmp(folder_content->d_name, ".") == 0) || 
				(strcmp(folder_content->d_name, "..") == 0)
			) {
			// Directory references, continue
			continue;
		}

		fprintf(stdout, "\t%s\n", folder_content->d_name);
		
		zim_files_names[zim_file_counter++] = folder_content->d_name;

		if (zim_file_counter >= DYNAMIC_ARRAY_BUFFER) {
			// number of zim files greater than the dynamic array buffer
			// increment the buffer by the power of 2
			// counter * 2; 16 * 2 = 32; 32 * 2 = 64; ...
			zim_files_names = (char **) realloc(zim_files_names, zim_file_counter * 2);
		}
	}

	number_zim_files = zim_file_counter;

	sprintf(zim_file_counter_str, "%d", zim_file_counter);
	zim_files_names[0] = zim_file_counter_str;
	zim_files_names = (char **) realloc(zim_files_names, zim_file_counter);

	return zim_files_names;
}

/**
 * Generate a Kiwix Library File from a list of zim files 
 * in the 'zim_file_folder' path
 * @return{char *} path of the generated Kiwix Library File
 **/
char *generate_kiwix_library_file () {
	char **zim_file_names = NULL;
	char *library_path = (char *) malloc(sizeof(char) * PATH_BUFFER);
	char *share_path = (char *) alloca(sizeof(char) * PATH_BUFFER);
	char *zim_folder_path = (char *) alloca(sizeof(char) * PATH_BUFFER);
	char *zim_files_length_str = NULL;
	long zim_files_length = 0;

	fprintf(stdout, "CHECKING FOR zim files TO GENERATE kiwix library file\n");

	zim_folder_path = "/home/bl4ky/.local/share/gtk-kiwix/zim-files/";

	zim_file_names = get_zim_files(zim_folder_path);

	// If there's less than one element, 
	// the length of the array, exit
	zim_files_length_str = concat(
		zim_files_length_str, 
		zim_file_names[0],
		NULL
	);
	zim_files_length = strtol(zim_files_length_str, NULL, 10);
	if (zim_files_length <= 1) {
		fprintf(stderr, "NO zim files AVAILABLE. EXIT");
		exit(EXIT_FAILURE);
	}
	
	share_path = "/home/bl4ky/.local/share/gtk-kiwix/";

	fprintf(stdout, "FOUND %d zim files, CREATING kiwix library file\n", zim_files_length);

	for (int i = 1; i < zim_files_length; i++) {
		FILE *kiwix_manage_pipe = NULL;
		char *pipe_command = NULL;
		char pipe_output[PIPE_BUFFER] = "";

		pipe_command = concat(
			KIWIX_MANAGE_PATH,
			share_path,
			"library.xml",
			" add ",
			zim_folder_path,
			zim_file_names[i],
			NULL
		);

		kiwix_manage_pipe = popen(pipe_command, "r");

		if (kiwix_manage_pipe == NULL) {
			fprintf(stderr, "ERROR EXECUTING kiwix-manage");
			continue;
		}

		while (fgets(pipe_output, sizeof(pipe_output), kiwix_manage_pipe) != NULL) {
			if (strlen(pipe_output) >= 1) {
				fprintf(stderr, "ERROR EXECUTING kiwix-manage");
				continue;
			}
		}

		pclose(kiwix_manage_pipe);
	}

	library_path = concat(
		share_path,
		"library.xml",
		NULL
	);

	fprintf(stdout, "SUCCESSFULLY CREATED kiwix library IN %s file VIA %s", library_path, KIWIX_MANAGE_PATH);

	return library_path;
}

/**
 * Gets the Kiwix Library File, 
 * which is a list of all the available ZIM files.
 * If the file is not available in 'XDG_DATA_HOME' as 'library.xml', 
 * it will generate a new library file with the ZIM files 
 * available in 'XDG_DATA_HOME/zim-files/'
 * @return{char *} char allocated pointer of the library file path
 **/
char *get_kiwix_library_file () {
	char *library_path = (char *) malloc(sizeof(char) * PATH_BUFFER);

	library_path = "/home/bl4ky/.local/share/gtk-kiwix/library.xml";

	if (access(library_path, F_OK) == 0) {
		fprintf(stdout, "FOUND Kiwix Library File at: %s\n", library_path);
		return library_path;
	}

	fprintf(stdout, "Kiwix Library File NOT FOUND, CREATING NEW Kiwix Library File\n");

	library_path = generate_kiwix_library_file();

	fprintf(stdout, "Kiwix Library File SUCCESSFULLY CREATED\n");

	return library_path;
}

/**
 * Run and executes the Kiwix Server via commandline, 
 * using the passed localhost port and 
 * @return{int} Status of the Server: 0 Fine; 1 Not Fine
 **/
int run_server (const int port, const int program_pid, const char *library_path) {
	FILE *kiwix_serve_pipe = NULL;
	char port_str[INT_STRING_BUFFER] = "";
	char program_pid_str[INT_STRING_BUFFER] = "";
	char *pipe_command;
	char pipe_output[PIPE_BUFFER] = "";
	char success_msg_str[REGEX_BUFFER] = "running";
	char error_msg_str[REGEX_BUFFER] = "Unable";
	regex_t success_msg_regex;
	regex_t error_msg_regex;
	int status = 0;

	sprintf(port_str, "%d", port);
	sprintf(program_pid_str, "%d", program_pid);

	if (regcomp(&success_msg_regex, success_msg_str, REG_ICASE | REG_NOSUB)) {
		fprintf(stderr, "ERROR IN REGEX COMPILATION");
		status = 1;
		exit(EXIT_FAILURE);
	} 

	if (regcomp(&error_msg_regex, error_msg_str, REG_ICASE | REG_NOSUB)) {
		fprintf(stderr, "ERROR IN REGEX COMPILATION");
		status = 1;
		exit(EXIT_FAILURE);
	}

	pipe_command = concat(
		KIWIX_SERVE_PATH, 
		" --library ", 
		library_path, 
		" -p ", 
		port_str,
		" --attachToProcess=",
		program_pid_str,
		" -d ",
		NULL
	);

	printf("HERE:%s\n", pipe_command);

	kiwix_serve_pipe = popen(pipe_command, "r");

	while (fgets(pipe_output, sizeof(pipe_output), kiwix_serve_pipe) != NULL) {
		if (regexec(&success_msg_regex, pipe_output, 0, NULL, 0) == 0) {
			// Just break the loop, otherwise it'll be an infinite loop
			fprintf(stdout, "KIWIX SERVER RUNNING in http://%s:%d/\n", HOSTNAME, port);
			break;
		} else if (regexec(&error_msg_regex, pipe_output, 0, NULL, 0) == 0) {
			fprintf(stderr, "ERROR KIWIX SERVER COULDN'T START");
			status = 1;
			exit(EXIT_FAILURE);
		}
	}

	pclose(kiwix_serve_pipe);

	return status;
}

/**
 * Starts the Kiwix Server, 
 * first checks for an available port
 * second, gets the program pid in order to link 
 * the shutdown of the server with the termination of the program
 * third, gets the Kiwix Library File, or creates one if needed
 * fourth, runs the server. Enjoy!
 * @return{void}
 **/
void start_server () {
	char *library_path = NULL;
	int is_available_port = 0;
	int program_pid = 0;
	int server_status = 0;

	fprintf(stdout, "STARTING LOCAL KIWIX SERVER\n");

	fprintf(stdout, "CHECKING FOR AN AVAILABLE port\n");
	is_available_port = check_available_ports(KIWIX_SERVER_PORT_MIN, KIWIX_SERVER_PORT_MAX, &kiwix_server_port);
	if (!is_available_port) {
		fprintf(stderr, "NO AVAILABLE port FOR THE KIWIX SERVER. EXIT\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "AVAILABLE port FOUND, USING port %d\n", kiwix_server_port);

	fprintf(stdout, "GETTING CURRENT program process id\n");
	program_pid = (int) get_program_process_id();
	fprintf(stdout, "GOT CURRENT program process id: %d\n", program_pid);

	fprintf(stdout, "GETTING kiwix library file\n");
	library_path = get_kiwix_library_file();
	fprintf(stdout, "GOT kiwix library file AT %s\n", library_path);

	fprintf(stdout, "KIWIX SERVER PARAMATERS READY. STARTING TO RUN KIWIX SERVER\n");
	server_status = run_server(kiwix_server_port, program_pid, library_path);
	if (server_status != 0) {
		fprintf(stderr, "ERROR IN KIWIX SERVER");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "KIWIX SERVER SUCCESSFULLY DEPLOYED\n");

	return;
}

/**
 * Method that refreshes the 'kiwix library file' from the GUI,
 * checks if there's a file size change and then returns according to the result
 * @return{int} 0 if there's any change in zim file count. 1 if there's none
 **/
int refresh_kiwix_library_file () {
	char *library_file_path = (char *) malloc(sizeof(char) * PATH_BUFFER);

	library_file_path = "/home/bl4ky/.local/share/gtk-kiwix/library.xml";
	unlink(library_file_path);

	return 0;
}

/**
 * Getter, available for other modules, 
 * for current kiwix server port
 * @return {int} current kiwix server port
 **/
int get_kiwix_server_port () {
	return kiwix_server_port;
}
