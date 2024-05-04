#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include <time.h>
#include"grapher.hpp"
#include"block.hpp"
using namespace std;

class plotmanager{
private:
    int numblocks = 0,
        timer = 0,
        // draw use
        xtics = 20,
        ytics = 20,
        boundarx = 400,
        boundary = 400,
        MaxHeight = 3000,
        MaxWidth = 3000,
        x,y; // load file use
    float minaspectratio = 0.5,
        maxaspectratio = 2;
    string strbuffer;
    block *tempblock;

    time_t start, end;
    
    vector<block> bstack;

public:
    grapher *g2 = NULL;
    plotmanager();
    ~plotmanager();
    void loadfile(string file);
    
    void createplot();
    void annealing();

    void outputfile(string file);
    void outputpic(string file);
};
plotmanager::plotmanager(){
    start = time(NULL);
}
plotmanager::~plotmanager(){}

void plotmanager::loadfile(string file){
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
        //  <name> <width> <height>
        fin>>strbuffer>>x>>y;
        tempblock = new block(x,y,strbuffer);

        // data input might be false, so remeber to correct it!
        tempblock->validateaspectratio( minaspectratio , maxaspectratio);
        
        bstack.push_back( *tempblock ); // push the block into it
    }
    return;
}

inline void plotmanager::createplot(){
    grapher g1(numblocks, bstack);
    g2 = &g1;
    g1.initialize();
    // check validation
    
        // check the gamma plot

    // make direction graph to help create 
    g1.makedirgraph(); 

        // check size
    annealing();
        // g1.Costcalculation();
    // finishing
    g1.showplot();
    bstack = g1.bstack;

    //debug use
    // cout<<endl<<"after change:";
    // // show all blocks' position
    // for (int i = 0; i < numblocks; i++){
    //     cout <<endl<< bstack[ i ].name <<" "<< bstack[ i ].getx1() << " "
    //          << bstack[ i ].gety1();
    // }
}

inline void plotmanager::annealing(){
    for (int i = 0; i < 1000000000; i++){
        //dummy wait
    }
    
    end = time(NULL);
    double diff = difftime(end, start);

    while (diff < 600){ // wait until 10 minutes
        //do annealing
        diff = difftime(end,start);
        // debug use
        break;
    }
    

    cout<<"start = "<<start<<endl;
    cout<<"end = "<<end<<endl;
    cout<<"diff time = "<<diff<<endl;
}

inline void plotmanager::outputfile(string file){
    //  output form:
    // < chip_width > < chip_height >
    // < maccro_name > < maccro_width > < maccro_height > <x1> <y1> <x2> <y2>
    fstream fout;
    fout.open(file,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    
    fout<<MaxWidth<<" "<<MaxHeight<<endl;

    //blocks
    for (int i = 0; i < numblocks; i++){
        fout<<bstack[i].name<<" "<<bstack[i].width<<" "<<bstack[i].height<<" "
                            <<bstack[i].getx1()<<" " << bstack[i].gety1()<<" "
                            <<bstack[i].getx2()<<" " << bstack[i].gety2()<<endl;
    }

}

void plotmanager::outputpic(string file){
    
    //output
    fstream fout;
    fout.open(file,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }

    fout<<"reset\n"
        <<"set title \"result\" \n"
        <<"set xlabel \"X\"\n"
        <<"set ylabel \"Y\"\n";
    
    //blocks
    for (int i = 0; i < numblocks; i++){
        fout<<"set object "<<i + 1 <<" rect from "<<bstack[i].getx1()<<","<<bstack[i].gety1()
        <<" to "<<bstack[i].getx2()<<","<<bstack[i].gety2()<<endl
        <<"set label \""<<bstack[i].name<<"\" at "<<( bstack[i].getx1() + bstack[i].getx2() )/2
                        <<","<<( bstack[i].gety1() + bstack[i].gety2() )/2<<" center\n";
    }

    //end
    fout<<"set xtics "<<20*numblocks
        <<endl
        <<"set ytics "<<20*numblocks
        <<endl
        <<"plot [0:"<<boundarx*numblocks<<"][0:"<<boundary*numblocks<<"]0\n"
        <<"set terminal png size 1024,1024\n"
        <<"set output \"output"<<numblocks<<".png\"\n"
        <<"replot";
}

