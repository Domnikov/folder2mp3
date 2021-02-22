/**
 * \file encoder_pool.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans ThreadPool class. This class gets container with data and process it with different threads by Processor
 *
 */
#pragma once

#include "lame_encoder.hpp"

#include <filesystem>
#include <thread>
#include <mutex>
#include <vector>
#include <list>

namespace folder2cpp
{


namespace folder2cppImpl
{

/**
 * @brief This class proides convinient way process data in thread pool
 *
 * This is template class which can accept any kind of processors.
 * Processor must have 'listType' data type for any kind of container complient with std::back_insert_iterator.
 * Processor data type 'listType' must have 'value_type'
 * Processor must have process(listType::value_type&, bool) static method to process elements one by one.
 * In ThreadPool destructor main thread will join to all other threads. So it will wait until processing last data element
 *
 */
template <typename Processor>
class ThreadPool final
{
    public:

        /**
         * \brief Static method to process given data list
         *
         * This function creates thread pool instance, run threads and wait until last data element will be processed
         * dataList must be moved into ThreadPool.
         *
         * \param Number of threads
         * \param Data list as Processor::listType
         * \returns CmdOption object
         */
        static void process(int threadNUmber, typename Processor::listType&& dataList, bool verbose)
        {
            ThreadPool pool;
            {
                std::lock_guard<std::mutex> lock(pool.m_mutex);
                std::move(dataList.cbegin(), dataList.cend(), std::back_inserter(pool.m_queue));
            }
            pool.m_verbose = verbose;
            pool.run(threadNUmber);
        }


        /**
         * \brief Copy of ThreadPool cannot be created
         */
        ThreadPool(const ThreadPool& ) = delete;


        /**
         * \brief ThreadPool cannot be copied
         */
        ThreadPool& operator=(const ThreadPool& ) = delete;

    private:

        ThreadPool() = default;


        /**
         * \brief ThreadPool destructor. Will join to all threads
         */
        ~ThreadPool()
        {
            for(auto& t : m_pool)
            {
                t.join();
            }
        }


        /**
         * \brief Run method will create threads for data processing
         *
         * \param Number of threads
         */
        void run(int threadNUmber)
        {
            m_pool.reserve(threadNUmber);

            for(int i = 0; i < threadNUmber; ++i)
            {

                // Creating thread
                m_pool.push_back(std::thread([this]{
                    bool lv_done = false;

                    while (!lv_done)
                    {
                        typename Processor::listType::value_type element;
                        {
                            std::lock_guard<std::mutex> lock(m_mutex);
                            if(m_queue.size())
                            {
                                element = std::move(m_queue.back());
                                m_queue.pop_back();
                            }
                            else
                            {
                                lv_done = true;
                            }
                        }
                        if (!lv_done)
                        {
                            try
                            {
                                Processor::process(std::move(element), m_verbose);
                            }
                            catch(std::runtime_error& ex)
                            {
                                fprintf(stderr, "Error: %s\n", ex.what());
                            }
                        }
                    }
                    }));
            }
        }

        bool m_verbose = false;
        std::vector<std::thread> m_pool;
        std::list<typename Processor::listType::value_type> m_queue;
        std::mutex m_mutex;

};
} // namespace folder2cppImpl

/**
 * \brief Nickmane for ThreadPool with LameEncoder as processor
 */
using EncoderPool = folder2cppImpl::ThreadPool<LameEncoder>;


} // namespace folder2cpp
