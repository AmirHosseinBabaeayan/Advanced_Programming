#include <iostream>
#include <map>
#include <fstream>
#include <string>

using namespace std;

string table_name = "";
map<string, string>table;
fstream table_file;

string get()
{
    string x;
    char a;
    while ((a = getchar()) != '(') continue;
    while ((a = getchar()) != ')') x = x + a;
    return x;
}

void USE()
{
    cin >> table_name;
    if (table_file.is_open()) table_file.close();
    table.clear();
    string path = "storage/" + table_name + ".csv";
    table_file.open((path).c_str(), ios::in|ios::out);
    if (!table_file.good())
    {
        table_file.open((path).c_str(), ios::in|ios::out|ios::trunc);
        return;
    }
    string line;
    while (getline(table_file, line))
    {
        int index = line.find_first_of(",");
        string key = line.substr(0, index);
        string value = line.substr(index + 1);
        table[key] = value;
    }
}

void update(string path, string key)
{
    fstream tmp;
    tmp.open("storage/tmp.csv", ios::in|ios::out|ios::trunc);
    table_file.close();
    table_file.open((path).c_str(), ios::in|ios::out);
    string line;
    while (getline(table_file, line))
    {
        if (key == line.substr(0, line.find_first_of(","))) continue;
        tmp << line << endl;
    }
    tmp.close();
    table_file.close();
    tmp.open("storage/tmp.csv", ios::in|ios::out);
    table_file.open((path).c_str(), ios::in|ios::out|ios::trunc);
    while (getline(tmp, line)) table_file << line << endl;
    tmp.close();
}

void SET()
{
    string key, value;
    key = get();
    value = get();
    if (table_name == "")
    {
        cout << "Error: No table have chosen. Please chose one first..." << endl;
        return;
    }
    if (table.count(key)) update("storage/" + table_name + ".csv", key);
    table[key] = value;
    string row = key + "," + value;
    table_file << row << endl;
}

void GET()
{
    string x;
    x = get();
    if (table_name == "")
    {
        cout << "Error: No table have chosen. Please chose one first..." << endl;
        return;
    }
    if (table.count(x)) cout << table[x] << endl;
    else cout << "Error: (" << x << ") was not found." << endl;
}

void EXIST()
{
    string x;
    x = get();
    if (table_name == "")
    {
        cout << "Error: No table have chosen. Please chose one first..." << endl;
        return;
    }
    cout << table.count(x) << endl;
}

void DELETE()
{
    string x;
    string path = "storage/" + table_name + ".csv";
    x = get();
    if (table_name == "")
    {
        cout << "Error: No table have chosen. Please chose one first..." << endl;
        return;
    }
    table.erase(x);
    fstream tmp;
    tmp.open("storage/tmp.csv", ios::in|ios::out|ios::trunc);
    table_file.close();
    table_file.open((path).c_str(), ios::in|ios::out);
    string y;
    while (getline(table_file, y))
    {
        if (x == y.substr(0, y.find_first_of(","))) continue;
        tmp << y << endl;
    }
    tmp.close();
    tmp.open("storage/tmp.csv", ios::in|ios::out);
    table_file.close();
    table_file.open((path).c_str(), ios::in|ios::out|ios::trunc);
    while (getline(tmp, y)) table_file << y << endl;
    tmp.close();
}

int main()
{
    string command;
    while (true)
    {
        cout << table_name << ">";
        cin >> command;
        if (command == "USE") USE();
        else if (command == "SET") SET();
        else if (command == "GET") GET();
        else if (command == "EXIST") EXIST();
        else if (command == "DELETE") DELETE();
        else if (command == "EXIT")
        {
            table_file.close();
            break;
        }
        else cout << "No such command." << endl;
    }
    return 0;
}
