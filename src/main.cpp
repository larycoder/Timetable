#include "utils.h"
#include <cstring>
#include <iostream>
#include <vector>

#define MAX 9000

using namespace std;

char buffer[MAX];

/**
 * data: list of values
 * row_len: number of value in single row
 *
 */
void build(vector<char*> data, int row_len)
{
    draw_table(buffer, 5, 10);
}

void test()
{
    // setup
    vector<char*> pointer;
    pointer.push_back(get("Key 1"));
    pointer.push_back(get("Value 1"));
    pointer.push_back(get("Key 2"));
    pointer.push_back(get("Value 2"));

    // run
    build(pointer, 2);

    // print result
    cout << "[TEST] input:" << endl;
    for (int i = 0; i < pointer.size(); i++)
        cout << pointer.at(i) << ", ";

    cout << "\n\n"
         << "[TEST] output: " << endl
         << buffer << endl;
}

int main(int argc, char* argv[])
{
    memset(buffer, '\0', MAX);
    test();
    return 0;
}
