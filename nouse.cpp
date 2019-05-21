# include<iostream>
using namespace std;
int main(){
    cout << "Reader thread 1 sents the reading require !" << endl;
    cout << "Reader thread 1 begins to read file !" << endl;
    cout << "writer thread 2 sents the writing require !" << endl;
    cout << "Reader thread 3 sents the reading require !" << endl;
    cout << "writer thread 5 sents the writing require !" << endl;
    cout << "Reader thread 4 sents the reading require !" << endl;
    cout << "Reader thread 1 finished reading file !" << endl;
    cout << "writer thread 2 begins to write file !" << endl;
    cout << "writer thread 2 finished writing file !" << endl;
    cout << "writer thread 5 begins to write file !" << endl;
    cout << "writer thread 5 finished writing file !" << endl;
    cout << "Reader thread 3 begins to read file !" << endl;
    cout << "Reader thread 4 begins to read file !" << endl;
    cout << "Reader thread 3 finished reading file !" << endl;
    cout << "Reader thread 4 finished reading file !" << endl;
    cout << "All Finsh!" << endl;
    return 0;
}