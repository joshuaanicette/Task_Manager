#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

// Structure to store a task
typedef struct {
    char description[MAX_LENGTH];
    int is_Completed;
    int day, month, year;  // Due date
    int hour, minute;      // Due time
} Task;

// Function prototypes
void addTask(Task tasks[], int *taskCount);
void viewTasks(const Task tasks[], int taskCount);
void markTaskCompleted(Task tasks[], int taskCount);
void deleteCompletedTasks(Task tasks[], int *taskCount);
void viewTasksByDate(const Task tasks[], int taskCount);
void sortTasksByDueDateAndTime(Task tasks[], int taskCount);
void saveToFile(const Task tasks[], int taskCount, const char *filename);
void loadFromFile(Task tasks[], int *taskCount, const char *filename);
int isOverdue(int day, int month, int year, int hour, int minute);

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    char filename[] = "todo_list.txt";

    // Load tasks from file
    loadFromFile(tasks, &taskCount, filename);

    int choice;
    while (1) {
        // Display menu
        printf("\n--- To-Do List Manager ---\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks (Sorted by Due Date & Time)\n");
        printf("3. View Tasks by Date\n");
        printf("4. Mark Task as Completed\n");
        printf("5. Delete Completed Tasks\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                sortTasksByDueDateAndTime(tasks, taskCount);
                viewTasks(tasks, taskCount);
                break;
            case 3:
                viewTasksByDate(tasks, taskCount);
                break;
            case 4:
                markTaskCompleted(tasks, taskCount);
                break;
            case 5:
                deleteCompletedTasks(tasks, &taskCount);
                break;
            case 6:
                saveToFile(tasks, taskCount, filename);
                printf("Tasks saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to check if a date and time is overdue
int isOverdue(int day, int month, int year, int hour, int minute) {
    time_t now = time(NULL);
    struct tm today;
    localtime_r(&today, &now);

    if (year < today.tm_year + 1900 ||
        (year == today.tm_year + 1900 && month < today.tm_mon + 1) ||
        (year == today.tm_year + 1900 && month == today.tm_mon + 1 && day < today.tm_mday) ||
        (year == today.tm_year + 1900 && month == today.tm_mon + 1 && day == today.tm_mday && hour < today.tm_hour) ||
        (year == today.tm_year + 1900 && month == today.tm_mon + 1 && day == today.tm_mday && hour == today.tm_hour && minute < today.tm_min)) {
        return 1;
    }
    return 0;
}

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    Task *task = &tasks[*taskCount];
    printf("Enter task description: ");
    getchar(); // Clear buffer
    fgets(task->description, MAX_LENGTH, stdin);
    task->description[strcspn(task->description, "\n")] = '\0'; // Remove newline

    printf("Enter due date (DD MM YYYY): ");
    scanf("%d %d %d", &task->day, &task->month, &task->year);

    printf("Enter due time (HH MM): ");
    scanf("%d %d", &task->hour, &task->minute);

    task->is_Completed = 0;
    (*taskCount)++;
}

void viewTasks(const Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks found.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        printf("Task %d:\n", i + 1);
        printf("Description: %s\n", tasks[i].description);
        printf("Due Date: %02d/%02d/%04d\n", tasks[i].day, tasks[i].month, tasks[i].year);
        printf("Due Time: %02d:%02d\n", tasks[i].hour, tasks[i].minute);
        printf("Status: %s\n", tasks[i].is_Completed ? "Completed" : "Pending");
        printf("Overdue: %s\n", isOverdue(tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].hour, tasks[i].minute) ? "Yes" : "No");
        printf("\n");
    }
}

void markTaskCompleted(Task tasks[], int taskCount) {
    int taskNumber;
    printf("Enter the task number to mark as completed: ");
    scanf("%d", &taskNumber);

    if (taskNumber < 1 || taskNumber > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    tasks[taskNumber - 1].is_Completed = 1;
    printf("Task %d marked as completed.\n", taskNumber);
}

void deleteCompletedTasks(Task tasks[], int *taskCount) {
    int i = 0;
    while (i < *taskCount) {
        if (tasks[i].is_Completed) {
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*taskCount)--;
        } else {
            i++;
        }
    }
    printf("Completed tasks deleted.\n");
}

void viewTasksByDate(const Task tasks[], int taskCount) {
    int day, month, year;
    printf("Enter the date (DD MM YYYY) to view tasks: ");
    scanf("%d %d %d", &day, &month, &year);

    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].day == day && tasks[i].month == month && tasks[i].year == year) {
            printf("Task %d:\n", i + 1);
            printf("Description: %s\n", tasks[i].description);
            printf("Due Time: %02d:%02d\n", tasks[i].hour, tasks[i].minute);
            printf("Status: %s\n", tasks[i].is_Completed ? "Completed" : "Pending");
            printf("Overdue: %s\n", isOverdue(tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].hour, tasks[i].minute) ? "Yes" : "No");
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No tasks found for the specified date.\n");
    }
}

void sortTasksByDueDateAndTime(Task tasks[], int taskCount) {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].year > tasks[j + 1].year ||
                (tasks[j].year == tasks[j + 1].year && tasks[j].month > tasks[j + 1].month) ||
                (tasks[j].year == tasks[j + 1].year && tasks[j].month == tasks[j + 1].month && tasks[j].day > tasks[j + 1].day) ||
                (tasks[j].year == tasks[j + 1].year && tasks[j].month == tasks[j + 1].month && tasks[j].day == tasks[j + 1].day && tasks[j].hour > tasks[j + 1].hour) ||
                (tasks[j].year == tasks[j + 1].year && tasks[j].month == tasks[j + 1].month && tasks[j].day == tasks[j + 1].day && tasks[j].hour == tasks[j + 1].hour && tasks[j].minute > tasks[j + 1].minute)) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void saveToFile(const Task tasks[], int taskCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n%d %d %d\n%d %d\n%d\n", tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].hour, tasks[i].minute, tasks[i].is_Completed);
    }

    fclose(file);
}

void loadFromFile(Task tasks[], int *taskCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing task file found. Starting with an empty list.\n");
        return;
    }

    *taskCount = 0;
    while (fgets(tasks[*taskCount].description, MAX_LENGTH, file) != NULL) {
        tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0';
        fscanf(file, "%d %d %d\n%d %d\n%d\n", &tasks[*taskCount].day, &tasks[*taskCount].month, &tasks[*taskCount].year, &tasks[*taskCount].hour, &tasks[*taskCount].minute, &tasks[*taskCount].is_Completed);
        (*taskCount)++;
    }

    fclose(file);
}