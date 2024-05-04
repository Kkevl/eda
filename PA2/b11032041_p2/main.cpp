#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "plotmanager.hpp"
using namespace std;

int main(
    // int argc,char **argv
    ){
    //file fixed
    string argv[3] = {"../output/10.gp","../PA2_testcases/floorplan_10.txt","../output/10.out"}; // test use
    string file = argv[1], ofile = argv[0];
    plotmanager p1;
    p1.loadfile(file);
    p1.createplot();
    // p1.outputfile(argv[2]);
    // p1.outputpic(ofile);
    
    return 0;
}

