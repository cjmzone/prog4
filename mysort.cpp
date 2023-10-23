// Connor McKenna
// (CECS 325-01)
// Program 4 - Sorting Contest using pThreads
// Due Date (10/23/2023)
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <pthread.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

struct Thread_Data {
        int *start;
        int size;
};

void bubbleSort(int size, int *r_numbers ){
        for(int i = 0; i < size; i++){
                for(int j = i + 1; j < size; j++) {
                        if(r_numbers[j] < r_numbers[i]){
                                int temp = r_numbers[i];
                                r_numbers[i] = r_numbers[j];
                                r_numbers[j] = temp;
                        }
                }
        }
}

void *sortHelper(void *ptr) {
        Thread_Data *arg = (Thread_Data *) ptr;
        bubbleSort(arg->size, arg->start);
        return NULL;
}

void merge(int *s1, int size1, int *s2, int size2) {
    int totalsize = size1+size2;
    int *merged = new int[totalsize];
    int i = 0, j = 0, k = 0; 

    while (i < size1 && j < size2) {
        if (s1[i] < s2[j]) {
            merged[k++] = s1[i++];
        } else {
            merged[k++] = s2[j++];
        }
    }

    while (i < size1) {
        merged[k++] = s1[i++];
    }
    while (j < size2) {
        merged[k++] = s2[j++];
    }
    
    // copy merged in secion[0]
    for (int m = 0; m < totalsize; m++) {
       s1[m] = merged[m];
    }
    delete [] merged; 
}

int main(int count, char *file[]){

    if (count !=3){
            cout << "mysort accepts 2 paramenters only!" << endl;
            cout << "P1: input file" << endl;
            cout << "P2: output file" << endl;
            return 1;
    }

    // Input file
    ifstream fileIn;
    fileIn.open(file[1]);

    // Output file
    ofstream fileOut;
    fileOut.open(file[2], ios::out | ios::trunc);

    int array_size = 0;
    int num;

    // get the size
    while(fileIn >> num){
            array_size++;
    }
    // reset fileIn
    fileIn.close();
    fileIn.open(file[1]);

    int * r_numbers= new int[array_size];

    for(int i = 0; i < array_size; i++) {
            fileIn >> r_numbers[i];
    }

    // Create thread objects
    Thread_Data section[10];
    pthread_t thread[10];
    int returnThread[10];

    // intialize
    for (int i = 0; i < 10; i++){
        section[i].start = &r_numbers[i * 100000];
        section[i].size = 100000;
    }

    for(int i = 0; i < 10; i++) {
        returnThread[i] = pthread_create(&thread[i], NULL, sortHelper, (void*) &section[i]);
    }
    
    for(int i = 0; i < 10; i++) {
        pthread_join(thread[i], NULL);
    }

         // 1st round
    merge(section[0].start, section[0].size, section[1].start, section[1].size);
    merge(section[2].start, section[2].size, section[3].start, section[3].size);
    merge(section[4].start, section[4].size, section[5].start, section[5].size);
    merge(section[6].start, section[6].size, section[7].start, section[7].size);
    merge(section[8].start, section[8].size, section[9].start, section[9].size);

    // 2nd round
    merge(section[0].start, section[0].size + section[1].size, section[2].start, section[2].size + section[3].size);
    merge(section[4].start, section[4].size + section[5].size, section[6].start, section[6].size + section[7].size);

    // 3rd round 
    merge(section[0].start, section[0].size + section[1].size + section[2].size + section[3].size, section[4].start, section[4].size + section[5].size + section[6].size + section[7].size);

    // 4th round
    merge(section[0].start, section[0].size + section[1].size + section[2].size + section[3].size + section[4].size + section[5].size + section[6].size + section[7].size, section[8].start, section[8].size + section[9].size);

     for (int i = 0; i < 1000000; i++) {
       fileOut << r_numbers[i] << "\n";
    }

    delete []r_numbers;
    fileIn.close();
    fileOut.close();
    return 0;
}                                           
