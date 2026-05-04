#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
// Structure to hold all data for a single process
struct Process {
    string id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

//Vector to store our processes
vector<Process> processes;

//Function Prototypes
void input_processes() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter Process ID, Arrival Time, and Burst Time: ";
        cin >> p.id >> p.arrival_time >> p.burst_time;
        p.remaining_time = p.burst_time;
        processes.push_back(p);
    }
}
void fcfs(vector<Process> p) {
    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < p.size(); i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        current_time = p[i].completion_time;
    }
    // Print Average WT and TAT
cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
for (auto &proc : p) {
    cout << proc.id << "\t"
         << proc.arrival_time << "\t"
         << proc.burst_time << "\t"
         << proc.completion_time << "\t"
         << proc.turnaround_time << "\t"
         << proc.waiting_time << endl;
}

cout << "\nAverage Waiting Time = " << total_wt / p.size();
cout << "\nAverage Turnaround Time = " << total_tat / p.size() << endl;}
void sjf_non_preemptive(vector<Process> &p) {
    int current_time = 0, completed = 0;
    int n = p.size();
    vector<bool> is_completed(n, false);

    while (completed != n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i]) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].waiting_time = current_time - p[idx].arrival_time;
            p[idx].completion_time = current_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            is_completed[idx] = true;
            current_time = p[idx].completion_time;
            completed++;
        } else {
            current_time++;
        }
    }
float total_wt = 0, total_tat = 0;

cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
for (auto &proc : p) {
    total_wt += proc.waiting_time;
    total_tat += proc.turnaround_time;

    cout << proc.id << "\t"
         << proc.arrival_time << "\t"
         << proc.burst_time << "\t"
         << proc.completion_time << "\t"
         << proc.turnaround_time << "\t"
         << proc.waiting_time << endl;
}

cout << "\nAverage Waiting Time = " << total_wt / n;
cout << "\nAverage Turnaround Time = " << total_tat / n << endl;
}
void srtf(vector<Process> p) {
    int current_time = 0, completed = 0, n = p.size();
    int min_rem = 1e9, shortest = 0;
    bool check = false;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((p[i].arrival_time <= current_time) && (p[i].remaining_time < min_rem) && p[i].remaining_time > 0) {
                min_rem = p[i].remaining_time;
                shortest = i;
                check = true;
            }
        }

        if (!check) { current_time++; continue; }

        p[shortest].remaining_time--;
        min_rem = p[shortest].remaining_time;
        if (min_rem == 0) min_rem = 1e9;

        if (p[shortest].remaining_time == 0) {
            completed++;
            check = false;
            p[shortest].completion_time = current_time + 1;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
        }
        current_time++;
    }
float total_wt = 0, total_tat = 0;

cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
for (auto &proc : p) {
    total_wt += proc.waiting_time;
    total_tat += proc.turnaround_time;

    cout << proc.id << "\t"
         << proc.arrival_time << "\t"
         << proc.burst_time << "\t"
         << proc.completion_time << "\t"
         << proc.turnaround_time << "\t"
         << proc.waiting_time << endl;
}

cout << "\nAverage Waiting Time = " << total_wt / n;
cout << "\nAverage Turnaround Time = " << total_tat / n << endl;}

void round_robin(vector<Process> p, int quantum) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0, completed = 0, n = p.size();
    queue<int> q;
    vector<bool> in_queue(n, false);

    q.push(0);
    in_queue[0] = true;
    current_time = p[0].arrival_time;

    while (completed != n) {
        if (q.empty()) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && !in_queue[i] && p[i].remaining_time > 0) {
                    q.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        if (p[idx].remaining_time > quantum) {
            current_time += quantum;
            p[idx].remaining_time -= quantum;

            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && !in_queue[i] && p[i].remaining_time > 0) {
                    q.push(i);
                    in_queue[i] = true;
                }
            }

            q.push(idx);
        } else {
            current_time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = current_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && !in_queue[i] && p[i].remaining_time > 0) {
                    q.push(i);
                    in_queue[i] = true;
                }
            }
        }
    }

    float total_wt = 0, total_tat = 0;

    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;

        cout << p[i].id << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].completion_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << total_wt / n;
    cout << "\nAverage Turnaround Time = " << total_tat / n << endl;
}
bool isSafe(vector<int> processes, vector<int> avail,
            vector<vector<int>> max,
            vector<vector<int>> allot,
            int P, int R) {

    vector<vector<int>> need(P, vector<int>(R));
    vector<bool> finish(P, false);
    vector<int> safeSeq(P);
    vector<int> work = avail;

    // Calculate Need
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Print Need matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    int count = 0;

    while (count < P) {
        bool found = false;

        for (int p = 0; p < P; p++) {
            if (!finish[p]) {

                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT SAFE\n";
            return false;
        }
    }

    cout << "\nSystem is SAFE\nSafe sequence: ";
    for (int i = 0; i < P; i++)
        cout << "P" << safeSeq[i] << " ";

    cout << endl;

    return true;
}
int main() {
    //Gather input from the user
    input_processes();
    cout << "\n--- Banker's Algorithm (User Input) ---\n";

int P, R;
cout << "Enter number of processes: ";
cin >> P;

cout << "Enter number of resources: ";
cin >> R;

vector<int> processes_id(P);
for (int i = 0; i < P; i++) processes_id[i] = i;

vector<int> avail(R);
cout << "Enter Available resources:\n";
for (int i = 0; i < R; i++) cin >> avail[i];

vector<vector<int>> max(P, vector<int>(R));
cout << "Enter Max matrix:\n";
for (int i = 0; i < P; i++)
    for (int j = 0; j < R; j++)
        cin >> max[i][j];

vector<vector<int>> allot(P, vector<int>(R));
cout << "Enter Allocation matrix:\n";
for (int i = 0; i < P; i++)
    for (int j = 0; j < R; j++)
        cin >> allot[i][j];

    cout << "\n--- First Come First Served (FCFS) ---" << endl;
     fcfs(processes);

    cout << "\n--- Shortest Job First (Non-Preemptive) ---" << endl;
   sjf_non_preemptive(processes);

    cout << "\n--- Shortest Remaining Time First (SRTF) ---" << endl;
   srtf(processes);

    cout << "\n--- Round Robin (Time Quantum = 2) ---" << endl;
    round_robin(processes, 2);
    isSafe(processes_id, avail, max, allot, P, R);
return 0;
}
