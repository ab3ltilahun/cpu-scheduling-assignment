void sjf_non_preemptive(vector<Process> p) {
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