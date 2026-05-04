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
