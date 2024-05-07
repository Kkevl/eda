#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<math.h>
#include"DAG.hpp"
#include"block.hpp"
using namespace std;
class grapher{
private:
public:
    int numofblocks,
        thisHeight,
        thisWidth,
        cost = INT_MAX,
        tempcost = 0,
        bestHeight = 0,
        bestWidth = 0,
        x = 0,y = 0,temp = 0,i = 0,j = 0; // dummy use
    float CoolingRate = 0.75,
        temperature = 18000, 
        heatbound;
    // gamma_plus is the random the relation of each block, pos is the axis in the dag graph
    vector<int> gamma_plus,pos_plus, tempgamma_plus,
                gamma_minus,pos_minus, tempgamma_minus;
    vector< vector<int> > directiongraph;
    vector<block> bstack;
    DAG* HorizontalGraph,*VerticalGraph;


    void initialize();
    // to return the cost for annealing
    void Costcalculation( int time ); // calculate the area and count the cost(use lcs?)

    void setgammaposition();
    void makedirgraph();
    void initializeDAG();
    void DAGreconnect( int u);

    // purturbs
    void perturbs_M1(int x,int y); // annealing method 1 // random switch 2 blocks in 2 graph
    void perturbs_M2(int x,int y); // annealing method 2 // random 
    void perturbs_M3(int x,int y); // annealing method 3 // turn the blocks around
    
    void layout();
    
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
    HorizontalGraph = new DAG(numofblocks+2);
    VerticalGraph = new DAG(numofblocks+2);
}
grapher::~grapher(){}

// initialize gammas
inline void grapher::initialize(){
    srand(time(NULL));
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

    // tempgamma save the best one now
    tempgamma_plus.assign( gamma_plus.begin(),gamma_plus.end());
    tempgamma_minus.assign( gamma_minus.begin(),gamma_minus.end());
    
    setgammaposition();
    makedirgraph();
    Costcalculation(0);
    layout();
}

inline void grapher::Costcalculation( int time ){

    // modify the dag graph
    // cout<<"Height's :"<<endl;
    // HorizontalGraph->longestPath(0);
    // cout<<"Width's :"<<endl;
    // VerticalGraph->longestPath(0);
    // thisHeight = VerticalGraph->maxlength; 
    // thisWidth = HorizontalGraph->maxlength;

    // recaculate the max height and width
    layout(); // update the this height and this width

    // calaulate max and min
    tempcost = (thisHeight>thisWidth?thisHeight:thisWidth);
                //since it's same to calculate 1 dimention
                //*(thisHeight>thisWidth?thisHeight:thisWidth);

    if ( cost > tempcost ){ 
        // if cost is lesser, than remember the bstack
        cost = tempcost;
        bestHeight = thisHeight;
        bestWidth = thisWidth;
        tempgamma_plus.assign(gamma_plus.begin(),gamma_plus.end());
        tempgamma_minus.assign(gamma_minus.begin(),gamma_minus.end());
        // dummy prevention
        if ( cost < 0 ){
            cout<<"error!"<<endl;
            cout<<"plus = "<<endl;
            for (int i = 0; i < gamma_plus.size(); i++){
                cout<<gamma_plus[i]<<" ";
            }cout<<"Minus = "<<endl;
            for (int i = 0; i < gamma_minus.size(); i++){
                cout<<gamma_minus[i]<<" ";
            }            
            exit(0);
        }        
    }
    else{   // cost <tempcost
        // load it with probability 
        float rate = (float)(rand()) / (float)(RAND_MAX); // falls in 1 ~ 0
        heatbound =  exp( (-1) * ( (tempcost - cost) / temperature ) );
        if ( rate < heatbound){
            //have probability to accept the result
            cost = tempcost;
            bestHeight = thisHeight;
            bestWidth = thisWidth;
            // refresh the buffer;
            tempgamma_plus.assign(gamma_plus.begin(),gamma_plus.end());
            tempgamma_minus.assign(gamma_minus.begin(),gamma_minus.end());
        }
        else{
            gamma_plus.assign(tempgamma_plus.begin(),tempgamma_plus.end());
            gamma_minus.assign(tempgamma_minus.begin(),tempgamma_minus.end());
        }
    }
    temperature *= CoolingRate;
    setgammaposition();
    makedirgraph();
    return;
}

inline void grapher::setgammaposition(){
    // we use when the looping value == index(the real number), output the looping index
    for (int i = 0; i < gamma_plus.size(); i++){
        for (int j = 0; j < gamma_plus.size(); j++){
            if (gamma_plus[j] == i+1){
                pos_plus[i] = j+1;
            }
        }
    }
    for (int i = 0; i < gamma_minus.size(); i++){
        for (int j = 0; j < gamma_minus.size(); j++){
            if (gamma_minus[j] == i+1){
                pos_minus[i] = j+1;
            }
        }
    }  
}

// make the picture of the direction graph
inline void grapher::makedirgraph(){
    for (int i = 0; i < directiongraph.size(); i++){   // gamma[i] = a

        for (int j = 0; j < directiongraph[i].size(); j++){  // gamma[j] = b

            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[i] < pos_plus[j] && pos_minus[i] < pos_minus[j] ) ||
                (pos_plus[i] > pos_plus[j] && pos_minus[i] > pos_minus[j] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            //( a. b , ... b. a ) means the b is on the under of a
            else if( ( pos_plus[i] < pos_plus[j] && pos_minus[i] > pos_minus[j] ) ||
                     ( pos_plus[i] > pos_plus[j] && pos_minus[i] < pos_minus[j] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
        }
    }
    // output the direction graph
    // cout<<endl<<"graph :"<<endl;
    // for (int i = 0; i < directiongraph.size(); i++){
    //     for (int j = 0; j < directiongraph[i].size(); j++){
    //         cout<<directiongraph[i][j]<<"  ";
    //     }cout<<endl;
    // }
    // cout<<"--------------------------------"<<endl;
}

inline void grapher::initializeDAG(){
    // create sources and tails edges
    for (int i = 1; i < numofblocks+1; i++){
        // add source 
        HorizontalGraph->addEdge(0,i,0);
        VerticalGraph->addEdge(0,i,0);
        // add tails
        HorizontalGraph->addEdge(i,numofblocks+1,bstack[i-1].width);
        VerticalGraph->addEdge(i,numofblocks+1,bstack[i-1].height);
    }
    //horixontal part
    // { 3 , 7 , 6 , 4 , 2 , 1 , 5 }
    //1  ^
    //2  L   ^
    //3  L   L   ^
    for (int i = 0; i < directiongraph.size(); i++){
        x = gamma_minus[i] ;
        for (int j = 0; j < i; j++){
            y = gamma_minus[j];
            if ( directiongraph[ x - 1 ][ y - 1 ] == 1 ){ 
                // from u to v, weight
                HorizontalGraph->addEdge( y , x , bstack[y - 1].width );
            }else if( directiongraph[ x - 1 ][ y - 1 ] == 2 ){ // dir == 2
                VerticalGraph->addEdge( y , x , bstack[y - 1].height);
            }
        }
    }
}

// do not use!! this is not working yet!!!!
inline void grapher::DAGreconnect( int u ){
    for (int i = 0; i < directiongraph.size(); i++){
        HorizontalGraph->eraseEdge(gamma_minus[i],u);
        HorizontalGraph->eraseEdge(u,gamma_minus[i]);
        VerticalGraph->eraseEdge(gamma_minus[i],u);
        VerticalGraph->eraseEdge(u,gamma_minus[i]);
    }

    int v;    
    // u = a, v = b
    for (int j = 0; j < pos_minus[ u - 1 ] - 1; j++){ // < pos[x] since we have only have to look the number 
                                            // before it from gamma_minus
        v = gamma_minus[j];
        if ( directiongraph[ u - 1 ][ v - 1 ] == 1 ){ 
            // from u to v, weight
            HorizontalGraph->addEdge( v , u , bstack[v - 1].width );
        }else if( directiongraph[ u - 1 ][ v - 1 ] == 2 ){ // dir == 2
            VerticalGraph->addEdge( v , u , bstack[v - 1].height);
        }
    }
    // u = b, v = a. since we change the perspective, the axis of dirgraph should change
    for (int j = pos_minus[ u - 1 ] ; j < directiongraph.size(); j++){
        v = gamma_minus[j];
        if ( directiongraph[ v - 1 ][ u - 1 ] == 1 ){ 
            // from u to v, weight
            HorizontalGraph->addEdge( u , v , bstack[u - 1].width );
        }else if( directiongraph[ v - 1 ][ u - 1 ] == 2 ){ // dir == 2
            VerticalGraph->addEdge( u , v , bstack[u - 1].height);
        }
    }
}

inline void grapher::perturbs_M1(int x,int y){  // swap gamma_minus
    
    int temparray[2] = {x,y};

    //switch the x and y in gamma+
    for (int i = 0; i < gamma_minus.size(); i++){
        if (gamma_minus[i] == x){
            gamma_minus[i] = y;
        }else if (gamma_minus[i] == y){
            gamma_minus[i] = x;
        }
    }
    
    // update the position graph
    temp = pos_minus[ x - 1 ];
    pos_minus[ x - 1 ] = pos_minus[ y - 1 ];
    pos_minus[ y - 1 ] = temp;

    // update the directiongraph
    for (int icounter = 0; icounter < 2; icounter++){
        i = temparray[icounter] - 1;
        for (int j = 0; j < directiongraph[i].size(); j++){  // gamma[j] = b
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[i] < pos_plus[j] && pos_minus[i] < pos_minus[j] ) ||
                (pos_plus[i] > pos_plus[j] && pos_minus[i] > pos_minus[j] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            else if( ( pos_plus[i] < pos_plus[j] && pos_minus[i] > pos_minus[j] ) ||
                    ( pos_plus[i] > pos_plus[j] && pos_minus[i] < pos_minus[j] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[j] < pos_plus[i] && pos_minus[j] < pos_minus[i] ) ||
                (pos_plus[j] > pos_plus[i] && pos_minus[j] > pos_minus[i] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[j][i] = 1;
            }
            else if( ( pos_plus[j] < pos_plus[i] && pos_minus[j] > pos_minus[i] ) ||
                    ( pos_plus[j] > pos_plus[i] && pos_minus[j] < pos_minus[i] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[j][i] = 2;
            }
        }
    }
    // reconnect the edge
    // for (int i = 0; i < 2; i++){    
    //     DAGreconnect(temparray[i]);
    // }
}

inline void grapher::perturbs_M2(int x,int y){ // swap gamma_plus
    int temparray[2] = {x,y};

    //switch the x and y in gamma+
    for (int i = 0; i < gamma_plus.size(); i++){
        if (gamma_plus[i] == x){
            gamma_plus[i] = y;
        }else if (gamma_plus[i] == y){
            gamma_plus[i] = x;
        }
    }
    
    // update the position graph
    temp = pos_plus[ x - 1 ];
    pos_plus[ x - 1 ] = pos_plus[ y - 1 ];
    pos_plus[ y - 1 ] = temp;

    // update the directiongraph
    for (int icounter = 0; icounter < 2; icounter++){
        i = temparray[icounter] - 1;
        for (int j = 0; j < directiongraph[i].size(); j++){  // gamma[j] = b
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[i] < pos_plus[j] && pos_minus[i] < pos_minus[j] ) ||
                (pos_plus[i] > pos_plus[j] && pos_minus[i] > pos_minus[j] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            else if( ( pos_plus[i] < pos_plus[j] && pos_minus[i] > pos_minus[j] ) ||
                    ( pos_plus[i] > pos_plus[j] && pos_minus[i] < pos_minus[j] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[j] < pos_plus[i] && pos_minus[j] < pos_minus[i] ) ||
                (pos_plus[j] > pos_plus[i] && pos_minus[j] > pos_minus[i] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[j][i] = 1;
            }
            else if( ( pos_plus[j] < pos_plus[i] && pos_minus[j] > pos_minus[i] ) ||
                    ( pos_plus[j] > pos_plus[i] && pos_minus[j] < pos_minus[i] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[j][i] = 2;
            }
        }
    } 
    // reconnect the edge
    // for (int i = 0; i < 2; i++){    
    //     DAGreconnect(temparray[i]);
    // }
}

inline void grapher::perturbs_M3(int x,int y){
    int temparray[2] = {x,y};

    //switch the x and y in gamma+
    for (int i = 0; i < gamma_plus.size(); i++){
        if (gamma_plus[i] == x){
            gamma_plus[i] = y;
        }else if (gamma_plus[i] == y){
            gamma_plus[i] = x;
        }
        if (gamma_minus[i] == x){
            gamma_minus[i] = y;
        }else if (gamma_minus[i] == y){
            gamma_minus[i] = x;
        }
    }
    
    // update the position graph
    temp = pos_plus[ x - 1 ];
    pos_plus[ x - 1 ] = pos_plus[ y - 1 ];
    pos_plus[ y - 1 ] = temp;
    temp = pos_minus[ x - 1 ];
    pos_minus[ x - 1 ] = pos_minus[ y - 1 ];
    pos_minus[ y - 1 ] = temp;
    
    // update the directiongraph
    for (int icounter = 0; icounter < 2; icounter++){
        i = temparray[icounter] - 1;
        for (int j = 0; j < directiongraph[i].size(); j++){  // gamma[j] = b
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[i] < pos_plus[j] && pos_minus[i] < pos_minus[j] ) ||
                (pos_plus[i] > pos_plus[j] && pos_minus[i] > pos_minus[j] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[i][j] = 1;
            }
            else if( ( pos_plus[i] < pos_plus[j] && pos_minus[i] > pos_minus[j] ) ||
                    ( pos_plus[i] > pos_plus[j] && pos_minus[i] < pos_minus[j] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[i][j] = 2;
            }
            //a's position in gamma+ vs b's position in gamma-
            if ( ( pos_plus[j] < pos_plus[i] && pos_minus[j] < pos_minus[i] ) ||
                (pos_plus[j] > pos_plus[i] && pos_minus[j] > pos_minus[i] ) ){
                //( a. b , ... a. b ) means the a is on the left of b
                directiongraph[j][i] = 1;
            }
            else if( ( pos_plus[j] < pos_plus[i] && pos_minus[j] > pos_minus[i] ) ||
                    ( pos_plus[j] > pos_plus[i] && pos_minus[j] < pos_minus[i] ) ){
                //( a. b , ... b. a ) means the b is on the under of a
                directiongraph[j][i] = 2;
            }
        }
    }

    // reconnect the edge
    // for (int i = 0; i < 2; i++){    
    //     DAGreconnect(temparray[i]);
    // }
}

// print out the set axises 
inline void grapher::layout(){
    // look from gamma_minus first to gamma_minus end
    thisHeight = 0;
    thisWidth = 0;
    for (int i = 0; i < gamma_minus.size(); i++){
        x = 0;
        y = 0;
        for (int j = 0 ;j < i ; j++){
            // cout<< gamma_minus[j] <<" ";
            if ( directiongraph[ gamma_minus[i] - 1 ][ gamma_minus[j] - 1 ] == 1 ) {
                // if = 2, then add on to x axis
                x = max<int>( x , bstack[ gamma_minus[j] - 1 ].getx2() );
            }else{
                y = max<int>( y , bstack[ gamma_minus[j] - 1 ].gety2() );
            }
        }
        bstack[ gamma_minus[i] - 1].setxy(x,y);
        thisWidth = thisWidth>bstack[gamma_minus[i] - 1].getx2()?thisWidth:bstack[gamma_minus[i] - 1].getx2();
        thisHeight = thisHeight>bstack[gamma_minus[i] - 1].gety2()?thisHeight:bstack[gamma_minus[i] - 1].gety2();
    }
    
    // show all blocks' position
    // for (int i = 0; i < numofblocks; i++){
    //     cout << bstack[ tempgamma_minus[i] - 1 ].name <<" "
    //          << bstack[ tempgamma_minus[i] - 1 ].getx1() << " "
    //          << bstack[ tempgamma_minus[i] - 1 ].gety1() << " "
    //          << bstack[ tempgamma_minus[i] - 1 ].getx2() << " "
    //          << bstack[ tempgamma_minus[i] - 1 ].gety2() << " "<<endl;
    // }
}

