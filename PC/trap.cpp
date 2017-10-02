#include <iostream>
#include "omp.h"
#include "fstream"
#include <math.h>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>
#include <array>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<float>dur;

using namespace std;

float trapezoidal(float,float,int);
float MonteCarlo(float,float,float,int);
float trapezoidalThread(float,float,int,int);
float MonteCarloThread(float,float,float,int,int);
void savePerformance(string filename,vector<int> x,vector<float> y1,vector<float>,vector<float>,vector<float>);
void saveAccuracy(string filename,vector<int> x,vector<float> y1,float ans);
void trapezoidalPerformance();

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / (RAND_MAX+1.0))) + a;
}

int main() {
srand(time(NULL));
    //trapezoidalPerformanc();
    vector<int> xT;
    vector<float> yTSerial;
    vector<float> yTthread2;
    vector<float> yTthread4;
    vector<float> yTthread8;

    float a=0,b=20;
    float steps=(b-a)/10000;
    float RecHeight=0;
    for (float i = a; i <= b; i+=steps) {
      float f=i*exp(-i);
      if (f>RecHeight)
          RecHeight=f;
    }
    RecHeight+=1;


    for (size_t i = 5000; i < 20000; i+=500) {
      xT.push_back(i);
      int count=3;

      //************* SERIAL

      float ans=0;

      for (size_t j = 0; j < count; j++) {
        /* code */
        auto startTime=Clock::now();
          MonteCarloThread(a,b,RecHeight,i,1) ;
          // MonteCarlo(a,b,RecHeight,i) ;
        auto endTime=Clock::now();
        dur clockTicksTaken = endTime - startTime;
        ans+=clockTicksTaken.count();
      }
      yTSerial.push_back(ans/count);

      //************* THREAD2
      float ans2=0;
      for (size_t j = 0; j < count; j++) {
        /* code */
        auto startTime=Clock::now();
          MonteCarloThread(a,b,RecHeight,i,2) ;
        auto endTime=Clock::now();
        dur clockTicksTaken = endTime - startTime;
        ans2+=clockTicksTaken.count();
      }
      yTthread2.push_back(ans2/count);

      //************* THREAD4
      float ans4=0;
      for (size_t j = 0; j < count; j++) {
        /* code */
        auto startTime=Clock::now();
          MonteCarloThread(a,b,RecHeight,i,4) ;
        auto endTime=Clock::now();
        dur clockTicksTaken = endTime - startTime;
        ans4+=clockTicksTaken.count();
      }
      yTthread4.push_back(ans4/count);

      //************* THREAD8
      float ans8=0;
      for (size_t j = 0; j < count; j++) {
        /* code */
        auto startTime=Clock::now();
          MonteCarloThread(a,b,RecHeight,i,8) ;
        auto endTime=Clock::now();
        dur clockTicksTaken = endTime - startTime;
        ans8+=clockTicksTaken.count();
      }
      yTthread8.push_back(ans8/count);
      std::cout<<"CASE " << i << '\n';
    }




    savePerformance("monte_performance.dat",xT,yTSerial,yTthread2,yTthread4,yTthread8);

    cout << "apezoidal" << '\n';
    //cout << trapezoidal(a,b,10000) << '\n';


  return 0;
}

void trapezoidalPerformance(/* arguments */) {
  /* code */
      vector<int> xT;
      vector<float> yTSerial;
      vector<float> yTthread2;
      vector<float> yTthread4;
      vector<float> yTthread8;

      float a=0,b=20;
      float steps=(b-a)/10000;
      float RecHeight=0;

      for (size_t i = 100; i < 10000; i+=100) {
        xT.push_back(i);
        int count=2000;

        //************* SERIAL

        float ans=0;

        for (size_t j = 0; j < count; j++) {
          /* code */
          auto startTime=Clock::now();
            trapezoidal(a,b,i) ;
          auto endTime=Clock::now();
          dur clockTicksTaken = endTime - startTime;
          ans+=clockTicksTaken.count();
        }
        yTSerial.push_back(ans/count);

        //************* THREAD2
        float ans2=0;
        for (size_t j = 0; j < count; j++) {
          /* code */
          auto startTime=Clock::now();
            trapezoidalThread(a,b,i,2) ;
          auto endTime=Clock::now();
          dur clockTicksTaken = endTime - startTime;
          ans2+=clockTicksTaken.count();
        }
        yTthread2.push_back(ans2/count);

        //************* THREAD4
        float ans4=0;
        for (size_t j = 0; j < count; j++) {
          /* code */
          auto startTime=Clock::now();
            trapezoidalThread(a,b,i,4) ;
          auto endTime=Clock::now();
          dur clockTicksTaken = endTime - startTime;
          ans4+=clockTicksTaken.count();
        }
        yTthread4.push_back(ans4/count);

        //************* THREAD8
        float ans8=0;
        for (size_t j = 0; j < count; j++) {
          /* code */
          auto startTime=Clock::now();
            trapezoidalThread(a,b,i,8) ;
          auto endTime=Clock::now();
          dur clockTicksTaken = endTime - startTime;
          ans8+=clockTicksTaken.count();
        }
        yTthread8.push_back(ans8/count);
        std::cout<<"CASE " << i << '\n';
      }




      savePerformance("trapezoidal_performance.dat",xT,yTSerial,yTthread2,yTthread4,yTthread8);
}


void Accuracy(/* arguments */) {
  /* code */
      float a=0,b=20;
      float steps=(b-a)/10000;
      float RecHeight=0;
      vector<int> x;
      vector<float> y1;
      for (float i = a; i <= b; i+=steps) {
        float f=i*exp(-i);
        if (f>RecHeight)
            RecHeight=f;
      }
      RecHeight+=2;

    for (size_t i = 5000; i < 1000000; i+=1000) {
      /* code */
      float y=MonteCarlo(a,b,RecHeight,i);
      y1.push_back(y);
      x.push_back(i);
      std::cout << i << '\n';
    }
    saveAccuracy("MonteCarlo_Correctness.dat",x,y1,0.99999995671);

        for (size_t i = 100; i < 10000; i+=100) {
          /* code */
          float y= trapezoidal(a,b,i) ;
          y1.push_back(y);
          x.push_back(i);
          std::cout << i << '\n';
        }
        saveAccuracy("Trapezoidal_Correctness.dat",x,y1,0.99999995671);
}

float trapezoidal(float a,float b,int numSteps){
  //func is e^x
  float steps=(b-a)/numSteps;
  float Area=0;

  for (float i = a; i < b; i+=steps) {
    /* code */
    float trapArea=0.5*(i*exp(-i-steps)+i*exp(-i))*steps;
    Area+=trapArea;
  }

  return Area;
}
float trapezoidalThread(float a,float b,int numSteps,int threadNum){
  //func is e^x
  float steps=(b-a)/numSteps;
  float Area=0;
  int c2 = 0;

  #pragma omp parallel num_threads(threadNum)
  {
      #pragma omp for reduction(+:Area)
      for (int j = 0; j < numSteps; j++) {
        /* code */
        float i=a+j*steps;
        float trapArea=0.5*(i*exp(-i-steps)+i*exp(-i))*steps;
        Area+=trapArea;
      }
  }

  return Area;
}

float MonteCarlo(float a,float b,float RecHeight,int numBalls){
  float numInSquare=0,numInGraph=0;
  float Area=0;

  for (int i = 0; i <numBalls; i++) {
    /* code */
    float y=rand_FloatRange(0,RecHeight);
    float x=rand_FloatRange(a,b);
    //std::cout << "x="<<x<<"\ty="<<y << '\n';
    float f=x*exp(-x);
    //throw darts()
    if (y<=RecHeight) {
      numInSquare++;
      /* code */
    }
    if (y<=f) {
      numInGraph++;
    }


  }
  float AreaSquare=RecHeight*(b-a);
  float dotsRatio=numInGraph/numInSquare;
  //std::cout << "Height="<<RecHeight<<" a="<<a<<" b="<<b<<'\n'<<"numInGraph="<<numInGraph<<" numInSquare="<<numInSquare<<'\n'<<"dotsRatio="<<dotsRatio<<" AreaSquare="<<AreaSquare << '\n';
  Area=dotsRatio*AreaSquare;


  return Area;

}

float MonteCarloThread(float a,float b,float RecHeight,int numBalls,int threadNum){
  float numInSquare=0,numInGraph=0;
  float Area=0;
  float y;
  float x;
  //std::cout << "x="<<x<<"\ty="<<y << '\n';
  float f;
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> disx(a,b);
  uniform_real_distribution<> disy(0.0, RecHeight);

  #pragma omp parallel num_threads(threadNum)
  {
    #pragma omp for reduction(+:numInGraph)
    for (int i = 0; i <numBalls; i++) {
      /* code */
      y=disy(gen);
      x=disx(gen);
      //std::cout << "x="<<x<<"\ty="<<y << '\n';
      f=x*exp(-x);
      //throw darts()
      if (y<=f) {
        numInGraph++;
      }


    }
  }
  numInSquare=numBalls;
  float AreaSquare=RecHeight*(b-a);
  float dotsRatio=numInGraph/numInSquare;
  //std::cout << "Height="<<RecHeight<<" a="<<a<<" b="<<b<<'\n'<<"numInGraph="<<numInGraph<<" numInSquare="<<numInSquare<<'\n'<<"dotsRatio="<<dotsRatio<<" AreaSquare="<<AreaSquare << '\n';
  Area=dotsRatio*AreaSquare;


  return Area;

}

void savePerformance(string filename,vector<int> x,vector<float> y1,vector<float> y2,vector<float> y3,vector<float> y4){
  ofstream myFile;
  int n=x.size();
  myFile.open(filename);
  for (size_t j = 0; j < n; j++) {
    myFile<<to_string(x[j])<<" "<<to_string(y1[j])<<" "<<to_string(y2[j])<<" "<<to_string(y3[j])<<" "<<to_string(y4[j])<<endl;
  }
  myFile.close();

}

void saveAccuracy(string filename,vector<int> x,vector<float> y1,float ans){
  ofstream myFile;
  int n=x.size();
  myFile.open(filename);
  for (size_t j = 0; j < n; j++) {
    myFile<<to_string(x[j])<<" "<<to_string(y1[j])<<" "<<ans<<endl;
  }
  myFile.close();

}
