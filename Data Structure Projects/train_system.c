#include <stdio.h>
#include <stdlib.h>
struct Compartment {
    int id;
    struct Compartment *next;
};
struct Compartment* createCompartment(int id) {
    struct Compartment* newCompartment = (struct Compartment*) malloc(sizeof(struct Compartment));

    newCompartment->id = id;
    newCompartment->next = NULL;
    return newCompartment;
}
void addCompartmentAtEnd(struct Compartment **head, int id) {
    struct Compartment *newCompartment = createCompartment(id);
    if (*head == NULL) {
        *head = newCompartment;
        return;
    }
    struct Compartment *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newCompartment;
}
void removeCompartmentById(struct Compartment **head, int id) {
    struct Compartment *temp = *head, *prev = NULL;
    
    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Compartment with ID %d removed successfully.\n", id);
        return;
    }
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Compartment with ID %d not found.\n", id);
        return; 
    }
    prev->next = temp->next;
    free(temp);
    printf("Compartment with ID %d removed successfully.\n", id);
}
void swapCompartments(struct Compartment **head, int id1, int id2) {
    if (id1 == id2) {
        printf("IDs are the same, no need to swap.\n");
        return;
    }
    struct Compartment *prevX = NULL, *prevY = NULL, *currX = *head, *currY = *head;
    while (currX && currX->id != id1) {
        prevX = currX;
        currX = currX->next;
    }
    while (currY && currY->id != id2) {
        prevY = currY;
        currY = currY->next;
    }
    if (!currX || !currY) {
        printf("Swap not possible: One or both compartments not found.\n");
        return;
    }
    if (prevX != NULL)
        prevX->next = currY;
    else
        *head = currY;
    if (prevY != NULL)
        prevY->next = currX;
    else
        *head = currX;
    struct Compartment *temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
    printf("Compartments with ID %d and ID %d have been swapped.\n", id1, id2);
}
void displayTrain(struct Compartment *head) {
    if (head == NULL) {
        printf("The train has no compartments.\n");
        return;
    }
    struct Compartment *temp = head;	    
    printf("The existing compartments of the train are:\n");
    while (temp != NULL) {
        printf("[ID: %d] -> ", temp->id);
        temp = temp->next;
    }
    printf("Train Engine\n");
}
void addDefaultCompartments(struct Compartment **train) {
    addCompartmentAtEnd(train, 1301);
    addCompartmentAtEnd(train, 3042);
    addCompartmentAtEnd(train, 7933);
    addCompartmentAtEnd(train, 2048);
    addCompartmentAtEnd(train, 5986);
}
void freeTrain(struct Compartment **head) {
    struct Compartment *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void addMultipleCompartments(struct Compartment **train) {
    int id;
    char choice;
    
    do {
        printf("Enter Compartment ID to add: ");
        scanf("%d", &id);
        addCompartmentAtEnd(train, id);
        printf("Compartment with ID %d added successfully.\n", id);        
        printf("Do you want to add another compartment? (y/n): ");
        scanf(" %c", &choice); 
        printf("\n");
    } while (choice == 'y' || choice == 'Y');
}

void removeMultipleCompartments(struct Compartment **train) {
    int id;
    char choice;
    do {
        printf("Enter Compartment ID to remove: ");
        scanf("%d", &id);
        removeCompartmentById(train, id);
        printf("Do you want to remove another compartment? (y/n): ");
        scanf(" %c", &choice); 
        printf("\n");
    } while (choice == 'y' || choice == 'Y');
}

void swapMultipleCompartments(struct Compartment **train) {
    int id1, id2;
    printf("Enter first compartment ID to swap: ");
    scanf("%d", &id1);
    printf("Enter second compartment ID to swap: ");
    scanf("%d", &id2);
    swapCompartments(train, id1, id2);
}
int main() {
    struct Compartment *train = NULL;
    int choice;
    addDefaultCompartments(&train);
    printf("\nWelcome to Train Compartment Simulation!\n");
    displayTrain(train);
    while (1) {
        printf("\nCompartments Menu\n");
        printf("1. Add Compartments\n");
        printf("2. Remove Compartments\n");
        printf("3. Swap Compartments\n");
        printf("4. Display Train\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addMultipleCompartments(&train); 
                break;

            case 2:
                removeMultipleCompartments(&train); 
                break;

            case 3:
                swapMultipleCompartments(&train); 
                break;

            case 4:
                displayTrain(train); 
                break;

            case 5:
                printf("Exiting........\n");
                freeTrain(&train);
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    }
    return 0;
}
