#include "predictor.h"

HawkeyePredictor::HawkeyePredictor(std::size_t num_entries, int counter_bits)
    : num_entries(num_entries), counter_bits(counter_bits) {
        max_ctr = (1 << counter_bits) - 1;
        msb_checker = (1 << (counter_bits - 1));
        predictor.resize(num_entries, msb_checker);
    }

std::uint64_t HawkeyePredictor::hash(uint64_t pc) const {
    return pc ^ (pc >> 12);
}

void HawkeyePredictor::train(uint64_t pc, bool opt_hit) {
    std::size_t idx = (hash(pc) & (num_entries - 1)); 
    
    if(opt_hit) {
        if(predictor[idx] < max_ctr) predictor[idx]++;
    }
    else {
        if(predictor[idx] > 0) predictor[idx]--;
    }
}

bool HawkeyePredictor::predict(uint64_t pc) const {
    return (get_counter(hash(pc)) & msb_checker) > 0;
}

int HawkeyePredictor::get_counter(uint64_t pc) const {
    std::size_t idx = hash(pc) & (num_entries - 1); 
    return predictor[idx];
}
