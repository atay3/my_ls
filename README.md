# Welcome to My Ls
***

## Task
Write a prgoram called `my_ls` that functions similarly to `ls`. It displays the name and information of a file for any operand that is a file of a type other than a directory. If the operand is a file of type directory, then the program must display the names of files contained within that directory, as well as any requested, associated information.

If there are no operands given, the contents within the current directory must be displayed. If there are more than one operands given, then  non-directory operands must be displayed first. The directory and non-directory operands are required to be sorted separately and in lexicographical order.

It is requried to implement the following options:
-a Include directory entries whose names begin with a dot (.).
-t Sort by time modified (with the most recently modified first) before sorting the operands by lexicographical order.

## Description
`My_ls` is a simple implementation of the `ls` command in C, designed to display directory contents and file information. It allows users to see the files and content in different directories and organizes the output in lexicographical order. Users are also able to view a list of directory content sorted by the modification time of the files, starting from the most recently modified.

It utilizes `stat`, `tv_sec`, and `tv_nsec` to retrieve and compare the modification times of files and directories and uses a custom quicksort implementation to sort by time modified as well as alexicographically. The program also contains other custom functions such as `my_strcmp` and `my_strlen` to compare strings and get the length of a string.

This implementation also supports varius command flags such as `-a`, `-t`, `-ta`, and `-at`.

-a includes the directories whose names begin with a dot (.).
-t sorts by the time modified, starting with the most recently modified; operands with the same time are then sorted lexicographically.
-at and -ta sort by the time modified, starting with the most recently modified, and includes directories whose names begin with a dot.

## Installation
Users can compile the program using the provided Makefile. Once the repository is cloned, navigate to the project directory and run the following command:
```
make
```

To remove the compiled executable and object files use the following:
```
make clean
```

To completely clean the project directory, removing all compiled files and the executable, use the following:
```
make fclean
```

To recompile the program from scratch after making changes to the source code use the following:
```
make re
```

## Usage
You can clone the project repository from GitHub using the following command:
```
git clone https://github.com/atay3/my_ls.git
```

After compiling the code, run it by using:
```
./my_ls
```

Here's an example of how to use a flag:
```
./my_ls -t
```
This will print the contents of the current directory sorted by time modified.

To pass in other operands such as directory name:
```
./my_ls dir1 dir2
```
where dir1 and dir2 are the directories whose contents will be displayed in lexicographical order.

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>


