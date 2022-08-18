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

void build_array(int *array, int start, int step, int len)
{
    for (int i = 0; i < len; i++) {
        array[i] = start + i * step;
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
    } else {
        memcpy(ret, array, len * sizeof(int));
        
    }
    
    return ret;
}

int* merge(int* low, int* high, int c_low, int c_high) 
{
    int *ret = (int *) malloc((c_low + c_high) * sizeof(int));
    int c = 0;
    int i = 0;
    int j = 0;

    while (i < c_low && j < c_high) {
        if (low[i] < high[j]) {
            ret[c] = low[i];
            i++;
            c++;
        } else if (low[i] > high[j]) {
            ret[c] = high[j];
            j++;
            c++;
        } else {
            ret[c] = low[i];
            i++;
            c++;
            ret[c] = high[j];
            j++;
            c++;
        }
    }

    while (i < c_low) {
        ret[c] = low[i];
        i++;
        c++;
    }
    
    while (j < c_high) {
        ret[c] = high[j];
        j++;
        c++;
    }
    
    return ret;
}

int* merge_sort(int *array, int len)
{
    int *ret = (int *) malloc(len * sizeof(int));

    if (len > 1) {
        int c_low = len/2;
        int *low = (int *) malloc(c_low * sizeof(int));
        int c_high = len - len/2;
        int *high = (int *) malloc(c_high * sizeof(int));

        cpy_array(low, array, c_low);
        cpy_array(high, &array[c_low], c_high);

        cpy_array(ret, merge(merge_sort(low, c_low), merge_sort(high, c_high), c_low, c_high), len);
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

int get_idx_in_sorted_list(int *array, int len, int element)
{
    int start = 0;
    int end = len;

    while (start != end) {
        int mid = (end)/2 + (start + 1)/2;
        printf("%d ... %d ... %d\n", start, mid, end);
        if (array[mid] < element) {
            start = mid;
        } else if (array[mid] > element) {
            end = mid;
        } else {
            return mid;
        }
    }
    
    return -1;
}

int main (int argc, char *argv[]) 
{
    int a[100];

    int len = sizeof(a)/sizeof(int);

    // build_rndm_array(a, len, 100000);

    // bubble_sort(a, len);
    // selection_sort(a, len);
    // insertion_sort(a, len);
    // memcpy(a, quick_sort(a, len), len * sizeof(int));
    // memcpy(a, merge_sort(a, len), len * sizeof(int));
    

    build_array(a, 0, 1, len);
    print_array(a, len);

    

    printf("%d\n", get_idx_in_sorted_list(a, len, 1));


    if (is_sorted(a, len)) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }
    
}