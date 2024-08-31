/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include<vector>
using namespace std;
#include <cmath>
#include<fstream>


int main()
{
	double L=0.5;
	int N=50;
	double dx;
	dx=L/(N-1);
	double T_left=100;
	double T_right=500;
	int k=0;
	//k=number of iterations
	double accuracy=1e-6;
	//distance from node 0 to nth node is x[n-1]
	vector<double>x;
	for(int i=0; i<N; i++) {
		double d;
		d=(L*i)/(N-1);
		x.push_back(d);
	}
	//analytical temp at each node
	vector<double>T_analytical;
	//temperature at nth node is T_analytical[n-1]
	for(int i=0; i<N; i++) {
		double T;
		T= T_left+(T_right-T_left)*x[i]/L;
		T_analytical.push_back(T);
		cout<<"analytical temperature at "<<i+1<<"th node is "<<T_analytical[i]<<"\n";
	}
	//fdm method
	vector<double>Temp;
	for(int i=0; i<N; i++) {
		double T;
		T=(T_right+T_left)/2;
		Temp.push_back(T);
	}
	vector<double>T_new(N);
	T_new[0]=T_left;
	T_new[N-1]=T_right;
	double max_dt=1;//difference between analytical and fdm temperature
	while(max_dt>accuracy ) {
		max_dt=0;
		for(int i=1; i<(N-1); i++) {
			T_new[i]=(Temp[i+1]+Temp[i-1])*0.5;

		}
		for(int i=0; i<(N); i++) {

			double dt;
			dt=fabs(Temp[i]-T_new[i]);
			if(dt>max_dt) {
				max_dt=dt;
			}
			Temp[i]=T_new[i];
		}
		// cout<<"max difference"<<max_dt;
		k=k+1;
		// cout<<"iteration number"<<k<<"\n";

	}
	cout<<"number of iterations"<<k;
	for(int i=0; i<N; i++) {
		cout<<"analytical temp at node"<<i+1<<" is "<<T_analytical[i]<<" fdm temp is "<<Temp[i]<<"\n";
	}
    ofstream myfile("fdmq1sol.txt");
    
    if (myfile.is_open()) {
         
        for (int i = 0; i < N; i++) {
            myfile << "Node " << i + 1 << ": Temperature = " << Temp[i] << endl;
        }
        myfile.close();
        cout << "Temperature values have been written to fdmq1sol.txt" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
    
	return 0;
}