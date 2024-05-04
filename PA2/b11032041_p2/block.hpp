#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#pragma once
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
    float i = aspectrartio;
    int j = 0;
    // TO-DO adjust the size to fit the aspect constraint
    while (aspectrartio > max || min > aspectrartio ){ // height is bigger than width
                                                    // or width is bigger than height
        if (j++>10){
            break;
        }
        
        cout<<"aspect error!!"<<endl;
    }
    aspectrartio = height/width;
    // set ratio
    cout<<"correction!";
}
