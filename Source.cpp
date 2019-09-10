/*
Kevin Lehman - 1463553
Tarrant County College - COSC 1437 - Fall 2017
Assignment  3-2 Source Code
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;
void checkSort(vector<string>);
bool binary(string, vector<string>);
bool sequential(string, vector<string>);

vector<string> split(const string& s, const string& delim)
{
	const bool keep_empty = true;
	vector<string> result;

	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true)
	{
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty())
		{
			result.push_back(temp);
		}
		if (subend == s.end())
		{
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

int main()
{
	ifstream inputFile;
	string input;
	string airportSearch;
	vector<string> airportCode;
	vector<string> result;
	int size;
	int length;
	int searchType = 0;
	bool locate;

	inputFile.open("airports.dat");

	if (inputFile)
	{
		cout << "Step 1: Opening File." << endl;

		getline(inputFile, input);

		cout << "Step 2: Reading a line from airport.dat." << endl;

		while (inputFile)
		{
			cout << " Passing current line to split method." << endl;

			result = split(input, ",");

			cout << "Validating airport code is 3 letters in length." << endl;

			cout << result[4] << endl;

			size = result[4].size();

			if (size == 3)
			{
				cout << "Storing valid airport code in new vector." << endl;
				airportCode.push_back(result[4]);
			}
			getline(inputFile, input);
		}

		length = airportCode.size();

		cout << "Step 3: The new vector Airport Code is " << length << " codes long." << endl;

		cout << "Step 4: Checking if vector is sorted." << endl;

		checkSort(airportCode);

		cout << "Step 5: Sorting Vector." << endl;

		sort(airportCode.begin(), airportCode.end());

		cout << "Step 6: Checking if vector is sorted." << endl;

		checkSort(airportCode);
	}
	else
	{
		cout << "There was an error opening the file." << endl;
	}

	while (searchType != 3)
	{
		cout << "Enter 3 character airport code to locate." << endl;
		cin >> airportSearch;

		cout << "Search Options:" << endl;
		cout << "1. Binary Search." << endl;
		cout << "2. Sequential Search." << endl;
		cout << "3. Exit" << endl;

		cin >> searchType;

		if (searchType == 1)
		{
			locate = binary(airportSearch, airportCode);
			if (locate = true)
			{
				cout << "Airport Code was located." << endl;
			}
			else
			{
				cout << "Airport Code was not located." << endl;
			}
		}
		else if(searchType == 2)
		{
			locate = sequential(airportSearch, airportCode);
			if (locate = true)
			{
				cout << "Airport Code was located." << endl;
			}
			else
			{
				cout << "Airport Code was not located." << endl;
			}
		}
		else
		{
			break;
		}
	}
	inputFile.close();
	system("Pause");
	return 0;
}

void checkSort(vector<string> airportCode)
{
	if (is_sorted(airportCode.begin(), airportCode.end()))
	{
		cout << "Vector Airport Code is sorted." << endl;
	}
	else
	{
		cout << "Vector Airport Code is not sorted." << endl;
	}
}

bool binary(string airportSearch, vector<string> airportCode)
{
	int numElements = airportCode.size();;
	bool found = false;
	int index = 0;
	int last = numElements - 1;
	int middle;
	int position = -1;

	while (!found && index <= last)
	{
		middle = (index + last) / 2;
		if (airportCode[middle] == airportSearch)
		{
			found = true;
			position = middle;
		}
		else if (airportCode[middle] > airportSearch)
		{
			last = middle - 1;
		}
		else
		{
			index = middle + 1;
		}
	}
	cout << position << " comparisons were made." << endl;
	return found;
}
bool sequential(string airportSearch, vector<string> airportCode)
{
	int numElements = airportCode.size();;
	bool found = false;
	int index = 0;

	while (index < numElements && !found)
	{
		if (airportCode[index] == airportSearch)
		{
			found = true;
		}
		index++;
	}
	cout << (index + 1) << " comparisons were made." << endl;
	return found;
}