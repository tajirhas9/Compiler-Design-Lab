#include <bits/stdc++.h>
using namespace std;

string table[5][6];

void table_entry()
{
    table[0][0] = "Te";
    table[0][3] = "Te";
    table[1][1] = "+Te";
    table[1][4] = "x";
    table[1][5] = "x";
    table[2][0] = "Ft";
    table[2][3] = "Ft";
    table[3][1] = "x";
    table[3][2] = "*Ft";
    table[3][4] = "x";
    table[3][5] = "x";
    table[4][0] = "i";
    table[4][3] = "(E)";
}

void table_display(string a[5][6], string rows[5], string cols[6])
{
    cout << "\t";
    for (int k = 0; k < 6; k++)
        cout << cols[k] << "\t";
    cout << endl;
    int flag = -1;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (flag == -1)
            {
                cout << rows[i] << "\t";
                flag = 0;
            }
            cout << table[i][j] << "\t";
        }
        flag = -1;
        cout << endl;
    }
}

int main()

{
#ifdef tajir
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            table[i][j] = "null";
    table_entry();
    string cols[6] = {"i", "+", "*", "(", ")", "$"}, rows[5] = {"E", "e", "T", "t", "F"};
    string temp_row, temp_col;
    table_display(table, rows, cols);
    string input;
    input = "+ii+i*$"; //i+i*i$
    //cin>>input;
    int length = input.length();
    int done;
    string check[100] = {"null"};
    string stacc = "+iE$";
    cout << "stack = " << stacc << "\tinput = " << input << endl;
    //cout<<typeid(stacc[0]).name()<<endl;;
    while (1) //&& input[0] != '$')
    {
        done = 0;
        //cout<<"while e somossa"<<endl;
        if (stacc[0] == '$' && input[0] != '$')
        {
            cout << "wrong" << endl;
            break;
        }
        if (stacc[0] == '$' && input[0] == '$')
        {
            cout << "parse successful" << endl;
            break;
        }
        temp_row = stacc[0];
        temp_col = input[0];
        cout << stacc[0] << "\t" << input[0] << endl;
        cout << "stack = " << stacc << "\tinput = " << input << endl;
        if (temp_row == temp_col)
        {
            input.erase(input.begin() + 0);
            stacc.erase(stacc.begin() + 0);
            cout << "stack = " << stacc << "\tinput = " << input << endl;
            continue;
        }
        //cout<<temp_row<<endl<<temp_col<<endl;
        for (int i = 0; i < 5; i++)
        {
            if (done == 1)
                break;
            //cout<<"first for e somossa"<<endl;
            if (rows[i] == temp_row)
                for (int j = 0; j < 6; j++)
                {
                    //cout<<"second for e somossa"<<endl;
                    if (cols[j] == temp_col)
                    {
                        if (table[i][j] == "null")
                        {
                            cout << "wrong" << endl;
                            done = 1;
                            exit(0);
                            break;
                        }
                        string temp_str;
                        temp_str = table[i][j];
                        if (temp_str == "x")
                        {
                            stacc.erase(0, 1);
                            done = 1;
                            break;
                        }
                        else
                        {
                            stacc.replace(0, 1, temp_str);
                            done = 1;
                            break;
                        }
                        //cout<<temp_row<<endl<<temp_col<<endl<<endl;
                        //break;
                    }
                }
        }
    }
    //get_output(input, stacc, table, rows, cols);
}