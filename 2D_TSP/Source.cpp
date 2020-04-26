#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class vertix
{
public:
	bool operator==(vertix v)
	{
		return (v.x == x && v.y == y ? true : false);
	}
	long x, y;
};

string record = "";

long Len(vector<vertix> problemVertix)
{
	long len = 0;
	for (size_t i = 0; i < problemVertix.size() - 1; i++)
		len += (long)sqrt(powl(problemVertix.at(i).x - problemVertix.at(i + 1).x, 2) + powl(problemVertix.at(i).y - problemVertix.at(i + 1).y, 2));
	return len;
}

void solver(const vector<vertix> &problemVertix, vector<vertix> included, long &upper_bound)
{
	long lenght = Len(included);

	if (lenght >= upper_bound)
		return;

	vector<vertix> not_included;

	for (size_t i = 0; i < problemVertix.size(); i++)
		if (find(included.begin(), included.end(), problemVertix.at(i)) == included.end())
			not_included.push_back(problemVertix.at(i));

	if (not_included.size() == 0)
	{
		record.clear();
		upper_bound = lenght;
		record += "Result : ";
		for (size_t i = 0; i < included.size(); i++)
			record += "(" + to_string(included.at(i).x) + ", " + to_string(included.at(i).y) + ") ";

		return;
	}

	for (size_t i = 0; i < not_included.size(); i++)
		for (size_t j = 1; j <= included.size() - 1; j++)
		{
			vector<vertix> objNewInclude(included);
			objNewInclude.insert(objNewInclude.begin() + j, not_included.at(i));
			solver(problemVertix, objNewInclude, upper_bound);
		}
}

int main()
{
	int size = 0;

	cout << "Please enter size of TSP : " << endl;
	cin >> size;

	if (size < 3)
		return 1;

	cout << "Enter city locations : " << endl;
	vector<vertix> problemVertix;

	for (size_t i = 0; i < size; i++)
	{
		vertix objVertix;
		cout << "x y : ";
		cin >> objVertix.x >> objVertix.y;
		problemVertix.push_back(objVertix);
	}

	long upper_bound = LONG_MAX; //  hanoz nemidonim kamtarin tol cheghadre binahayat dar nazar migirim

	for (size_t i = 0; i < problemVertix.size(); i++)
	{
		vector<vertix> included;

		included.push_back(problemVertix.at(i)); // ebteda : noghte shoro
		included.push_back(problemVertix.at(i)); // enteha : noghte shoro

		solver(problemVertix, included, upper_bound);
	}

	cout << record;

	fflush(stdin);
	getchar();

	return 0;
}