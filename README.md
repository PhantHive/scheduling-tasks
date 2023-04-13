
<div align="center">

<H1>Scheduling Tasks</H1>

</div>

<div align="center">

[![Language][langue-shield]][issues-url]
[![Issues][issues-shield]][issues-url]

![img_1.png](img_1.png)

</div>

---

In this project, I implemented some algorithms for scheduling tasks.

## Structure

[//]: # (make a table containing all .h files and the main.cpp with description)

| File               | Description                                         |
|--------------------|-----------------------------------------------------|
| `main.cpp`         | Main file                                           |
| `rate-monotonic.h` | Rate Monotonic algorithm                            |
| `deadline-monotonic.h` | Deadline Monotonic algorithm                        |
| `earliest-deadline-first.h` | Earliest Deadline First algorithm                   |
| `least-laxity-first.h` | Least Laxity First algorithm (not working properly) |

>> Note: I used a `Task` class to represent a task. It has the following attributes:
> - `id` : task id
> - `period` : task period
> - `deadline` : task deadline
> - `remaining_time` : remaining time to execute the task
> - `arrival_time` : task arrival time
> - `capacity` : task execution time

>> monotonic-scheduler.h : allow common functions for all algorithms such as:
> - `checkSchedulability` : check if the tasks are schedulable or not
> - `findEarliestAvailableTimeSlot` : find the earliest available time slot



## Algorithms

- [x] Rate Monothonic
- [x] Deadline Monotonic
- [x] Earliest Deadline First
- [] Least Laxity First : code is not working :/

PS: I wasn't able to implement LLF for now. I will try to fix it later.



<!-- MARKDOWN LINKS & IMAGES -->
[langue-shield]: https://img.shields.io/badge/Language-C++-lightblue.svg?style=for-the-badge&logo=c%2B%2B
[issues-url]: https://github.com/PhantHive/scheduling-tasks/issues/
[issues-shield]: https://img.shields.io/github/issues/PhantHive/scheduling-tasks?style=for-the-badge

