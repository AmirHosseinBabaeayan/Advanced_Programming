#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <list>
#include <math.h>
using namespace std;

#define _USE_MATH_DEFINES



struct Object //Objects given in dataset will be saved here
{
	string Name;
	list<double> KLengths;
	list<double> KWidths;
	list<double> GLengths;
	list<double> GWidths;

};

struct ExamineObject //Objects given to examine will be saved here
{
	double KLengths;
	double KWidths;
	double GLengths;
	double GWidths;
};


list<string> ExamineData(list<ExamineObject> &examinedata, list<Object> &objs);
void AddDataToList(list<Object> &objs, double KL, double KW, double GL, double GW, string name);
list<Object> LoadDataFromFile();
double Ave(list<double> &nums);
double Variancep(list<double> &nums);
inline float CollectionProbablity(Object obj, int itemcount);
int GetAllFeaturesCount(list<Object> &objs);
inline double FeatureOfObjectInClassProbablityExponentPower(double itemfeature, list<double> &features);
inline double FeatureOfObjectInClassProbablity(double itemfeature, list<double> &features);
list<ExamineObject> ReadExamineData();


int main()
{
	list<Object> objs = LoadDataFromFile();

	cout << GetAllFeaturesCount(objs) << " Data item loaded.\nPlease enter data to examine based on the given template.\n";

	list<ExamineObject> examinedata;
	string name;
	double max = 0;
	string candid;
	double temp = 0;
	list<string> results;

	examinedata = ReadExamineData();
	results = ExamineData(examinedata, objs);

	for each (string result in results)
	{
		cout << result << '\n';
	}

	getch();
	return 0;
}


void AddDataToList(list<Object> &objs, double KL, double KW, double GL, double GW, string name) //checks if the current object should be added or it already exists, so only the features will be added to object
{

	bool added = false;

	for (list<Object>::iterator i = objs.begin(); i != objs.end(); i++)
	{
		Object &obj = *i;
		if (obj.Name == name)
		{
			obj.KLengths.insert(obj.KLengths.end(), KL);
			obj.GLengths.insert(obj.GLengths.end(), GL);
			obj.KWidths.insert(obj.KWidths.end(), KW);
			obj.GWidths.insert(obj.GWidths.end(), GW);
			added = true;
		}
	}
	if (!added)
	{
		Object obj;
		obj.KLengths.insert(obj.KLengths.end(), KL);
		obj.GLengths.insert(obj.GLengths.end(), GL);
		obj.KWidths.insert(obj.KWidths.end(), KW);
		obj.GWidths.insert(obj.GWidths.end(), GW);
		obj.Name = name;
		objs.insert(objs.end(), obj);
	}
	added = false;
}

list<Object> LoadDataFromFile() //Loads data from DataSet.data file, then copies them into a list
{
	list<Object> objs;
	fstream file("DataSet.data");
	double KL, KW, GL, GW;
	string name;
	int ElementCount;

	file >> ElementCount;

	for (int i = 0; i < ElementCount; i++)
	{
		file >> KL;
		file >> KW;
		file >> GL;
		file >> GW;
		file >> name;
		AddDataToList(objs, KL, KW, GL, GW, name);

	}
	return objs;
}


double Ave(list<double> &nums) //calculates the average of given numbers
{
	double total = 0;
	for each (double num in nums)
	{
		total += num;
	}
	return total / nums.size();
}

double Variancep(list<double> &nums) //calculates variance of numbers, squared
{
	double temp = 0;
	double ave = Ave(nums);
	for each (double num in nums)
	{
		temp += pow(num - ave, 2);
	}
	return temp;
}

inline float CollectionProbablity(Object obj, int itemcount) //calculates the P(Ck)
{

	return (double)obj.GLengths.size() / itemcount;
}

int GetAllFeaturesCount(list<Object> &objs) //counts all of the features added into the data list
{
	int total = 0;
	for each (Object obj in objs)
	{
		total += obj.KLengths.size();
	}
	return total;
}

inline double FeatureOfObjectInClassProbablityExponentPower(double itemfeature, list<double> &features) //the name says what it does
{
	return exp(-1 * (pow((itemfeature - Ave(features)), 2) / 2 * Variancep(features)));
}

inline double FeatureOfObjectInClassProbablity(double itemfeature, list<double> &features) //the name says what it does
{
	if (Variancep(features) != 0)
		return FeatureOfObjectInClassProbablityExponentPower(itemfeature, features) / sqrt(2 * 3.1415926535*Variancep(features));
	else
		return 0; //Variance may be 0(for 1 data)
}


list<ExamineObject> ReadExamineData() //reads data to be examined from input
{
	list<ExamineObject> data;
	int elementcount;
	double GL, GW, KL, KW;
	cin >> elementcount;

	for (int i = 0; i < elementcount; i++)
	{
		ExamineObject obj;
		cin >> KL >> KW >> GL >> GW;
		obj.GLengths = GL;
		obj.GWidths = GW;
		obj.KLengths = KL;
		obj.KWidths = KW;
		data.insert(data.end(), obj);
	}
	return data;
}

list<string> ExamineData(list<ExamineObject> &examinedata, list<Object> &objs) //examins given list of ExamineObjects and returns the result as a list
{
	list<string> result;
	double temp, max = 0;
	string candid;
	for each (ExamineObject examineitem in examinedata)
	{
		for each (Object obj in objs) //Find Max Probablity Of The Object
		{
			temp = CollectionProbablity(obj, GetAllFeaturesCount(objs)) * FeatureOfObjectInClassProbablity(examineitem.KLengths, obj.KLengths) * FeatureOfObjectInClassProbablity(examineitem.GLengths, obj.GLengths) * FeatureOfObjectInClassProbablity(examineitem.KWidths, obj.KWidths) * FeatureOfObjectInClassProbablity(examineitem.GWidths, obj.GWidths);
			if (temp > max)
			{
				max = temp;
				candid = obj.Name;
			}
		}
		max = 0;
		result.insert(result.end(), candid);
	}

	return result;
}


