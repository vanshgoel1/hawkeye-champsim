// hawkeye.h
#ifndef HAWKEYE_H
#define HAWKEYE_H
#include "modules.h"
#include "optgen.h"
#include "predictor.h"
#include "rrip.h"
#include "vector"
#include "unordered_map"
#include "cache.h"

#include <iostream>

struct hawkeye : public champsim::modules::replacement {
    // TODO: instantiate different modules
    long NUM_SET, NUM_WAY;
    OPTgen optgen;
    HawkeyePredictor predictor;
    
    // TODO: Add any new data structures or functions to connect each of the modules
    std::vector<std::vector<int>> rrpv;
    std::unordered_map<uint64_t, uint64_t> prev_pc_for_addr;

    // TODO: Complete the definitions for the following functions that are required across all replacement policies. You can use the other replacement policies as a reference. Each should be implemented primarily by calling optgen.access(...), predictor.train(...)/predict(...), and update_rrpv(...)/find_victim(...) from rrip.h, do not re-implement OPTgen/predictor/RRIP logic here.
    // find_victim (args);
    // replacement_cache_fill (args);
    // update_replacement_state (args);

    explicit hawkeye(CACHE* cache);
    hawkeye(CACHE* cache, long sets, long ways);

    long find_victim(uint32_t triggering_cpu, uint64_t instr_id, long set, const champsim::cache_block* current_set, champsim::address ip,
                   champsim::address full_addr, access_type type);
    void replacement_cache_fill(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr,
                              access_type type);
    void update_replacement_state(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr,
                                access_type type, uint8_t hit);
}; 

#endif
