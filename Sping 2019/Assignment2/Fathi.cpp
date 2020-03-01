// MAP Classifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#define e 2.72//neper number
#define pi 3.14//pi number
using namespace std;

float calculation(vector<float> data,float xi)
{
	
	float average=0;
	for (int i = 0; i < data.size(); i++)
	{
		average += data[i];
	}
	average = average / data.size();//average of data
	if (average ==data[0])//if all datas are equals you can ignore they effect so reture 1
	{
		return 1;
	}

	float variance=0;
	for (int i = 0; i < data.size(); i++)
	{
		variance += (average - data[i])*(average - data[i]);
	}
	
	
	variance = variance / (data.size() - 1);//this is variance ^ 2

	float temp2;
	temp2 = (-1)*powf((xi - average), 2) / (2 * variance);//last part of function
	

	float temp1;
	temp1 = (1 / sqrtf(2 * pi*variance))*powf(e,temp2);
	return temp1;//return the first function result
}
float func_main1(string c_name, vector<string>cname , int num_samples,int data_f)
{
	int counter = 0;
	for (int i = 0; i < cname.size(); i++)
	{
		if (c_name == cname[i])
		{
			counter++;//this is count number of table that belongs to classes k
		}
	}
	
		return (static_cast<float>(counter) / num_samples);//result of first function
}

float func_main2(string c_name, vector<string>cname, vector<vector<float>> t, vector <float>nd)
{
	float tempel = 1;
	vector<float>data_set;
	
	for (int j = 0; j < t[0].size(); j++)
	{
		for (int i = 0; i < cname.size(); i++)
		{
			if (c_name == cname[i])
			{
				data_set.push_back(t[i][j]);//if the tables belongs to classes k its get in calculation
			}
		}
		tempel *= calculation(data_set,nd[j]);//nd[j]		
		data_set.clear();
	}
	return tempel;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int feature_num, record_num;
	string file_name;
	int class_num=3;
	string classes_name_temp;
	vector<string> classes_name;
	

	cout << "enter number of feature" << endl;
	cin >> feature_num;

	cout << "enter number of classes" << endl;
	cin >> class_num;
	for (int i = 0; i < class_num; i++)
	{
		cout << "enter class " << i + 1 << endl;
		cin >> classes_name_temp;
		classes_name.push_back(classes_name_temp);
	}

	cout << "enter file name" << endl;
	cin >> file_name;

	float temp;
	string str;
	vector < float > data;
	vector<vector<float>> table;
	vector<string> data_classes;

	ifstream input(file_name, ios::in);
	input >> record_num;
	for (int i = 0; i < record_num;i++)
	{
		for (int j = 0; j < feature_num ; j++)
		{
			input >> temp;
			data.push_back(temp);
		}
		input >> str;
		data_classes.push_back(str);
		table.push_back(data);
		data.clear();
	}
	input.close();
	cout << table.size() << endl;

	cout << "enter your new data number" << endl;
	int new_data_num;
	cin >> new_data_num;
	int counter_newdata_num=0;
	vector<float> items;
	float get_item;
	float result;
	float tem = 0;
	float index = 0;
	while (counter_newdata_num < new_data_num)
	{
		cout << "enter your new data" << endl;
		for (int i = 0; i < feature_num; i++)
		{
			cin >> get_item;
			items.push_back(get_item);
		}

		for (int i = 0; i < class_num; i++)
		{
			result = func_main2(classes_name[i], data_classes, table, items)* func_main1(classes_name[i], data_classes, table.size(), feature_num);
			if (result > tem)
			{
				tem = result;
				index = i;
			}
			//cout << classes_name[i] << "      " << result << endl;
		}
		cout << classes_name[index] << endl;
		items.clear();
		counter_newdata_num++;
	}
	return 0;
}

