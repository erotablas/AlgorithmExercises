#include <iostream>
#include <fstream>
using namespace std;

int LCSlenght(string x , string y, int m, int n){
    //int C[m+1][n+1];
    int **C=new int*[m+1];
    for(int i=0; i<m+1; i++){
    	C[i]=new int[n+1];
	}
    for(int i = 0; i < m+1; i++)
        C[i][0] = 0;
    for(int i = 0; i < n+1; i++)
        C[0][i] = 0;
    
    for(int i = 1; i < m+1; i++){
        for(int j = 1; j < n+1; j++){
            if(x[i-1] == y[j-1])
                C[i][j] = C[i-1][j-1]+1;
            else
            	C[i][j] = max(C[i-1][j], C[i][j-1]);
        }
    }

    return C[m][n];
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

	int m;
    while(in >> m){
        int n; 
		in >> n;
        string x; 
		in >> x;
        string y; 
		in >> y;
		
        int risultato = LCSlenght(x, y, m, n);
        
        cout << risultato << endl;
        
        out << risultato;
        out << endl;
    }
}