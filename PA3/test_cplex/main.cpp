#define IL_STD
#include<iostream>
#include<fstream>
#include<vector>
#include <ilcplex/ilocplex.h>
ILOSTLBEGIN
using namespace std;
void solve();
void expsolve();
struct block{
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
    int argc,char **argv
){
    string infile = argv[1], 
        ofile = argv[2],
    // string infile,ofile,
            strbuffer;
    // infile = "../testcases/5_5_6.in";
    // ofile = "../testcases/5_5_6.out";
    vector<block> bucket;
    vector< vector< int > > edge;
    block* tempblock;

    int id,x,y,numholes,mapx,mapy,temp;
    //read files
    fstream fin,fout;
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

    fin>>strbuffer>> mapx >> mapy
       >>strbuffer>>strbuffer>>numholes;
    for (int i = 0; i < numholes; i++){
        fin>>id>>x>>y;
        tempblock = new block(id,x,y);
        bucket.push_back( *tempblock );
    }
    fin.close();

    //link the edge
    vector<int> buffer(numholes,0),temptest;
    for (int i = 0; i < numholes; i++){
        edge.push_back(buffer);
    }
    
    for (int i = 0; i < numholes; i++){
        for (int j = 0; j < i; j++){
            if ( (bucket[i].x - bucket[j].x <= 2) && (bucket[j].x - bucket[i].x <= 2) ){
                if((bucket[i].y - bucket[j].y <= 2) && (bucket[j].y - bucket[i].y <= 2))
                    edge[i][j] = 1;
            }
            cout<<edge[i][j]<<" ";
        }
        cout<<0<<endl;
    }
    
    // solving 
    IloEnv env;
    try {
        IloModel model(env);
        IloCplex cplex(model);
        // Define decision variables
        IloNumVarArray colors1(env, numholes, 0, 1 ,ILOINT); // declare colors
        IloNumVarArray colors2(env, numholes, 0, 1 ,ILOINT); // declare colors

        IloNumVarArray conflict(env), conflict1(env),conflict2(env);
        IloRangeArray con(env); // conditions
        IloExpr expr(env);
        // Add constraints -> colors can only be one ( 00 , 01 , 10 )
        for (int i = 0; i < numholes; i++){
            con.add( colors1[i] + colors2[i] <= 1);
        }
        for (int i = 0; i < numholes; i++){
            for (int j = 0; j < numholes; j++){
                conflict.add( IloNumVar( env , 0.0 , 1.0 , ILOINT ) );
                conflict1.add( IloNumVar( env , 0.0 , 1.0 , ILOINT ) );
                conflict2.add( IloNumVar( env , 0.0 , 1.0 , ILOINT ) );
            }
        }
        
        // checkers
        cout<<"edges : "<<endl;
        for (int i = 0; i < numholes; i++){
            for (int j = 0; j < numholes; j++){
                if ( edge[i][j] == 1){  // means have edges
                    con.add( colors1[i] + colors1[j] - 1 - conflict1[ i*numholes + j ] <=0 ); // xi+ xj <= 1 + cij1
                    con.add( colors1[i] + colors1[j] + conflict1[ i*numholes + j ] >= 1 ); // xi+ xj <= 1 + cij1
                    
                    con.add( colors2[i] + colors2[j] - 1 - conflict2[ i*numholes + j ] <=0 ); // xi+ xj <= 1 + cij2
                    con.add( colors2[i] + colors2[j] + conflict2[ i*numholes + j ] >= 1 ); // xi+ xj <= 1 + cij2
                    con.add( conflict1[ i*numholes + j ] + conflict2[ i*numholes + j ] - conflict[ i*numholes + j ] <= 1);
                    
                    expr += conflict[ i*numholes + j ]; // take E(cij)'s minimal
                }
            }
            cout<<endl;
        }
        model.add(con);
        // Objective function
        model.add(IloMinimize( env, expr ));

        // Solve the problem
        cplex.solve();

        // Print solution
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            // feasible means it has at least find a solution
            assert( cplex.getStatus() == IloAlgorithm::Feasible ||
                cplex.getStatus() == IloAlgorithm::Optimal); 
            // build in function to make sure condition is true
            env.out() << "Solution status = " << cplex.getStatus() << std::endl;
            std::cout << "Objective Value: " << cplex.getObjValue() << std::endl; // best conflict
            cout<<"solutions :"<<endl;
            for (int i = 0; i < numholes; i++){
                cout<<i<<" "<<(cplex.getValue( colors1[i]*2 + colors2[i] + 1))<<endl;
            }
            // output file
            try{
                fout.open(ofile,fstream::out);
            }
            catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            if(!fout.is_open()){
                cout << "Error: the output file is not opened!!" << endl;
                exit(1);
            }
            fout<<cplex.getObjValue()<<endl;
            for (int i = 0; i < numholes; i++){
                fout<<i<<" "<<(cplex.getValue( colors1[i]*2 + colors2[i] + 1))<<endl;
            }
            
        } else {
            std::cout << "No solution found" << std::endl;
        }
    } 
    catch (IloException& ex) {
        std::cerr << "Error: " << ex << std::endl;
    }
    env.end();
    // solve();
    cout<<"finish!";
    return 0;
}
