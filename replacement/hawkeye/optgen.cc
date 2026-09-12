#include "optgen.h"

OPTgen::OPTgen(std::size_t num_sets, std::size_t associativity, std::size_t history_multiplier)
    : num_sets(num_sets), associativity(associativity), history_multiplier(history_multiplier) {
        window_len = history_multiplier * associativity;
        curr_idx.assign(num_sets, 0);
        occupancy_vector.assign(num_sets, std::vector<std::size_t>(window_len, 0));
        prev_idx.resize(num_sets);
    } 

bool OPTgen::access(std::size_t set_idx, uint64_t address) {
    std::uint64_t curr = curr_idx[set_idx];
    bool hit = false;
    if(isPresent(set_idx, address)) {
        std::uint64_t prev = prev_idx[set_idx][address];
        hit = true;
        for(uint64_t i = prev; i < curr; i++) {
            if(occupancy_vector[set_idx][i % window_len] == associativity) {
                hit = false; break;
            }
        }
        for(uint64_t i = prev; i < curr && hit; i++) {
            occupancy_vector[set_idx][i % window_len]++;
        }
    }
    curr_idx[set_idx]++;
    prev_idx[set_idx][address] = curr;
    occupancy_vector[set_idx][curr % window_len] = 0;
    return hit;
}

bool OPTgen::isPresent(std::size_t set_idx, uint64_t address) { 
    return prev_idx[set_idx].find(address) != prev_idx[set_idx].end() && curr_idx[set_idx] - prev_idx[set_idx][address] <= window_len;
}