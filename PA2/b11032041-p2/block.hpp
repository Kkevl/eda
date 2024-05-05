#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
using namespace std;

class block{
private:
    int x1 = 0,x2 = 0,
        y1 = 0,y2 = 0,
        area;
    float aspectrartio;
public:
    string name;
    int width,height;
    block(int w,int h,string str);
    void setaspectratio(float r){ 
        height *=aspectrartio/r;
        width *= r/aspectrartio;
        aspectrartio = r;
    }
    int getx1();
    int gety1();
    int getx2();
    int gety2();
    void setxy(int x, int y);
    void validateaspectratio(float min,float max);
    float getaspestratio(){ return aspectrartio; }
    ~block(){};
};

block::block(int w,int h,string str){
    name = str;
    width = w;
    height = h;
    aspectrartio = float(height)/float(width);
    area = height*width;
}

inline void block::setxy(int x, int y){
    x1 = x;
    y1 = y;
    x2 = x + width;
    y2 = y + height;
}

inline int block::getx1(){
    return x1;
}

inline int block::gety1(){
    return y1;
}

inline int block::getx2(){
    return x2;
}

inline int block::gety2(){
    return y2;
}

inline void block::validateaspectratio(float min, float max){
    int j = 0; // use as counter
    // TO-DO adjust the size to fit the aspect constraint
    // while (aspectrartio > max || min > aspectrartio ){
    
    j = sqrt(area);
    // only find the posible to fall in the region, 
    // if the rectangle can't fall in the region, it should return false
    for ( ; j >= (height<width?height:width) ; j--){
        if (area % j == 0){
            (height>width?height:width) = j;
            (height<width?height:width) = area/j;
            // set ratio
            aspectrartio = float(height)/float(width);
            if ( aspectrartio >= min && aspectrartio <= max ){
                return;
            }
            else break;
        }
    }
    cerr<<"the block is not valid!! please check the input block is correct block!!";
    exit(1);
}
