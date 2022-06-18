#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


void prefix_function(int * prefix_arr, int pattern_len, char pattern[]);

long mtime()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    long mt = t.tv_nsec;
    return mt;
}

int main() {
    int p_len, s_len;
    char string[5001], pattern[1001];
    printf("Please, input a string:\n");
    fgets(string, 5000, stdin);
    printf("Please, input a pattern:\n");
    fgets(pattern, 1000, stdin);
    p_len = strlen(pattern) - 1;
    s_len = strlen(string) - 1;
    for (int i = 0; i < p_len; i++) {
        pattern[i] = tolower(pattern[i]);
    }
    for (int i = 0; i < s_len; i++) {
        string[i] = tolower(string[i]);
    }
    int * index;
    int * tmp;
    int * pref = (int *) malloc(p_len * sizeof(int));
    prefix_function(pref, p_len, pattern);
    int i = 0, j = 0, count = 1;
	long t = mtime();
    while (i < s_len) {
        if (pattern[j] != string[i]) {
            if (j > 0) {
                j = pref[j - 1];
            }
            else {
                i += 1;
            }
        }
        else {
            if (j == p_len - 1 && count > 1) {
                tmp = (int *) malloc(sizeof(index) + sizeof(int));
                tmp = index;
                index = (int *) malloc(count * sizeof(int));
                index = tmp;
                index[count - 1] = i - j;
                count++;
                i += 1;
                j = pref[j];
            }
            else if (j == p_len - 1 && count == 1) {
                index = (int *) malloc(count * sizeof(int));
                index[count - 1] = i - j;
                count++;
                i += 1;
                j = pref[j];
            }
            else {
                j += 1;
                i += 1;
            }
        }
    }
	t = mtime() - t;
    if (count > 1) {
        printf("Indexes where the pattern was found are: ");
        for (i = 0; i < count - 1; i++) {
          printf("%d ", index[i]);
        } 
    }
    else {
        printf("No coincidence was found in the string");
    }
    float mc_sec = (float) t / 1000;
	printf("\nTime of searching equals %f microseconds\n", mc_sec);
    if (count > 1) {
       free(index);
    }
    free(pref);
    return 0;
}

void prefix_function(int * prefix_arr, int pattern_len, char pattern[]){
    prefix_arr[0] = 0;
    int i = 1, j = 0;
    while (i < pattern_len) {
        if (pattern[i] != pattern[j]) {
            if (j > 0) {
                j = prefix_arr[j - 1];
            }
            else {
                prefix_arr[i] = 0;
                i += 1;
            } 
        }
        else {
            prefix_arr[i] = j + 1;
            j += 1;
            i += 1;
        }
    } 
} 
