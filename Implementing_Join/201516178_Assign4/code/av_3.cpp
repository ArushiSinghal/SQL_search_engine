#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ios>
using namespace std;
string a[6000000];
long long int b[6000000];
string leff[6000000];
long long int b1[6000000];
int Merge_second1(long long int ini,long long int mid,long long int fin)
{
	for(long long int i=ini;i<=fin;i++)
	{
		leff[i] = a[i];
		b1[i] = b[i];
	}
	long long int k =  ini;
	long long int j = mid + 1;
	long long int m = ini;
	while(k<=mid && j<=fin)
	{
		long long int var1, var2;
                int aa, bb;
                istringstream twonumbers,twonumbers1;
                twonumbers.str(leff[k]);
                twonumbers >> aa >> bb;
                var1 = aa;
                twonumbers1.str(leff[j]);
                twonumbers1 >> aa >> bb;
                var2 = aa;
		if (var2 <= var1)
		{
			a[m] = leff[j];
			b[m] = b1[j];
			j++;
			m++;
		}
		else
		{
			a[m] = leff[k];
			b[m] = b1[k];
			k++;
			m++;
		}
	}
	while (k<=mid)
	{
		a[m] = leff[k];
		b[m] = b1[k];
		m++;
		k++;
	}
	while (j<=fin)
	{
		a[m] = leff[j];
		b[m] = b1[j];
		m++;
		j++;
	}
	return 0;
}

int Merge1(long long int ini,long long int mid,long long int fin)
{
	for(long long int i=ini;i<=fin;i++)
	{
		leff[i] = a[i];
	}
	long long int k =  ini;
	long long int j = mid + 1;
	long long int m = ini;
	while(k<=mid && j<=fin)
	{
		long long int var1, var2;
		int aa, bb;
		istringstream twonumbers,twonumbers1;
		twonumbers.str(leff[k]);
		twonumbers >> aa >> bb;
		var1 = aa;
		twonumbers1.str(leff[j]);
		twonumbers1 >> aa >> bb;
		var2 = aa;
		if (var2 <= var1)
		{
			a[m] = leff[j];
			j++;
			m++;
		}
		else
		{
			a[m] = leff[k];
			k++;
			m++;
		}
	}
	while (k<=mid)
	{
		a[m] = leff[k];
		m++;
		k++;
	}
	while (j<=fin)
	{
		a[m] = leff[j];
		m++;
		j++;
	}
	return 0;
}
void sorting1(long long int num_of_record,long long int initial, int flag)
{
	if(initial == num_of_record-1)
		return;
	long long int mid = (initial+num_of_record-1)/2;
	sorting1(mid+1,initial,flag);
	sorting1(num_of_record,mid+1,flag);
	if (flag == 0)
		Merge1(initial,mid,num_of_record-1);
	else
		Merge_second1(initial,mid,num_of_record-1);
	return;
}

int main_function1(string input_filesname,string output_filenames ,long long int blocks) {
	long long int memory = blocks*100;
	ifstream myfile;
	myfile.open(input_filesname);
	long long int buffer = 0;
	string line;
	while (getline(myfile, line))
	{
		a[0] = line;
		long long int count = 1;
		while (getline(myfile, line))
		{
			a[count] = line;
			count += 1;
			if (count == memory)
				break;
		}
		sorting1(count,0,0);
		string filenames = "firstsort";
		filenames = filenames + to_string(buffer);
		filenames =  filenames + ".txt";
		ofstream ofs(filenames, ios::out | ios::trunc);
		for (long long int i= 0;i<count;i++)
		{
			ofstream log(filenames, std::ios_base::app | std::ios_base::out);
			a[i] = a[i].substr(0, a[i].size());
			log << a[i] << "\n";
		}
		buffer += 1;
	}
	myfile.close();
	////////////////////////////////second phase///////////////////////
	ifstream myfiles[2000];
	for(int i=0;i< buffer;i++)
	{
		string file = "firstsort" + to_string(i) + ".txt";
		myfiles[i].open(file);
	}
	long long int count;
	ofstream ofs(output_filenames, ios::out | ios::trunc);
	while(1)
	{
		count = 0;
		for(int i=0;i< buffer;i++)
		{
			if(myfiles[i].eof() || myfiles[i].peek() == EOF)
				{
					int p;
				}
			else
			{
				streampos oldpos = myfiles[i].tellg();  // stores the position
				getline(myfiles[i], a[count], '\n');
				myfiles[i].seekg (oldpos);   // get back to the position
				b[count] = i;
				count +=1;
			}
		}
		if (count == 0)
			break;
		sorting1(count,0,1);
		ofstream log(output_filenames, ios_base::app | ios_base::out);
		a[0] = a[0].substr(0, a[0].size());
		log << a[0] << "\n";
		getline(myfiles[b[0]], a[0], '\n');
	}
	return 0;
}
