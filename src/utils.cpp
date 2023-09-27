#include "utils.h"
#include <fstream>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

Table::Table()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    this->screen_width = w.ws_col;
    this->screen_height = w.ws_row - 2;
}

Table::~Table()
{
    for (int i = 0; i < this->headers.size(); i++)
        free((void*)this->headers.at(i));
    for (int r = 0; r < this->rows.size(); r++)
        for (int i = 0; i < this->rows.at(r).size(); i++)
            free((void*)this->rows.at(r).at(i));
}

int Table::get_col_nb()
{
    return this->col_nb;
}

int Table::get_row_nb()
{
    return this->row_nb;
}

int Table::get_col_max_bytes()
{
    return this->col_max_bytes;
}

int Table::get_row_max_bytes()
{
    return this->row_max_bytes;
}

/* set headers equivalent to clear old table */
void Table::set_headers(const char** head, unsigned sz)
{
    this->~Table();
    this->headers.clear();
    this->rows.clear();
    this->row_nb = this->col_nb = 0;
    this->row_max_bytes = this->col_max_bytes = 0;
    for (unsigned i = 0; i < sz; i++) {
        char* head_cpy = (char*)malloc(strlen(head[i]) + 1);
        memcpy(head_cpy, head[i], strlen(head[i]) + 1);
        this->headers.push_back(head_cpy);
        this->col_nb++;
        this->col_max_bytes += strlen(head[i]);
    }
}

int Table::add_row(const char** row, unsigned sz)
{
    int col_max_bytes = 0;
    std::vector<const char*> item;

    if (sz != this->col_nb)
        return 1;
    for (unsigned i = 0; i < sz; i++) {
        char* row_cpy = (char*)malloc(strlen(row[i]) + 1);
        memcpy(row_cpy, row[i], strlen(row[i]) + 1);
        item.push_back(row_cpy);
        col_max_bytes += strlen(row[i]);
    }
    if (col_max_bytes > this->col_max_bytes)
        this->col_max_bytes = col_max_bytes;
    this->rows.push_back(item);
    this->row_nb++;
    return 0;
}

void Table::draw(char* buffer, int max)
{
    int real_width = this->screen_width + 1;

    /* prepare screen */
    for (int h = 0; h < this->screen_height; h++) {
        memset(&buffer[h * real_width], ' ', this->screen_width);
        buffer[h * real_width + this->screen_width] = '\n';
    }
    /* draw content */
    int sub_w = (int)(this->screen_width / this->get_col_nb());
    int sub_h = (int)(this->screen_height / (this->get_row_nb() + 1));
    for (int i = 0; i < this->col_nb; i++) {
        int win = (this->screen_width + 1) + (i * sub_w + 1);
        this->write_text(buffer, win, sub_w, sub_h,
            this->headers.at(i), strlen(this->headers.at(i)));
        this->write_box(buffer, sub_w * i, sub_w, sub_h);
    }
    for (int r = 0; r < this->row_nb; r++)
        for (int c = 0; c < this->col_nb; c++) {
            int win = (r + 1) * sub_h * (this->screen_width + 1) + c * sub_w;
            int text_win = (c * sub_w + 1)
                + ((r + 1) * sub_h + 1) * (this->screen_width + 1);
            this->write_text(buffer, text_win, sub_w, sub_h,
                this->rows.at(r).at(c), strlen(this->rows.at(r).at(c)));
            this->write_box(buffer, win, sub_w, sub_h);
        }
}

void Table::write_text(char* screen, int win,
    int w, int h, const char* text, int sz)
{
    int pos_w = 0, pos_h = 0;
    char* pos = screen + win;

    for (int i = 0; i < sz; i++) {
        pos[pos_w++] = text[i];
        if (pos_w >= w) { // jump to next line, reset pos pointer
            pos = screen + win + (this->screen_width + 1);
            pos_w = 0;
            pos_h++;
            if (pos_h >= h)
                break;
        }
    }
}

void Table::write_box(char* screen, int win, int w, int h)
{
    char* pos = screen + win;
    memset(pos, '-', w);
    memset(pos + (h - 1) * (this->screen_width + 1), '-', w);
    for (int r = 0; r < h; r++) {
        int curr = r * (this->screen_width + 1);
        pos[curr] = '|';
        pos[curr + w - 1] = '|';
    }
}

void Table::load_table_csv(const char* file)
{
    std::ifstream f_stream;
    char line[5001];
    bool head_flag = true;

    f_stream.open(file);
    while (!f_stream.eof()) {
        std::vector<char*> data;
        memset(line, 0, sizeof(line));
        f_stream.getline(line, sizeof(line) - 1);
        data = this->parse_csv_to_vector(line, strlen(line));
        if (head_flag) {
            this->set_headers((const char**)data.data(), data.size());
            head_flag = false;
        } else {
            this->add_row((const char**)data.data(), data.size());
        }
    }
    f_stream.close();
}

std::vector<char*> Table::parse_csv_to_vector(char* line, int sz)
{
    std::vector<char*> data;
    int cur_pos = 0;
    for (int i = 0; i < sz; i++) {
        if (line[i] == ',') {
            line[i] = 0;
            data.push_back(&line[cur_pos]);
            cur_pos = i + 1;
        }
    }
    data.push_back(&line[cur_pos]);
    return data;
}
