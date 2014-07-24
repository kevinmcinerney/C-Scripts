/*It should have similar interface and behavior as strcmp, except for case insensitivity:
int mystrcmp(const char * str1, const char * str2);
It should return 0 for strings "test" and "TeSt", like strcmp does for identical strings. It should return 
1 for "Ireland" and "Dublin", and -1 for "Dublin" and "Ireland", because these strings are different, 
even in the lower case. The - sign shows that the first character that does not match has a lower 
lexicographical value in the first string.The submitted code should not contain main. On your 
laptop you need main to test how mystrcmp works. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int mystrcmp(const char* str1, const char* str2);
int mystrcmp(const char* str1, const char* str2)
{
    char strL1;
    char strL2;


    int ans = 0;
    int i = 0;
    while ((strL1 = str1[i]) || (strL2 = str2[i]) !='\0') {
            strL1 = tolower(str1[i]);
            strL2 = tolower(str2[i]);
        if (strL1 != strL2){
            if (strL1 > strL2){
                ans = 1;
                break;
            }
            else if (strL2 > strL1){
                ans = -1;
                break;
            }
        }
        else{
            ans= 0;
            
        }
        i++;
    }
    //printf("Strings Equal \n");
    return ans;
}


/*myps should not handle any program arguments. ps should be invoked with -o option to print pid and command line of all processes run by the root user (-u option), in two columns. Please, check man ps about the custom-format output. The output of ps should be pipelined to C and printed with all lines numbered as follows:
$ ./myps
1: 1234 /path/to/program1 arguments
2: 4356 /path/to/program2 arguments
Some system processes does not have corresponding programs and may be in brackets and without arguments.
On your laptop, you may need to add #define _GNU_SOURCE in the first line of your code. Please, see comp30570-L13 about pipelining.*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main()
{
  
    FILE* fp = popen( "ps auxwe -U root -u root u | awk 'BEGIN { OFS=\" init .\" } { print $2, $11 }'", "r");
    if (fp == NULL){
        printf("The command returned nothing!");
    }
    char path[256];
    int count = 0;
    while ( fgets( path, 256, fp) != NULL ){
        if (count != 0 ){
                printf("%d: %s",count, path );
        }
        count++;
    }
    return pclose(fp);
}

/* Implement myls tool that prints out in a column the list of all entries in a directory. The directory name is 
specified by the input argument. If the argument is missing, take the current working directory. The entries should
be taken from the directory only, excluding the entries from subdirectories (no recursion!). Do not sort the
entries and do not print out dot (".") and dot-dot ("..") directories. What do these directories represent? myls 
should be invoked as follows:
$ ./myls
or
$ ./myls name 
and return the following output:
directory1 
file1
With -l option, myls should print two columns: column of letters f (file), d (directory), l (link), o (other)
and column of names:
 $ ./myls -l name
d directory1
f file1
On your laptop, you need to add #define _GNU_SOURCE in the first line of your code. You should use file system API 
to iterate over directory entries and getopt to handle -l option. The directory name argument should not be handled 
by getopt. You can access this argument after the getopt loop by using argv[optind] (please, see the last example 
in comp30570-L10). You should handle the case of missing directory name:
$ ./myls -l
In this case, you should use the current working directory and print out its entries in two columns. 
Hint: after the getopt loop, optind will be equal to argc.

                                                                                                                                        #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]) {
    bool col = false;
    int opt;
    DIR* dp;
    struct stat st;

  while ((opt = getopt(argc, argv, "hl")) != -1){
    switch (opt) {
      case 'h':
        fprintf(stderr, "Usage: %s [-d directory] [-l ] \n", argv[0]);
        exit(EXIT_SUCCESS);
        break;
      case 'l':
        col = true;
        break;
      default:
        fprintf(stderr, "Usage: %s [-d directory] [-l ] \n", argv[0]);
        exit(EXIT_FAILURE);
        break;
    }   
  }
    if (argv[optind] == NULL)
    dp = opendir("./");
    else
    dp = opendir(argv[optind]);
    
    struct dirent *ent;
    if (dp != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dp)) != NULL) {
        
        //char full_path[512] = realpath("./");
        //strcat(full_path, ent->d_name);
        //lstat(full_path, &st);  
        
        lstat(ent->d_name, &st);
        char* c = ent->d_name;
        if(strcmp(c, ".") != 0 && strcmp(c, "..") != 0){
            if (col){
                if (ent->d_type == DT_DIR)
                        printf("d ");

               else if (ent->d_type == DT_REG)
                        printf("f ");

               else if (ent->d_type == DT_LNK)
                        printf("l ");

               else
                        printf("o ");

            }
            printf ("%s\n", ent->d_name);
        }
    }
    closedir (dp);
    }
}


