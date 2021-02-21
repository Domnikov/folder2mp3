#pragma once

#include <filesystem>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <list>

namespace folder2cpp
{


class Printer
{
    public:

    static void process(std::filesystem::path&& file)
    {
        static std::mutex lv_mutex;
        std::lock_guard<std::mutex> lock(lv_mutex);
        fprintf(stderr, "%s --> ", file.c_str());
        file.replace_extension(".mp3");
        fprintf(stderr, "%s\n", file.c_str());
    }

    using listType = std::vector<std::filesystem::path>;
};


template <typename Processor>
class ThreadPool final
{
    public:

        static void process(int threadNUmber, typename Processor::listType&& value)
        {
            ThreadPool pool;
            {
                std::lock_guard<std::mutex> lock(pool.m_mutex);
                std::move(value.cbegin(), value.cend(), std::back_inserter(pool.m_queue));
            }
            pool.run(threadNUmber);
        }

    private:

        ThreadPool() = default;


        ~ThreadPool()
        {int  i =0;
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
                m_pool.push_back(std::thread([this, i]{
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
                            Processor::process(std::move(element));
                        }
                    }
                    }));
            }
        }


        std::vector<std::thread> m_pool;
        std::condition_variable m_cond;
        std::list<typename Processor::listType::value_type> m_queue;
        std::mutex m_mutex;

};


using EncoderPool = ThreadPool<Printer>;


} // namespace folder2cpp
