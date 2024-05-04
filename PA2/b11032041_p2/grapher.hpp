#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include"block.hpp"
using namespace std;
class grapher{
private:
public:
    int numofblocks;
    // gamma_plus is the random the relation of each block, pos is the axis in the dag graph
    vector<int> gamma_plus,pos_plus,
                gamma_minus,pos_minus;
    vector< vector<int> > directiongraph;
    vector<block> bstack;

    void initialize();
    
    // to return the cost for annealing
    int Costcalculation(); // calculate the area and count the cost(use lcs?)

    void makedirgraph();
    void showplot();

    // purturbs
    void perturbs_M1(); // annealing method 1
    
    grapher(int numblock ,vector<block> blocks);
    ~grapher();
};

grapher::grapher(int numblock, vector<block> blocks ){
    numofblocks = numblock;
    for(int i = 1 ; i <= numofblocks ; i++){
        gamma_plus.push_back(i);
        pos_plus.push_back(0);
        gamma_minus.push_back(i);
        pos_minus.push_back(0);
        bstack.push_back(blocks[i-1]);
    }
}
grapher::~grapher(){}

// initialize gammas
inline void grapher::initialize(){
    srand(time(NULL));
    int x,y,temp;
    for (int i = 0; i < numofblocks; i++){
        x = rand()%(numofblocks-1)+1;
        y = rand()%(numofblocks-1)+1;
        //swap by random generation
        temp = gamma_plus[x];
        gamma_plus[x] = gamma_plus[y];
        gamma_plus[y] = temp;

        x = rand()%(numofblocks-1)+1;
        y = rand()%(numofblocks-1)+1;
        temp = gamma_minus[x];
        gamma_minus[x] = gamma_minus[y];
        gamma_minus[y] = temp;
        // for easy use, the code output now is the number in the sequence
        // ex: a[1] = 4 means 1 is in the 4th place in this sequence.
    }

    //initialize direction picture
    vector<int> tempvec(numofblocks,0);
    for (int i = 0; i < numofblocks; i++){
        directiongraph.push_back(tempvec);
    }

    //gamma presents the position of each blocks
    //debug use
    // gamma_plus = {1,4,7,6,5,2,3};
    // gamma_minus = {3,7,5,4,2,1,6};
    // gamma_plus = {1,6,7,2,5,4,3};
    // gamma_minus = {6,5,1,4,3,7,2};

    // print out gammas
    // we use when the looping value == index(the real number), output the looping index
    cout<<endl<<"Gamma_plus_positions = ";
    for (int i = 0; i < gamma_plus.size(); i++){
        for (int j = 0; j < gamma_plus.size(); j++){
            if (gamma_plus[j] == i+1){
                pos_plus[i] = j+1;
                cout<<pos_plus[i]<<" ";
            }
        }
    }

    cout<<endl<<"Gamma_mius_positions = ";
    for (int i = 0; i < gamma_minus.size(); i++){
        for (int j = 0; j < gamma_minus.size(); j++){
            if (gamma_minus[j] == i+1){
                pos_minus[i] = j+1;
                cout<<pos_minus[i]<<" ";
            }
        }
    }    
}

// make the picture of the direction graph
inline void grapher::makedirgraph(){
    for (int i = 0; i < directiongraph.size(); i++){   // gamma[i] = a
        for (int j = 0; j < directiongraph[i].size(); j++){  // gamma[j] = b

            //a's position in gamma+ vs b's position in gamma-
            if ( pos_plus[i] < pos_plus[j] && pos_minus[i] < pos_minus[j] ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            else if ( pos_plus[i] > pos_plus[j] && pos_minus[i] > pos_minus[j] ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            //( a. b , ... b. a ) means the b is on the under of a
            else if ( pos_plus[i] < pos_plus[j] && pos_minus[i] > pos_minus[j] ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
            else if ( pos_plus[i] > pos_plus[j] && pos_minus[i] < pos_minus[j] ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
        }        
    }
    
    // output
    cout<<endl<<"graph :"<<endl;
    for (int i = 0; i < directiongraph.size(); i++){
        for (int j = 0; j < directiongraph[i].size(); j++){
            cout<<directiongraph[i][j]<<"  ";
        }cout<<endl;
    }
    cout<<"--------------------------------"<<endl;
}


// print out the best solution
inline void grapher::showplot(){
    int x,y;
    // look from gamma_minus first to gamma_minus end
    for (int i = 0; i < gamma_minus.size(); i++){
        x = 0;
        y = 0;
        for (int j = 0 ;j < i ; j++){
            // cout<< gamma_minus[j] <<" ";
            if ( directiongraph[ gamma_minus[i] - 1 ][ gamma_minus[j] - 1 ] == 1 ) 
            { // if = 2, then add on to x axis
                x = max<int>( x , bstack[ gamma_minus[j] - 1 ].getx2() );
            }else{
                y = max<int>( y , bstack[ gamma_minus[j] - 1].gety2() );
            }
        }
        bstack[ gamma_minus[i] - 1].setxy(x,y);
    }
    
    // show all blocks' position
    for (int i = 0; i < numofblocks; i++){
        cout <<endl<< bstack[ gamma_minus[i] - 1 ].name <<" "<< bstack[ gamma_minus[i] - 1 ].getx1() << " "
             << bstack[ gamma_minus[i] - 1 ].gety1();
    }
    
}


