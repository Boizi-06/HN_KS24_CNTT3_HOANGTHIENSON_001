#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Task {
    int id;
    char title[100];
    int priority;
    char deadline[20];
} Task;


typedef struct TaskNode {
    Task task;
    struct TaskNode* next;
} TaskNode;


typedef struct HistoryNode {
    Task task;
    struct HistoryNode* prev;
    struct HistoryNode* next;
} HistoryNode;


typedef struct TaskManager {
    TaskNode* activeTasks;
    HistoryNode* completedTasks;
    int nextId;
} TaskManager;


void initTaskManager(TaskManager* manager) {
    manager->activeTasks = NULL;
    manager->completedTasks = NULL;
    manager->nextId = 1;
}


Task createTask(int id, const char* title, int priority, const char* deadline) {
    Task task;
    task.id = id;
    strncpy(task.title, title, sizeof(task.title) - 1);
    task.title[sizeof(task.title) - 1] = '\0';
    task.priority = priority;
    strncpy(task.deadline, deadline, sizeof(task.deadline) - 1);
    task.deadline[sizeof(task.deadline) - 1] = '\0';
    return task;
}


void addTask(TaskManager* manager) {
    char title[100], deadline[20];
    int priority;
    printf("nhap tieu de: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("nhap tu tu uu tine: ");
    scanf("%d", &priority);
    printf("nhap deadline: ");
    getchar();
    fgets(deadline, sizeof(deadline), stdin);
    deadline[strcspn(deadline, "\n")] = '\0';

    Task task = createTask(manager->nextId++, title, priority, deadline);

    TaskNode* newNode = (TaskNode*)malloc(sizeof(TaskNode));
    newNode->task = task;
    newNode->next = manager->activeTasks;
    manager->activeTasks = newNode;

    printf("them thanh cong!\n");
}


void displayTasks(TaskManager* manager) {
    if (manager->activeTasks == NULL) {
        printf("dsach rong.\n");
        return;
    }
    printf("\n ListTask:\n");
    printf("ID | Title | Priority | Deadline\n");
    printf("--------------------------------\n");
    TaskNode* current = manager->activeTasks;
    while (current != NULL) {
        printf("%d | %s | %d | %s\n",
               current->task.id, current->task.title,
               current->task.priority, current->task.deadline);
        current = current->next;
    }
}


void deleteTask(TaskManager* manager) {
    int id;
    printf("nhap id can xoa: ");
    scanf("%d", &id);

    TaskNode* current = manager->activeTasks;
    TaskNode* prev = NULL;

    while (current != NULL && current->task.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("ko tim thay.\n");
        return;
    }

    if (prev == NULL) {
        manager->activeTasks = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("xoa thanh cong!\n");
}

// Update task information
void updateTask(TaskManager* manager) {
    int id;
    printf("nhap id task muon cap nhat: ");
    scanf("%d", &id);

    TaskNode* current = manager->activeTasks;
    while (current != NULL && current->task.id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("ko tim thay task.\n");
        return;
    }

    char title[100], deadline[20];
    int priority;
    printf("nhap ten tieu de moi'%s': ", current->task.title);
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    if (strlen(title) > 0) {
        strncpy(current->task.title, title, sizeof(current->task.title) - 1);
        current->task.title[sizeof(current->task.title) - 1] = '\0';
    }

    printf("nhap thu tu uu tien moi %d : ", current->task.priority);
    scanf("%d", &priority);
    if (priority != -1) {
        current->task.priority = priority;
    }

    printf("nhap deadline moi '%s': ", current->task.deadline);
    getchar();
    fgets(deadline, sizeof(deadline), stdin);
    deadline[strcspn(deadline, "\n")] = '\0';
    if (strlen(deadline) > 0) {
        strncpy(current->task.deadline, deadline, sizeof(current->task.deadline) - 1);
        current->task.deadline[sizeof(current->task.deadline) - 1] = '\0';
    }

    printf("cap nhat thanh cong!\n");
}


void markTaskCompleted(TaskManager* manager) {
    int id;
    printf("nhap id task hoan thanh: ");
    scanf("%d", &id);

    TaskNode* current = manager->activeTasks;
    TaskNode* prev = NULL;

    while (current != NULL && current->task.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("ko tim thay.\n");
        return;
    }


    if (prev == NULL) {
        manager->activeTasks = current->next;
    } else {
        prev->next = current->next;
    }


    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    newNode->task = current->task;
    newNode->next = manager->completedTasks;
    newNode->prev = NULL;

    if (manager->completedTasks != NULL) {
        manager->completedTasks->prev = newNode;
    }
    manager->completedTasks = newNode;

    free(current);
    printf("da danh dau task hoan thanh!\n");
}


void sortTasks(TaskManager* manager) {
    if (manager->activeTasks == NULL || manager->activeTasks->next == NULL) {

        return;
    }

    TaskNode* sorted = NULL;
    TaskNode* current = manager->activeTasks;

    while (current != NULL) {
        TaskNode* next = current->next;
        if (sorted == NULL || sorted->task.priority < current->task.priority) {
            current->next = sorted;
            sorted = current;
        } else {
            TaskNode* temp = sorted;
            while (temp->next != NULL && temp->next->task.priority >= current->task.priority) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    manager->activeTasks = sorted;
    printf("xap xep thanh cong \n");
}


void searchTasks(TaskManager* manager) {
    char searchTitle[100];
    printf("nhap tieu de ");
    getchar();
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0';

    TaskNode* current = manager->activeTasks;
    int found = 0;


    printf("ID | Title | Priority | Deadline\n");
    printf("--------------------------------\n");
    while (current != NULL) {
        if (strstr(current->task.title, searchTitle) != NULL) {
            printf("%d | %s | %d | %s\n",
                   current->task.id, current->task.title,
                   current->task.priority, current->task.deadline);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf(" ko tim thay \n" );
    }
}





void freeTaskManager(TaskManager* manager) {

    TaskNode* currentTask = manager->activeTasks;
    while (currentTask != NULL) {
        TaskNode* temp = currentTask;
        currentTask = currentTask->next;
        free(temp);
    }


    HistoryNode* currentHistory = manager->completedTasks;
    while (currentHistory != NULL) {
        HistoryNode* temp = currentHistory;
        currentHistory = currentHistory->next;
        free(temp);
    }
}


void displayMenu() {
    printf("—————————— ORDER MANAGER —————————— \n");
    printf("1.them nhiem vu \n");
    printf("2. hien thi toan bo nhiem vu \n");
    printf("3. Xoa nhiem vu (theo id)\n");
    printf("4. Cap nhat thong tin nhiem vu \n");
    printf("5. Danh dau nhiem vu da hoan thanh\n");
    printf("6. Xap xep nhiem vu theo thu tu uu tien \n");
    printf("7. Tim kiem nhiem vu \n");
    printf("8. Thoat chuong trinh \n");
}

// Main function
int main() {
    TaskManager manager;
    initTaskManager(&manager);
    int choice;

    while (1) {
        displayMenu();
        printf("moi ban nhap lua chon");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&manager);
                break;
            case 2:
                displayTasks(&manager);
                break;
            case 3:
                deleteTask(&manager);
                break;
            case 4:
                updateTask(&manager);
                break;
            case 5:
                markTaskCompleted(&manager);
                break;
            case 6:
                sortTasks(&manager);
                break;
            case 7:
                searchTasks(&manager);
                break;
            case 8:
               printf("out chuong trinh");
                break;
            default:
                printf("moi nhap lai .\n");
        }
    }
    freeTaskManager(&manager);

    return 0;
}