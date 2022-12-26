#include "utils.h"
#include <string.h>

void debug(std::string msg)
{
    std::cout << "[DEBUG] " << msg << std::endl;
}

/* Clone string to heap memory */
char* get(char const* const string)
{
    char* p = (char*)malloc(strlen(string));
    memcpy(p, string, strlen(string) + 1);
    return p;
}

void draw_table(char* buffer, int row, int col)
{
    char delimiter = '|';
    for (int i = 0; i < row; i++) {
        if (i == 0 || i == (row - 1)) {
            delimiter = '+';
        } else {
            delimiter = '|';
        }

        buffer[i * col] = delimiter;
        buffer[i * col + col - 2] = delimiter;

        memset(buffer + i * col + 1, ' ', col * sizeof(char));

        buffer[i * col + col - 1] = '\n';

    }

    memset(buffer + 0, '-', col * sizeof(char));
    //memset(buffer + (row - 1) * col + 1, '-', col * sizeof(char));
}
