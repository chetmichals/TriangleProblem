#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector <vector<int>> inputValues;
vector <vector<int>> maxValues; 

//Function Prototypes
void ReadFile();
int GetMaxValue(int rowNumber = 0, int columnNumber = 0);
int GetMaxValueDynamic();

//Main
int main()
{
	ReadFile();
	//cout << GetMaxValue
	cout << GetMaxValueDynamic() << endl;
	system("pause");
}

//Function Defintions

//Used to read in the input file. File uses full path for simplicity. 
void ReadFile()
{
	string line;
	string number;
	ifstream inputFile("Z:\\triangle.txt");

	//Get a line from input file, place values into vector
	while (getline(inputFile, line))
	{
		vector<int> newRow;
		istringstream lineStringStream;
		lineStringStream.str(line);

		//Parce out each number from the file
		while (getline(lineStringStream, number, ' '))
		{
			newRow.push_back(stoi(number));
		}
		inputValues.push_back(newRow);
	}
}

//Recursive way to get the max value. Technically works, but slow. I believe this is O(2^N)? What I know is I programed the second version before this one finished running.  
int GetMaxValue(int rowNumber, int columnNumber)
{
	if (rowNumber >= inputValues.size()) return 0;
	int myNumber = inputValues[rowNumber][columnNumber];
	int pathA = GetMaxValue(rowNumber + 1, columnNumber);
	int pathB = GetMaxValue(rowNumber + 1, columnNumber + 1);

	if (pathA > pathB) myNumber += pathA;
	else myNumber += pathB;

	return myNumber;	
}


//Uses a dynamic programing technique to find the largest value possible at each point.
int GetMaxValueDynamic()
{
	int rowCount = inputValues.size();

	//Determine the highest possible value for each element
	for (int i = 0; i < rowCount; i++)
	{
		vector<int> maxValuesRow;
		int currentValue = 0;
		int columnCount = inputValues[i].size();
		for (int j = 0; j < columnCount; j++)
		{
			currentValue = inputValues[i][j];
			if (i > 0)
			{
				int pathA = 0;
				int pathB = 0;

				if (j < columnCount - 1)
				{
					pathA = maxValues[i - 1][j];
				}
				if (j > 0)
				{
					pathB = maxValues[i - 1][j - 1];
				}

				if (pathA > pathB) currentValue += pathA;
				else currentValue += pathB;
			}
			maxValuesRow.push_back(currentValue);
		}
		maxValues.push_back(maxValuesRow);
	}

	//Determine which element in the final row has the largest value
	int finalColumnSize = maxValues[rowCount - 1].size();
	int largestValue = 0;
	for (int i = 0; i < finalColumnSize; i++)
	{
		int testValue = maxValues[rowCount - 1][i];
		if (testValue > largestValue) largestValue = testValue;
	}
	return largestValue;
}
