#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#pragma once
using namespace std;

class block{
private:
    int x1 = 0,x2 = 0,
        y1 = 0,y2 = 0;
    float aspectrartio;
public:
    string name;
    int width,height,area;
    block(int w,int h,string str);
    void setaspectratio(float r){ 
        height *=aspectrartio/r;
        width *= r/aspectrartio;
        aspectrartio = r;
    }
    float getaspestratio(){ return aspectrartio; }
    ~block();
};

block::block(int w,int h,string str){
    width = w;
    height = h;
    aspectrartio = height/width;
    area = height*width;
    name = str;
}
block::~block(){}

