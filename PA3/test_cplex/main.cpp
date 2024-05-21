#define IL_STD
#include <iostream>
#include<fstream>
#include<vector>
// #include <ilcplex/ilocplex.h>
// ILOSTLBEGIN
using namespace std;
void solve();
struct block
{
    int id = 0,
        x = 0,
        y = 0;
    int color = 0;
    block(){};
    block(int id,int x,int y){
        this->id = id;
        this->x = x;
        this->y = y;
        this->color = 0;
    }
};

int main(
    // int argc,char **argv
){
    int id,x,y,numholes,mapx,mapy,temp;
    vector<block> bucket;
    block* tempblock;
    // string infile = argv[1], 
    //     ofile = argv[2],
    string infile,strbuffer;
    infile = "../testcases/5_5_6.in";
    fstream fin;
    try{
        fin.open(infile,fstream::in);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    if(!fin.is_open()){
        cout << "Error: the input file is not opened!!" << endl;
	    exit(1);
    }
    fin>>strbuffer>> mapx >> mapy;
    fin>>strbuffer>>strbuffer>>numholes;
    for (int i = 0; i < numholes; i++){
        fin>>id>>x>>y;
        tempblock = new block(id,x,y);
        bucket.push_back( *tempblock );
    }    
    cout<<"finish";
    return 0;
}

void solve(){
    /*IloEnv env;
    try {
        IloModel model(env);
        IloCplex cplex(model);

        // Define decision variables
        IloNumVar x(env, 0.0, IloInfinity, ILOFLOAT);
        IloNumVar y(env, 0.0, IloInfinity, ILOFLOAT);

        model.add(IloMaximize(env, 3 * x + 2 * y)); // Objective function

        // Add constraints
        model.add(2 * x + y <= 8);
        model.add(x + 2 * y <= 6);

        // Solve the problem
        cplex.solve();

        // Print solution
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            std::cout << "Objective Value: " << cplex.getObjValue() << std::endl;
            std::cout << "x = " << cplex.getValue(x) << std::endl;
            std::cout << "y = " << cplex.getValue(y) << std::endl;
        } else {
            std::cout << "No solution found" << std::endl;
        }
    } catch (IloException& ex) {
        std::cerr << "Error: " << ex << std::endl;
    }
    env.end();*/
}
