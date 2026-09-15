# Hawkeye Cache Replacement Policy in ChampSim
An implementation and evaluation of the Hawkeye cache replacement policy in the ChampSim cache simulator.

# ChampSim
ChampSim is a trace-based simulator for a microarchitecture study. 
For more details on champsim, refer: [ChampSim GitHub Repository](https://github.com/ChampSim/ChampSim)

# Hawkeye 
Hawkeye works like an approximation of Belady's optimal replacement policy. It uses past memory-access behavior to predict whether cache blocks are likely to be reused. It uses these predictions to retain cache-friendly blocks and evict cache-averse blocks.
For more details on the policy, refer to the research paper used in this implementation: ** A. Jain and C. Lin, “Back to the Future: Leveraging Belady’s Algorithm for Improved Cache Replacement,”
ISCA 2016. **
