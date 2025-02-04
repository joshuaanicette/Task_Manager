# Task_Manager
The To-Do List Manager is a command-line application developed in C that helps users manage their tasks efficiently. It allows users to add, view, mark as completed, and delete tasks. Additionally, it supports saving tasks to a file and loading them back, ensuring task persistence across sessions.

Features
Add Task: Users can input a task description, due date, and due time.
View All Tasks: Displays all tasks sorted by their due date and time, indicating their completion status and whether they are overdue.
View Tasks by Date: Filters and displays tasks that are due on a specific date.
Mark Task as Completed: Allows users to mark tasks as completed, updating their status.
Delete Completed Tasks: Removes tasks that have been marked as completed from the list.
Save and Load Tasks: Tasks can be saved to a file (todo_list.txt) and loaded from it, allowing users to maintain their task list across different sessions.

How It Works
Data Structure
The application uses a Task structure to store information about each task. This structure includes:
description: A string describing the task.
is_Completed: An integer flag indicating whether the task is completed.
day, month, year: Integers representing the due date.
hour, minute: Integers representing the due time.

Main Menu
The application runs in a loop, presenting a menu with options for the user to interact with the task list. The options include adding tasks, viewing tasks, marking tasks as completed, deleting completed tasks, and saving or exiting the application.

Task Management
Tasks are stored in an array, and the application keeps track of the number of tasks using a counter. The maximum number of tasks is defined by the MAX_TASKS constant, set to 100 by default.

Sorting and Viewing
Tasks are automatically sorted by due date and time whenever they are viewed, ensuring that the most urgent tasks are displayed first. This sorting is done using a simple bubble sort algorithm.

File Operations
Tasks can be saved to a file and loaded from it, allowing users to maintain their task list across different sessions. The file operations handle reading and writing task data to a text file.

Overdue Check
The application includes a function to check if a task is overdue based on the current date and time. This helps users prioritize tasks that need immediate attention.
