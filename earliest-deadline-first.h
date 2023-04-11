//
// Created by Zakaria on 11/04/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

class EarliestDeadlineFirst {
private:
    vector<Task> tasks;
    int hyperperiod;
    vector<int> timeline;

public:

    static bool compareByPeriod(const Task& task1, const Task& task2) {
        return task1.deadline < task2.deadline;
    }

    EarliestDeadlineFirst(vector<Task> tasks) : tasks(tasks) {

        bool canSchedule = checkSchedulability(tasks);

        if (!canSchedule) {
            return;
        }

        // sort the tasks by their periods (shortest period => highest priority)

        sort(this->tasks.begin(), this->tasks.end(), compareByPeriod);

        // calculate the hyperperiod (lcm of all task periods)
        hyperperiod = 1;
        for (auto task: this->tasks) {
            hyperperiod = lcm(hyperperiod, task.period);
        }

        // initialize the timeline
        timeline = vector<int>(hyperperiod);
        cout << "Timeline size: " << timeline.size() << endl;

        // assign each task to a processor based on their priorities (periods)
        for (auto task: this->tasks) {
            for (int t = task.arrival_time; t < hyperperiod; t += task.period) {
                int start_time = MonotonicScheduler::findEarliestAvailableTimeSlot(timeline, t, hyperperiod);
                assignTaskToProcessor(timeline, task, this->tasks, start_time);
            }
        }
    }

    static void assignTaskToProcessor(vector<int>& timeline, Task& task, vector<Task>& tasks, int start_time) {

        /*
         * Assign a task to a processor.
         * The task is assigned to the processor for the duration of its capacity.
         */
        for (int i = start_time; i < start_time + task.period; i++) {
            if (task.remaining_capacity == 0) {
                task.remaining_capacity = task.capacity;
                break;
            }
            int t = i % timeline.size();

            for (auto otherTask : tasks) {
                if (otherTask.id == task.id) {
                    continue;
                }
                int otherTaskCurrentPeriod = floor((double) t / otherTask.period) * otherTask.period;
                int otherTaskDeadline = otherTaskCurrentPeriod + otherTask.deadline;
                int taskCurrentPeriod = floor((double) t / task.period) * task.period;
                int taskDeadline = taskCurrentPeriod + task.deadline;
                if ((otherTaskDeadline < taskDeadline) && (otherTask.remaining_capacity > 0) && (i < otherTaskDeadline)) {
                    // jump after the capacity of the task with higher priority
                    continue;
                }
                else {
                    if (timeline[t] == 0) {
                        timeline[t] = task.id;
                        task.remaining_capacity--;
                    }
                }

            }
        }
    }


    bool checkSchedulability(vector<Task>& tasks) {
        /*
         * The tasks are schedulable if the sum of the utilization factors is less than or equal to 1.
         */
        double sum = 0;
        for (auto task : tasks) {
            sum += (double) task.capacity / task.period;
        }
        if (sum <= 1) {
            cout << "The tasks are schedulable." << endl;
            return true;
        }
        else {
            cout << "The tasks are not schedulable." << endl;
            return false;
        }
    }

    void printSchedule() {

        // if nothing to print
        if (timeline.size() == 0) {
            cout << "No schedule to print." << endl;
            return;
        }

        // print the schedule based on the timeline
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


};


