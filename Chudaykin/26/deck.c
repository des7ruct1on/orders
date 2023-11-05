#include "deck.h"
// Function to initialize the deque
void initializeDeque(Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
    deque->size = 0;
}

// Function to display the contents of the deque
void displayDeque(const Deque* deque) {
    if (deque->size == 0) {
        printf("Дек пуст.\n");
        return;
    }

    printf("Содержимое дека: ");
    for (int i = 0; i < deque->size; ++i) {
        printf("%d ", deque->arr[(deque->front + i) % MAX_SIZE]);
    }
    printf("\n");
}

// Function to get the size of the deque
int getSize(const Deque* deque) {
    return deque->size;
}

// Function to insert an element at the front of the deque
void insertFront(Deque* deque, int value) {
    if ((deque->front - 1 + MAX_SIZE) % MAX_SIZE == deque->rear) {
        printf("Дек полон. Невозможно вставить элемент в начало.\n");
        return;
    }

    if (deque->size == 0) {
        deque->front = deque->rear = 0;
    } else {
        deque->front = (deque->front - 1 + MAX_SIZE) % MAX_SIZE;
    }

    deque->arr[deque->front] = value;
    deque->size++;
}

// Function to insert an element at the rear of the deque
void insertRear(Deque* deque, int value) {
    if ((deque->rear + 1) % MAX_SIZE == deque->front) {
        printf("Дек полон. Невозможно вставить элемент в конец.\n");
        return;
    }

    if (deque->size == 0) {
        deque->front = deque->rear = 0;
    } else {
        deque->rear = (deque->rear + 1) % MAX_SIZE;
    }

    deque->arr[deque->rear] = value;
    deque->size++;
}

// Function to delete an element from the front of the deque
void deleteFront(Deque* deque) {
    if (deque->size == 0) {
        printf("Дек пуст. Невозможно удалить элемент из начала.\n");
        return;
    }

    if (deque->size == 1) {
        initializeDeque(deque);
    } else {
        deque->front = (deque->front + 1) % MAX_SIZE;
    }

    deque->size--;
}

// Function to delete an element from the rear of the deque
void deleteRear(Deque* deque) {
    if (deque->size == 0) {
        printf("Дек пуст. Невозможно удалить элемент из конца.\n");
        return;
    }

    if (deque->size == 1) {
        initializeDeque(deque);
    } else {
        deque->rear = (deque->rear - 1 + MAX_SIZE) % MAX_SIZE;
    }

    deque->size--;
}

// Function to clear the deque
void clearDeque(Deque* deque) {
    initializeDeque(deque);
}