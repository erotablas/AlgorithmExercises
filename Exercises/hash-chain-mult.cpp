#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

template <class T> class HashTable
{  		 
  public:	     	
	     virtual HashTable<T>* insertKey(T x)=0;
	     virtual HashTable<T>* deleteKey(T key)=0;	 
		
		 virtual int searchKey(T key) = 0;	
};


template <class T> class ChainedHashTable : public HashTable<T>
{
  private:
	       int slots;    // Number of slots 	
	       list<T> *table; 
		   int size;	
  public:
	virtual int computeHashFunction(T x) = 0;
	ChainedHashTable<T>(int x)
	{
		this->slots = x;
		table = new list<T>[slots];
		size = 0;		
	}

	ChainedHashTable<T>* insertKey(T key)
	{
		int index = computeHashFunction(key);
		table[index].push_back(key);
		size++;
		return this;
	}


	ChainedHashTable<T>* deleteKey(T key)
	{		
		int index = computeHashFunction(key);
		int pos1 = -1;
		int pos2 = -1;
		searchKey(key, &pos1, &pos2);
		if (pos1 != -1)
		{
			typename list<T>::iterator i = table[pos1].begin();
			advance(i, pos2);
			table[pos1].erase(i);
			size--;
		}
		return this;
	}
	
	int searchKey(T key)
	{
		int index = computeHashFunction(key);
		typename list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
				return index;
		}
		return -1;	
	}

	void searchKey(T key, int* pos1, int* pos2)
	{
		int index = computeHashFunction(key);
		typename list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
			{
				*pos1 = index;
				*pos2 = distance(table[index].begin(), i);
				return;
			}
		}
		*pos1 = -1;
		*pos2 = -1;
		return;
	}

	int getSlotNumber()
	{
		return slots;
	}

	int getSize()
	{
		return size;
	}

	void printHashTable(ofstream &output)
	{
		for (int i = 0; i < this->getSlotNumber(); i++) 
		{
			int j=0;
			for (auto x : table[i])
				j++;
			output << j;
			output << " ";
		}
	}

};


template <class T> class MultiplicationChainedHashTable : public ChainedHashTable<T>
{
private:
	double c;
	int computeHashFunction(T x) 
	{
		double y = x * c;
		double a = y - (int)y;
		int h = (int)(a * this->getSlotNumber());
		return h;
	}
public:
	MultiplicationChainedHashTable(int edge_number) : ChainedHashTable<T>(edge_number)
	{
		c = 0.61803;
	}
};

template <class T> void read(int size, int bucket, ifstream &input, ofstream &output)
{
	//T** arr = new T * [size + 1];
	MultiplicationChainedHashTable<T>* dc = new MultiplicationChainedHashTable<T>(bucket);
	for (int i = 0; i < size; i++)
	{
		T d;
		input >> d;
		dc->insertKey(d);
		//arr[i + 1] = new T(d);
	}
	dc->printHashTable(output);
	output << endl;
	//delete [] arr;
	return;	
}


int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");	    
	string type;
	int bucket;
	int operations;	
	while (input >> type)
	{
		if (type == "\n")
			continue;
		input >> bucket;
		input >> operations;
		if (type == "double")
			read<double>(operations, bucket, input, output);
		else if (type == "char")
			read<char>(operations, bucket, input, output);
		else
			read<int>(operations, bucket, input, output);
	}
	input.close();
	output.close();
	return 1;
}
