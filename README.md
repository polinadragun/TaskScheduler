# Task Scheduler

## Overview

The Task Scheduler project implements a `TaskScheduler` class to manage and execute interdependent tasks efficiently. Each task can depend on other tasks’ results, forming a Directed Acyclic Graph (DAG) where nodes represent individual tasks, and edges represent dependencies between them. This system ensures optimized calculations by reusing intermediate results and enabling efficient, ordered task execution.

An example use case is solving a quadratic equation with two roots, where calculating the discriminant once is sufficient for both root calculations. This design minimizes redundant computations and guarantees that tasks execute in the correct order, as determined by dependencies.

## Key Components

### `TaskScheduler` Class
The `TaskScheduler` class provides an intuitive API for defining, managing, and executing tasks. It supports tasks with no arguments, a single argument, or two arguments, and it organizes tasks based on their interdependencies. Core features include:
- **Adding Callable Objects**: Tasks are added with zero, one, or two parameters and are stored as instances of `Node`. Each task can be any callable object, including functions, lambdas, or functors, allowing flexibility in task definition.
- **Dependency Management**: Dependencies between tasks are specified upon addition, automatically creating a DAG structure that ensures dependent tasks wait for the completion of their prerequisite tasks.
- **Topological Sorting for Execution Order**: A topological sort of the DAG determines the execution order, preventing cyclic dependencies and ensuring tasks execute only after all dependencies are satisfied.
- **Task Execution and Results Storage**: Tasks are executed in sorted order, with results stored and accessible via unique task identifiers.

### `Node` Class
The `Node` class encapsulates each task and its dependencies, storing the callable object, arguments, and results:
- **Task Storage**: Using the `FuncStorage` class, `Node` stores the task in a flexible way that supports various types and numbers of arguments.
- **Result Management**: After execution, each task’s result is stored as an `any` type, enabling generic storage and retrieval of results without type constraints.

### `FuncStorage` Class
`FuncStorage` is a type-erased wrapper for callable objects (e.g., functions, lambdas, or functors) and supports tasks with varying arguments:
- **Type-Erasured Callable Storage**: By storing tasks polymorphically, `FuncStorage` enables dynamic invocation of any callable object with zero, one, or two arguments.
- **Flexible Invocation**: The polymorphic design abstracts over specific callable types, storing any callable object while handling its invocation and result storage, all within a unified interface.

### `any` Class
The `any` class provides type-erased storage for task results, allowing tasks to return results of any type:
- **Type-Erased Container**: `any` can store and retrieve any type of result, ensuring that the `TaskScheduler` can handle diverse return types across tasks.
- **Dynamic Typing Support**: The class achieves type-erased storage using an abstract base (`base_val`) and template-based subclasses (`val<T>`) to store, clone, and retrieve the stored value.

### Callable Object Flexibility
The `TaskScheduler` is designed to handle any callable object, including:
- **Functions**: Supports regular functions that perform predefined operations.
- **Lambdas and Functors**: Supports lambdas and functor classes, providing the flexibility to create inline or reusable functions with state.
- **Flexible Arguments**: Each callable can accept zero, one, or two arguments, making the system adaptable to various computational requirements.

## Example Usage

```cpp
#include "task_scheduler.hpp"
#include <iostream>

int main() {
    // Initialize TaskScheduler instance
    TaskScheduler scheduler;

    // Define a lambda function for addition
    auto add_lambda = [](int x, int y) { return x + y; };

    // Add tasks to the scheduler
    // Task 1: Adds 8 and 5
    auto task1_id = scheduler.add(add_lambda, 8, 5);

    // Task 2: Adds 3 and the result of Task 1
    auto task2_id = scheduler.add([](int x, int y) { return x + y; }, 3, scheduler.getFutureResult<int>(task1_id));

    // Task 3: Adds 1 and 3 (independent task)
    auto task3_id = scheduler.add(add_lambda, 1, 3);

    // Execute all tasks in the scheduler
    scheduler.executeAll();

    // Retrieve the result of Task 3
    int result_task3 = scheduler.getResult<int>(task3_id);
    std::cout << "Result of Task 3 (1 + 3): " << result_task3 << std::endl;

    return 0;
}
```
