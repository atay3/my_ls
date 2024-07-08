#ifndef MY_LS_H
#define MY_LS_H

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

#define ERROR_MSG_1 "my_ls: cannot access '"
#define ERROR_MSG_2 "': No such file or directory\n"
#define ERROR_MSG_1_SIZE 22
#define ERROR_MSG_2_SIZE 29


char* check_flags(char** argv, int num_flags, char*** files, int* num_files, char* dir_path);
char* dir_content(char*** files, int* num_files, char* flag, char* dir_path);
int get_num_operands(char** argv, int argc);
int compare_alphabet(const void* file_1, const void* file_2);
int compare_mod_times(const void* file_1, const void* file_2);
void print_files(char** files, int num_files);
void print_dirs(char** directories, int index);
void print_error(const char* path_name);
int my_putchar(char c);
int is_dir(const char* path);
int process_input(char** argv, int index, int argc, char*** files, int* num_files);
void handle_dirs(char** argv, int num_flags, int num_dirs, char*** directories, char*** files, int* num_files);
char* get_flags(char** argv, int num_flags);
char* my_strdup(const char* str_1);
int my_strcmp(const char* str_1, const char* str_2);
int my_strlen(const char* str_1);
void swap(void** arr, int i, int j);
int partition(void** arr, int low, int high, int (*compare)(const void*, const void*));
void quicksort(void** arr, int low, int high, int (*compare)(const void*, const void*));
void free_mem(char** files, int num_files);

#endif
