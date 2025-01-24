///////////////////////////////////////////////////////
/// \file version.h
///
///  This header defines the current ZSON configs.
//////////////////////////////////////////////////////

#ifndef ZSON_CONFIGS_H
#define ZSON_CONFIGS_H

#include <iostream>
#include <chrono>
#include <string.h> // for strlen()

namespace zlog

{
    ///////////////////////////////////////////////////////
    /// \file version.h
    ///
    //////////////////////////////////////////////////////
    class System
    {
    private:
        std::string m_Name;
        struct tm m_Time;

        int m_Year;
        int m_Month;
        int m_Day;
        int m_Hour;
        int m_Minute;
        int m_Second;

    public:
        System(/* args */)
        {
            time_t tim = time(NULL);
            m_Time = *localtime(&tim);
            m_Year = m_Time.tm_year + 1900;
            m_Month = m_Time.tm_mon + 1;
            m_Day = m_Time.tm_mday;
            m_Hour = m_Time.tm_hour;
            m_Minute = m_Time.tm_min;
            m_Second = m_Time.tm_sec;
        };

        int year() { return m_Year; };
        int month() { return m_Month; };
        int day() { return m_Day; };
        int hour() { return m_Hour; };
        int min() { return m_Minute; };
        int sec() { return m_Second; };
    };

    class Scoped
    {
        using Clock = std::chrono::high_resolution_clock;
        using Timepoint = std::chrono::time_point<Clock>;

    public:
        /**
         *  @brief  String with Arrow.
         *  @param  name Input Text for String With Arrow.
         */
        Scoped(const char *name)
            : m_Name(name)
        {
            startTimePoint = Clock::now();
        };

        /**
         *  @brief  String with Arrow.
         */
        Scoped()
            : m_Name("")
        {
            startTimePoint = Clock::now();
        };

        ~Scoped()
        {
            auto endTimePoint = Clock::now();
            using namespace std::chrono;

            double duration = duration_cast<milliseconds>(endTimePoint - startTimePoint).count();
            double ms = duration * 0.001f;

            if (strlen(m_Name) == 0)
                std::cout << "Duration :  (" << duration << ")us (" << ms << ")ms ]" << std::endl;
            else
                std::cout << m_Name << " Took : [ Duration: (" << duration << ")us (" << ms << ")ms ]" << std::endl;
        };

    private:
        Timepoint startTimePoint;
        const char *m_Name;
    };

    class Interval
    {
    public:
        using Clock = std::chrono::high_resolution_clock;
        using Timepoint = std::chrono::time_point<Clock>;

        /**
         *  @brief  String with Arrow.
         *  @param  name Input Text for String With Arrow.
         */
        Interval(const char *name);

        /**
         *  @brief  String with Arrow.
         */
        Interval();

        /**
         *  @brief  String with Arrow.
         */
        void start() { m_Start = Clock::now(); };

        /**
         *  @brief  String with Arrow.
         */
        void stop() { m_Stop = Clock::now(); };

        /**
         *  @brief  String with Arrow.
         */
        double getSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_Stop - m_Start).count() * 0.001f * 0.001f;

            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        double getMicroSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_Stop - m_Start).count();
            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        double getMilliSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_Stop - m_Start).count() * 0.001f;
            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outSeconds() const
        {
            double duration = getSeconds();
            if (strlen(m_Name) == 0)
                std::cout << "Duration :  (" << duration << ")s " << std::endl;
            else
                std::cout << m_Name << "Took : [ Duration: (" << duration << ")s " << std::endl;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outMicroSeconds() const
        {
            double duration = getMicroSeconds();

            if (strlen(m_Name) == 0)
                std::cout << "Duration :  (" << duration << ")us " << std::endl;
            else
                std::cout << m_Name << "Took : [ Duration: (" << duration << ")us " << std::endl;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outMilliSeconds() const
        {
            double duration = getMilliSeconds();

            if (strlen(m_Name) == 0)
                std::cout << "Duration :  (" << duration << ")ms " << std::endl;
            else
                std::cout << m_Name << "Took : [ Duration: (" << duration << ")ms " << std::endl;
        };

        operator double() const { return getMilliSeconds(); };

    private:
        Timepoint m_Start;
        Timepoint m_Stop;
        const char *m_Name;
    };
}
#endif /* ZSON_CONFIGS_H */
