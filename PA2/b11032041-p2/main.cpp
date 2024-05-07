#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<vector>
#include "plotmanager.hpp"
#include"DAG.hpp"
using namespace std;

int main( 
    int argc,char **argv  
    ){
    //file fixed to debugging usage
    // string argv[3] = {"", "../PA2_testcases/floorplan_100.txt","../output/100.out"};
    string file = argv[1], ofile = argv[0];
    plotmanager p1; 
    srand(time(NULL));
    p1.loadfile(file);
    p1.createplot();
    p1.outputfile(argv[2]);
    // use this can output the .gp file, but the axis have to be adjust mannuelly
    // p1.outputpic(); 
    // p1.outputlog();  // remember to turn on the loader in annaling!
    return 0;
}