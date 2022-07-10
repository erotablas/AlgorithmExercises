#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


void Knapsack(vector<int> vett, int pmax, ostream &out){
    int sum = 0;
    sort(vett.begin(), vett.end(), greater<int>());

    for(int i = 0; i < pmax; i++)
        sum += vett[i];
    
    out << sum;
	out << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

	int n;
    while(in >> n){
        int pmax; 
		in >> pmax;

        vector<int> vett;

        for(int j = 0; j < n; j++){
            int tmp;
			in >> tmp;
            vett.push_back(tmp);
        }

        Knapsack(vett, pmax, out);

        vett.~vector();
    }
}
