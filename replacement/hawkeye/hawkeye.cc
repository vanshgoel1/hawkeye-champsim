// hawkeye.cc
#include "hawkeye.h" 
#include <iostream>

hawkeye::hawkeye(CACHE* cache) : hawkeye(cache, cache->NUM_SET, cache->NUM_WAY) {}

hawkeye::hawkeye(CACHE* cache, long sets, long ways)
    :replacement(cache), NUM_SET(sets), NUM_WAY(ways),
    optgen(sets, ways, 8),
    predictor(8192, 3),
    rrpv(sets, std::vector<int>(ways, 0)) {}

// TODO: implement find_victim / replacement_cache_fill / update_replacement_state here, delegating to optgen / predictor / rrip.h as described in hawkeye.h above.

long hawkeye::find_victim(uint32_t triggering_cpu, uint64_t instr_id, long set, const champsim::cache_block* current_set, champsim::address ip, champsim::address full_addr, access_type type) {
    std::size_t victim = ::find_victim(rrpv[set]);
    return victim;
}

void hawkeye::replacement_cache_fill(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr, access_type type) {
    // uint64_t vict_addr = victim_addr.to<uint64_t>();
    // detrain load if eviction is cache friendly and present in window
    // if(optgen.isPresent(set, vict_addr) && predictor.predict(prev_pc_for_addr[vict_addr])){
    //     predictor.train(prev_pc_for_addr[vict_addr], false);
    // }

    uint64_t new_pc = ip.to<uint64_t>();
    
    bool is_cache_friendly = predictor.predict(new_pc);
    Classification cls = is_cache_friendly ? Classification::CACHE_FRIENDLY : Classification::CACHE_AVERSE;
    ::update_rrpv(rrpv[set], way, cls, false);
}

void hawkeye::update_replacement_state(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr, access_type type, uint8_t hit) {
    uint64_t addr = full_addr.to<uint64_t>();
    uint64_t new_pc = ip.to<uint64_t>();

    bool opt_pred = optgen.access(set, addr >> 6);
    if(prev_pc_for_addr.find(addr) != prev_pc_for_addr.end()){
        predictor.train(prev_pc_for_addr[addr], opt_pred);
    }
    prev_pc_for_addr[addr] = new_pc;
    
    if(hit){
        bool is_cache_friendly = predictor.predict(new_pc);
        Classification cls = is_cache_friendly ? Classification::CACHE_FRIENDLY : Classification::CACHE_AVERSE;
        ::update_rrpv(rrpv[set], way, cls, hit);
    }
}

