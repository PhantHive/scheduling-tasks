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
    LeastLaxityFirst(vector<Task> tasks) {
        this->tasks = tasks;
        for (auto task : tasks) {
            this->hyperperiod = lcm(this->hyperperiod, task.period);
        }
        this->timeline = vector<int>(hyperperiod, 0);

        // check if the tasks are schedulable
        if (!checkSchedulability(tasks)) {
            cout << "The tasks are not schedulable." << endl;
            return;
        }


    }

    static bool compareByPeriod(const Task& task1, const Task& task2) {
        return task1.period < task2.period;
    }

    static bool checkSchedulability(vector<Task> tasks) {
        /*
         * Check if the tasks are schedulable using the least laxity first algorithm.
         * The algorithm is based on the following formula:
         *  sum of ((Ti - Ci) / Ti) <= 1
         * where:
         *  Ci = task capacity
         *  Ti = task period
         */
        double sum = 0;
        for (auto task : tasks) {
            sum += (double) (task.period - task.capacity) / task.period;
        }
        return sum <= 1;
    }

    void printSchedule() {
        // if nothing to print
        if (timeline.size() == 0) {
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