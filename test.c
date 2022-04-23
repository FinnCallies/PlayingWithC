#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int *array, int len) 
{
    if (!len)
        return;

    printf("%d", array[0]);
    for (int i = 1; i < len; i++) {
        printf(", %d", array[i]);
    }
    printf("\n");
}

void build_rndm_array(int *array, int len, int max) {
    for (int i = 0; i < len; i++) {
        array[i] = rand() % max;
    }
}

void bubble_sort(int *array, int len) 
{
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int *array, int len)
{
    for (int i = 0; i < len; i++) {
        int idx = 0;
        for (int j = 1; j < len - i; j++) {
            if (array[j] > array[idx])
                idx = j;
        } 
        int temp = array[len - i - 1];
        array[len - i - 1] = array[idx];
        array[idx] = temp;
    }
}

void insertion_sort(int *array, int len) 
{
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j > 0; j--) {
            if (array[j] < array[j - 1]) {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            } else {
                j = 0;
            }
        }
    }
}

void cpy_array(int *dest, int *src, int len)
{
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

int* quick_sort(int *array, int len)
{
    int *ret = (int *) malloc(len * sizeof(int));
    if (len > 1) {
        int *low = (int *) malloc(len * sizeof(int));
        int c_low = 0;
        int *high = (int *) malloc(len * sizeof(int));
        int c_high = 0;
        int *same = (int *) malloc(len * sizeof(int));
        int c_same = 0;

        int temp = array[0];

        for (int i = 1; i < len; i++) {
            if (array[i] > temp) {
                high[c_high] = array[i];
                c_high++;
            } else if (array[i] < temp) {
                low[c_low] = array[i];
                c_low++;
            } else {
                same[c_same] = array[i];
                c_same++;
            }
        }

        if (c_low)
            memcpy(ret, quick_sort(low, c_low), c_low * sizeof(int));
        
        if (c_same)
            memcpy(&ret[c_low], same, c_same * sizeof(int));
        
        ret[c_same + c_low] = temp;

        if (c_high)
            memcpy(&ret[c_same + c_low + 1], quick_sort(high, c_high), c_high * sizeof(int));

        free(c_low);
        free(c_same);
        free(c_high);
    } else {
        memcpy(ret, array, len * sizeof(int));
        
    }
    
    return ret;
}

int is_sorted(int *array, int len) 
{
    for (int i = 0; i < len - 1; i++) {
        if (array[i] > array[i + 1])
            return 0;
    }
    return 1;
}

int main (int argc, char *argv[]) 
{
    int a[100000];

    int len = sizeof(a)/sizeof(int);

    build_rndm_array(a, len, 1000);

    // bubble_sort(a, len);
    // selection_sort(a, len);
    // insertion_sort(a, len);
    // memcpy(a, quick_sort(a, len), len * sizeof(int));


    if (is_sorted(a, len)) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }
    
}