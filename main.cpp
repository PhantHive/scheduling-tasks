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

    Task(int id, int arrival_time, int period, int deadline, int capacity, int i)
            : id(id), arrival_time(arrival_time), period(period), deadline(deadline), capacity(capacity) {}

    bool operator<(const Task& other) const {
        return deadline < other.deadline;
    }
};