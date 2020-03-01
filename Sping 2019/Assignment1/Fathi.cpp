// FileProj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct values
{
	int pos;
	char key[32];
	char val[256];
};

int main(int argc, _TCHAR* argv[])
{
	bool choosed_db = false;
	string str;
	string str2 = "use";
	string str3 = "set";
	string str4 = "get";
	string str5 = "delete";
	string str6 = "exist";
	string my_file;
	std::getline(cin, str);
	while (str!="exit")
	{
		
		if ((str.find(str2))!=std::string::npos&&str[0]=='u')//use
		{	
			my_file=str.substr(4, str.size());
			ifstream input(my_file,ios::in);
			if (!input)
			{
				input.close();
				ofstream out(my_file, ios::out);
				if (!out)
				{
					cout << "really fuckd up :(";
				}
				out.close();
			}
			else
			{
				input.close();
			}
			choosed_db = true;
		}

		

		if ((str.find(str6)) != std::string::npos&&str[0] == 'e'&&str[3] == 's'&&choosed_db)//exist
		{
			string my = str.substr(6, str.size());
			bool total = false;
			size_t size1 = str.find("(");
			size_t size2 = str.find(")");
			struct values param;

			string val_key = str.substr(size1 + 1, size2 - size1 - 1);

			ifstream input(my_file, ios::in);
			if (!input)
			{
				cout << "file cannot open" << endl;
				input.close();
			}
			while (input)
			{
				input.read(reinterpret_cast<char *>(&param), sizeof(struct values));

				if (input.eof())
				{
					break;
				}
				bool flag = true;
				if (param.pos == 1)
				{
					for (int i = 0; i < val_key.length(); i++)
					{
						if (param.key[i] != val_key[i])
						{
							flag = false;
						}
					}
					if (flag == true)
					{
						cout << "1" << endl;
						total = true;
					}
				}

			}
			input.close();
			if (total == false)
			{
				cout << "0" << endl;
			}
		}

		

		if ((str.find(str3)) != std::string::npos&&str[0] == 's'&&choosed_db)//set
		{
			string val1,val2;
			struct values parameters;
			size_t size1 = str.find("(");
			size_t size2 = str.find(")");
			size_t size3 = str.find("(", size1 + 1);
			size_t size4 = str.find(")", size2 + 1);

			val1 = str.substr(size1+1,size2-size1-1);

			ifstream in(my_file, ios::in);
			if (!in)
			{
				cout << "cannot open the file" << endl;
			}
			struct values pm;
			bool tt = true;
			while (in)
			{
				in.read(reinterpret_cast<char *>(&pm), sizeof(struct values));
				if (in.eof())
				{
					break;
				}
				bool flag = true;
				if (pm.pos == 1)
				{
					for (int i = 0; i < val1.length(); i++)
					{
						if (pm.key[i] != val1[i])
						{
							flag = false;
						}
					}
					if (flag == true)
					{
						tt = false;
					}
				}

			}
			if (tt)
			{
				for (int i = 0; i < val1.length(); i++)
				{
					parameters.key[i] = val1[i];
				}
				parameters.key[val1.length()] = '\0';

				val2 = str.substr(size3 + 1, size4 - size3 - 1);
				for (int i = 0; i < val2.length(); i++)
				{
					parameters.val[i] = val2[i];
				}
				parameters.val[val2.length()] = '\0';

				fstream mf(my_file, ios::in | ios::out | ios::app);
				if (!mf)
				{
					cout << "file cannot open" << endl;
					continue;
				}
				//mf.seekp(ios::end);
				parameters.pos = 1;
				mf.write(reinterpret_cast<const char *>(&parameters), sizeof(struct values));
				mf.close();
			}
			in.close();
			
		}
		
		if ((str.find(str4)) != std::string::npos&&str[0] == 'g'&&choosed_db)//get
		{
			bool total = false;
			size_t size1 = str.find("(");
			size_t size2 = str.find(")");
			struct values param;

			string val_key = str.substr(size1 + 1, size2 - size1 - 1);
			
			ifstream input(my_file, ios::in);
			if (!input)
			{
				cout << "file cannot open" << endl;
				input.close();
			}
			while (input)
			{								
				input.read(reinterpret_cast<char *>(&param), sizeof(struct values));

				if (input.eof())
				{
					break;
				}
				bool flag = true;
				if (param.pos == 1)
				{
					for (int i = 0; i < val_key.length(); i++)
					{
						if (param.key[i] != val_key[i])
						{
							flag = false;
						}
					}
					if (flag == true)
					{
						cout << param.val << endl;
						total = true;
					}
				}
				
			}
			input.close();
			if (total == false)
			{
				cout << "not exist" << endl;
			}
		}

		if ((str.find(str5)) != std::string::npos&&str[0] == 'd'&&choosed_db)//delete
		{
			size_t size1 = str.find("(");
			size_t size2 = str.find(")");
			string val_key = str.substr(size1 + 1, size2 - size1 - 1);

			struct values v;

			ifstream fl(my_file, ios::in);
			if (!fl)
			{
				cout << "cannot open the file" << endl;
				fl.close();
			}

			bool flag_total = false;
			while (fl)
			{
				fl.read(reinterpret_cast<char *>(&v), sizeof(struct values));

				if (fl.eof())
				{
					break;
				}
				bool flag = true;
				if (v.pos == 1)
				{
					for (int i = 0; i < val_key.length(); i++)
					{
						if (v.key[i] != val_key[i])
						{
							flag = false;
						}
					}
					if (flag == true)
					{
						v.pos = 0;
						//fl.seekp();
						int a = fl.tellg();
						int b = a - sizeof(struct values);
						fl.close();
						fstream fl2(my_file, ios::out|ios::in);
						if (!fl2)
						{
							cout << "cannot write to file" << endl;
							continue;
						}
						fl2.seekp(b);
						fl2.write(reinterpret_cast<const char*>(&v), sizeof(struct values));
						fl2.close();
						flag_total = true;
					}
				}

			}
			fl.close();
			if (flag_total == false)
			{
				cout << "no record found" << endl;
			}
		}
		cout << my_file << "> ";
		std::getline(cin, str);
	}
	return 0;
}

