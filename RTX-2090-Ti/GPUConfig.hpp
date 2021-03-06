#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <optional>

#include "ImageHandler.hpp"

namespace RTXLib {

// very meme enum
enum class Algorithm {
    CORGI_LEGACY = 69,
    BRIGHTNESS_COMPENSATE = 420,
    CORGI_HSV = 1337,
    BLEND_S = 177013
};

const auto ConfigLists = std::vector<std::string>{
    "Output Video Path", "Output Video Resolution",
    "Output Video FPS",  "Output Video Length Per Loop",
    "Number of Loops",   "Algorithm"};

const auto ConfigDescription = std::vector<std::string>{
    "The path to the output video file.",
    "The resolution of the output video file.",
    "The FPS of the output video file.",
    "The length of each loop in the output video file.",
    "The number of loops to be made in the output video file.",
    "The algorithm to be used in rendering."};

const auto AlgoEnumToString = std::map<Algorithm, std::string>{
    {Algorithm::CORGI_LEGACY, "Corgi Legacy"},
    {Algorithm::BRIGHTNESS_COMPENSATE,
     "Corgi Legacy with Brightness Compensate"},
    {Algorithm::CORGI_HSV, "Corgi HIV"},
    {Algorithm::BLEND_S, "Blend Sukhoi"}};

const auto OutputConfigConstraint = std::vector<std::string>{
    "Path must not be empty!", "Dimension must ...", "FPS must be at least 1",
    "Length must be at least 1 seconds", "Number of loops must be at least 1"};

/**
 * Struct containing configuraions related to output
 *
 * - std::string path: Output path without extensions
 * - std::pair<int, int> dims: xy
 * - int fps
 * - double length: Length per loop
 * - int loops
 * - Algorithm algo
 */
struct OutputConfig {
    // Ordered according to ConfigLists & ConfigDescription
    std::string path
#ifdef _MSC_VER
        = "TEMP"
#endif
        ;
    std::pair<int, int> dims = {480, 480};
    int fps = 30;
    double length = 5.5;
    int loops = 6;
    Algorithm algo = Algorithm::BLEND_S;
    /**
     * Validate the configurations.
     *
     * @returns Reason if failed, std::nullopt if pass
     */
    std::optional<std::string> validate() const;
};

/**
 * Configuration payload for generating video,
 * does not relate to GPU like its name.
 *
 * reminder: everything here is meme.
 */
class GPUConfig {
  public:
    GPUConfig();
    std::string inputPath;
    OutputConfig output;
    std::vector<std::pair<int, int>> warpLocations;

    bool setOutputDims(const std::pair<int, int>& newDims);

    bool setWarpLocations(const std::string& locations);
    bool setWarpLocations(const std::vector<std::pair<int, int>>& locations);
    /**
     * Remove Invalid Warp Locations based on current dims, .
     * automatically added missing warp locations.
     *
     * @returns true if warp locations is changed
     */
    bool validateWarpLocations();
    void resetWarpLocations();
    std::string warpLocationsAsStr() const;
};

}  // namespace RTXLib
