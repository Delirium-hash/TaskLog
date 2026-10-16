#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

// Task structure: unique ID (assigned by TaskLog), name, due date, priority and Done/Not Done status
struct Task
{
    // Enum class defining priority levels
    enum class Priority
    {
        LOW,
        MEDIUM,
        HIGH
    };

    struct Date
    {
        int day;
        int month;
        int year;

        Date()
        : day(0), month(0), year(0)
        {}

        Date(int newDay, int newMonth, int newYear)
        : day(newDay), month(newMonth), year(newYear)
        {}

        // Prints the date in the format DD.MM.YYYY (day and month zero-padded to 2 digits)
        void Print(std::ostream& out = std::cout) const
        {
            out << std::setfill('0')
                << std::setw(2) << day << "."
                << std::setw(2) << month << "."
                << year
                << std::setfill(' ');
             
        }
    };

    int Task_Id;
    std::string Task_Name;
    Date Task_Due_Date;
    Priority Task_Priority;
    bool Task_Done;

    // Constructor of Task: a new task starts as not done and prints a confirmation with its ID
    Task(int newId, std::string name, Date newDate, Priority newPriority)
    : Task_Id(newId), Task_Name(name), Task_Due_Date(newDate), Task_Priority(newPriority), Task_Done(false)
    {}
};