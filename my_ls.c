#include "my_ls.h"

int main(int argc, char* argv[]) {

    char** files = malloc(0);
    int num_files = 0;
    int num_operands = get_num_operands(argv, argc);
    char* flag = NULL;

    if (num_operands > 0) {
        int index = argc - num_operands; //index of first file or directory
        process_input(argv, index, argc, &files, &num_files);
    }
    else if (num_operands == 0 && argc == 1) { //no flags
        flag = dir_content(&files, &num_files, NULL, ".");
    }
    else { //one or multiple flags
        flag = check_flags(argv, argc - num_operands - 1, &files, &num_files, ".");
    }

    if (num_operands <= 1 && flag != NULL && (my_strcmp(flag, "-t") == 0 || my_strcmp(flag, "-at") == 0 || my_strcmp(flag, "-ta") == 0)) {
        printf("flag is %s, calling quicksort - time\n", flag);
        
        quicksort((void**) files, 0, num_files - 1, compare_mod_times);

    }
    else if (num_operands <= 1) {
        printf("flag is %s, calling quicksort\n", flag);
        quicksort((void**) files, 0, num_files - 1, compare_alphabet);
    }

    print_files(files, num_files);

    free_mem(files, num_files);

    return 0;
}

char* check_flags(char** argv, int num_flags, char*** files, int* num_files, char* dir_path) {
    char* flag = NULL;
    if (num_flags == 2) {
        if ((my_strcmp(argv[1], "-a") == 0) && my_strcmp(argv[2], "-t") == 0) {
            flag = dir_content(files, num_files, "-at", dir_path);
        }
        else if (my_strcmp(argv[1], "-t") == 0 && my_strcmp(argv[2], "-a") == 0) {
            flag = dir_content(files, num_files, "-ta", dir_path);
        }
    }
    else if (my_strcmp(argv[1], "-t") == 0) {
        flag = dir_content(files, num_files, "-t", dir_path);
    }
    else if (my_strcmp(argv[1], "-a") == 0) {
        flag = dir_content(files, num_files, "-a", dir_path);
    }
    else if (my_strcmp(argv[1], "-ta") == 0) {
        flag = dir_content(files, num_files, "-ta", dir_path);
    }
    else if (my_strcmp(argv[1], "-at") == 0) {
        flag = dir_content(files, num_files, "-at", dir_path);
    }

    return flag;
}

char* dir_content(char*** files, int* num_files, char* flag, char* dir_path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);

    while ((entry = readdir(dir)) != NULL) {
        if ((flag == NULL || my_strcmp(flag, "-t") == 0) && entry->d_name[0] == '.') {
            continue;
        }

        char* filename = my_strdup(entry->d_name);
        *files = realloc(*files, (*num_files + 1) * sizeof(char*));
        (*files)[*num_files] = filename;
        (*num_files)++;

        // printf("Added file: %s\n", filename);
    }

    closedir(dir);

    // if (flag != NULL && (my_strcmp(flag, "-t") == 0 || my_strcmp(flag, "-at") == 0 || my_strcmp(flag, "-ta") == 0)) {
    //     printf("flag is %s, calling quicksort - time\n", flag);
        
    //     quicksort((void**) *files, 0, *num_files - 1, compare_mod_times);

    // }
    // else {
    //     printf("flag is %s, calling quicksort\n", flag);
    //     quicksort((void**) *files, 0, *num_files - 1, compare_alphabet);
    // }
    return flag;
}

int get_num_operands(char **argv, int argc) {
    int num_operands = argc - 1;

    for (int i = 1; i < argc; i++) {
        if (my_strcmp(argv[i], "-t") == 0 || my_strcmp(argv[i], "-a") == 0) {
            num_operands = argc - 1 - i;
        }
        else if (my_strcmp(argv[i], "-at") == 0 || my_strcmp(argv[i], "-ta") == 0) {
            num_operands = argc -1 - i;
        }
    }

    return num_operands;
}

int compare_alphabet(const void* file_1, const void* file_2) {
    if (file_1 == NULL || file_2 == NULL) {
        return 0;
    }

    const char* f1 = (const char*) file_1;
    const char* f2 = (const char*) file_2;

    if (f1[0] == '.' && f2[0] == '.') {
        return my_strcmp(f1, f2);
    }
    else if (f1[0] == '.' && f2[0] != '.') {
        return -1;
    } else if (f2[0] == '.' && f1[0] != '.') {
        return 1;
    }

    return my_strcmp(f1, f2);
}

int compare_mod_times(const void* file_1, const void* file_2) {
    if (file_1 == NULL || file_2 == NULL) {
        return 0;
    }

    const char* f1 = (const char*) file_1;

    const char* f2 = (const char*) file_2;

    struct stat stat_f1, stat_f2;
    stat(f1, &stat_f1);
    stat(f2, &stat_f2);

    if (stat_f1.st_mtim.tv_sec < stat_f2.st_mtim.tv_sec) {
        return 1; //file 2 is more recent
    }
    else if (stat_f1.st_mtim.tv_sec > stat_f2.st_mtim.tv_sec) {
        return -1; //file 1 is more recent
    }
    else {
        if (stat_f1.st_mtim.tv_nsec < stat_f2.st_mtim.tv_nsec) {
            return 1;
        }
        else if (stat_f1.st_mtim.tv_nsec > stat_f2.st_mtim.tv_nsec) {
            return -1;
        }
        else {
            return my_strcmp(f1, f2); //if times are equal, compare alphabetically
        }
    }

    return 0;
}

int is_dir(const char* path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);

    if (dir == NULL) {
        //unable to open the directory
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (my_strcmp(entry->d_name, ".") == 0 || my_strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        closedir(dir);
        return 1; //at least one entry found, so it's a directory
    }

    closedir(dir);

    return 0; //no entries found, so it's not a directory
}

void process_input(char** argv, int index, int argc, char*** files, int* num_files) {
    int num_flags = index - 1;
    int num_dirs = 0;
    char** directories = malloc(0);
    
    while (index < argc) {
        char* path = argv[index];

        if (is_dir(path) == 0) {
            printf("%s is a file\n", path);
            *files = realloc(*files, (*num_files + 1) * sizeof(char*));
            (*files)[*num_files] = my_strdup(path);
            (*num_files)++;
        }
        else if (is_dir(path) == 1) {
            directories = realloc(directories, (num_dirs + 1) * sizeof(char*));
            directories[num_dirs] = my_strdup(path);
            num_dirs++;

        }
        else {
            print_error(path);
        }

        index++;
    }

    handle_dirs(argv, num_flags, num_dirs, &directories, files, num_files);

    free_mem(directories, num_dirs);

}

void handle_dirs(char** argv, int num_flags, int num_dirs, char*** directories, char*** files, int* num_files) {
    int files_per_dir[num_dirs];
    char* flag = NULL;

    for (int i = 0; i < num_dirs; i++) {
        //store files in the directory
        if (num_flags > 0) {
            flag = check_flags(argv, num_flags, files, num_files, (*directories)[i]);
        }
        else {
            flag = dir_content(files, num_files, NULL, (*directories)[i]);
        }

        if (i == 0) {
            files_per_dir[i] = *num_files;
        }
        else {
            files_per_dir[i] = *num_files - files_per_dir[i - 1];
        }
    }

    quicksort((void**) *directories, 0, num_dirs - 1, compare_alphabet);

    int start_index = 0;
    for (int i = 0; i < num_dirs; i++) {
        print_dirs(*directories, i);
        int end_index = start_index + files_per_dir[i] - 1;

        if (flag != NULL && (my_strcmp(flag, "-t") == 0 || my_strcmp(flag, "-at") == 0 || my_strcmp(flag, "-ta") == 0)) {
            quicksort((void**) *files, start_index, end_index, compare_mod_times);
        } 
        else {
            quicksort((void**) *files, start_index, end_index, compare_alphabet);
        }

        start_index += files_per_dir[i];
    }
}

void print_files(char** files, int num_files) {
    for (int i = 0; i < num_files; i++) {
        int length = my_strlen(files[i]);
        write(1, files[i], length);
        write(1, "\n", 1);
    }
}

void print_dirs(char** directories, int index) {
    write(1, directories[index], my_strlen(directories[index]));
    my_putchar(':');
    my_putchar(' ');
    my_putchar('\n');
}

void print_error(const char* path_name) {
    write(1, ERROR_MSG_1, ERROR_MSG_1_SIZE);
    write(1, path_name, my_strlen(path_name));
    write(1, ERROR_MSG_2, ERROR_MSG_2_SIZE);
}

int my_putchar(char c) {
    return write(1, &c, 1);
}

int my_strlen(const char* str_1) {
    int length = 0;

    while (*str_1 != '\0') {
        length++;
        str_1++;
    }

    return length;
}

char* my_strdup(const char* str_1) {
    int length = my_strlen(str_1);
    char* string = (char*) malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        string[i] = str_1[i];
    }

    string[length] = '\0';

    return string;
}

int my_strcmp(const char* str_1, const char* str_2) {
    while (*str_1 != '\0' || *str_2 != '\0') {
        if (*str_1 < *str_2) {
            return -1;
        }
        else if (*str_1 > *str_2) {
            return 1;
        }
        str_1++;
        str_2++;
    }
    return 0;
}

void swap(void** arr, int i, int j) {
    char* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(void** arr, int low, int high, int (*compare)(const void *, const void *)) {
    char* pivot = (char*) arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot) < 0) {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, high);
    return i + 1;
}

void quicksort(void** arr, int low, int high, int (*compare)(const void *, const void *)) {
    if (low < high) {
        int pi = partition(arr, low, high, compare);
        quicksort(arr, low, pi - 1, compare);
        quicksort(arr, pi + 1, high, compare);
    }
}

void free_mem(char** files, int num_files) {
    for (int i = 0; i < num_files; i++) {
        free(files[i]);
    }
    free(files);
}