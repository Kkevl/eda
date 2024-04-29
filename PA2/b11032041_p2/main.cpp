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
    string argv[3] = {"","../PA2_testcases/floorplan_10.txt","../output/10.gp"}; // test use
    string file = argv[1], ofile = argv[2];
    plotmanager p1;
    p1.loadfile(file);
    p1.createplot();
    // p1.outputfile(ofile);
    
    return 0;
}

