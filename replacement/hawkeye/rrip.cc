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
    int max_idx = 0, max_val = rrpv[0];
    for(int i = 0; i < rrpv.size(); i++) {
        if(rrpv[i] > max_val){
            max_idx = i;
            max_val = rrpv[i];
        }
    }
    if(max_val < 7) { 
        for(int i = 0; i < rrpv.size(); i++) {
            rrpv[i] += 7 - max_val;
        }
    }
    return max_idx;
}
