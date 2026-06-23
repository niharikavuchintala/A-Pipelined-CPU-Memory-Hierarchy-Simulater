#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string name;
    int time_needed;
    vector<string> memory_list;
};

bool is_in_cache(vector<string>& cache, string block) {
    for (int i = 0; i < cache.size(); i++) {
        if (cache[i] == block) return true;
    }
    return false;
}

void add_to_cache(vector<string>& cache, int max_size, string block) {
    if (is_in_cache(cache, block)) return; 
    
    if (cache.size() == max_size) {
        cache.erase(cache.begin());
    }
    cache.push_back(block);
}

// HELPER: Reads the text file and gives us a list of tasks
vector<Task> load_tasks_from_file() {
    vector<Task> task_list;
    ifstream file("input.txt");
    string word;
    Task temp;

    while (file >> word) {
        if (word == "TASK") {
            if (temp.name != "") task_list.push_back(temp);
            temp = Task(); 
            file >> temp.name;
        }
        else if (word == "BURST") file >> temp.time_needed;
        else if (word == "MEM")   continue; // Skip this word
        else                      temp.memory_list.push_back(word);
    }
    task_list.push_back(temp); // Save the last one
    return task_list;
}


// --- 3. THE MAIN PROGRAM (SUPER SIMPLE NOW) ---

int main() {
    // 1. Get our tasks (The messy file reading is hidden above!)
    vector<Task> all_tasks = load_tasks_from_file();

    // 2. Set up our empty caches
    vector<string> l1, l2, l3;
    int ram_hits = 0;
    int cycle = 1;

    // 3. Keep working until all tasks are done
    bool still_working = true;
    
    while (still_working == true) {
        still_working = false; // Assume we are finished until we find a task

        // Go down the list of tasks one by one
        for (int i = 0; i < all_tasks.size(); i++) {
            
            // If this task still needs time to run
            if (all_tasks[i].time_needed > 0) {
                
                still_working = true; // We found work! Keep the while loop going.

                // Figure out how many times it can run (Max 3 for Round Robin)
                int loops = 3;
                if (all_tasks[i].time_needed < 3) {
                    loops = all_tasks[i].time_needed;
                }

                // Run the task for its allowed loops
                for (int step = 0; step < loops; step++) {
                    cout << "Cycle " << cycle << " | Task: " << all_tasks[i].name << " | ";

                    // Does it want memory?
                    if (all_tasks[i].memory_list.size() > 0) {
                        
                        // Grab the first memory block and remove it from the task's list
                        string mem = all_tasks[i].memory_list[0];
                        all_tasks[i].memory_list.erase(all_tasks[i].memory_list.begin());

                        cout << "Needs: " << mem << " | ";

                        // Check the L1 Cache
                        if (is_in_cache(l1, mem) == true) {
                            cout << "HIT L1!\n";
                        } 
                        // If it missed L1, force it into all caches (RAM Fetch)
                        else {
                            add_to_cache(l1, 32, mem);
                            add_to_cache(l2, 128, mem);
                            add_to_cache(l3, 512, mem);
                            ram_hits++;
                            cout << "MISS! Fetched from RAM.\n";
                        }
                    } 
                    // It doesn't want memory, just pure CPU time
                    else {
                        cout << "Doing CPU Math (No memory needed)\n";
                    }

                    all_tasks[i].time_needed--; // Subtract 1 from the time it needs
                    cycle++;                    // Increase the global cycle clock
                }
            }
        }
    }

   // 4. Print final score
    cout << "\n=== Final Results ===\n";
    cout << "Total Cycles: " << cycle - 1 << "\n"; 
    cout << "Tasks Completed: " << all_tasks.size() << "\n";
    cout << "Scheduler: Round Robin (quantum = 3)\n";
    cout << "RAM Accesses: " << ram_hits << "\n";
    
    return 0;
}