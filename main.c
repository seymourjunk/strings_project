#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 4096
#define DEFAULT_STR_LEN 4

void find_and_print_strings(FILE* fp, size_t n)
{
    char read_buffer[BUFFER_SIZE];
    char temp_str[BUFFER_SIZE];
    size_t current_pos = 0; 
    size_t bytes_read = 0;
    size_t string_offset = 0x0;
    size_t file_offset = 0x0;
    bool new_string = false;


    printf("  offset     len    string\n");
    printf("--------------------------\n");
    while ((bytes_read = fread(read_buffer, 1, BUFFER_SIZE, fp)) > 0)
    { 
        for (size_t i = 0; i < bytes_read; i++)
        {
            if (isprint(read_buffer[i]))
            {
                if (!new_string)
                {
                    string_offset = file_offset;
                    new_string = true;
                }
                temp_str[current_pos++] = read_buffer[i];
            }
            else
            {
                if (current_pos >= n)
                {
                    temp_str[current_pos] = '\0';
                    printf("0x%08zx    %-2zu      %s\n", string_offset, current_pos, temp_str);
                }
                new_string = false;
                current_pos = 0;
            }
            file_offset++;
        }
    }

    // if last character is printable -- not EOF
    if (current_pos >= n)
    {

        temp_str[current_pos] = '\0'; 
        printf("0x%08zx    %-2zu      %s\n", string_offset, current_pos, temp_str);
    }
}


// argv[1] -- <file>
// argv[2] -- <lenght for searching string>
int main(int argc, char* argv[])
{
    size_t n_len = DEFAULT_STR_LEN;
    
    if (argc == 1 || argc > 3)
    {
        fprintf(stderr, "Usage: %s <file> [length_string]\n", argv[0]);
        return 1;
    }

    if (argc == 3)
    {
        char* endptr;
        long input_len = strtol(argv[2], &endptr,  10);
        if (*endptr != '\0' || input_len <=0)
        {
            fprintf(stderr, "Invalid length: %s\n", argv[2]);
            return 1;
        }
        n_len = (size_t)input_len;
    }
    
    FILE *fp = fopen(argv[1], "rb");

    if (!fp)
    {
        perror("File opening failed");
        return 1;
    }
    
    find_and_print_strings(fp, n_len);

    fclose(fp);
    return 0;
}
