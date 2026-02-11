# Dining Philosophers Problem

A comprehensive implementation of the classic dining philosophers synchronization problem, developed as part of the 42 School curriculum. This project demonstrates mastery of concurrent programming, thread synchronization, mutex management, and process coordination using both threads and processes.

## Project Overview

The dining philosophers problem is a classical computer science challenge that illustrates synchronization issues in concurrent algorithm design and resource allocation. The problem models philosophers sitting at a round table who alternate between thinking and eating, requiring two forks to eat but having only one fork between each pair of adjacent philosophers.

This implementation provides two distinct solutions: a threaded approach using mutexes and a process-based approach using semaphores, each addressing the challenge differently while preventing deadlock, starvation, and race conditions.

## Repository Structure

```
dining-philosophers/
├── philo/              Mandatory: Thread-based implementation
│   ├── SRCS/          Source files
│   ├── headers/       Header files
│   └── Makefile       Build configuration
└── philo_bonus/       Bonus: Process-based implementation
    ├── SRCS/          Source files
    ├── headers/       Header files
    └── Makefile       Build configuration
```

## Technical Specifications

### Mandatory Part (philo)

**Implementation Details:**
- Programming Language: C
- Concurrency Model: POSIX threads (pthread)
- Synchronization: Mutexes
- Compilation Flags: `-Wall -Wextra -Werror`
- External Functions: `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`, `usleep`, `gettimeofday`

**Architecture:**
- Each philosopher is represented as a separate thread
- Each fork is protected by a dedicated mutex
- Shared state includes simulation start time and death flags
- Thread-safe printing ensures ordered output
- Monitoring thread checks for philosopher deaths

### Bonus Part (philo_bonus)

**Implementation Details:**
- Programming Language: C
- Concurrency Model: Processes
- Synchronization: POSIX semaphores
- Additional Functions: `fork`, `kill`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

**Architecture:**
- Each philosopher is represented as a separate process
- Forks are represented using semaphores
- Inter-process communication for death detection
- Process termination propagates to all philosophers
- Semaphore-based resource management

## Problem Description

### Rules and Constraints

1. **Table Configuration**: N philosophers sit at a round table with N forks
2. **Eating Requirements**: A philosopher needs two forks (left and right) to eat
3. **Actions**: Philosophers can eat, think, or sleep
4. **Communication**: Philosophers do not communicate with each other
5. **Resource Limitation**: Only one fork exists between each pair of philosophers

### Death Conditions

A philosopher dies if:
- They do not start eating within `time_to_die` milliseconds of their last meal
- `time_to_die` milliseconds have passed since the simulation began without eating

### Program Arguments

```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

**Parameters:**
- `number_of_philosophers`: Number of philosophers and forks (1-200 optimal)
- `time_to_die`: Time in milliseconds before a philosopher dies without eating
- `time_to_eat`: Time in milliseconds a philosopher spends eating
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: Optional; simulation ends when all philosophers have eaten this many times

**Example Usage:**
```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
./philo 4 310 200 100  # Should die
```

## Implementation Details

### Thread-Based Solution (philo)

**Core Components:**

1. **Philosopher Thread Function**
   - Implements the philosopher lifecycle
   - Handles fork acquisition with deadlock prevention
   - Manages eating, sleeping, and thinking states
   - Updates meal counter and last meal timestamp

2. **Mutex Management**
   - Fork mutexes prevent simultaneous access
   - Print mutex ensures ordered console output
   - Death flag mutex protects simulation state
   - Proper initialization and destruction

3. **Death Monitoring**
   - Dedicated monitoring thread
   - Periodic checks of philosopher states
   - Timestamp comparison for starvation detection
   - Simulation termination on death

4. **Time Management**
   - High-precision timing using `gettimeofday`
   - Custom sleep function for accurate delays
   - Timestamp tracking for each action
   - Microsecond-level precision

**Deadlock Prevention:**
- Philosophers acquire forks in a consistent order
- Odd-numbered philosophers acquire left fork first
- Even-numbered philosophers acquire right fork first
- Prevents circular wait condition

### Process-Based Solution (philo_bonus)

**Core Components:**

1. **Process Creation**
   - Fork creates child process for each philosopher
   - Independent memory space per philosopher
   - Parent process coordinates simulation
   - Process synchronization via semaphores

2. **Semaphore Synchronization**
   - Named semaphores for inter-process communication
   - Fork semaphore limits concurrent eaters
   - Print semaphore serializes output
   - Cleanup on termination

3. **Process Monitoring**
   - Parent process monitors child processes
   - Death detection triggers global termination
   - Signal handling for graceful shutdown
   - Resource cleanup across processes

4. **Inter-Process Communication**
   - Shared semaphores for state coordination
   - Process termination signals
   - Synchronized output across processes

## Key Algorithms

### Fork Acquisition Strategy

**Thread Implementation:**
```
if (philosopher_id is even):
    lock(right_fork)
    lock(left_fork)
else:
    lock(left_fork)
    lock(right_fork)

eat()

unlock(left_fork)
unlock(right_fork)
```

**Benefits:**
- Breaks circular wait condition
- Prevents deadlock in all scenarios
- Maintains fairness across philosophers
- Minimal performance overhead

### Death Detection Algorithm

```
for each philosopher:
    current_time = get_current_time()
    time_since_last_meal = current_time - philosopher.last_meal_time
    
    if time_since_last_meal >= time_to_die:
        print_death_message(philosopher)
        terminate_simulation()
        break
```

**Characteristics:**
- Constant time complexity O(1) per philosopher check
- Periodic execution by monitoring thread/process
- Immediate termination on detection
- Thread-safe state access

## Synchronization Challenges

### Race Conditions Addressed

1. **Fork Access**: Mutexes/semaphores ensure exclusive access
2. **Output Ordering**: Dedicated print protection prevents interleaving
3. **Death Detection**: Atomic checks prevent missed deaths
4. **State Updates**: Protected writes to shared variables

### Avoiding Deadlock

**Conditions Prevented:**
- **Mutual Exclusion**: Maintained through proper locking
- **Hold and Wait**: Limited through acquisition ordering
- **No Preemption**: Not applicable in this design
- **Circular Wait**: Broken through asymmetric fork acquisition

### Starvation Prevention

- Fair scheduling through OS thread scheduler
- Equal opportunity for fork acquisition
- No priority inversion
- Bounded waiting time

## Performance Considerations

### Timing Accuracy

- `usleep` alternative for better precision
- Busy-wait loops avoided for efficiency
- Timestamp granularity: microseconds
- Compensation for system call overhead

### Resource Management

- Minimal memory allocation
- Efficient mutex/semaphore usage
- Proper cleanup on termination
- No memory leaks under any scenario

### Scalability

- Tested with 1-200 philosophers
- Linear memory growth with philosopher count
- Constant time death detection
- Bounded by system thread/process limits

## Testing Strategies

### Basic Functionality Tests

```bash
./philo 1 800 200 200      # Single philosopher should die
./philo 5 800 200 200      # Normal operation, no deaths
./philo 4 410 200 200      # Edge case for timing
./philo 4 310 200 100      # Should result in death
```

### Stress Tests

```bash
./philo 200 800 200 200    # Maximum philosophers
./philo 5 800 200 200 7    # With meal limit
./philo 2 800 200 200      # Minimum philosophers
```

### Edge Cases

- Zero time_to_die (immediate death)
- Very large philosopher counts
- Minimal timing values
- Single philosopher scenario
- Equal time values for all actions

### Validation Criteria

1. **No Data Races**: Verified with thread sanitizer
2. **No Deadlocks**: Extended runtime tests
3. **Accurate Timing**: Death occurs within 10ms of expected time
4. **Proper Output**: All state changes logged correctly
5. **Clean Termination**: All resources freed properly

## Compilation and Execution

### Building the Projects

**Mandatory (Thread-based):**
```bash
cd philo
make        # Compile the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

**Bonus (Process-based):**
```bash
cd philo_bonus
make        # Compile the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

### Running the Simulations

**Basic Execution:**
```bash
./philo 5 800 200 200
./philo_bonus 5 800 200 200
```

**With Meal Limit:**
```bash
./philo 5 800 200 200 7
./philo_bonus 5 800 200 200 7
```

### Expected Output Format

```
[timestamp_in_ms] [philosopher_id] has taken a fork
[timestamp_in_ms] [philosopher_id] is eating
[timestamp_in_ms] [philosopher_id] is sleeping
[timestamp_in_ms] [philosopher_id] is thinking
[timestamp_in_ms] [philosopher_id] died
```

**Example:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## Learning Objectives

This project develops proficiency in:

1. **Concurrent Programming**: Thread and process management
2. **Synchronization Primitives**: Mutexes, semaphores, and their proper usage
3. **Race Condition Prevention**: Critical section protection
4. **Deadlock Avoidance**: Resource ordering and acquisition strategies
5. **Real-Time Constraints**: Precise timing and deadline management
6. **Resource Management**: Proper allocation and cleanup
7. **Inter-Process Communication**: Process coordination techniques
8. **Debugging Concurrent Systems**: Race detection and timing issues

## Common Pitfalls and Solutions

### Pitfall 1: Data Races in Death Checking

**Problem**: Unsynchronized access to last_meal_time
**Solution**: Protect reads and writes with mutex

### Pitfall 2: Delayed Death Detection

**Problem**: Philosopher dies but detection is late
**Solution**: Reduce monitoring interval, optimize checks

### Pitfall 3: Inconsistent Timestamps

**Problem**: Using different time sources
**Solution**: Single time reference, consistent calculation

### Pitfall 4: Memory Leaks on Early Termination

**Problem**: Resources not freed when philosopher dies
**Solution**: Proper cleanup in all exit paths

### Pitfall 5: Printf Interleaving

**Problem**: Output messages get mixed
**Solution**: Protected print function with mutex/semaphore

## Advanced Optimizations

### Timing Precision

- Custom sleep function avoiding usleep inaccuracies
- Busy-wait for final microseconds
- Timestamp caching to reduce system calls

### Memory Efficiency

- Stack allocation where possible
- Minimal heap usage
- Proper alignment for cache performance

### Monitoring Optimization

- Adaptive check intervals
- Early termination on full meal count
- Batch state checks

## Additional Notes

This implementation emphasizes correctness and educational value over extreme optimization. The code demonstrates fundamental concurrent programming concepts applicable to real-world systems including databases, operating systems, and distributed applications.

Both implementations are designed to handle edge cases gracefully, provide clear error messages, and terminate cleanly under all circumstances. The project serves as a foundation for understanding more complex synchronization challenges in modern software systems.

## Requirements

- **Operating System**: Linux or macOS
- **Compiler**: GCC or Clang with C99 support
- **Libraries**: POSIX threads (pthread), POSIX semaphores
- **Tools**: Make for building

## Debugging Tools

**Recommended for development:**
- **Valgrind**: Memory leak detection
- **Helgrind**: Thread error detector
- **GDB**: Step-through debugging
- **Address Sanitizer**: Runtime error detection

**Example:**
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
gcc -fsanitize=thread -g SRCS/*.c -o philo
```

## Acknowledgments

Developed as part of the 42 Network curriculum, this project teaches essential skills in concurrent programming and system-level thinking. The dining philosophers problem remains a cornerstone of computer science education, illustrating fundamental concepts that appear throughout distributed systems, operating system design, and parallel computing.
