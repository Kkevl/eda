#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int main(int argc,char **argv){
    //input
    fstream fin;
    string file = argv[1], ofile = argv[2];
    fin.open(file, fstream::in);
    if(!fin.is_open()){
        cout << "Error: the input file is not opened!!" << endl;
	    exit(1);
    }
    int xtics = 20,
        ytics = 20,
        boundarx = 0,
        boundary = 0,
        macro = 0,
        x1,y1,x2,y2;
    string strbuffer;
    vector<string> names;
    vector<int> positions;
    
    //load blocks
    fin>>strbuffer>>boundarx>>boundary;
    fin>>strbuffer>>macro;
    xtics = boundarx/5;
    ytics = boundary/5;
    //start reading each blocks
    for (int i = 0; i < macro; i++){
        fin>>strbuffer>>x1>>y1>>x2>>y2;
        names.push_back(strbuffer);
        positions.push_back(x1);
        positions.push_back(y1);
        positions.push_back(x2);
        positions.push_back(y2);
    }

    //output
    fstream fout;
    fout.open(ofile,fstream::out);
    if(!fout.is_open()){
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }

    //begin
    fout<<"reset\n"
        <<"set title \"result\" \n"
        <<"set xlabel \"X\"\n"
        <<"set ylabel \"Y\"\n";
    
    //blocks
    for (int i = 0; i < macro; i++){
        fout<<"set object "<<i + 1 <<" rect from "<<positions[i*4]<<","<<positions[i*4+1]<<" to "<<positions[i*4+2]<<","<<positions[i*4+3]<<endl
        <<"set label \""<<names[i]<<"\" at "<<(positions[i*4]+positions[i*4+2])/2<<","<<(positions[i*4+1]+positions[i*4+3])/2<<" center\n";
    }

    //end
    fout<<"set xtics "<<xtics<<endl
        <<"set ytics "<<ytics<<endl
        <<"plot [0:"<<boundarx<<"][0:"<<boundary<<"]0\n"
        <<"set terminal png size 1024,768\n"
        <<"set output \"output.png\"\n"
        <<"replot";    
    return 0;
}