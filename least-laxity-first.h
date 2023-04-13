using namespace std;

class LeastLaxityFirst {
private:
    struct TaskInfo {
        int deadline;
        int laxity;
    };

    vector<Task> tasks;
    int hyperperiod;
    vector<int> timeline;
    vector<TaskInfo> taskInfos;

public:
    LeastLaxityFirst(vector<Task> tasks) : tasks(tasks) {
        hyperperiod = 1;
        for (const auto& task : tasks) {
            hyperperiod = lcm(hyperperiod, task.period);
        }
        timeline = vector<int>(hyperperiod, 0);

        // check if the tasks are schedulable
        if (!checkSchedulability(tasks)) {
            cout << "The tasks are not schedulable." << endl;
            return;
        }

        // sort the tasks by their periods (shortest period => highest priority)
        sort(this->tasks.begin(), this->tasks.end(), compareByPeriod);

        // initialize the taskInfos
        for (const auto& task : tasks) {
            TaskInfo taskInfo;
            taskInfo.deadline = task.arrival_time + task.period;
            taskInfo.laxity = taskInfo.deadline - task.remaining_capacity;
            taskInfos.push_back(taskInfo);
        }

        // initialize the timeline
        timeline = vector<int>(hyperperiod);
        cout << "Timeline size: " << timeline.size() << endl;

        // assign each task to a processor based on their priorities (periods)
        for (auto task : this->tasks) {
            for (int t = task.arrival_time; t < hyperperiod; t += task.period) {
                int start_time = MonotonicScheduler::findEarliestAvailableTimeSlot(timeline, t, hyperperiod);
                assignTaskToProcessor(timeline, task, this->tasks, start_time);
            }
        }


    }

    static bool compareByPeriod(const Task& task1, const Task& task2) {
        return task1.period < task2.period;
    }


    void assignTaskToProcessor(vector<int>& timeline, Task& task, vector<Task>& tasks, int start_time) {
        int highestPriorityTaskIndex = 0;
        int highestPriorityTaskLaxity = taskInfos[0].laxity;

        // find the task with the highest priority based on laxity
        for (int i = 1; i < taskInfos.size(); i++) {
            if (taskInfos[i].laxity < highestPriorityTaskLaxity) {
                highestPriorityTaskIndex = i;
                highestPriorityTaskLaxity = taskInfos[i].laxity;
            }
        }

        // assign the task to the processor
        for (int i = start_time; i < timeline.size(); i++) {
            if (task.remaining_capacity == 0) {
                task.remaining_capacity = task.capacity;
                break;
            }
            int t = i % timeline.size();

            // check processor availability
            bool isProcessorFree = true;
            for (auto otherTask : tasks) {
                if (otherTask.id == task.id) {
                    continue;
                }
                if (t >= otherTask.arrival_time && t < otherTask.arrival_time + otherTask.capacity) {
                    isProcessorFree = false;
                    break;
                }
            }

            if (isProcessorFree) {
                timeline[t] = task.id;
                task.remaining_capacity--;
            }
        }

        // update the deadline
        taskInfos[highestPriorityTaskIndex].deadline += task.period;

        // update the laxity of the highest priority task
        taskInfos[highestPriorityTaskIndex].laxity = taskInfos[highestPriorityTaskIndex].deadline - tasks[highestPriorityTaskIndex].remaining_capacity;
    }




    static bool checkSchedulability(const vector<Task>& tasks) {
        int utilization = 0;
        for (const auto& task : tasks) {
            utilization += task.capacity / task.period;
        }
        if (utilization <= 1) {
            cout << "The tasks are schedulable." << endl;
            //
            return true;
        } else {
            cout << "The tasks are not schedulable." << endl;
            return false;
        }
    }

    void printSchedule() {
        // if nothing to print
        if (timeline.empty()) {
            cout << "No schedule to print." << endl;
            return;
        }

        // print the schedule based on the timeline
        cout << "Schedule using Least Laxity First algorithm:" << endl;
        for (int t = 0; t < hyperperiod; t++) {
            if (timeline[t] != 0) {
                cout << "t=" << t << ": Task " << timeline[t] << endl;
            } else {
                cout << "t=" << t << ": ---" << endl;
            }
        }
    }


};