#include <stdio.h>
#include <stdlib.h>
#define TAPESIZE 100000
#define LEFTBRACE 91
#define RIGHTBRACE 93
#define PLUS 43
#define MINUS 45
#define DOT 46
#define LEFTANGLE 60
#define RIGHTANGLE 62

int countCharacters(const char *str) {
    // Count the number of characters in a string
    int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

void brace_match(const char *input, int *jump_forward, int *jump_back){
    // Write the index of the matching ] (right brace) into the jump_forward array, 
    // at the index corresponding each [ (left brace) in the input. Vice versa for jump_back. 
    int input_size = countCharacters(input);
    // Initialise stack as an array and the index of the last element
    int stack[input_size + 1];
    int last_element = 0;
    for (int i=0; i < input_size; i++){
        if (input[i] == LEFTBRACE){
            // Push onto stack
            last_element++;
            stack[last_element] = i;
        }
        else if (input[i] == RIGHTBRACE) {
            // The stack should not be empty at this point, so if it is there is a mismatched
            // brace, exit early
            if (last_element < 0){
                printf("Mismatched braces! Please provide a valid BF command set! \n");
                exit(1);
            }
            // Get the index of the left brace, given that the index of the right brace is i.
            // Write indices to the corresponding arrays and then pop off stack. 
            int leftbrace = stack[last_element];
            jump_forward[leftbrace] = i;
            jump_back[i] = leftbrace;
            last_element--;
        }
    }
    // The stack should be empty at this point, so if it is not there is a mismatched brace, exit early 
    if (last_element > 0){
        printf("Mismatched braces! Please provide a valid BF command set! \n");
        exit(1);
    }
    return; 
}

int main(int argc, char *argv[]) {
    // Check number of arguments is correct 
    if (argc == 1){
        printf("Please provide a set of BF commands to interpret! \n");
        exit(1);
    }
    else if (argc > 2){
        printf("Please provide the BF command as a single string without whitespace! \n");
        exit(1); 
    }
    // Initialisation
    char tape[TAPESIZE];
    int data_pointer = TAPESIZE / 2;
    int instruction_pointer = 0;
    int char_count = countCharacters(argv[1]);
    int jump_forward[char_count];
    int jump_back[char_count];
    // Write matched braces to the jump_forward and jump_back arrays
    brace_match(argv[1], jump_forward, jump_back);
    while (instruction_pointer < char_count){
        char command = argv[1][instruction_pointer];
        // Rules of the BF language
        switch(command){
            case LEFTANGLE:
            data_pointer--;
            break;
            case RIGHTANGLE:
            data_pointer++;
            break;
            case PLUS:
            tape[data_pointer]++;
            break;
            case MINUS:
            tape[data_pointer]--;
            break;
            case DOT:
            printf("%c", tape[data_pointer]);
            break;
            case LEFTBRACE:
            if (tape[data_pointer] == 0){
                instruction_pointer = jump_forward[instruction_pointer];
            }
            break;
            case RIGHTBRACE:
            if (tape[data_pointer] != 0){
                instruction_pointer = jump_back[instruction_pointer];
            }
            break;
        }
        instruction_pointer++;
    }
    // Print a newline to more clearly see output of interpreter
    printf("\n");
    return 0;
}