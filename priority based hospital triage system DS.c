#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define structure for patient node
typedef struct Patient {
 int id;
 char name[50];
 int priority; // 1: High, 2: Medium, 3: Low
 struct Patient *next;
} Patient;
// Define structure for queue
typedef struct {
 Patient *front;
 Patient *rear;
} Queue;
// Function to create a new patient node
Patient *createPatient(int id, char name[], int priority) {
 Patient *newPatient = (Patient *)malloc(sizeof(Patient));
 if (newPatient != NULL) {
 newPatient->id = id;
 strcpy(newPatient->name, name);
 newPatient->priority = priority;
 newPatient->next = NULL;
}
 return newPatient;
}
// Function to create a new queue
Queue *createQueue() {
 Queue *newQueue = (Queue *)malloc(sizeof(Queue));
 if (newQueue != NULL) {
 newQueue->front = NULL;
 newQueue->rear = NULL;
 }
 return newQueue;
}
// Function to insert a patient into the queue based on priority
void enqueue(Queue *queue, int id, char name[], int priority) {
 Patient *newPatient = createPatient(id, name, priority);
 if (queue->front == NULL) {
 queue->front = queue->rear = newPatient;
 } else {
 Patient *temp = queue->front;
 Patient *prev = NULL;
 while (temp != NULL && temp->priority <= priority) {
 prev = temp;
 temp = temp->next;
 }
 if (prev == NULL) {
 newPatient->next = queue->front;
 queue->front = newPatient;
} else {
 prev->next = newPatient;
 newPatient->next = temp;
 if (temp == NULL) {
 queue->rear = newPatient;
 }
 }
 }
}
// Function to remove and return the highest priority patient from the queue
Patient *dequeue(Queue *queue) {
 Patient *removedPatient;
 if (queue->front != NULL) {
 removedPatient = queue->front;
 if (queue->front == queue->rear) {
 queue->front = queue->rear = NULL;
 } else {
 queue->front = queue->front->next;
 }
 free(removedPatient);
 }
 return removedPatient;
}
// Function to display the patients in the queue
void displayQueue(Queue *queue) {
 if (queue->front == NULL) {
 printf("Queue is empty.\n");
} else {
 printf("Patients in the queue:\n");
 Patient *temp = queue->front;
 while (temp != NULL) {
 printf("ID: %d, Name: %s, Priority: %d\n", temp->id, temp->name, 
temp->priority);
 temp = temp->next;
 }
 }
}
// Function to add a patient
void addPatient(Queue *queue) {
 int id;
 char name[50];
 int priority;
 printf("Enter patient ID: ");
 scanf("%d", &id);
 printf("Enter patient name: ");
 scanf("%s", name);
 printf("Enter patient priority (1: High, 2: Medium, 3: Low): ");
 scanf("%d", &priority);
 enqueue(queue, id, name, priority);
}
// Function to search for a patient
void searchPatient(Queue *queue) {
int id;
 printf("Enter patient ID to search: ");
 scanf("%d", &id);
 Patient *temp = queue->front;
 while (temp != NULL) {
 if (temp->id == id) {
 printf("ID: %d, Name: %s, Priority: %d\n", temp->id, temp->name, 
temp->priority);
 return;
 }
 temp = temp->next;
 }
 printf("Patient not found.\n");
}
// Function to delete a patient
void deletePatient(Queue *queue) {
 int id;
 printf("Enter patient ID to delete: ");
 scanf("%d", &id);
 Patient *prev = NULL;
 Patient *temp = queue->front;
 while (temp != NULL && temp->id != id) {
prev = temp;
 temp = temp->next;
 }
 if (temp == NULL) {
 printf("Patient not found.\n");
 return;
 }
 if (prev == NULL) {
 queue->front = temp->next;
 if (queue->front == NULL) {
 queue->rear = NULL;
 }
 } else {
 prev->next = temp->next;
 if (temp == queue->rear) {
 queue->rear = prev;
 }
 }
 free(temp);
}
int main() {
 Queue *queue = createQueue();
 int choice;
do {
 printf("Hospital Triage System\n");
 printf("1. Add New Patient\n");
 printf("2. Search Patient\n");
 printf("3. Delete Patient\n");
 printf("4. Display Patients\n");
 printf("5. Exit\n");
 scanf("%d", &choice);
 switch (choice) {
 case 1:
 addPatient(queue);
 break;
 case 2:
 searchPatient(queue);
 break;
 case 3:
 deletePatient(queue);
 break;
 case 4:
 displayQueue(queue);
 break;
 case 5:
 break;
 default:
 printf("Invalid choice.\n");
 break;
 }
 } while (choice != 5);
return 0;
}