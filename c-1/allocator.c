////////////////////////////////////////////////////////////////////////////////
// COMP1521 22T1 --- Assignment 2: `Allocator', a simple sub-allocator        //
// <https://www.cse.unsw.edu.au/~cs1521/22T1/assignments/ass2/index.html>     //
//                                                                            //
// Written by Fadi Al Hatu (z5309136) on 25/04/2022.                          //
//                                                                            //
// 2021-04-06   v1.0    Team COMP1521 <cs1521 at cse.unsw.edu.au>             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// A program that allows a user to innitialise a heap and allocater and free space
// Throughout the heap dynamically allocating memory, basically impersonates 
// mymalloc() and free() functions without calling them

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"

// DO NOT CHANGE CHANGE THESE #defines

/** minimum total space for heap */
#define MIN_HEAP 4096

/** minimum amount of space to split for a free chunk (excludes header) */
#define MIN_CHUNK_SPLIT 32

/** the size of a chunk header (in bytes) */
#define HEADER_SIZE (sizeof(struct header))

/** constants for chunk header's status */
#define ALLOC 0x55555555
#define FREE 0xAAAAAAAA

// ADD ANY extra #defines HERE

// DO NOT CHANGE these struct defintions

typedef unsigned char byte;

/** The header for a chunk. */
typedef struct header {
    uint32_t status; /**< the chunk's status -- shoule be either ALLOC or FREE */
    uint32_t size;   /**< number of bytes, including header */
    byte     data[]; /**< the chunk's data -- not interesting to us */
} header_type;


/** The heap's state */
typedef struct heap_information {
    byte      *heap_mem;      /**< space allocated for Heap */
    uint32_t   heap_size;     /**< number of bytes in heap_mem */
    byte     **free_list;     /**< array of pointers to free chunks */
    uint32_t   free_capacity; /**< maximum number of free chunks (maximum elements in free_list[]) */
    uint32_t   n_free;        /**< current number of free chunks */
} heap_information_type;

// Footnote:
// The type unsigned char is the safest type to use in C for a raw array of bytes
//
// The use of uint32_t above limits maximum heap size to 2 ** 32 - 1 == 4294967295 bytes
// Using the type size_t from <stdlib.h> instead of uint32_t allowing any practical heap size,
// but would make struct header larger.


// DO NOT CHANGE this global variable
// DO NOT ADD any other global  variables

/** Global variable holding the state of the heap */
static struct heap_information my_heap;

// ADD YOUR FUNCTION PROTOTYPES HERE

// Initialise my_heap
// Footnote:

// Init Heap is a function used to initialise the first chunk of memory that we use in the 
// Program, the first chunk (i.e the heap) is initialised to size:size (whatever the user 
// requests), if the input isn't big enough or a factor of 4, the size is altered to meet 
// certain requirements. The function then initialises the static struct and allocates pointers
// To the start of the heap. A free list is also malloc'd to store all 'free' chunks of data 
// in the heap
int init_heap(uint32_t size) {
    // Setting size to be minimum heap if inputted size is less than MIN_HEAP
    if (size < MIN_HEAP) {
        size = MIN_HEAP;
    }
    // If size isn't divisible by 4, setting size to be divisible by 4 (next highest factor)
    int remainder;
    remainder = size % 4; 
    if (remainder != 0) {
        size = size + (4 - remainder); 
    }

    // Initialise a section of memory on the heap to equal to SIZE bytes
    void* heap_pointer;
    heap_pointer = malloc(size);

    // Set the struct values accordingly, my_heap.heap_mem needs to point to the first byte 
    // of the set heap 

    // Setting the heap pointer to equal the 'heap_pointer'
    my_heap.heap_mem = (byte*)heap_pointer;
    //Setting the heaps size to equal the allocated size of the heap
    my_heap.heap_size = size;

    //Set up header 
    //Set the start of the header to be equal to the pointer of the start of
    //the heap, typecast to make it compatible
    header_type* header_pointer = (header_type*)heap_pointer;

    //header_type initial_chunk; 
    header_pointer -> status = FREE;
    header_pointer -> size = size;
    
    //Setting the free list array
    int total_size = size/HEADER_SIZE;
    byte** free_list_pointer;
    //Mallocing an array the size that is needed
    free_list_pointer = malloc(total_size * sizeof(byte));
    my_heap.free_list = free_list_pointer;
    //Setting the first element of the list to equal to the first pointer
    my_heap.free_capacity = size/(HEADER_SIZE); 
    //Setting the first element of the free list to equal the start of heap
    my_heap.free_list[0] = (byte*)heap_pointer;
    my_heap.n_free = 1;

    // Return 0 if successful, -1 if not 
    if (my_heap.heap_mem == NULL) {
        return -1;
    }
    if (header_pointer == NULL) {
        return -1;
    }
    if (free_list_pointer == NULL) {
        return -1;
    }

    return 0; 
}

// Allocate a chunk of memory large enough to store `size' bytes

// Footnote: the my_malloc function returns a pointer to the first usable byte 
// that has just been allocated within the heap, the function takes in a size 
// inputted by the user and looks through the free list array to find the most 
// fit free chunk to use to become 'allocated', if all the free chunks are too small 
// then allocate the biggest small one, if all the free chunks are too big, then allocate
// the smallest big one, and split the chunk to make a new free chunk.

void *my_malloc(uint32_t size) {
    //Error statements/adjustements for if size isnt within requirements
    //If there are not free elements
    if (my_heap.n_free == 0) {
        return NULL;
    }
    //If the size is less than 1
    if (size < 1) {
        return NULL;
    }

// If size isnt a factor of 4, round it up to the nearest factor of 4
    int remainder;
    remainder = size % 4; 
    if (remainder != 0) {
        size = size + (4 - remainder); 
    }

    // Set a total size to equal size + header size
    int total_size = HEADER_SIZE + size;  
  
    //Set a new header to compare it with the free list 
    header_type *chosen = NULL;
    // if there are elements in the free list, chosen points to the first elements
    if (my_heap.free_list[0] != NULL) {
    //Points a new pointer to the free list section we want to use
        chosen = (header_type *)my_heap.free_list[0];
    }
    //Store the value of i for when the correct free chunk is selected
    int index = 0;
    //Loop through the free list array to find the smallest (big enough chunk) 
    //within the free list array
    int new_chunk_size = 0;
    int checked = 0;
    // int biggest_size = 0;
    // int biggest = 0;

    for (int i = 0; i < (my_heap.n_free); i++) {
        //extract the header pointer from each index of the free list
        header_type *free = (header_type *)my_heap.free_list[i];
        //Store the biggest free element size, in case there arent any big enough for 
        //our requirements, biggest variable just stores the index that has the biggest 
        //free chunk
        // if (free->size > biggest_size) {
        //     biggest_size = free->size;
        //     biggest = i;
        // }
        //Initial check to see if the free array is big enough to store out desired chunk
        //If statement is for the first valid chunk that can store our chunk, new_chunk_size
        //stores the size of the first valid chunk, the following if statements use this to 
        //try find any smaller valid chunks
        //Checked variable just is used to see if there is already a free element that could
        //store the chunk
        if (
            free->status == FREE &&
            free->size >= total_size && 
            checked == 0) {
            new_chunk_size = free->size;
            checked++;
            //Store the index of the free list that we are using
            index = i;
        }    
        // If there has already been a free element that is valid, compare it with any further 
        // free elements to make sure the smallest free element is stored
        if (checked != 0) {
            if (
                free->status == FREE &&
                free->size >= total_size && 
                free->size < new_chunk_size) {
                new_chunk_size = free->size;
                //Store the index of the free list that we are using
                index = i;
            }    
        }
    }
    //If there are no chunks the size of total size available, allocate the whole chunk
    //Change the size of total size to equal the biggest chunk available so we dont go over
    //the available space
    // if (biggest_size < total_size) {
    //     total_size = biggest_size;
    //     index = biggest;
    // }
    // Make the chosen chunk point to the free element we have chosen and change the status to ALLOC
    chosen = (header_type *)my_heap.free_list[index];
    chosen->status = ALLOC; 

    //Create a new header for any possible new free chunk required if the allocated space is too big
    header_type* new_free_chunk = NULL;
    int new_size = new_chunk_size;
    // If the size of the free chunk is bigger than the needed allocated space + minimum 
    // space for a chunk then we need to make a new free chunk
    // If the difference is bigger than the minimum chunk size 
    if ((new_size - total_size) >= MIN_CHUNK_SPLIT) {    
        // The chosen chunks size can be finalised to equal the requested size 
        // (i.e we dont need to reduce allocated space)
        chosen->size = total_size;
        //Find the difference between the requested space vs the amount of free space allocated
        int difference = new_size - total_size;
        //Create a new header for the new free chunk and point it to the same spot that the 
        // previous free chunk was in, set the size to equal the difference between new and total size
        new_free_chunk = (header_type*)((byte*)chosen + total_size);
        new_free_chunk->status = FREE;
        new_free_chunk->size = difference;
        my_heap.free_list[index] = (byte*)new_free_chunk;
    }
    // If it is the perfect size or bigger than the free space we need to reset the order of the free list 
    // Furthermore we don't need to change the size of chosen->size because the free chunk already has the 
    // perfect requirements, we only need to change the status
    else {
        int i = 0;
        //For the amount of free elements in the heap
        for (i = 0; i < (my_heap.n_free); i++) {
            //Bring forward the free items that are available (after or at the same place)
            // as the one that has been used, i.e if the third free chunk has been used
            // we dont need to move the 1st or 2nd as they are already in order 
            if (i >= index) {
                my_heap.free_list[i] = my_heap.free_list[i+1];
            }
        }
        //Set the final array in the free list to equal NULL
        my_heap.free_list[i] = NULL;
        //We need to reduce the number of free elements in the free array, and set the final array to NULL
        my_heap.n_free = my_heap.n_free - 1;
    }
    //Return the first usuable byte from the new chunk, which is equal to the new chunk without the header
    void* first_usable;
    first_usable = (byte*)chosen + HEADER_SIZE;
    return first_usable;
}


// Deallocate chunk of memory referred to by `ptr'

//Footnote: Function that given a pointer to the first usable part of an allocated chunk
// Changes the status of that chunk from allocated to free and sets the free list 
// accordingly
void my_free(void *ptr) {
    // If we have been given a pointer to a NULL address, then exit the program
    if (ptr == NULL) {
        fprintf(stderr, "Attempt to free unallocated chunk\n");
        exit(1);
    }
    //Set the ptr to point to the header of the chunk rather than the first usable byte
    header_type *ptr_header = (header_type *)(ptr-HEADER_SIZE);
    //If its not pointing to a free chunk, exit the function
    if (ptr_header->status != ALLOC) {
        fprintf(stderr, "Attempt to free unallocated chunk\n");
        exit(1);
    }
    
    //For fragmentation, we need to see if there are any adjacent free chunks on either side
    int right = 0;
    int left = 0;
    // Variables that store the location of the adjacent chunks (index1 for the right and 
    // index2 for the left)
    int index1 = -1;
    int index2 = -1;
    
    //Look to see if any free chunks in the free list are to the RIGHT or LEFT of the attempted free block 
    
    //Initialise two header pointers (for any adjacent chunks) to equal to null
    header_type *chunk_after = NULL;
    header_type *chunk_before = NULL;
    for (int i = 0; i < my_heap.n_free; i++) {
        int ptr_size = ptr_header->size;
        //CHUNK TO THE RIGHT
        //If the free element is equal to our pointer + the pointers size (i.e the next chunk in the heap)
        //Then we set the previously intialised variables accordingly and store the relavent index 
        if (my_heap.free_list[i] == (byte*)((byte*)ptr_header + ptr_size)) {
            right++;
            index1 = i;
            chunk_after = (header_type*)(my_heap.free_list[index1]);
        }
        //CHUNK TO THE LEFT
        //If the size of a free list element + the same elements size is equal to our ptr then we 
        //Set the previously initialised variables accordingly
        header_type *chunk = (header_type*)(my_heap.free_list[i]);
        if ((my_heap.free_list[i]+chunk->size) == (byte*)ptr_header) {
            left++;
            index2 = i;
            chunk_before = (header_type*)(my_heap.free_list[index2]);
        }
    } 
    //We then need to adjust the free list array accordingly (rearrange the order etc..)
    //We have case situations for any possibilities

    // If the ptr has no adjacent chunks at all
    if (left == 0 && right == 0) {
        //Set status to free
        ptr_header->status = FREE; 
        int i = 0;
        // While the elements in the free list point somewhere before the ptr, keep incrementing
        while (my_heap.free_list[i] < (byte*)ptr_header && i < my_heap.n_free -1) {
            i++;
        }
        // Once free list element after where out new free chunk should be
        // we move all the remaining elements further along the list and 
        // store the position which we want the new chunk to be in

        int position = i;
        // Increment the remaining elements up one spot 
        while (i < my_heap.n_free) {
            //If the free element is past where we need to put our new chunk in, we need to 
            //rearrange the order
            if (i >= position) {
                // Making the 'next' element equal to the current
                my_heap.free_list[i + 1] = my_heap.free_list[i];
            }
            i++;
        }
        //Set the new ptr to be set in the 'position' spot (i.e the position that the new chunk 
        //should be placed in)
        my_heap.free_list[position] = (byte*)ptr_header;
        //As there is now a new free chunk we need to add to my_heap.n_free
        my_heap.n_free++;
    }

    // If the ptr has 1 adjacent chunk to the left
    else if (left == 1 && right == 0) {
        //Make the earlier chunks size equal to its size and the newly freed chunks size
        chunk_before->size = chunk_before->size + ptr_header->size;
        ptr_header = NULL;
    }

    // If the ptr has 1 adjacent chunk to the right
    else if (left == 0 && right == 1) {
        int size = chunk_after->size;
        chunk_after = ptr_header;
        //Set the size of the chunk in the position of ptr to equal to its initial size
        //aswell as the size of the adjacent chunk to the right
        chunk_after->size = ptr_header->size + size; 
        chunk_after->status = FREE;
        //The free list element ordering wont change, but make sure the relavent index is
        //pointing to the correct chunk
        my_heap.free_list[index1] = (byte*)chunk_after;
    }

    // If ptr has 2 adjacent blocks, one to the right and left
    else if (left == 1 && right == 1) {
        int size = chunk_after->size;
        //Set the first chunk of the three (chunk before) to have their size equal to 
        //Its initial size + the ptr size and the size of the final free chunk
        chunk_before->size = chunk_before->size + ptr_header->size + size;

        //Reset the free list array, we need to push back all the elements 
        //After the position that we store our new free array
        int i = 0;
        for (i = 0; i < (my_heap.n_free); i++) {
            //If the index is past or equal to where we need to set our free chunk
            //Then set all free array elements to equal 'the index after'
            if (i >= index1) {
                my_heap.free_list[i] = my_heap.free_list[i+1];
            }
        } 
        //Point the final index to equal NULL as we no longer are using it
        my_heap.free_list[i] = NULL;
        //Reduce the amount of free elements in the heap
        my_heap.n_free--;
        //Setting pointers to NULL just so they dont cause further issues
        chunk_after = NULL;
        ptr_header = NULL;
    }
}

// DO NOT CHANGE CHANGE THiS FUNCTION
//
// Release resources associated with the heap
void free_heap(void) {
    free(my_heap.free_list);
}


// DO NOT CHANGE CHANGE THiS FUNCTION

// Given a pointer `obj'
// return its offset from the heap start, if it is within heap
// return -1, otherwise
// note: int64_t used as return type because we want to return a uint32_t bit value or -1
int64_t heap_offset(void *obj) {
    if (obj == NULL) {
        return -1;
    }
    int64_t offset = (byte *)obj - my_heap.heap_mem;
    if (offset < 0 || offset >= my_heap.heap_size) {
        return -1;
    }
    return offset;
}


// DO NOT CHANGE CHANGE THiS FUNCTION
//
// Print the contents of the heap for testing/debugging purposes.
// If verbosity is 1 information is printed in a longer more readable form
// If verbosity is 2 some extra information is printed
void dump_heap(int verbosity) {

    if (my_heap.heap_size < MIN_HEAP || my_heap.heap_size % 4 != 0) {
        printf("ndump_heap exiting because my_heap.heap_size is invalid: %u\n", my_heap.heap_size);
        exit(1);
    }

    if (verbosity > 1) {
        printf("heap size = %u bytes\n", my_heap.heap_size);
        printf("maximum free chunks = %u\n", my_heap.free_capacity);
        printf("currently free chunks = %u\n", my_heap.n_free);
    }

    // We iterate over the heap, chunk by chunk; we assume that the
    // first chunk is at the first location in the heap, and move along
    // by the size the chunk claims to be.

    uint32_t offset = 0;
    int n_chunk = 0;
    while (offset < my_heap.heap_size) {
        struct header *chunk = (struct header *)(my_heap.heap_mem + offset);

        char status_char = '?';
        char *status_string = "?";
        switch (chunk->status) {
        case FREE:
            status_char = 'F';
            status_string = "free";
            break;

        case ALLOC:
            status_char = 'A';
            status_string = "allocated";
            break;
        }

        if (verbosity) {
            printf("chunk %d: status = %s, size = %u bytes, offset from heap start = %u bytes",
                    n_chunk, status_string, chunk->size, offset);
        } else {
            printf("+%05u (%c,%5u) ", offset, status_char, chunk->size);
        }

        if (status_char == '?') {
            printf("\ndump_heap exiting because found bad chunk status 0x%08x\n",
                    chunk->status);
            exit(1);
        }

        offset += chunk->size;
        n_chunk++;

        // print newline after every five items
        if (verbosity || n_chunk % 5 == 0) {
            printf("\n");
        }
    }

    // add last newline if needed
    if (!verbosity && n_chunk % 5 != 0) {
        printf("\n");
    }

    if (offset != my_heap.heap_size) {
        printf("\ndump_heap exiting because end of last chunk does not match end of heap\n");
        exit(1);
    }

// // ADD YOUR EXTRA FUNCTIONS HERE
}