#include "test_array.h"
#include "test_list.h"

int main() 
{
    // Add all test runners here
    printf("Testing array...\n");
    test_array();
    printf("Finished testing array\n");

    printf("Testing list...\n");
    test_list();
    printf("Finished testing list\n");

    printf("All tests passed\n");
    return 0;
}