#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>


using namespace std;


class DeadlineMonotonic {
private:
    vector<Task> tasks;
    int hyperperiod;
    vector<int> timeline;

public:
    static bool compareByDeadline(const Task& task1, const Task& task2) {
        return task1.deadline < task2.deadline;
    }

    DeadlineMonotonic(vector<Task> tasks) : tasks(tasks) {

        bool canSchedule = MonotonicScheduler::checkSchedulability(tasks);

        if (!canSchedule) {
            return;
        }

        // sort the tasks by their periods (shortest period => highest priority)
        sort(this->tasks.begin(), this->tasks.end(), compareByDeadline);
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
            if (timeline[t] != 0 && tasks[timeline[t]-1].deadline < task.deadline) {
                // jump after the capacity of the task with higher priority
                continue;
            }
            else {
                timeline[t] = task.id;
                task.remaining_capacity--;
            }
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

