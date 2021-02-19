#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const  int INF = 9999;
class Simulator
{
public:

    struct E
    {
        char from;
        char to;
        int weight;
        E(char from = ' ', char to = ' ',int weight = 0):from(from), to(to),weight(weight){}
    };
    Simulator(int N, int M)
    {
        hash = new char[2*N + 2*M];
        size = 2*N + 2*M;
    }
    ~Simulator()
    {
        delete[] hash;
        for(int i = 0; i < size; ++i)
            delete[] graph[i];
        delete[] graph;
        for(int i = 0; i < size;i++)
            delete[] shortestPaths[i];
        delete[] shortestPaths;

    }
    void createGraphMatrix()
    {
        int n = findElementsOfSet(size);
        size = n;
        graph = new int*[n];
        for(int i = 0; i < n;i++)
            graph[i] = new int[n];
        shortestPaths = new int*[n];
        for(int i = 0; i < n; i++)
            shortestPaths[i] = new int[n];
        for(int i = 0; i < n;i++)
        {
            for(int j = 0; j < n;j++)
            {
                if(i == j)
                {
                    graph[i][j] =0;
                    shortestPaths[i][j] =0;
                }
                else
                {
                    graph[i][j] =INF;
                    shortestPaths[i][j] =INF;
                }
            }
        }
        for(auto it = G.begin(); it != G.end(); ++it)
        {
            int i = -1, j = -1;
            for(int k = 0; k < size;k++)
            {
                if(hash[k] == (*it).from)
                    i = k;
                if(hash[k] == (*it).to)
                    j = k;
                if(i != -1 && j != -1)
                    break;
            }
            graph[i][j] = (*it).weight;
            shortestPaths[i][j] = graph[i][j];
        }
 /*       for(int i = 0; i < size; i++)
        {
            cout<<endl;
            for(int j = 0; j < size; j++)
            {
                cout<<graph[i][j]<<" ";
            }
        }*/
    }
    void createHashFunc()
    {
        int count = 0;
        for(; count < necklace_1.size();count++)
         {
              hash[count] = necklace_1[count];
         }
        for(int i = 0; i < necklace_2.size();i++)
         {
              hash[count] = necklace_2[i];
              count++;
         }
         for(auto it = G.begin(); it != G.end();++it)
         {
                hash[count] = (*it).from;
                count++;
                hash[count] = (*it).to;
                count++;
         }
    }
    void LoadDataGraph(char a,char b,int n)
    {
        G.push_back(E(a,b,n));
    }
    void LoadDataNecklace_1(string S)
    {
        necklace_1 = S;
    }
    void LoadDataNecklace_2(string S)
    {
        necklace_2 = S;
    }
    int findElementsOfSet(int n)
    {
        int count = 0;
        char* arr = new char[n];
        bool exist;
        for(int i = 0; i < n; i++)
        {
            exist = false;
            for(int j = 0; j < count; j++)
            {
                if(hash[i] == arr[j])
                {
                    exist = true;
                    break;
                }
            }
            if(!exist)
            {
                arr[count] = hash[i];
                count++;
                exist = false;
            }
        }
        delete[] hash;
        hash = new char[count];
        for(int i = 0; i < count;i++)
            hash[i] = arr[i];
        delete[] arr;
        return count;
    }

    void compareNecklaces()
    {
        int min = INF;
        int sum = 0;
        bool terminate = true;
        for(int i = 0; i < necklace_1.size();i++)
        {
            min = INF;
            if(necklace_1[i] == necklace_2[i])
                continue;
            else
            {
               // cout<<endl;
                int p1 = -1,p2 = -1;
                for(int j = 0; j < size;j++)
                {
                    if(hash[j] == necklace_1[i])
                        p1 = j;
                    if(hash[j] == necklace_2[i])
                        p2 = j;
                    if(p1 != -1 && p2 != -1)
                        break;
                }
               // cout<<p1<<" "<<p2;
                for(int j = 0; j < size; j++)
                {
                    /*if(shortestPaths[p1][p2] < min)
                    {
                        min =  shortestPaths[p1][p2];
                        necklace_1[i] = hash[j];
                        necklace_2[i] = hash[j];
                    }
                    if(shortestPaths[p2][p1] < min)
                    {
                        min =  shortestPaths[p2][p1];
                        necklace_1[i] = hash[j];
                        necklace_2[i] = hash[j];
                    }
                    if( ( shortestPaths[p1][j] + shortestPaths[j][p2] ) < min )
                    {
                        min =  shortestPaths[p1][j] + shortestPaths[j][p2];
                        necklace_1[i] = hash[j];
                        necklace_2[i] = hash[j];
                    }*/
                    if( ( shortestPaths[p1][j] + shortestPaths[p2][j] ) < min )
                    {
                        min =  shortestPaths[p1][j] + shortestPaths[p2][j];
                        necklace_1[i] = hash[j];
                        necklace_2[i] = hash[j];
                    }
                   /* if( ( shortestPaths[p2][j] + shortestPaths[j][p1] ) < min )
                    {
                        min =  shortestPaths[p2][j] + shortestPaths[j][p1];
                        necklace_1[i] = hash[j];
                        necklace_2[i] = hash[j];
                    }*/
                }
            }
            if(min == INF)
            {
                terminate = false;
                cout<<-1<<endl<<"not possible";
                break;
            }
            else sum+=min;



        }
        if(terminate)
        {
            cout<<necklace_1<<" "<<sum;
        }
    }

    void floydWarshallAlgorithm ()
    {

        int i, j, k;

        for (k = 0; k < size; k++)
        {
            for (i = 0; i < size; i++)
            {
                for (j = 0; j < size; j++)
                {
                    if (shortestPaths[i][k] + shortestPaths[k][j] < shortestPaths[i][j])
                        shortestPaths[i][j] = shortestPaths[i][k] + shortestPaths[k][j];
                }
            }
        }
        for(int i = 0;i <size;i++)
            shortestPaths[i][i] = 0;
           /* cout<<endl<<endl<<endl;
        for(int q = 0; q < size; q++)
        {
            cout<<endl;
            for(int w = 0; w < size; w++)
                cout<<shortestPaths[q][w]<<" ";
        }*/

    }
private:
    string necklace_1;
    string necklace_2;
    list<E> G;
    char* hash;
    int** graph;
    int** shortestPaths;
    int size;


};


int main ()
 {
    ifstream file;
    file.open("file.txt",ios::in);
    int M,N;
    file>>M>>N;
    Simulator H(M,N);
    string nec1,nec2;
    file>>nec1>>nec2;
    H.LoadDataNecklace_1(nec1);
    H.LoadDataNecklace_2(nec2);
    char a,b;
    int w;
    while(!file.eof())
    {
        file>>a>>b>>w;
        H.LoadDataGraph(a,b,w);
    }
    file.close();
    H.createHashFunc();
    H.createGraphMatrix();
    H.floydWarshallAlgorithm();
    H.compareNecklaces();

     return 0;
 }
