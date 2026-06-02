/* This is code developed by <Abdullah Taher Anwer Shaikh> */
#include "cmpe351.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
int quantum = 0;
    string input_file = "";
    string output_file = "";
    int opt;
    
    while ((opt = getopt(argc, argv, "t:f:o:")) != -1) {
        switch (opt) {
            case 't': quantum = stoi(optarg); break;
            case 'f': input_file = optarg; break;
            case 'o': output_file = optarg; break;
            default:
                cerr << "Usage: " << argv[0] << " -t <quantum> -f <input> -o <output>\n";
                return 1;
        }
    }
    
    cout << "Quantum: " << quantum << " Input: " << input_file << "\n";
return 0;
}
