#include "../include/cmd_options.h"

#include <iostream>

constexpr auto CMD_ERROR = R"(
Using:
    folder2mp3 [OPTION]... [DIRECTORY]...

Options:
    -v, --verbose       explain what is being done
    -t=N, --threads=N   option to configure how many threads use for coding. Default N = CPU number [1..99]
    --version           output version information and exit
)";


int main(int argc, const char **argv)
{
    try
    {
        auto lv_options = CmdOptions::getOptions(argc, argv);
    }
    catch(std::runtime_error& err)
    {
        std::cout << "Command line arguments error: " << err.what() << std::endl;
        std::cout << CMD_ERROR << std::endl;
    }

    return 0;
}
