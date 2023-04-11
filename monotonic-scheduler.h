//
// Created by sunn on 11/04/2023.
//

#ifndef TP2_MONOTONIC_SCHEDULER_H
#define TP2_MONOTONIC_SCHEDULER_H

#endif //TP2_MONOTONIC_SCHEDULER_H

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

    Task(int id, int arrival_time, int period, int deadline, int capacity)
            : id(id), arrival_time(arrival_time), period(period), deadline(deadline), capacity(capacity), remaining_capacity(capacity) {}

};

class MonotonicScheduler {
public:
    static bool checkSchedulability(const vector<Task>& tasks) {
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
            return true;
        } else {
            cout << "The tasks are not schedulable" << endl;
            return false;
        }
    }

    static int findEarliestAvailableTimeSlot(const vector<int> &timeline, int t, int hyperperiod) {
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

};