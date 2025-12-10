#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleMaker(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts, 
    size_t day, 
    size_t curr_shift);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)

{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    for (size_t i = 0; i < avail.size(); i++) { 
        vector<Worker_T> daily_sched(dailyNeed, -1); 
        sched.push_back(daily_sched); 
    }
    vector<size_t> shifts(avail[0].size(), 0); 
    return scheduleMaker(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool scheduleMaker(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts, 
    size_t day, 
    size_t curr_shift) 
{
    size_t num_workers = avail[0].size();

    // All days are filled 
    if (day == avail.size()) { 
        return true; 
    }
    
    else { 
        for (size_t worker = 0; worker < num_workers; worker++) { 
            // Current worker has not reached the max shifts and is available that day 
            if (shifts[worker] < maxShifts && avail[day][worker]) { 
                //Assign worker to current shift 
                sched[day][curr_shift] = worker; 
                shifts[worker]++; 
                
                bool success;
                // If this complete's the shift limit, move on to next day
                if (curr_shift + 1 == dailyNeed) { 
                    success = scheduleMaker(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
                }
                //  Otherwise, move to next shift on same day
                else {
                    success = scheduleMaker(avail, dailyNeed, maxShifts, sched, shifts, day, curr_shift + 1); 
                }
                
                // If there is a valid schedule, stop 
                if (success) { 
                    return true; 
                }
                
                //Backtrack and try next worker
                shifts[worker]--; 
                sched[day][curr_shift] = -1; 
            }
        } 
    }
    return false; 

}
