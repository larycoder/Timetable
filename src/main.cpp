#include <cstring>
#include <iostream>
#include <vector>

#define MAX 9000

using namespace std;

typedef struct cell {
    int rowSize;
    int colSize;
} Cell;

char buffer[MAX];

void debug(string msg)
{
    cout << "[DEBUG] " << msg << endl;
}

char* get(char const* const string)
{
    char* p = (char*)malloc(strlen(string));
    memcpy(p, string, strlen(string) + 1);
    return p;
}

void drawTable(vector<char*> data, vector<Cell> cellInfo, int num, Cell table)
{
    debug("table: " + to_string(table.rowSize) + ", " + to_string(table.colSize));
    for (int row = 0; row < table.rowSize; row++)
        for (int col = 0; col < table.colSize; col++) {
            // debug(to_string(row) + to_string(col));
            if (col == 0)
                strcat(buffer, "| ");
            else if (col == (table.colSize - 1))
                strcat(buffer, " |\n");
            else if (row == 0 || row == (table.rowSize - 1))
                strcat(buffer, "-");
            else
                strcat(buffer, "#");
        }
}

/**
 * data: list of values
 * num: number of value in single row
 *
 */
void build(vector<char*> data, int num)
{
    vector<Cell> cellInfo;

    // analyze step
    int rowSize, colSize;
    for (int i = 0; i < data.size(); i++) {
        int row = i / num;
        int col = i % num;

        rowSize = 1; // default
        colSize = 0;
        for (int j = 0; j < data.size(); j++)
            if (j % num == col && strlen(data.at(j)) > colSize)
                colSize = strlen(data.at(j));

        cellInfo.push_back({ rowSize, colSize });
    }

    // table size computation
    Cell table = { (int)cellInfo.size() / num + 2, 0 };
    for (int i = 0; i < num; i++) {
        table.colSize += cellInfo.at(i).colSize + 1;
    }

    // draw table
    drawTable(data, cellInfo, num, table);
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
