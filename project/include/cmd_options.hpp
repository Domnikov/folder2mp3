/**
 * \file cmd_options.hpp
 * \author Domnikov Ivan
 * \copyright © Domnikov Ivan 2021
 * File contans class CmdOptions for checking all command line options and return as an object with read options as its members
 *
 */
#pragma once

#include <string_view>

namespace folder2cpp
{


/**
 * @brief This class proides convinient way to convert command line options into an object
 *
 * To create class instance need to call its static method getOptions with parameters given in main function.
 * As a result it will return CmdOptions object instance. This object does nopt allocate any resources.
 * Instance of this class must not live longer then 'const char **argv'
 * because folder location path stores as string_view with pointer to last argv.
 * If argv will be invalid then CmdOptions::getPath will return invalid std::string_view
 *
 */
class CmdOptions final
{
    public:

        /**
         * \brief Method to get CmdOption instance from main function arguments
         *
         * This function will throw std::runtime_error exception if arguments is wrong
         *
         * \param Number of arguments
         * \param Array to arguments
         * \returns CmdOption object
         */
        static CmdOptions getOptions(int argc, const char **argv);


        /**
         * \brief Return true if verbose flag ('-v' or '--verbose') was given
         */
        bool  isVerbose()const noexcept { return m_verbose; }


        /**
         * \brief Return true if version flag ('--version') was given
         */
        bool  isVersion()const noexcept { return m_version; }


        /**
         * \brief Return number of threads from '-t=N' or '--threads=N'
         *
         * Default value is -1. Then need to use another way to find how many thread need to create
         */
        int   getThreadsNumb()const noexcept { return m_threadsNumb; }


        /**
         * \brief Get path of folder where files for encodding is locating
         *
         * Returns value is a std::string_view with pointing to last argv as its buffer.
         * Need to be sure the argv will leave longer then CmdOptions object.
         */
        std::string_view getPath () const noexcept { return m_path; }

    private:
        CmdOptions() = default;

        /**
         * \brief Maximum number of thread which application can consume
         */
        static constexpr auto MAXIMUM_THREADS = 99;

        bool  m_verbose     = false;
        bool  m_version     = false;
        int   m_threadsNumb = -1   ;

        std::string_view m_path;
};

} // namespace folder2cpp
