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

bool is_in_cache(vector<string>& cache, string block) 
{
    for (int i = 0; i < cache.size(); i++) 
    {
        if (cache[i] == block) 
        return true;
    }
    return false;
}

void add_to_cache(vector<string>& cache, int max_size, string block) 
{
    if (is_in_cache(cache, block)) 
    return; 
    
    if (cache.size() == max_size) 
    {
        cache.erase(cache.begin());
    }
    cache.push_back(block);
}

vector<Task> load_tasks_from_file() 
{
    vector<Task> task_list;
    ifstream file("input.txt");
    string word;
    Task temp;

    while (file >> word)
    {
        if (word == "TASK") 
        {
            if (temp.name != "") task_list.push_back(temp);
            temp = Task(); 
            file >> temp.name;
        }
        else if (word == "BURST") file >> temp.time_needed;
        else if (word == "MEM");
        else temp.memory_list.push_back(word);
    }
    task_list.push_back(temp); 
    return task_list;
}

int main() 
{
 vector<Task> all_tasks = load_tasks_from_file();
    
    vector<string> l1, l2, l3;
    int ram_hits = 0;
    int cycle = 1;

    bool still_working = true;
    
    while (still_working == true) 
    {
        still_working = false; 

        for (int i = 0; i < all_tasks.size(); i++) 
        {
     
            if (all_tasks[i].time_needed > 0) 
           
            {
              still_working = true;

                int loops = 3;
                if (all_tasks[i].time_needed < 3) 
                {
                    loops = all_tasks[i].time_needed;
                }

                for (int step = 0; step < loops; step++) 
                {
                    cout << "Cycle " << cycle << " | Task: " << all_tasks[i].name << " | ";

                    if (all_tasks[i].memory_list.size() > 0) 
                    
                    {    
                        string mem = all_tasks[i].memory_list[0];
                        all_tasks[i].memory_list.erase(all_tasks[i].memory_list.begin());

                        cout << "Needs: " << mem << " | ";

                        if (is_in_cache(l1, mem) == true) {
                            cout << "HIT L1!\n";
                        } 
                            
                        else 
                        {
                            add_to_cache(l1, 32, mem);
                            add_to_cache(l2, 128, mem);
                            add_to_cache(l3, 512, mem);
                            ram_hits++;
                            cout << "MISS! Fetched from RAM.\n";
                        }
                    } 
                   
                    else 
                    {
                        cout << "Doing CPU Math (No memory needed)\n";
                    }

                    all_tasks[i].time_needed--; 
                    cycle++;                    
                }
            }
        }
    }

    cout << "\nFinal Results!\n";
    cout << "Total Cycles: " << cycle - 1 << "\n"; 
    cout << "Tasks Completed: " << all_tasks.size() << "\n";
    cout << "Scheduler: Round Robin (quantum = 3)\n";
    cout << "RAM Accesses: " << ram_hits << "\n";
    
    return 0;
}
