//
// Created by sunn on 06/04/2023.
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
    int remaining_capacity; // remaining capacity of task

    Task(int id, int arrival_time, int period, int deadline, int capacity, int remaining_capacity)
            : id(id), arrival_time(arrival_time), period(period), deadline(deadline), capacity(capacity), remaining_capacity(remaining_capacity) {}

    bool operator<(const Task& other) const {
        return period < other.period;
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

void assignTaskToProcessor(vector<int>& timeline, const Task& task, vector<Task>& tasks, int start_time) {
    /*
     * Assign a task to a processor.
     * The task is assigned to the processor for the duration of its capacity.
     */
    for (int i = start_time; i < start_time + task.capacity; i++) {
        int t = i % timeline.size();
        if (timeline[t] != 0 && tasks[timeline[t]-1].period < task.period) {
            // task cannot be scheduled starting at this time, as there is another task with a shorter period running
            break;
        }
        timeline[t] = task.id;
    }
}


void rateMonotonic(vector<Task>& tasks) {
    // sort the tasks by their periods (shortest period => highest priority)
    sort(tasks.begin(), tasks.end());

    // calculate the hyperperiod (lcm of all task periods)
    int hyperperiod = 1;
    for (auto task : tasks) {
        hyperperiod = lcm(hyperperiod, task.period);
    }

    // initialize the timeline
    vector<int> timeline(hyperperiod);
    cout << "Timeline size: " << timeline.size() << endl;


    // schedule the tasks while there are capacity remaining for any task during a period
    for (int t = 0; t < hyperperiod; t++) {
        for (auto & task : tasks) {
            if (t % task.period == 0) {
                // reset the remaining capacity of the task
                task.remaining_capacity = task.capacity;
            }
        }

        for (auto & task : tasks) {
            if (task.remaining_capacity > 0) {
                // find the earliest available time slot for the task to be scheduled
                int start_time = findEarliestAvailableTimeSlot(timeline, t, hyperperiod);

                // assign the task to the processor
                assignTaskToProcessor(timeline, task, tasks, start_time);

                // update the remaining capacity of the task
                task.remaining_capacity -= (start_time - t + task.capacity);
            }
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
        rateMonotonic(tasks);
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
        tasks.emplace_back(i+1, arrival_time, period, deadline, capacity, capacity);
    }

    checkSchedulability(tasks);

    return 0;
}

