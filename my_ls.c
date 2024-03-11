#include "my_ls.h"

int main(int argc, char* argv[]) {

    char** files = malloc(0);
    int num_files = 0;
    // int num_directories = 0;
    int num_operands = get_num_operands(argv, argc);

    if (num_operands > 0) {
        printf("num_operands: %d\n", num_operands);
        //if num_operands > 0 call a function that will check each operand given to determine which is a dir and which is a file
        //then calls the appropriate function to handle it
    }
    else if (num_operands == 0 && argc == 1) {
        dir_content(&files, &num_files, NULL, ".");
    }
    else {
        check_flags(argv, argc - num_operands - 1, &files, &num_files, ".");
    }

    print_files(files, num_files);

    free_mem(files, num_files - 1);

    return 0;
}

void check_flags(char** argv, int num_flags, char*** files, int* num_files, char* dir_path) {
    if (num_flags == 2) {
        if ((my_strcmp(argv[1], "-a") == 0) && my_strcmp(argv[2], "-t") == 0) {
            dir_content(files, num_files, "-at", dir_path);
        }
        else if (my_strcmp(argv[1], "-t") == 0 && my_strcmp(argv[2], "-a") == 0) {
            dir_content(files, num_files, "-ta", dir_path);
        }
    }
    else if (my_strcmp(argv[1], "-t") == 0) {
        dir_content(files, num_files, "-t", dir_path);
    }
    else if (my_strcmp(argv[1], "-a") == 0) {
        dir_content(files, num_files, "-a", dir_path);
    }
    else if (my_strcmp(argv[1], "-ta") == 0) {
        dir_content(files, num_files, "-ta", dir_path);
    }
    else if (my_strcmp(argv[1], "-at") == 0) {
        dir_content(files, num_files, "-at", dir_path);
    }
}

void dir_content(char*** files, int* num_files, char* flag, char* dir_path) {
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
    }

    closedir(dir);

    if (flag != NULL && (my_strcmp(flag, "-t") == 0 || my_strcmp(flag, "-at") || my_strcmp(flag, "-ta"))) {
        quicksort((void**) *files, 0, *num_files - 1, compare_mod_times);

    }
    else {
        quicksort((void**) *files, 0, *num_files - 1, compare_alphabet);
    }
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

void print_files(char** files, int num_files) {
    for (int i = 0; i < num_files; i++) {
        int length = my_strlen(files[i]);
        write(1, files[i], length);
        write(1, "\n", 1);
    }
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
    if (num_files < 0) {
        free(files);
    }
    else {
        free(files[num_files]);
        free_mem(files, --num_files);
    }
}