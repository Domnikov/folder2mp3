#include "../include/cmd_options.h"
#include "../include/file_list.hpp"
#include "../include/encoder_pool.hpp"
#include "../include/lame_wrapper.h"

#include <iostream>
#include <memory>

namespace
{

constexpr auto VERSION = "0.1.1";

constexpr auto CMD_ERROR = R"(
Using:
    folder2mp3 [OPTION]... [DIRECTORY]...

Options:
    -v, --verbose       explain what is being done
    -t=N, --threads=N   option to configure how many threads use for coding. Default N = CPU number [1..99]
    --version           output version information and exit
)";

}

using namespace folder2cpp;

int main(int argc, const char **argv)
{
    try
    {
        auto lv_options = CmdOptions::getOptions(argc, argv);

        if (lv_options.isVersion())
        {
            std::cout << "folder2mp3 version: " << VERSION <<std::endl;
            std::cout << "Lame (libmp3lame) version: " << LameWrapper::getLameVersion() <<std::endl;
            return 0;
        }

        auto files = FileList::get(lv_options.getPath(), ".wav");

        auto lv_threadNumb = lv_options.getThreadsNumb();
        if (lv_threadNumb < 1)
        {
            lv_threadNumb = std::thread::hardware_concurrency();
        }

        EncoderPool::process(lv_threadNumb, std::move(files), lv_options.isVerbose());
    }
    catch(std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
        std::cout << CMD_ERROR << std::endl;
    }

    return 0;
}
