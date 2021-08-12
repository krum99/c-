#include <iostream>

using namespace std;

#include "Table.h"

int main()
{
    Table t;
    //t.load_data_from_file("pr.txt");
    Table b(t);

    //b.edit("A1", "=C1+C1");
    //b.edit("Y18", "=C1+C1+D4/A2");
   // cout<<endl<<t.take_value_of_cell("C1");
   // b.print();
    b.start_menu();

    return 0;
}
