//
// Created by Zakaria on 11/04/2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

struct Task {
    int id;             // task id
    int arrival_time;   // arrival time of task
    int period;         // period of task
    int deadline;       // deadline of task
    int capacity;       // capacity of task

    Task(int id, int arrival_time, int period, int deadline, int capacity)
            : id(id), arrival_time(arrival_time), period(period), deadline(deadline), capacity(capacity) {}

    bool operator<(const Task& other) const {
        return deadline < other.deadline;
    }
};

int findEarliestAvailableTimeSlot(const vector<int> &timeline, int t, int hyperperiod) {
    /*
     * Find the earliest available time slot for a task to be scheduled.
     * If the time slot is available, return the time slot.
     */
    int start_time = t;
    while (timeline[start_time % hyperperiod] != 0) {
        start_time++;
    }
    return start_time;
}

void assignTaskToProcessor(vector<int>& timeline, const Task& task, int start_time) {
    /*
     * Assign a task to a processor.
     * The task is assigned to the processor for the duration of its capacity.
     */
    for (int i = start_time; i < start_time + task.capacity; i++) {
        timeline[i % timeline.size()] = task.id;
    }
}


void deadlineMonotonic(vector<Task>& tasks) {
    // sort the tasks by their periods (shortest period => highest priority)
    sort(tasks.begin(), tasks.end());

    // calculate the hyperperiod (lcm of all task periods)
    int hyperperiod = 1;
    for (auto task : tasks) {
        hyperperiod = lcm(hyperperiod, task.deadline);
    }

    // initialize the timeline
    vector<int> timeline(hyperperiod);
    cout << "Timeline size: " << timeline.size() << endl;

    // assign each task to a processor based on their priorities (periods)
    for (auto task : tasks) {
        for (int t = task.arrival_time; t < hyperperiod; t += task.period) {
            int start_time = findEarliestAvailableTimeSlot(timeline, t, hyperperiod);
            assignTaskToProcessor(timeline, task, start_time);
        }
    }

    // print the schedule
    cout << "Schedule using Rate Monotonic algorithm:" << endl;
    for (int t = 0; t < hyperperiod; t++) {
        if (timeline[t] != 0) {
            cout << "t=" << t << ": Task " << timeline[t] << endl;
        }
        else {
            cout << "t=" << t << ": ---" << endl;
        }
    }
}


// check if the tasks are schedulable

void checkSchedulability(vector<Task>& tasks) {
    /*
     * The tasks are schedulable if the sum of the deadlines divided by the periods is less than or equal to
     * the number of tasks multiplied by (2^(1/n) - 1), where n is the number of tasks.
     */
    int sum = 0;
    for (auto & task : tasks) {
        sum += task.deadline / task.period;
    }

    if (sum <= tasks.size() * (pow(2, 1.0 / tasks.size()) - 1)) {
        cout << "The tasks are schedulable" << endl;
        deadlineMonotonic(tasks);
    } else {
        cout << "The tasks are not schedulable" << endl;
    }
}

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

    checkSchedulability(tasks);

    return 0;
}
