#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

#include "Validation.h"

class Table: public Validation
{
private:
    vector<vector<string>> t;
public:
    void start_menu();
    string calculate_formula(string );
    double take_value_of_cell(string);
    int* table_shaping();
    void edit(string,string);
    void load_data_from_file(string );
    void resize_table(int , int );
    void resize_cols(int );
    void resize_rows(int );
    void print ();
};

#endif // TABLE_H
