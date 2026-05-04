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