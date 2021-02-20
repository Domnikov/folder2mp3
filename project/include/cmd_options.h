#pragma once

#include <string_view>

namespace folder2cpp
{

class CmdOptions final
{
public:
    static CmdOptions getOptions(int argc, const char **argv);

    bool  isVerbose     () { return m_verbose    ; }
    bool  isVersion     () { return m_version    ; }
    int   getThreadsNumb() { return m_threadsNumb; }
    std::string_view getPath       () { return m_path       ; }

private:
    CmdOptions() = default;

    bool  m_verbose     = false  ;
    bool  m_version     = false  ;
    int   m_threadsNumb = -1     ;
    std::string_view m_path      ;
};

} // namespace folder2cpp
