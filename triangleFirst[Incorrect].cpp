#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector <vector<int>> inputVales;
vector <vector<int>> bestPaths;

//Function Prototypes
void ReadFile();
int GetMaxValue(int rowNumber = 0, int columnNumber = 0);
int GetMaxValueDynamic();
void FindBestPaths();

//Main
int main()
{
	ReadFile();
	FindBestPaths();
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
		inputVales.push_back(newRow);
	}
}

//Recursive way to get the max value. Technically works, but slow. I believe this is O(2^N)? What I know is I programed the second version before this one finished running.  
int GetMaxValue(int rowNumber, int columnNumber)
{
	if (rowNumber >= inputVales.size()) return 0;
	int myNumber = inputVales[rowNumber][columnNumber];
	int pathA = GetMaxValue(rowNumber + 1, columnNumber);
	int pathB = GetMaxValue(rowNumber + 1, columnNumber + 1);

	if (pathA > pathB) myNumber += pathA;
	else myNumber += pathB;

	return myNumber;	
}

//For each child, determines which possible parrent would have resulted in the largest value. Used in the Dynamic soultion.
void FindBestPaths()
{
	int rowCount = inputVales.size() - 1;
	for (int j = rowCount; j >= 0; j--)
	{
		vector<int> currentRow;
		int rowSize = inputVales[j].size();
		for (int i = 0; i < rowSize; i++)
		{
			int currentValue = inputVales[j][i];
			int pathA = 0;
			int pathB = 0;
			if (j > 0)
			{
				if (i > 0)
				{
					pathA = inputVales[j - 1][i - 1];
				}
				if (i < rowSize - 1)
				{
					pathB = inputVales[j - 1][i];
				}
			}
			
			int indexNum;
			if (pathA > pathB) indexNum = i - 1;
			else indexNum = i;
			currentRow.push_back(indexNum);
		}
		bestPaths.push_back(currentRow);
	}
}

//A methoid using a bottom up dynamic programing technique to solve the problem.
//Makes use of the info generated in FindBestPaths to get the result much faster then the recursive version
int GetMaxValueDynamic()
{
	int bestPathValue = 0;
	int rowCount = inputVales.size();
	int columnCount = inputVales[rowCount - 1].size();
	for (int i = 0; i < columnCount; i++)
	{
		int pathValue = inputVales[rowCount - 1][i] + inputVales[0][0];
		int indexOfBestPath = i;
		for (int j = 0; j < rowCount - 2; j++)
		{
			indexOfBestPath = bestPaths[j][indexOfBestPath];
			pathValue += inputVales[rowCount - 2 - j][indexOfBestPath];
		}
		if (pathValue > bestPathValue) bestPathValue = pathValue;
	}
	return bestPathValue;
}