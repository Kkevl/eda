#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include<time.h>
#include <climits>
#include"grapher.hpp"
#include"block.hpp"
#include"DAG.hpp"
using namespace std;

class plotmanager{
private:
    int numblocks = 0,
        timer = 0,
        // draw use
        xtics = 40,
        ytics = 40,
        boundarx = 400,
        boundary = 400,
        bestHeight = 3000,
        bestWidth = 3000,
        endtime = 599,
        x,y; // load file use
    float minaspectratio = 0.5,
        maxaspectratio = 2;
    string strbuffer;
    block *tempblock;

    time_t start, end;
    vector<block> bstack;
    vector<int> bestscorelog;
public:
    grapher *g2 = NULL;
    plotmanager();
    ~plotmanager();
    void loadfile(string file);
    
    void createplot();
    void annealing();

    void outputfile(string file);
    void outputpic();
    void outputlog();
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

        // checking validation
        // data input might be false, so remeber to correct it!
        tempblock->validateaspectratio( minaspectratio , maxaspectratio);
        
        bstack.push_back( *tempblock ); // push the block into it
    }
    return;
}

inline void plotmanager::createplot(){
    grapher g1(numblocks, bstack);
    g2 = &g1;
    g2->initialize(); // already have make dirgraph and calculate it

    annealing();

    // finishing
    // get the best sol

    cout<<endl<<"best :";
    g2->layout(); // load the axis
    bstack = g2->bstack;

    bestHeight = g2->bestHeight;
    cout<<endl<<"bestHeight = "<<bestHeight;
    bestWidth = g2->bestWidth;
    cout<<endl<<"bestWidth = "<<bestWidth;
    cout<<endl<<"bestratiocost = "<< float(g2->cost)/(bestHeight*bestWidth);
    cout<<endl<<"best cost = "<<g2->cost;

}

inline void plotmanager::annealing(){
    // end = time(NULL);
    double diff = 0,tempdiff;
    int perturb_mode,times = 0;
    while ( diff < endtime ){ // wait until 10 minutes
        
        // switchcase to choose perturb
        perturb_mode = rand()%(33);

        // counting
        // cout<<"times:"<<times++<<" ";

        //execute annealing
        switch ( perturb_mode%3 + 1 ){
            case 1:
                g2->perturbs_M1();
                break;
            case 2:
                g2->perturbs_M2();
                break;
            case 3:
                g2->perturbs_M3();
                break;
            default:
                cout<<endl<<"executing worse!"<<endl;
                exit(1);
                break;
        }
        // check size
        g2->Costcalculation();

        // setting break time
        end = time(NULL);
        diff = difftime(end,start);

        // debug use
        if (tempdiff != diff){
            tempdiff = diff;
            cout<<"clock : "<<diff<<endl;
            if (int(tempdiff)%5 == 0){
                bestscorelog.push_back(g2->cost);
            }
        }
    }
    
    // total finish time
    // cout<<endl<<"end - start = "<< end - start <<endl;
    // cout<<"diff time = "<<diff<<endl;
}

inline void plotmanager::outputfile(string file){
    //  output form:
    // < chip_Area>
    // < chip_width > < chip_height >
    // < maccro_name > < maccro_width > < maccro_height > <x1> <y1> <x2> <y2>
    fstream fout;
    fout.open(file,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    
    // chip titles
    fout<< bestWidth <<" "<< bestHeight <<endl;
    //blocks
    for (int i = 0; i < numblocks; i++){
        fout<<bstack[i].name<<" "<<bstack[i].width<<" "<<bstack[i].height<<" "
                            <<bstack[i].getx1()<<" " << bstack[i].gety1()<<" "
                            <<bstack[i].getx2()<<" " << bstack[i].gety2()<<endl;
    }

}

void plotmanager::outputpic(){
    //output
    string file = "../output/"+to_string(numblocks)+".gp";
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
    fout<<"set xtics "<<40*numblocks
        <<endl
        <<"set ytics "<<40*numblocks
        <<endl
        <<"plot [0:"<<boundarx*numblocks<<"][0:"<<boundary*numblocks<<"]0\n"
        <<"set terminal png size 1024,1024\n"
        <<"set output \"output"<<numblocks<<".png\"\n"
        <<"replot";
}

inline void plotmanager::outputlog(){
    string file = "../output/logs/"+to_string(numblocks)+".log";
    fstream fout;
    fout.open(file,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }
    for (int i = 0; i < bestscorelog.size(); i++){
        fout<<i<<" "<<bestscorelog[i]<<endl;
    }
    
}
