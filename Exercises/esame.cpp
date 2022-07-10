#include<iostream>
#include<fstream>

using namespace std;

int max(int a, int b){
	if(a>b) return a;
	else return b;
}
	
double Knapsack(int W, int p[], double val[], int n, ofstream &out){
	int i,w;
    double K[n + 1][W + 1];
	for(i=0; i <=n; i++){
        for(w = 0; w<= W; w++)
        {
            if (i == 0 || w == 0){
                K[i][w] = 0;
        	}
            else if (p[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - p[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    
    double res= K[n][W];
    out << res << " ";
    w = W;
    for (i = n; i > 0 && res > 0; i--) {
         
        if (res == K[i - 1][w]) 
            continue;        
        else {
  			out <<"(" << val[i-1] << "," << p[i - 1] << ") ";
            res = res - val[i - 1];
            w = w - p[i - 1];
        }
    }
}

int main(){
	fstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	
	string type;
	while(in>>type){
		int pMax;
		in >> pMax;
		int n;
		in >> n;
		
		char tmp;
		double val[n];
		int p[n];	
		for(int i=0; i<n; i++){
			in >> tmp;
			in >> val[i];
			in >> tmp;
			in >> p[i];
			in >> tmp;
		}
		
	    Knapsack(pMax,p,val,n,out);
		out << endl;
	}
}
