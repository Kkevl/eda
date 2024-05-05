#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<vector>
#include "plotmanager.hpp"
#include"DAG.hpp"
using namespace std;

void testDAG();

int main(  
    // int argc,char **argv  
    ){
    //file fixed
    string argv[3] = {"", "../PA2_testcases/floorplan_30.txt","../output/30.out"};
    string file = argv[1], ofile = argv[0];
    plotmanager p1;
    srand(time(NULL));
    p1.loadfile(file);
    p1.createplot();
    p1.outputfile(argv[2]);
    // use this can output the .gp file, but the axis have to be adjust mannuelly
    p1.outputpic(); 
    p1.outputlog();
    // testDAG();
    
    return 0;
}

void testDAG(){
time_t start, end;
    clock_t a, b;
    //test for DAG
        DAG g( 6 + 2 ); // num 0 is source
        // test for source part
        for (int i = 1; i < 7; i++){
            g.addEdge(0,i,0);
        }
        g.eraseEdge(1,3);
        g.addEdge(1,1+1,5);
        g.addEdge(1,2+1,3);
        g.eraseEdge(1,2+1);
        g.addEdge(1,2+1,3);
        g.addEdge(2,3+1,6);
        g.addEdge(2,2+1,2);
        g.addEdge(3,4+1,4);
        g.addEdge(3,5+1,2);
        g.addEdge(3,3+1,7);
        g.addEdge(4,5+1,1);
        g.addEdge(4,4+1,-1);
        g.addEdge(5,5+1,-2);
        // tail part
        for (int i = 1; i < 7; i++){
            g.addEdge(i,7,2);
        }
        
        // for (int i = 0; i < 2; i++){
            // start = time(NULL);
            // a = clock();
            g.longestPath(1);
            g.longestPath(0);
            //test time
            // b = clock();
            // end = time(NULL);
            // cout<<"b - a = "<<b-a<<endl;
            // cout<<"end - start = "<<(end - start)<<endl;
        // }
}
