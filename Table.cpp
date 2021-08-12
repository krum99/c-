#include "Table.h"


void Table::start_menu()
{
    string file_name = "";
    bool is_open = false;
    string option;
    cout<<endl<<"Enter command:"<<endl;
    cin>>option;
    for_each(option.begin(), option.end(), [](char& c)
    {
        c=::tolower(c);
    });
    while(option != "exit")
    {
        if(option == "open")
        {
            string path;
            cin>>path;
            load_data_from_file(path);
            file_name = path;
            is_open = true;
            cin>>option;
            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;
        }
        else if(option == "save")
        {
            if(is_open)
            {
                fstream out(file_name,ios::out);
                for(int i = 0; i < t.size();i++)
                {
                    for(int j = 0; j < t[0].size() - 1; j++)
                    {
                        if(is_integer(t[i][j] ) || is_double(t[i][j]))
                            out<<t[i][j]<<" ,";
                        else
                            out<<"\""<<t[i][j]<<"\"" ;
                    }
                    if(is_integer(t[i][t[0].size() - 1] ) || is_double(t[i][t[0].size() - 1]))
                        out<<t[i][t[0].size() - 1]<<"\n";
                    else
                        out<<"\""<<t[i][t[0].size() - 1]<<"\""<<"\n";
                }
                out.close();
                cin>>option;

                for_each(option.begin(), option.end(), [](char& c)
                {
                    c=::tolower(c);
                });
                continue;
                }
                else
                {
                    cout<<"there is no open file";
                }
        }
        else if(option == "saveas")
        {
            string path;
            cin>>path;
            fstream out(path,ios::out);
            for(int i = 0; i < t.size();i++)
            {
                for(int j = 0; j < t[0].size() - 1; j++)
                {
                    if(is_integer(t[i][j] ) || is_double(t[i][j]))
                        out<<t[i][j]<<" ,";
                    else
                        out<<"\""<<t[i][j]<<"\"" ;
                }
                if(is_integer(t[i][t[0].size() - 1] ) || is_double(t[i][t[0].size() - 1]))
                    out<<t[i][t[0].size() - 1]<<"\n";
                else
                    out<<"\""<<t[i][t[0].size() - 1]<<"\""<<"\n";
            }
            out.close();
            cin>>option;

            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;
        }
        else if(option == "close")
        {
            file_name = "";
            is_open = false;
            cin>>option;

            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;

        }
        else if (option == "print")
        {
            print();
            cin>>option;

            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;
        }
        else if (option == "edit")
        {
            string  cell, value;
            cin>>cell>>value;
            edit(cell,value);
            cin>>option;

            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;
        }
        else
        {
            cout<<"invalid command, pleasy try again."<<endl;
            cin>>option;

            for_each(option.begin(), option.end(), [](char& c)
            {
                c=::tolower(c);
            });
            continue;

        }
    }
    cout<<"Do you want to save the changes on the table on the current file? (y/n)"<<endl;
    char answer;
    cin>>answer;
    if(answer == 'y')
    {
            if(is_open)
            {
                fstream out(file_name,ios::out);
                for(int i = 0; i < t.size();i++)
                {
                    for(int j = 0; j < t[0].size() - 1; j++)
                    {
                        if(is_integer(t[i][j] ) || is_double(t[i][j]))
                            out<<t[i][j]<<" ,";
                        else
                            out<<"\""<<t[i][j]<<"\"" ;
                    }
                    if(is_integer(t[i][t[0].size() - 1] ) || is_double(t[i][t[0].size() - 1]))
                        out<<t[i][t[0].size() - 1]<<"\n";
                    else
                        out<<"\""<<t[i][t[0].size() - 1]<<"\""<<"\n";
                }
                out.close();
            }
            else
                cout<<"there is no open file";
            return;
    }
    else
        return;
}


string Table::calculate_formula(string formula)
{
    if(formula[0] == '=')
    {
        vector<char> operators;
        vector<double> numbers;
        for(int i = 1; i < formula.size(); i++)
        {
            if(formula[i] == ' ')
                continue;
            else if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^' )
                operators.push_back(formula[i]);
            else
            {
                string cell;
                cell.push_back(formula[i]);
                i++;
                while(formula[i] >= '1' && formula[i] <= '9')
                {
                    cell.push_back(formula[i]);
                    i++;
                }
                i--;
                numbers.push_back( take_value_of_cell(cell) );
            }
        }
        //Storing the operators and the numbers the same order as the formula represents the formula itself
        //Actually every vector with n operators and vector with n+1 doubles represents only one formula (semantic level i mean...)
        for(int i = 0; i < operators.size(); i++)
        {
            if(operators[i] == '^')
            {
                numbers[i] = pow(numbers[i],numbers[i+1]);
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i );
                i--;
            }
        }
        for(int i = 0; i < operators.size(); i++)
        {
            if(operators[i] == '/')
            {
                if(numbers[i+1] != 0)
                {
                    numbers[i] = numbers[i]/numbers[i+1];
                    numbers.erase(numbers.begin() + i + 1);
                    operators.erase(operators.begin() + i );
                    i--;
                }
                else
                    return"#ERROR";
            }
            if(operators[i] == '*')
            {
                numbers[i] = numbers[i]*numbers[i+1];
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i );
                i--;
            }
        }
        /* for(int i = 0; i< numbers.size(); i++)
             cout<<numbers[i]<<"  ";*/
        for(int i = 0; i < operators.size(); i++)
        {
            if(operators[i] == '+')
            {
                numbers[i] = numbers[i]+numbers[i+1];
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i );
                i--;

            }
            if(operators[i] == '-')
            {
                numbers[i] = numbers[i]-numbers[i+1];
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i );
                i--;
            }
        }
        // cout<<endl<<numbers[0]<<endl;
        return to_string(numbers[0]);
    }
    else
    {
        cout<<"Formula is invalid"<<endl;
        exit(1);
    }
}
double Table::take_value_of_cell(string cell)
{
    int col = (cell[0] - 'A');
    string a;
    for(int i = 1; i < cell.size(); i++)
        a.push_back(cell[i]);
    cell = a;
    int row = atoi(cell.c_str()) - 1;//atoi converts string to int
    //cout<<row<<"  "<<col<<t[row][col]<<endl;
    if(col >= t[0].size() || row >= t.size() )
        return 0.0;
    else if(!(is_integer(t[row][col]) || is_double(t[row][col]) ))
        return 0.0;
    else
        return stod(t[row][col]); // stod converts string to double

}
int* Table::table_shaping()
{
    int* m =new int[t[0].size()];
    for(int i = 0; i < t[0].size(); i++)
    {
        m[i] = t[0][i].size();
        for(int j = 1; j < t.size(); j++)
        {
            if(m[i] < t[j][i].size())
            {
                m[i] = t[j][i].size();
            }
        }
    }
    return m;
}
void Table::edit(string cell, string value )
{
    if(is_integer(value) || is_double(value) || is_string(value) || is_formula(value) )
    {
        int col = cell[0] - 'A';
        string a;
        for(int i = 1; i < cell.size(); i++)
            a.push_back(cell[i]);
        cell = a;
        int row = atoi(cell.c_str()) - 1;
        if(col >= t[0].size() || row >= t.size() )
            resize_table(col+1,row+1);
        if(is_formula(value))
            t[row][col]=calculate_formula(value);
        else
            t[row][col]=value;

        return;
    }
    else
    {
        cout<<"Invalid data"<<endl;
        return;
    }

}


void Table::load_data_from_file(string filename)
{
    fstream in(filename,ios::in|ios::app);
    //cout<<in.is_open();
    string line;
    string cell;
    vector<string> row;
    if(in.is_open())
    {
        while(getline(in,line))
        {
            for(int i = 0; i < line.size(); i++)
            {
                while(line[i] != ',' && i < line.size())
                {
                    cell.push_back(line[i]);
                    i++;
                }
                cell.erase (remove (cell.begin(), cell.end(), ' '), cell.end());
                if(cell[0] == '"')
                {
                    cell.erase(0,1);
                    cell.erase(cell.size()-1,1);
                }

                row.push_back(cell);
                cell.clear();
            }
            t.push_back(row);
            row.clear();

        }
    }
    else
        cout<<"File opening failed"<<endl;
    in.close();
    int max = 0;
    for(int i = 0; i < t.size(); i++)
    {
        if(max < t[i].size())
        {
            max = t[i].size();
        }
    }
    //cout<<"max:  "<<max<<endl;
    for(int i = 0 ; i < t.size(); i++)
    {
        int k = max - t[i].size();
        for(int j = 0; j < k; j++)
        {
            t[i].push_back(string("") );
        }
    }
    //checks if the data is valide
    for(int i = 0; i < t.size(); i++)
    {
        for(int j = 0; j < t[0].size(); j++)
        {
            if( is_formula(t[i][j]) )
                t[i][j] = calculate_formula( t[i][j] );
        }
    }
    return;

}

void Table::resize_table(int m, int n)
{
    resize_rows(m);
    resize_cols(n);
}

void Table::resize_cols(int n = 0)
{
    if(n > t.size())
    {
        vector<string> s;
        for(int i = 0; i < t[0].size(); i++)
        {
            s.push_back(string(" ") );
        }
        while(n > t.size())
            t.push_back(s);
    }

}

void Table::resize_rows(int n = 0)
{
    if(n > t[0].size())
    {
        for(int i = 0 ; i < t.size(); i++)
        {
            int k = n - t[i].size();
            for(int j = 0; j < k; j++)
            {
                t[i].push_back(string(" ") );
            }
        }
    }

}

void Table::print ()
{
    int n = t.size();
    int* align = table_shaping();
    // for(int i = 0; i < t[0].size(); i++)
    // cout<<align[i]<<" ";
    //cout<<endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < (int)(t[i].size()); j++)
        {
            cout<<t[i][j];
            int k = align[j] - t[i][j].size();
            for(int c = 0; c < k; c++)
            {
                cout<<" ";
            }
            cout<<"|";
        }
        cout<<endl;
    }
    delete[] align;
    return;
}
