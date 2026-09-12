#ifndef OPTGEN_H
#define OPTGEN_H

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

class OPTgen {
    private:
        std::size_t num_sets, associativity, history_multiplier;
        std::size_t window_len;
        std::vector<std::vector<std::size_t>> occupancy_vector;
        std::vector<std::uint64_t> curr_idx;
        std::vector<std::unordered_map<std::uint64_t,std::uint64_t>> prev_idx;
    public:
    // num_sets: number of cache sets tracked independently
    // associativity: W, the cache associativity (occupancy vector cap)
    // history_multiplier: length of tracked history, in units of the set's
    // capacity (paper uses 8x; see Figure 2), Default 8.
        OPTgen(std::size_t num_sets, std::size_t associativity, std::size_t history_multiplier = 8);
        // Processes one access to `address`, mapped to set `set_idx`, per Section 3.1.
        bool access(std::size_t set_idx, uint64_t address); 
        bool isPresent(std::size_t set_idx, uint64_t address);
};

#endif