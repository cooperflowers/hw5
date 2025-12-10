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




// Add prototypes for any helper functions here


// be recursive, fill the schedule slots // have current day, id for how many needed filled, each workers' shift count
bool help(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t current, size_t id);





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



    const size_t n = avail.size();          //number of days
    const size_t k = avail[0].size();       //number of workers

    if(k == 0 || dailyNeed == 0) {          //no workers or needed workers means no schedule
        return false;
    }

   
    if(dailyNeed > k) {                        //impossible case, saves checking everythin else          
        return false;
    }

    
    sched.clear();                                      //new sched
    for(size_t i = 0; i < n; ++i) {        
        std::vector<Worker_T> row(dailyNeed, 0);            //fill it up with empty "0"
        sched.push_back(row);                           //we get n x d daily needed
    }

    
    std::vector<size_t> shiftCount(k, 0);               //keep track of each workers shift count

    
    return help(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);          //start recursing


}


bool help(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t current, size_t id){
    
    
    const size_t n = avail.size();
    const size_t k = avail[0].size();

   
    if(current == n) {                      //all days scheduled
        return true;
    }

    
    if(id == dailyNeed) {                                                              //filled current day, move on
        return help(avail, dailyNeed, maxShifts, sched, shiftCount, current + 1, 0);
    }

    
    for(size_t w = 0; w < k; ++w) {                 //loop to go thru all workers to check availability

        if(!avail[current][w]) {                //check if worker is available
            continue;
        }

        if(shiftCount[w] >= maxShifts) {        //check if they have not exceeded max shifts
            continue;
        }

        bool workCheck = false;                 //need to check to prevent same person two shift slots
        for(size_t j = 0; j < id; ++j) {
            if(sched[current][j] == w) {
                workCheck = true;
                break;
            }
        }
        if(workCheck) {
            continue;
        }
        
        sched[current][id] = w;                 //worker is valid so assign to the shift
        shiftCount[w]++;                        //add to their shift count

        if(help(avail, dailyNeed, maxShifts, sched, shiftCount, current, id + 1)) {     //do next slot in shift, if all can be filled returns true
            return true;
        }

        sched[current][id] = 0;             //when above is false, we undo the assignment and redo to find a different worker
        shiftCount[w]--;
    }

    
    return false;               //no worker can create a valid schedule
}