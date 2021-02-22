#include "../include/cmd_options.hpp"

#include <cstring>
#include <stdexcept>


using namespace folder2cpp;


CmdOptions CmdOptions::getOptions(int argc, const char **argv)
{
    CmdOptions lv_options;

    // No command line arguments -> exit
    if (argc < 2)
    {
        throw std::runtime_error("Command line arguments error: Require minimum one argument");
    }

    // Check all arguments in a loop except of the last one
    for (int i = 1; i < argc-1; i++)
    {
        // -v or --verbose
        if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose"))
        {
            lv_options.m_verbose = true;
        }

        // --version
        else if (!strcmp(argv[i], "--version"))
        {
            lv_options.m_version = true;
        }

        // -t=N
        else if (strstr(argv[i], "-t=") != nullptr)
        {
            auto lv_threadsNumb = std::atoi( argv[i]+3 );

            if (lv_threadsNumb > 0 && lv_threadsNumb <= MAXIMUM_THREADS)
            {
                lv_options.m_threadsNumb = lv_threadsNumb;
            }
            else
            {
                throw std::runtime_error("Command line arguments error: Number of threads must be 1...99");
            }
        }

        // --threads=N
        else if (strstr(argv[i], "--threads=") != nullptr)
        {
            auto lv_threadsNumb = std::atoi( argv[i]+10 );

            if (lv_threadsNumb > 0 && lv_threadsNumb <= MAXIMUM_THREADS)
            {
                lv_options.m_threadsNumb = lv_threadsNumb;
            }
            else
            {
                throw std::runtime_error("Command line arguments error: Number of threads must be 1...99");
            }
        }

        // Throw an exception if option was not found
        else
        {
            std::string err_str = "Command line arguments error: Wrong command line option: ";
            err_str += argv[i];
            throw std::runtime_error(err_str);
        }
    }

    // Check last argument
    if (!strcmp(argv[argc-1], "--version"))
    {
        lv_options.m_version = true;
    }
    else
    {
        lv_options.m_path = argv[argc-1];
    }

    return lv_options;
}
