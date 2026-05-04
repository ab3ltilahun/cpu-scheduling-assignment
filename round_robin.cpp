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