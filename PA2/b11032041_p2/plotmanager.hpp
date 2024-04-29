#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"grapher.hpp"
#include"block.hpp"
using namespace std;

class plotmanager{
private:
    int numblocks = 0,
        xtics = 50,
        ytics = 50,
        boundarx = 0,
        boundary = 0,
        x,y;
    float minaspectratio = 0.5,
        maxaspectratio = 2;
    string strbuffer;
    vector<string> names; // to be delete
    vector<int> positions;  // to be delete
    vector<block> bstack;
public:
    plotmanager();
    void loadfile(string file);
    void createplot();
    void outputfile(string file);
    ~plotmanager();
};
plotmanager::plotmanager(){}
plotmanager::~plotmanager(){}

void plotmanager::loadfile(string file)
{
    fstream fin;
    fin.open(file, fstream::in);
    if(!fin.is_open()){
        cout << "Error: the input file is not opened!!" << endl;
	    exit(1);
    }
    //load blocks
    fin>>strbuffer>>numblocks;
    fin>>strbuffer>>minaspectratio
        >>strbuffer>>maxaspectratio;
    xtics = boundarx/5;
    ytics = boundary/5;
    //start reading each blocks
    for (int i = 0; i < numblocks; i++){
        fin>>strbuffer>>x>>y;
        bstack.push_back( block(x,y,strbuffer));
    }
    return;
}

inline void plotmanager::createplot(){
    grapher g1(numblocks);
    g1.initialize();
    for (int i = 0; i < numblocks; i++){
        cout<<bstack[i].name<<endl;
    }
    
}

void plotmanager::outputfile(string file){
    
    //output
    fstream fout;
    fout.open(file,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    
    //blocks
    for (int i = 0; i < numblocks; i++){
        fout<<"set object "<<i + 1 <<" rect from "<<positions[i*2]<<","<<positions[i*2+1]<<endl
        <<"set label \""<<names[i]<<"\" at "<<(positions[i*2]+positions[i*2+1])/2<<" center\n";
    }

    //end
    fout<<"set xtics "<<xtics<<endl
        <<"set ytics "<<ytics<<endl
        <<"plot [0:"<<boundarx<<"][0:"<<boundary<<"]0\n"
        <<"set terminal png size 1024,768\n"
        <<"set output \"output.png\"\n"
        <<"replot";
    return;
}

