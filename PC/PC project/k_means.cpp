#include <iostream>
#include <fstream>
#include <random>
using namespace std;
float d(float u[2], float x[2]) {
	return pow( ( pow(u[0]-x[0], 2) + pow(u[1]-x[1], 2) ), 0.5);
}
//k-means less data... store the sum of all the x values
int main() {
	/*************serial***************************/
	float data[50][2];
	float u[2][2];
	//storing the sums
	float usum0x;
	float usum0y;
	float usum0n;
	float usum1x;
	float usum1y;
	float usum1n;

	for(int i=0; i<50; i++) {
		cin >> data[i][0];
		cin >> data[i][1];
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);
	u[0][0] = dis(gen);
	u[0][1] = dis(gen);
	u[1][0] = dis(gen);
	u[1][1] = dis(gen);
	//min-max normalize
	float minx=data[0][0], miny=data[0][1], maxx=data[0][0], maxy=data[0][1];
	for(int i=0; i<50; i++) {
		minx = min(minx, data[i][0]);
		maxx = max(maxx, data[i][0]);
		miny = min(miny, data[i][1]);
		maxy = max(maxy, data[i][1]);
	} //a' = (a-min)/(max-min)
	for(int i=0; i<50; i++) {
		data[i][0] = (data[i][0]-minx)/(maxx-minx);
		data[i][1] = (data[i][1]-miny)/(maxy-miny);
	}
	float mu = 0.1; // learning rate (smaller mu == accurate)
	for(int i=0; i<1000; i++) {
		usum0x = 0.0f;
		usum0y = 0.0f;
		usum0n = 0.0f;
		usum1x = 0.0f;
		usum1y = 0.0f;
		usum1n = 0.0f;
		for(int j=0; j<50; j++) {
			if(d(u[0], data[j]) < d(u[1], data[j])) {
				usum0x += data[j][0];
				usum0y += data[j][1];
				usum0n += 1.0f;
			}else {
				usum1x += data[j][0];
				usum1y += data[j][1];
				usum1n += 1.0f;
			}
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
	for(int i=0; i<50; i++) {
		float color = 2.0;
		if(d(u[0], data[i]) < d(u[1], data[i]))
			color = 1.0;
		myfile << data[i][0] << " " << data[i][1] << " " << color << "\n";
	}
	myfile << u[0][0] << " " << u[0][1] << " " << 0 << "\n";
	myfile << u[1][0] << " " << u[1][1] << " " << 0 << "\n";

	myfile.close();
	return 0;
}
