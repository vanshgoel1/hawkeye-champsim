#include "rrip.h"

void update_rrpv(std::vector<int>& rrpv, std::size_t way, Classification cls, bool is_hit) {
    if(cls == Classification::CACHE_AVERSE) {
        rrpv[way] = 7;
        return;
    }
    if(!is_hit) {
        for(int i = 0; i < rrpv.size(); i++) {
            if(rrpv[i] < 6) rrpv[i]++;
        }
    }
    rrpv[way] = 0;
}

std::size_t find_victim(std::vector<int>& rrpv) {
    int max_idx = 0;
    for(int i = 0; i < rrpv.size(); i++) {
        if(rrpv[i] > rrpv[max_idx]) max_idx = i;
    }
    if(rrpv[max_idx] < 7) { 
        for(int i = 0; i < rrpv.size(); i++) {
            rrpv[i] += 7 - rrpv[max_idx];
        }
    }
    return max_idx;
}
