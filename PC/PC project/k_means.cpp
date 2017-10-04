#include <iostream>
#include <fstream>
#include <random>
using namespace std;
float d(float *u, float *x, int dim) {
	float ans = 0;
	for(int i=0; i<dim; i++)
		ans += pow(u[i]-x[i], 2);
	return pow(ans, 0.5);
}
//k-means less data... store the sum of all the x values
int main() {
	/*************serial***************************/

	/***********read in data************************/
	int len, dim, kmn;
	cin >> len >> dim >> kmn;
	ifstream infile("data2.txt");
	//float a, b;
	float points[len][dim];
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++) {
			float a;
			infile >> a;
			points[i][j] = a;
		}
	}
	cout << len << endl;

	/******preparing k means*****************/
	float u[kmn][dim];
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);
	for(int i=0; i<kmn; i++) {
		for(int j=0; j<dim; j++)
			u[i][j] = dis(gen);
	}
	//storing the sums
	float usum[kmn][dim+1]; //the x1, x2, ..., xdim, n in cluster


	/********normalizing with min-max********************************/
	float min[dim];
	float max[dim];
	for(int j=0; j<dim; j++) {
		min[j] = points[0][j];
		max[j] = points[0][j];
	}
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++) {
			min[j] = min(min[j], points[i][j]);
			max[j] = max(max[j], points[i][j]);
		}
	} //a' = (a-min)/(max-min)
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++)
			points[i][j] = (points[i][j]-min[j])/(max[j]-min[j]);
	}

	/*******************starting k-means********************************/
	float mu = 0.1; // learning rate (smaller mu == accurate)
	for(int ep=0; ep<1000; ep++) { //fix the number of iterations
		/************************* storing u averages as sums***********/
		for(int i=0; i<kmn; i++){
			for(int j=0; j<=dim; j++)
				usum[i][j] = 0.0f;
		}
		for(int i=0; i<len; i++) { // each data point
			int indx = 0;
			float minD = d(u[0], points[i], dim);
			for(int j=0; j<kmn; j++) {
				if(d(u[j], points[i]) < minD) {
					minD = d(u[j], points[i]);
					index = j;
				}
			}
			for(int k=0; k<dim; k++) {
				usum[index][k] += points[i][k];
			}
			usum[index][dim] += 1.0f;
		}
		cout << "the elements in cluster 0 is" << usum0n << endl;
		cout << "the elements in cluster 1 is" << usum1n << endl;
		u[0][0] = usum0x/usum0n;
		u[0][1] = usum0y/usum0n;
		u[1][0] = usum1x/usum1n;
		u[1][1] = usum1y/usum1n;
	}
	ofstream myfile;
	myfile.open ("data.txt");
	for(int i=0; i<len; i++) {
		float color = 2.0;
		if(d(u[0], points[i]) < d(u[1], points[i]))
			color = 1.0;
		myfile << points[i][0] << " " << points[i][1] << " " << color << "\n";
	}
	myfile << u[0][0] << " " << u[0][1] << " " << 0 << "\n";
	myfile << u[1][0] << " " << u[1][1] << " " << 0 << "\n";

	myfile.close();
	return 0;
}
