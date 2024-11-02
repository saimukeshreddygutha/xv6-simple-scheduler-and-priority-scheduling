#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFFER_SIZE 1024

int is_input_from_pipe() {
    struct stat st;
    fstat(0, &st);
    return st.type != T_DEV;
}

void print_and_copy(char *cur_line, char *prev_line) {
    printf(1, "%s\n", cur_line);
    strcpy(prev_line, cur_line);
}

int compare_lines(char *line1, char *line2, int width) {
    if (width == 0) {
        while (*line1 && *line2 && *line1 == *line2) {
            line1++;
            line2++;
        }
        return *line1 == *line2;
    } else {
        for (int i = 0; i < width; i++) {
            if (*line1 != *line2) return 0;
            if (!*line1 || !*line2) break;
            line1++;
            line2++;
        }
        return 1;
    }
}

void process_line(char *line, char *prev_line, int *count, int show_count, int show_uniq) {
    if(!show_count && !show_uniq){
        printf(1, "%s\n", prev_line);
    }
    else if (show_count && *count > 0) {
        printf(1, "%d %s\n", *count, prev_line);
    } else if (show_uniq && *count == 1) {
        printf(1, "%s\n", prev_line);
    }
    strcpy(prev_line, line);
    *count = 1;
}

int main(int argc, char *argv[]) {
    int fd = 0;  
    int show_count = 0, show_uniq = 0, width = 0;
    int i = 1;
    if(is_input_from_pipe()){fd = 0;}
    else{
        if(argc == 1){printf(1, "Error: uniq [options] <filename>\n");exit();};
        if((fd = open(argv[argc - 1], O_RDONLY)) == -1) {
            printf(1, "Couldn't open the file %s\n", argv[argc - 1]);
            exit();
        }
    }
    while(i < argc){
        if(argv[i][0] == '-'){
            switch(argv[i][1]){
                case 'c':
                    show_count = 1;
                    break;
                case 'u':
                    show_uniq = 1;
                    break;
                case 'w':
                    if (i + 1 < argc) width = atoi(argv[++i]);
                    break;
                default:
                    printf(1, "Error: uniq [options] <filename>, options can only be -c, -u, -w [N]\n");
                    exit();
            }
        }
        i++;
    }

    char buffer[BUFFER_SIZE], prev_line[BUFFER_SIZE] = "";
    int count = 0, is_first_line = 1, n;
    
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < n; i++) {
            char line[BUFFER_SIZE];
            int j = 0;
            while (i < n && buffer[i] != '\n') line[j++] = buffer[i++];
            line[j] = '\0';

            if (is_first_line) {
                strcpy(prev_line, line);
                count = 1;
                is_first_line = 0;
            } else if (compare_lines(prev_line, line, width)) {
                count++;
            } else {
                process_line(line, prev_line, &count, show_count, show_uniq);
            }
        }
    }

    if (count > 0 && !is_first_line) {
        process_line("", prev_line, &count, show_count, show_uniq);
    }

    if (n < 0) {
        printf(1, "uniq: couldn't read the file\n");
    }

    close(fd);
    exit();
}

