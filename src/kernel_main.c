char glbl[128];  

// Linked list structure
struct list_element {
    struct list_element *next;
    int data;  // Example data
};

//system timer definition with timer address
#define TIMER_COUNT_REGISTER 0xFE003004

// get current system count in microseconds
unsigned long get_timer_count() {
    return*(volatile unsigned long *)TIMER_COUNT_REGISTER;
}

//wait 1 second
void wait_1s(){
    unsigned long start_time = get_timer_count();
    while(get_timer_count() - start_time < 1000000){
    } 
}

// Function to clear the .bss segment
void clear_bss(void) {
    extern int __bss_start, __bss_end;
    char *bssstart = (char *)&__bss_start;
    char *bssend = (char *)&__bss_end;

    // Set all memory in .bss to 0
    while (bssstart < bssend) {
        *bssstart++ = 0;
    }
}

void list_add(struct list_element **list_head, struct list_element *new_element) {
    new_element->next = *list_head;  // New element points to the current head
    *list_head = new_element;        
}

void list_remove(struct list_element **list_head, struct list_element *element_to_remove) {
    if (*list_head == element_to_remove) {
        *list_head = element_to_remove->next;  // If head is the element, just update the head
    }
}

void kernel_main() {
    // Clear the .bss segment
    clear_bss();

    // Task 1
    unsigned long initial_timer_value = get_timer_count();
    esp_printf(putc, "Initial Timer Count: %lu\n", initial_timer_value);

    // Task 2
    esp_printf(putc, "Waiting for 1 ms...\n");
    wait_1ms();

    // Print the timer value after 1 second wait
    unsigned long after_wait_timer_value = get_timer_count();
    esp_printf(putc, "Timer Count After 1s Wait: %lu\n", after_wait_timer_value);

    // Create list elements
    struct list_element element1 = { .next = NULL, .data = 10 };
    struct list_element element2 = { .next = NULL, .data = 20 };
    struct list_element element3 = { .next = NULL, .data = 30 };

    // Head of the linked list
    struct list_element *head = NULL;

    // Add elements to the linked list
    list_add(&head, &element1);
    list_add(&head, &element2); 
    list_add(&head, &element3);  

    // Remove element2 from the list 
    list_remove(&head, &element2); 

    // Infinite loop to keep the kernel running
    while (1) {
    }
}
