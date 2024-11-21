#ifndef SIMH
#define SIMH

#include <vector>
#include <utility>

using namespace std;

using range=pair<int, int>;
using alloc=pair<range, int>;
using range_list=vector<range>;
using alloc_list=vector<alloc>;

const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
const int REQUEST_INTERVAL = 10;
const int MEMORY_SIZE = 1000;

// my functions
void init_free_list(range_list& free_list);
void init_allocated_list(alloc_list& allocated_list);
void print_free_list(range_list& free_list);
void print_allocated_list(alloc_list& allocated_list);
alloc generate_request(int clock);
int check_request(range_list& free_list, alloc request);
void fulfill_request(range_list& free_list, 
                     alloc_list& allocated_list, 
                     alloc request, 
                     int index);
void clean_allocated_blocks(range_list& free_list, 
                  alloc_list& allocation_list, 
                  int clock);
void merge_free_blocks(range_list& free_list, int& merge_count);
void print_request(alloc request);


#endif
