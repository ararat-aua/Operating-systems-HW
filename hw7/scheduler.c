#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

struct ProcessLinkedNode {
    struct Process process;
    struct ProcessLinkedNode* next;
};

int max(int a, int b){
    return a > b ? a : b;
}

void print_gatt_chart(int n, struct ProcessLinkedNode* head, char* scheduler_name) {
    struct ProcessLinkedNode* current = head;
    printf("\n\n=== %s ===\n", scheduler_name);
    printf("Gantt Chart:  |");
    while (current != NULL){
        printf("  P%d  |", current->process.pid);
        current = current->next;
    }
    printf("\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    current = head;
    while (current != NULL){
        printf("%d\t", current->process.pid);
        printf("%d\t", current->process.arrival_time);
        printf("%d\t", current->process.burst_time);
        printf("%d\t", current->process.waiting_time);
        printf("%d\t", current->process.turnaround_time);
        printf("%d\t", current->process.response_time);
        printf("\n");
        current = current->next;
    }
    printf("\n\n");
}

void calculate_metrics(int n, struct ProcessLinkedNode* head) {
    int total_time = 0;
    while (head != NULL) {
        head->process.waiting_time = max(0, total_time - head->process.arrival_time);
        head->process.turnaround_time = head->process.waiting_time + head->process.burst_time;
        head->process.response_time = head->process.waiting_time;
        total_time += head->process.burst_time;
        head = head->next;
    }
}

void fcfs_scheduler(int n, struct Process* processes) {
    struct ProcessLinkedNode* head = NULL;
    struct ProcessLinkedNode* current = NULL;
    struct Process process;
    float avg_wt = 0;
    float avg_tat = 0;
    float avg_rt = 0;

    for (int i = 0; i < n; i++){
        struct ProcessLinkedNode* new_node = (struct ProcessLinkedNode*)malloc(sizeof(struct ProcessLinkedNode));
        process = processes[i];
        new_node->process = process;
        new_node->next = NULL;
        if (head == NULL){
            head = new_node;
            continue;
        }
        if (head->process.arrival_time > process.arrival_time){
            new_node->next = head;
            head = new_node;
            continue;
        }
        current = head;
        while (current->next != NULL){
            if (current->next->process.arrival_time > process.arrival_time){
                new_node->next = current->next;
                current->next = new_node;
                break;
            }
            current = current->next;
        }
        if (current->next == NULL){
            current->next = new_node;
        }
    }
    calculate_metrics(n, head);
    print_gatt_chart(n, head, "First Come First Serve (FCFS)");
    while (head != NULL){
        avg_wt += head->process.waiting_time;
        avg_tat += head->process.turnaround_time;
        avg_rt += head->process.response_time;
        head = head->next;
    }
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    printf("Average Waiting Time: %f\n", avg_wt);
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("Average Response Time: %f\n", avg_rt);
}


struct ProcessLinkedNode* remove_node(struct ProcessLinkedNode* head, struct ProcessLinkedNode* node) {
    if (head == node){
        head = node->next;
        return head;
    }
    struct ProcessLinkedNode* current = head;
    while (current->next != NULL){
        if (current->next == node){
            current->next = node->next;
            return head;
        }
        current = current->next;
    }
    return head;
}

struct ProcessLinkedNode* create_linked_list(int n, struct Process* processes) {
    struct ProcessLinkedNode* head = NULL;
    struct ProcessLinkedNode* current = NULL;
    struct Process process;
    for (int i = 0; i < n; i++){
        struct ProcessLinkedNode* new_node = (struct ProcessLinkedNode*)malloc(sizeof(struct ProcessLinkedNode));
        new_node->process = processes[i];
        new_node->next = NULL;
        if(head == NULL){
            head = new_node;
            current = head;
        }
        else{
            current->next = new_node;
            current = current->next;
        }
    }
    return head;
}

void sjf_scheduler(int n, struct Process* processes) {
    struct ProcessLinkedNode* head = create_linked_list(n, processes);
    // print_gatt_chart(n, head, "Shortest Job First (SJF) - Before");
    // return;
    struct ProcessLinkedNode* gantt_chart_head = NULL;
    struct ProcessLinkedNode* gantt_chart_current = NULL;
    float avg_wt = 0;
    float avg_tat = 0;
    float avg_rt = 0;

    int total_burst_time = 0;
    while (head != NULL){
        int min_burst_time = -1;
        int min_arrival_time = -1;
        struct ProcessLinkedNode* min_node = NULL;
        struct ProcessLinkedNode* current = head;
        while (current != NULL){
            if (current->process.arrival_time <= total_burst_time){
                if (
                    min_burst_time == -1 || 
                    current->process.burst_time < min_burst_time || 
                    (
                        current->process.burst_time == min_burst_time 
                        &&
                        current->process.arrival_time < min_arrival_time
                    )
                ){
                    min_burst_time = current->process.burst_time;
                    min_arrival_time = current->process.arrival_time;
                    min_node = current;
                }
            }
            current = current->next;
        }
        if (min_node == NULL){
            total_burst_time++;
            continue;
        }
        head = remove_node(head, min_node);
        total_burst_time += min_burst_time;
        if (gantt_chart_head == NULL){
            gantt_chart_head = min_node;
            gantt_chart_current = gantt_chart_head;
        }
        else{
            gantt_chart_current->next = min_node;
            gantt_chart_current = gantt_chart_current->next;
        }
    }

    calculate_metrics(n, gantt_chart_head);
    print_gatt_chart(n, gantt_chart_head, "Shortest Job First (SJF)");
    
    while (gantt_chart_head != NULL){
        avg_wt += gantt_chart_head->process.waiting_time;
        avg_tat += gantt_chart_head->process.turnaround_time;
        avg_rt += gantt_chart_head->process.response_time;
        gantt_chart_head = gantt_chart_head->next;
    }
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    printf("Average Waiting Time: %f\n", avg_wt);
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("Average Response Time: %f\n\n", avg_rt);
}

int main() {
    int n;
    struct Process tmp_process;
    struct Process* raw_input_processes = NULL;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    raw_input_processes = (struct Process*)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &raw_input_processes[i].arrival_time, &raw_input_processes[i].burst_time);
        raw_input_processes[i].pid = i+1;
    }

    fcfs_scheduler(n, raw_input_processes);
    sjf_scheduler(n, raw_input_processes);
    return 0;
}