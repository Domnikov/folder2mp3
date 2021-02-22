#pragma once
#include "lame_encoder.hpp"

#include <filesystem>
#include <thread>
#include <mutex>
#include <vector>
#include <list>

namespace folder2cpp
{


template <typename Processor>
class ThreadPool final
{
    public:

        static void process(int threadNUmber, typename Processor::listType&& value, bool verbose)
        {
            ThreadPool pool;
            {
                std::lock_guard<std::mutex> lock(pool.m_mutex);
                std::move(value.cbegin(), value.cend(), std::back_inserter(pool.m_queue));
            }
            pool.m_verbose = verbose;
            pool.run(threadNUmber);
        }

    private:

        ThreadPool() = default;

        ~ThreadPool()
        {
            for(auto& t : m_pool)
            {
                t.join();
            }
        }


        void run(int threadNUmber)
        {
            m_pool.reserve(threadNUmber);

            for(int i = 0; i < threadNUmber; ++i)
            {
                m_pool.push_back(std::thread([this]{
                    bool lv_done = false;

                    while (!lv_done)
                    {
                        typename Processor::listType::value_type element;
                        {
                            std::lock_guard<std::mutex> lock(m_mutex);
                            if(m_queue.size())
                            {
                                element = std::move(m_queue.front());
                                m_queue.pop_front();
                            }
                            else
                            {
                                lv_done = true;
                            }
                        }
                        if (!lv_done)
                        {
                            Processor::process(std::move(element), m_verbose);
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


using EncoderPool = ThreadPool<LameEncoder>;


} // namespace folder2cpp
