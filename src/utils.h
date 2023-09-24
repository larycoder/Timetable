#include <iostream>
#include <vector>

class Table {
private:
    int col_nb, row_nb, col_max_bytes, row_max_bytes;
    std::vector<const char*> headers;
    std::vector<std::vector<const char*>> rows;
    int screen_height = 20, screen_width = 80;

private:
    void write_box(char* screen, int win, int w, int h);
    void write_text(char* screen, int win,
        int w, int h, const char* text, int sz);

public:
    Table();
    int get_col_nb();
    int get_row_nb();
    int get_col_max_bytes();
    int get_row_max_bytes();
    void set_headers(const char** head, unsigned sz);
    int add_row(const char** row, unsigned sz);
    void draw(char* buffer, int max);
};
