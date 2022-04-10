char** list_files(void); // List all files in the input directory
int number_of_files(char** files); // Get the number of files in the directory
int max_length_of_files(char** files); // Get the max length of the files' name in the directory
char* ask_file(char** files); // Ask to the user for a file name
int get_file_length(char* file_name); // Get the length of a file
int get_file_lines(char* file_name); // Get the number of lines of a file
char** import_file(char* file_name, int* nb_lines); // Import a file