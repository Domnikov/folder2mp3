/**
 * \file encoder_pool_tests.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contains unit tests for ThreadPool class
 *
 */
#pragma once

#include "../include/encoder_pool.hpp"

#include "gtest/gtest.h"



namespace folder2cpp::tests
{

using namespace folder2cpp::folder2cppImpl;

int result = 0;
constexpr auto SLEEP_FOR_MS = 10;


/**
 * \brief Small Processor simulation for unit test
 */
class Counter
{
    public:

    static void process(int number, bool)
    {
        static std::mutex lv_mutex;
        {
            std::lock_guard<std::mutex> lock(lv_mutex);
            result += number;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR_MS));
    }

    using listType = std::vector<int>;
};


/**
 * \brief Unit test to check if 10 threads works simultaniosly
 */
TEST(Encoder_Pool_Test, Count_10_threds)
{
    auto lv_start = std::chrono::high_resolution_clock::now();
    ThreadPool<Counter>::process(10, {1,1,1,1,1,1,1,1,1,1}, false);
    auto lv_end = std::chrono::high_resolution_clock::now();

    auto lv_duration = std::chrono::duration_cast<std::chrono::milliseconds>(lv_end - lv_start).count();
    ASSERT_EQ(result, 10) << "sum{1,1,1,1,1,1,1,1,1,1} != 10";
    ASSERT_LE(lv_duration, 1.5*SLEEP_FOR_MS) << "10 threads didn't work simultaniously";
}


/**
 * \brief Unit test to check if 2 threads works simultaniosly and consume all data
 */
TEST(Encoder_Pool_Test, Count_2_threds)
{
    result = 0;
    auto lv_start = std::chrono::high_resolution_clock::now();
    ThreadPool<Counter>::process(2, {1,1,1,1,1,1,1,1,1,1}, false);
    auto lv_end = std::chrono::high_resolution_clock::now();

    auto lv_duration = std::chrono::duration_cast<std::chrono::milliseconds>(lv_end - lv_start).count();
    ASSERT_EQ(result, 10) << "sum{1,1,1,1,1,1,1,1,1,1} != 10";
    ASSERT_LE(lv_duration, 5.5*SLEEP_FOR_MS) << "2 threads didn't work simultaniously";
}

} // namespace folder2cpp::tests
