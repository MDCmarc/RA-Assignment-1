#include <stdint.h>

#include <vector>

class GaltonBoard {
   public:
    GaltonBoard(uint64_t bins, uint64_t balls)
        : bins_(bins, 0), height_(bins - 1), balls_(balls) {};

    void RunAndSave();

   private:
    void SimulateBall();
    void Save();

    std::vector<uint64_t> bins_;  // counters
    const uint64_t height_;
    const uint64_t balls_;
};