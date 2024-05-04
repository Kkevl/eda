#include<iostream>
#include<string>
#include<vector>
#pragma once
using namespace std;

class node
{
private:
public:

    int cost; // calculate own cost untill now
    vector<node> previous, next;
    node();
    ~node(){};
};
node::node(){}

// edges' weight = width or height
class DAG{
private:
public:
    node source,tail,connect_all;
    DAG();
    ~DAG(){};
};
DAG::DAG(){

}

