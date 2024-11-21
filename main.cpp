#include "sim.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
  
    srand(time(0));

    // stat stuff
    int request_count=0;
    int satisfied_requests=0;
    int unsatisfied_requests=0;
    int smallest_size=99999;
    int largest_size=0;
    int size_sum=0;
    int smallest_lease=99999;
    int largest_lease=0;
    int lease_sum=0;
    int merge_count=0;

    int clock=0; 
    range_list free_list;
    alloc_list allocated_list;    

    init_free_list(free_list);
    init_allocated_list(allocated_list);

    while(clock<=TIME_LIMIT) {
        if(clock%REQUEST_INTERVAL==0) {
            alloc request=generate_request(clock);
            ++request_count;
            int request_size=request.first.second;
            int lease_size=request.second;
            if(request_size<smallest_size)
                smallest_size=request_size;
            if(request_size>largest_size)
                largest_size=request_size;
            size_sum+=request_size;
            if(lease_size-clock<smallest_lease)
                smallest_lease=lease_size-clock;
            if(lease_size-clock>largest_lease)
                largest_lease=lease_size-clock;
            lease_sum+=lease_size-clock;  
            int index=check_request(free_list, request);
            cout << "----------" << endl;
            cout << "Clock Cycle: " << clock << endl;
            cout << "Request: ";
            print_request(request);
            if(index!=-1) {
                cout << "Request fulfilled!" << endl;
                fulfill_request(free_list, allocated_list, request, index);
                ++satisfied_requests;
            } else {
                cout << "Request unfulfilled!" << endl;
                ++unsatisfied_requests;
            }
            clean_allocated_blocks(free_list, allocated_list, clock);
            merge_free_blocks(free_list, merge_count);
            print_free_list(free_list);
            print_allocated_list(allocated_list);
 
        }
        ++clock;
    }

    cout << endl << "--- Stats ---" << endl;
    cout << "Total Number of Requests: " << request_count << endl;
    cout << "Number of satisfied Requests: " << satisfied_requests << endl;
    cout << "Number of unsatisfied Requests: " << unsatisfied_requests << endl;
    cout << "Smallest Block Size: " << smallest_size << endl;
    cout << "Largest Block Size: " << largest_size << endl;
    cout << "Average Block Size: " << size_sum/request_count << endl;
    cout << "Shortest Lease Size: " << smallest_lease << endl;
    cout << "Longest Lease Size: " << largest_lease << endl;
    cout << "Average Lease Size: " << lease_sum/request_count << endl;
    cout << "Times merged: " << merge_count << endl;



    return 0;
}
