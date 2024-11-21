#include "sim.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void init_free_list(range_list& free_list) {
    free_list.clear(); 
    free_list.push_back({0, MEMORY_SIZE});
    return;
}
 
void init_allocated_list(alloc_list& allocated_list) {
    allocated_list.clear();
    return;
}

void print_free_list(range_list& free_list) {
    cout << "Free List: ";
    int n=free_list.size();
    if(n==0) {
        cout << "--empty--" << endl;
        return;
    }
    for(int i=0; i<n; ++i) {
        int first=free_list[i].first;
        int second=free_list[i].second;
        if(i%5==0&&i!=0)
            cout << endl;
        cout << "{" << first << ", " << second << "}";
        if(i!=n-1)
            cout << ", ";
    }
    cout << endl;
    return;
}

void print_allocated_list(alloc_list& allocated_list) {
    cout << "Allocated List: ";
    int n=allocated_list.size();
    if(n==0) {
        cout << "--empty--" << endl;
        return;
    }
    for(int i=0; i<n; ++i) {
        int first=allocated_list[i].first.first;
        int second=allocated_list[i].first.second;
        int third=allocated_list[i].second;
        if(i%4==0&&i!=0)
            cout << endl;
        cout << "[{" << first << ", " << second << "}, " << third << "]";
        if(i!=n-1)
            cout << ", ";
    }
    cout << endl;
    return;
}

alloc generate_request(int clock) {
    int start=(-1);
    int size=rand()%(MAX_SIZE-MIN_SIZE+1)+MIN_SIZE;
    int lease=rand()%(MAX_LEASE-MIN_LEASE+1)+MIN_LEASE;
    return {{start, size}, lease+clock};
}

int check_request(range_list& free_list, alloc request) {
    int size=request.first.second;
    int n=free_list.size();
    for(int i=0; i<n; ++i) {
        if(size<=free_list[i].second)
            return i;
    } 
    return -1; // returns -1 if request is unsatisfied
}

void fulfill_request(range_list& free_list, 
                     alloc_list& allocated_list, 
                     alloc request, 
                     int index) {
    request.first.first=free_list[index].first;
    allocated_list.push_back(request);
    int size=request.first.second;
    if(size==free_list[index].second)
        free_list.erase(free_list.begin()+index);
    else {
        free_list[index].first+=request.first.second;
        free_list[index].second-=request.first.second;
    }
    return;
}

void clean_allocated_blocks(range_list& free_list, 
                  alloc_list& allocation_list, 
                  int clock) {
    sort(allocation_list.begin(), allocation_list.end(), 
         [](const alloc& a, const alloc& b) {
             return a.first<b.first;
         });
    for(int i=0; i<allocation_list.size(); ++i) {
        if(allocation_list[i].second<=clock) {
            int size=allocation_list[i].first.second;
            int start=allocation_list[i].first.first;
            allocation_list.erase(allocation_list.begin()+i);
            free_list.push_back({start, size}); 
            --i;
        }
    }
}

void merge_free_blocks(range_list& free_list, int& merge_count) {
    sort(free_list.begin(), free_list.end(), [](range a, range b) {
        return a.first < b.first;
    });
    for(int i=0; i<free_list.size()-1;) {
        if(free_list[i].first+free_list[i].second==free_list[i+1].first) {
            free_list[i].second+=free_list[i+1].second;
            free_list.erase(free_list.begin()+i+1);
            ++merge_count;
        } else {
            ++i;
        }
    }
}

void print_request(alloc request) {
    int second=request.first.second;
    int third=request.second;
    cout << "[{na, " << second << "}, " << third << "]" << endl;
}
