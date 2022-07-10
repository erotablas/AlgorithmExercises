#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

void print(int* array, int size) 
{
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}


int* countingSort(int* inputArray, int size, int& newsize)
{
	int max = inputArray[0];
	int min = inputArray[0];
	for (int i = 1; i < size; i++)
	{
		if (max < inputArray[i])
			max = inputArray[i];
		else if (min > inputArray[i])
			min = inputArray[i];
	}
	int range = max - min + 1;
	newsize = range;
	int* temp = new int[size];
	int* frequencyArray = new int[range];
	for (int i = 0; i < range; i++)
		frequencyArray[i] = 0;
	for (int i = 0; i < size; i++)
		frequencyArray[inputArray[i] - min]++;
	for (int i = 1; i < range; i++)
		frequencyArray[i] += frequencyArray[i - 1];
	for (int i = size - 1; i >= 0; i--) //stable version
	{
		temp[frequencyArray[inputArray[i] - min] - 1] = inputArray[i];
		frequencyArray[inputArray[i] - min]--;
	}
	for (int i = 0; i < size; i++)
		inputArray[i] = temp[i];

	return frequencyArray;
	delete[] temp;
}


void countingSortInPlace(int* inputArray, int size)
{
	int max = inputArray[0];
	int min = inputArray[0];
	for (int i = 1; i < size; i++)
	{
		if (max < inputArray[i])
			max = inputArray[i];
		else if (min > inputArray[i])
			min = inputArray[i];
	}
	int range = max - min + 1;
	int* frequencyArray = new int[range];
	for (int i = 0; i < range; i++)
		frequencyArray[i] = 0;
	for (int i = 0; i < size; i++)
		frequencyArray[inputArray[i] - min]++;
	
	int j = 0;
	for (int i = 0; i < range; i++)
		while (frequencyArray[i] > 0)
		{
			inputArray[j] = i + min;
			frequencyArray[i]--;
			j++;
		}
	delete[] frequencyArray;
}

template <class T> void read(int size, ifstream &input, ofstream &output)
{
	T* arr = new T [size];
	for (int i = 0; i < size; i++)
	{
		T d;
		input >> d;
		arr[i] = d;
	}
	int newsize;
	T* newarr = countingSort(arr, size, newsize);
	for(int i = 0; i < newsize; i++){
		output << newarr[i];
		output << " ";
	}
	for(int i = 0; i< size; i++){
		output << arr[i];
		output << " ";
	}
	output << endl;
	delete [] arr;
	return;	
}


int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");	    
	int operations;	
	while (input >> operations)
	{ 
		read<int>(operations, input, output);
	}
	input.close();
	output.close();
	return 1;
}
