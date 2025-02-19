//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//

#ifndef JE_PROF_H
#define JE_PROF_H

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <vector>
#include <mutex>
#include <thread>

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    InstrumentationSession *m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
    std::mutex m_lock;

public:
    Instrumentor();

    void BeginSession(const std::string &name, const std::string &filepath = "results.json");

    void EndSession();

    void WriteProfile(const ProfileResult &result);

    void WriteHeader();

    void WriteFooter();

    static Instrumentor &Get();
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char *name);

    ~InstrumentationTimer();

    void Stop();

private:
    const char *m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#endif // JE_PROF_H
