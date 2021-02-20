#pragma once

namespace folder2cpp
{

class CmdOptions final
{
public:
    static CmdOptions getOptions(int argc, const char **argv);

    bool  isVerbose     () { return m_verbose    ; }
    bool  isVersion     () { return m_version    ; }
    int   getThreadsNumb() { return m_threadsNumb; }
    const char* getPath       () { return m_path       ; }

private:
    CmdOptions() = default;

    bool  m_verbose     = false  ;
    bool  m_version     = false  ;
    int   m_threadsNumb = -1     ;
    const char* m_path        = nullptr;
};

} // namespace folder2cpp::CmdOptions
