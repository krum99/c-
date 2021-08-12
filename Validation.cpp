#include "Validation.h"

 bool Validation::is_string(string data)
    {
        return data[0] == '"' && data[data.size() - 1] == '"';
    }
    bool Validation::is_integer(string data)
    {
        int n = data.size();
        if(data[0] != '+' && data[0] != '-' && data[0] > '9' && data[0] < '0' )
            return false;
        for(int i = 1; i < n; i++)
        {
            if(data[i] > '9' || data[i] < '0')
                return false;
        }
        return true;
    }
    bool Validation::is_double(string data)
    {
        int n = data.size();
        if(data[0] != '+' && data[0] != '-' && data[0] > '9' && data[0] < '0' )
            return false;
        int dots = 0;
        for(int i = 1; i < n; i++)
        {
            if(data[i] == '.'  )
                dots++;
            if( (data[i] > '9' || data[i] < '0') && data[i] != '.'  )
                return false;
        }
        return dots == 1;

    }
bool Validation::is_formula(string data)
{
    if(data[0] != '=')
        return false;
    string type;
    int n = data.size();
    for(int i = 1; i < n; i++)
    {
        if(data[i] == ' ')
        {
            i++;
            type="";
        }
        if(data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/' || data[i] == '^' )
        {
            if(data[i+1] != '+' && data[i+1] != '-' && data[i+1] != '*' && data[i+1] != '/' && data[i+1] != '^' )
            {
                type = "";
                continue;
            }
            else
                return false;
        }
        if( (data[i] >= 'A' && data[i] <= 'Z') )
            if(data[i+1] < 'A' || data[i+1] > 'Z')
            {
                type="";
                continue;
            }
            else
                return false;
        if( (data[i] >= '0' && data[i] <= '9') )
            type.push_back(data[i]);
        else
        {
            if(!is_integer(type))
                return false;
            else
                type = "";
        }
    }
   // return true;
    return is_integer(type);
}
