#include <iostream>
#include <vector>

class Table {
private:
    int col_nb, row_nb, col_max_bytes, row_max_bytes;
    std::vector<const char*> headers;
    std::vector<std::vector<const char*>> rows;
    int screen_height, screen_width;

public:
    Table();
    ~Table();
    int get_col_nb();
    int get_row_nb();
    int get_col_max_bytes();
    int get_row_max_bytes();
    void set_headers(const char** head, unsigned sz);
    int add_row(const char** row, unsigned sz);
    void draw(char* buffer, int max);
    void load_table_csv(const char* file);

private:
    void write_box(char* screen, int win,
        int w, int h, char width_delimiter);
    void write_text(char* screen, int win,
        int w, int h, const char* text, int sz);
    std::vector<char*> parse_csv_to_vector(
        char* line, int sz);
};
