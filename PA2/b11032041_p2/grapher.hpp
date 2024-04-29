#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<vector>
#include<time.h>
using namespace std;
class grapher{
private:
public:
    vector<int> gamma_plus,gamma_minus;
    int numofblocks;
    void initialize();
    grapher(int block);
    ~grapher();
};

grapher::grapher(int block){
    numofblocks = block;
    for(int i = 0 ; i < numofblocks ; i++){
        gamma_plus.push_back(i + 1);
        gamma_minus.push_back(i + 1);
    }
    
}
grapher::~grapher(){}

void grapher::initialize(){
    srand(time(NULL));
    int x,y,temp;
    for (int i = 0; i < numofblocks; i++){
        x = rand()%numofblocks;
        y = rand()%numofblocks;
        //swap
        temp = gamma_plus[x];
        gamma_plus[x] = gamma_plus[y];
        gamma_plus[y] = temp;
        x = rand()%numofblocks;
        y = rand()%numofblocks;
        temp = gamma_minus[x];
        gamma_minus[x] = gamma_minus[y];
        gamma_minus[y] = temp;
    }
    cout<<"Gamma_plus = ";
    for (int i = 0; i < gamma_plus.size(); i++){
        cout<<gamma_plus[i]<<" ";
    }
    cout<<endl<<"Gamma_minus = ";
    for (int i = 0; i < gamma_minus.size(); i++){
        cout<<gamma_minus[i]<<" ";
    }
    cout<<endl;
}