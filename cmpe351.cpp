/* This is code developed by <Abdullah Taher Anwer Shaikh - 22323166> */
#include "cmpe351.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
using namespace std;

struct Process {
    int id;
    int priority;
    int arrival;
    int burst;
    int rem;
    int wt;
    Process* next;
};

void run_fcfs(Process* head, int n) {
    int t = 0, completed = 0;
    while (completed < n) {
        Process* best = nullptr;
        for (Process* curr = head; curr != nullptr; curr = curr->next) {
            if (curr->rem > 0 && curr->arrival <= t) {
                if (!best || curr->arrival < best->arrival) {
                    best = curr;
                }
            }
        }
        if (best) {
            t += best->rem;
            best->rem = 0;
            best->wt = t - best->arrival - best->burst;
            completed++;
        } else {
            t++;
        }
    }
    cout << "FCFS simulation complete. Total time taken: " << t << "\n";
}

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
    
    ifstream infile(input_file);
    if (!infile) {
        cerr << "Error: Cannot open input file\n";
        return 1;
    }

    Process* head = nullptr;
    Process* tail = nullptr;
    int process_count = 0;
    int id_counter = 1;
    string line;

    while (getline(infile, line)) {
        if (line.empty()) continue;
        
        int colon1 = line.find(':');
        int colon2 = line.find(':', colon1 + 1);
        
        if (colon1 != -1 && colon2 != -1) {
            Process* p = new Process;
            p->id = id_counter++;
            p->burst = stoi(line.substr(0, colon1));
            p->arrival = stoi(line.substr(colon1 + 1, colon2 - colon1 - 1));
            p->priority = stoi(line.substr(colon2 + 1));
            p->rem = p->burst;
            p->wt = 0;
            p->next = nullptr;
            
            if (!head) {
                head = p;
                tail = p;
            } else {
                tail->next = p;
                tail = p;
            }
            process_count++;
        }
    }
    infile.close();
    cout << "Successfully parsed " << process_count << " processes. "<<quantum<<")\n";
    run_fcfs(head, process_count);
return 0;
}
