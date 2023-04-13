//
// Created by Zakaria on 11/04/2023.
//

#include <iostream>
#include <vector>
#include "monotonic-scheduler.h"
#include "rate-monotonic.h"
#include "deadline-monotonic.h"
#include "earliest-deadline-first.h"
#include "least-laxity-first.h"



using namespace std;

int main() {
    int n;
    cout << "Enter the number of tasks: ";
    cin >> n;

    // variables for tasks
    int arrival_time;
    int period;
    int deadline;
    int capacity;

    vector<Task> tasks;
    for (int i = 0; i < n; i++) {
        cout << "Enter the arrival time, period, deadline and capacity of task " << i+1 << ": ";
        cin >> arrival_time >> period >> deadline >> capacity;
        tasks.emplace_back(i+1, arrival_time, period, deadline, capacity);
    }

    // ask user for the method RM/DM
    int method;
    cout << "Enter:" << endl
            << " 1 for Rate Monotonic" << endl
            << " 2 for Deadline Monotonic" << endl
            << " 3 for Earliest Deadline First" << endl
            << " 4 /!\\ for Least Laxity First (is not working properly...)" << endl
            << "> ";

    cin >> method;

    if (method == 1) {
        RateMonotonic rm(tasks);
        rm.printSchedule();
    } else if (method == 2) {
        DeadlineMonotonic dm(tasks);
        dm.printSchedule();
    } else if (method == 3) {
        EarliestDeadlineFirst edf(tasks);
        edf.printSchedule();
    } else if (method == 4) {
        LeastLaxityFirst llf(tasks);
        llf.printSchedule();
    } else {
        cout << "Invalid method" << endl;
    }


    return 0;
}