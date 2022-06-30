# Operating System

This repository contains example problems covering Inter Process Communication, Process Management and Deadlocks.

[![Github repo size](https://img.shields.io/github/languages/code-size/adarshjoshy/OS)](https://github.com/adarshjoshy/OS)
[![GitHub top language](https://img.shields.io/github/languages/top/adarshjoshy/OS?color=green)](https://github.com/adarshjoshy/OS)
[![GitHub](https://img.shields.io/github/license/adarshjoshy/OS)](https://github.com/adarshjoshy/OS)

### Pipes [1]
Pipe is a communication medium between two or more related or interrelated processes. It can be either within one process or a communication between the child and the parent processes.
Named pipes are used for unrelated processes communication.

### Shared Memory [1]
Shared memory is a memory shared between two or more processes. 
Each process has its own address space, if any process wants to communicate  from its own address space to other processes,
it can be done using shared memory.

### Message Queues [1]
Messages are stored on the queue until they are processed and deleted.

### Banker's Algorithm [2]
The banker’s algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the 
allocation for predetermined maximum possible amounts of all resources.

### Dining Philosopher’s problem [3]
The dining philosophers problem states that there are 5 philosophers sharing a circular table and they eat and think alternatively. 
There is a bowl of rice for each of the philosophers and 5 chopsticks. A philosopher needs both their right and left chopstick to eat. 
A hungry philosopher may only eat if there are both chopsticks available. Otherwise a philosopher puts down their chopstick and begin thinking again.<br>

The dining philosopher is a classic synchronization problem as it demonstrates a large class of concurrency control problems.

## References
1. https://www.tutorialspoint.com/inter_process_communication/index.htm
2. https://tutorialspoint.dev/computer-science/operating-systems/operating-system-bankers-algorithm
3. https://www.tutorialspoint.com/dining-philosophers-problem-dpp
