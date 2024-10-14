#include <iostream>
#include <stdexcept>

#include "galton.h"

void PrintUsage() {
    std::cout << "Usage: GaltonBoard P1 P2" << std::endl;
    std::cout << "\tParam 1: Number of Bins" << std::endl;
    std::cout << "\tParam 2: Number of Balls" << std::endl;
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        PrintUsage();
        return 1;
    }

    const uint64_t number_of_bins = std::stoull(argv[1]);
    const uint64_t number_of_balls = std::stoull(argv[2]);

    GaltonBoard board(number_of_bins, number_of_balls);
    board.RunAndSave();

    return 0;
}

/**
 *     try
    {
        const uint64_t numberOfBins = std::stoull(argv[1]);
        const uint64_t numberOfBalls = std::stoull(argv[2]);

        // Validate inputs
        if (numberOfBins < 1 || numberOfBalls < 1)
        {
            std::cerr << "Error: The number of bins and balls must be at
 least 1." << std::endl; return 1;
        }

        GaltonBoard board(numberOfBins, numberOfBalls);
        board.Run();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid number format. Please enter valid integers
 for bins and balls." << std::endl; PrintUsage(); return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Number is too large." << std::endl;
        PrintUsage();
        return 1;
    }
 */