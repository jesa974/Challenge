#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// List all files in the input directory
char** list_files(void) {
    DIR* dir;
    struct dirent *file;
    char** files = NULL;
    int cpt = 0;

    // Open directory
    dir = opendir("./input/");

    printf("List of available inputs : \n");

    // Check if the directory exists
    while ((file = readdir(dir)) != NULL)
    {
        // Print the name of the file
        if (strncmp(file->d_name, ".", 1) &&  strncmp(file->d_name, "..", 2) != 0)
        {
            printf("%s\n", file->d_name);
            cpt++;
        }
    }

    // Allocate memory for the array of files
    files = (char**)malloc(sizeof(char*) * cpt);
    
    // Reset counter & the directory cursor
    cpt = 0;
    rewinddir(dir);

    // Check if the directory exists
    while ((file = readdir(dir)) != NULL)
    {
        // Print the name of the file
        if (strncmp(file->d_name, ".", 1) &&  strncmp(file->d_name, "..", 2) != 0)
        {
            // Put the names of the files in the array
            files[cpt] = file->d_name;
            cpt++;
        }
    }

    // Close directory
    closedir(dir);

    return files;
}

// Get the number of files in the directory
int number_of_files(char** files) {
    int cpt = 0;

    while (files[cpt] != NULL)
    {
        cpt++;
    }

    return cpt;
}

// Get the max length of the files' name in the directory
int max_length_of_files(char** files) {
    int max = 0;
    int cpt = 0;

    // Get the max length of the files' name
    while (files[cpt] != NULL)
    {
        if (strlen(files[cpt]) > max)
        {
            max = strlen(files[cpt]);
        }
        cpt++;
    }

    return max;
}

// Ask to the user for a file name
char* ask_file(char** files) {
    int nb_bytes = max_length_of_files(files);
    char* file_name = (char*)malloc(sizeof(char) * nb_bytes);

    printf("Enter the name of the file you wanted to opened : ");
    scanf("%s", file_name);

    do {
        // Check if the file exists
        for (int i = 0; i < number_of_files(files); i++) {
            if (strcmp(file_name, files[i]) == 0)
            {
                return file_name;
            }
        }

        // Ask again
        printf("The file doesn't exist. Please enter the name of the file you wanted to opened : ");
        scanf("%s", file_name);
    }
    while (1);

    return file_name;
}

// Get the length of a file
int get_file_length(char* file_name) {
    FILE* file = fopen(file_name, "r");
    int cpt = 0;
    char c;

    // Get the length of the file
    while ((c = fgetc(file)) != EOF)
    {
        cpt++;
    }

    // Close the file
    fclose(file);

    return cpt;
}

// Get the number of lines of a file
int get_file_lines(char* file_name) {
    FILE* file = fopen(file_name, "r");
    int cpt = 0;
    char c;

    // Get the number of lines of the file
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            cpt++;
        }
    }

    // Close the file
    fclose(file);

    return cpt;
}

// Import a file
char** import_file(char* file_name, int* nb_lines){
	char* PATH = "./input/";
    char** file_content = NULL;
    char* line = NULL;
	FILE* file;
	int cpt = 0;
	
    // Concatenate the path and the file name
    char* file_path = (char*)malloc(sizeof(char) * (strlen(PATH) + strlen(file_name) + 1));
    strcpy(file_path, PATH);
    strcat(file_path, file_name);

    // Open the file
	file = fopen(file_path, "rt");
	
    // Check if the file exists
	if (file == NULL)
    { 
		printf("File does not exist.\n");
        exit(0);
	} else
    {
        struct stat sb;
        stat(file_path, &sb);

        // Allocate memory for the file content
        file_content = (char**)malloc(sizeof(char*) * (get_file_lines(file_path) + 1));
        line = (char*)malloc(sizeof(char) * sb.st_size);
        
        // Get the file contents
        while (fscanf(file, "%[^\n] ", line) != EOF) {
            file_content[cpt] = (char*)malloc(sizeof(char) * (strlen(line) + 1));
            strcpy(file_content[cpt], line);
            cpt++;
        }
    }

    // Record the number of lines
    *nb_lines = cpt;
    
    // Close the file
    fclose(file);

    return file_content;
}