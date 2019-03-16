#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class file
{
public:
	
	file(); // default constructor
	void initializeFile();
	int getCount(ifstream &input); // open file and get number of line 
	int returnCount();
	void getData(ifstream &input);
	double getRow(int lineNumber);
	double getCol(int lineNumber);
	double getValue(int lineNumber);
	void add(file matrixA, file matrixB);
	void print();
	void sort();

private:
	double *row;
	double *col;
	double *value;
	int count;
};

void add(file matrixA, file matrixB);

int main()
{
	file matrixA;
	file matrixB;
	ifstream inputA;
	inputA.open("a3.txt");
	matrixA.getCount(inputA);
	inputA.close();
	
	matrixA.initializeFile();
	inputA.open("a3.txt");
	matrixA.getData(inputA);
	inputA.close();

	inputA.open("b3.txt");
	matrixB.getCount(inputA);
	inputA.close();
	
	matrixB.initializeFile();
	inputA.open("b3.txt");
	matrixB.getData(inputA);
	inputA.close();

	matrixA.sort();
	matrixB.sort();

	add(matrixA,matrixB);

	system("pause");
	return 0;
	
}

file::file()
{
	row = NULL;
	col = NULL;
	value = NULL;
	count = 0;
}

int file::getCount(ifstream &input)
{
	
	string line;
	if(!input.eof())
	{
		while(getline(input,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;

			count++;
		}
	}
	return count;
}

int file::returnCount()
{
	return count;
}

void file::initializeFile()
{
	row =new double[count];
	col = new double[count];
	value = new double[count];

	for(int i = 0; i<count ;i++)
	{
		row[i] =0;
		col[i] = 0;
		value [i] = 0;
	}
}

void file::getData(ifstream &input)
{
	string line;
	int i=0;

	if(!input.eof())
	{
		while(getline(input,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			ss>>row[i];
			ss>>col[i];
			ss>>value[i];
			i++;
		}
	}

}

double file::getRow(int lineNumber)
{
	return row[lineNumber];
}

double file::getCol(int lineNumber)
{
	return col[lineNumber];
}

double file::getValue(int lineNumber)
{
	return value[lineNumber];
}

void file::sort()
{
	double tem =0;
	for(int i = 0; i<count;i++)
	{
		for(int j =0;j<count-1;j++)
		{
			if(row[i]>row[i+1])
			{
				tem = row[j+1];
				row[j+1] = row[j];
				row[j] = tem;
				tem = col[j+1];
				col[j+1] = col[j];
				col[j] = tem;
				tem = value[j+1];
				value[j+1] = value[j];
				value[j] = tem;
			} else if(row[j] == row[j+1] && col[j] > col[j+1])
			{
				tem = col[j+1];
				col[j+1] = col[j];
				col[j] = tem;
				tem = value[j+1];
				value[j+1] = value[j];
				value[j] = tem;
			} 
		}
	}
}

void file::print()
{
	for(int i =0; i<count ;i++)
	{
		cout<< row[i]<<"   "<<col[i]<<"   "<<value[i]<<endl;
	}
}

void add(file matrixA, file matrixB)
{
	int countA = matrixA.returnCount();
	int countB = matrixB.returnCount();
	int i=0;
	int j=0;
	while(i<countA)
		while(j<countB)
		{
			if(matrixA.getRow(i) > matrixB.getRow(j))
			{
				cout <<matrixB.getRow(j) << "   "<< matrixB.getCol(j) <<"    "<<matrixB.getValue(j)<<endl;
				j++;
			} else if (matrixA.getRow(i) == matrixB.getRow(j) && matrixA.getCol(i) > matrixB.getCol(j))
			{
				cout <<matrixB.getRow(j) << "   "<< matrixB.getCol(j) <<"    "<<matrixB.getValue(j)<<endl;
				j++;
			}else if (matrixA.getRow(i) == matrixB.getRow(j) && matrixA.getCol(i) == matrixB.getCol(j))
			{
				cout <<matrixB.getRow(j) << "    "<< matrixB.getCol(j) << "    "<< matrixA.getValue(i) + matrixB.getValue(j) <<endl;
				i++;
				j++;
			}else
			{
				cout << matrixA.getRow(i) <<"    "<<matrixA.getCol(i)<<"    "<<matrixA.getValue(i)<<endl;
				i++;
			}

		}

}