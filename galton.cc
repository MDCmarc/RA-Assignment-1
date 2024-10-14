#include "galton.h"

#include <omp.h>

#include <iostream>
#include <random>
#include <fstream>

/**
 * -> Gven 4 bins -> we need 3 pegRows + 1 row for the results. HEGIHT = 3 and
 SIZE = 3*2 +1
 *  | - - - X - - - |  -> We start then at SIZE - 1 / 2 == HEIGHT = 3
 *  | - - X - X - - |  -> For each iteration ( balls goes down one floor from
 prev_i), the posibilities are 50% for it to be  prev_i -1 , prev_i +1 (left or
 right)
 *  | - X - X - X - |
 *  | U - U - U - U | -> We stop when j = HEIGHT and compute its position as
 bin_pos = last_i /2. Then +1 that counter.

 *  | - - - - X - - - - |
 *  | - - - X - X - - - |
 *  | - - X - X - X - - |
 *  | - X - X - X - X - |
 *  | U - U - U - U - U |
 */

// Can be further optimized if we start at position 0 and increase only if <
// 0.5.
//  ---> As step will be 50% even 50% odd, they probability mass will accumulate
//  at the center.
void GaltonBoard::SimulateBall() {
    uint64_t current_height = 0;
    uint64_t position = height_;  // start position

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    while (current_height < height_) {
        position += dist(rng) < 0.5 ? 1 : -1;

        ++current_height;
    }

#pragma omp atomic
    ++bins_[position / 2];
}


void GaltonBoard::Save(){
    char filename[256];
    std::sprintf(filename, "Simulations/simulation_%lu_%lu.csv", (height_ + 1), balls_); // Format: simulation_{height + 1}_{balls}.csv
    std::ofstream file(filename);

    file << "bin,balls\n";
    for (size_t i = 0; i < bins_.size(); ++i) {
        file << i << ", " << bins_[i] << "\n"; // Format: index, value
    }

    file.close();
}


void GaltonBoard::RunAndSave() {
#pragma omp parallel for
    for (uint64_t n = 0; n < balls_; ++n) {
        SimulateBall();
    }
    Save();
}
