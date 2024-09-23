#include <iostream>
#include <vector>

using namespace std;

struct Task {
    string description;
    bool isCompleted;

    Task(string desc) {
        description = desc;
        isCompleted = false;
    }
};

void displayMenu() {
    cout << "\n--- To-Do List Manager ---" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

void addTask(vector<Task> &tasks) {
    string taskDescription;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, taskDescription);
    tasks.push_back(Task(taskDescription));
    cout << "Task added!" << endl;
}

void viewTasks(const vector<Task> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    cout << "\n--- To-Do List ---" << endl;
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description
             << " [" << (tasks[i].isCompleted ? "Completed" : "Pending") << "]" << endl;
    }
}

void markTaskCompleted(vector<Task> &tasks) {
    int taskNumber;
    viewTasks(tasks);
    
    if (tasks.empty()) return;

    cout << "\nEnter the task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks[taskNumber - 1].isCompleted = true;
        cout << "Task marked as completed!" << endl;
    } else {
        cout << "Invalid task number!" << endl;
    }
}

void removeTask(vector<Task> &tasks) {
    int taskNumber;
    viewTasks(tasks);
    
    if (tasks.empty()) return;

    cout << "\nEnter the task number to remove: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks.erase(tasks.begin() + (taskNumber - 1));
        cout << "Task removed!" << endl;
    } else {
        cout << "Invalid task number!" << endl;
    }
}

int main() {
    vector<Task> tasks;
    int option;

    do {
        displayMenu();
        cin >> option;

        switch (option) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "Exiting To-Do List Manager." << endl;
                break;
            default:
                cout << "Invalid option! Please try again." << endl;
        }
    } while (option != 5);

    return 0;
}

