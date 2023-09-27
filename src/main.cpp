#include "utils.h"
#include <cstring>
#include <iostream>
#include <vector>

#define MAX 9000

using namespace std;

char buffer[MAX];

void static_test()
{
    Table table;
    const char* head[] = { "name", "Dob", "gender", "prefer" };
    const char* row0[] = { "hiep", "1999", "male", "C" };
    const char* row1[] = { "bach", "1999", "male", "Js" };
    const char* row2[] = { "huong", "1999", "female", "Japanese" };
    const char* row3[] = { "huyen", "1999", "female", "Bubble" };
    const char* row4[] = { "mai", "1999", "female", "Python" };

    table.set_headers(head, 4);
    table.add_row(row0, 4);
    table.add_row(row1, 4);
    table.add_row(row2, 4);
    table.add_row(row3, 4);
    table.add_row(row4, 4);
    table.draw(buffer, MAX);
}

void csv_test()
{
    Table table;
    table.load_table_csv("timetable.csv");
    table.draw(buffer, MAX);
}

int main(int argc, char* argv[])
{
    memset(buffer, 0, MAX);
    //static_test();
    csv_test();
    cout << buffer;
    return 0;
}
