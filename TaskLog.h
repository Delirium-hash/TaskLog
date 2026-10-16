#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <limits>



// Converts a Priority enum value to a readable string for display
    static const char* Priority_To_String(Task::Priority p)
{
    switch (p)
    {
    case Task::Priority::LOW:    return "LOW";
    case Task::Priority::MEDIUM: return "MEDIUM";
    case Task::Priority::HIGH:   return "HIGH";
    }
    return "UNKNOWN";
}

int shortMonths[4] = {4, 6, 9, 11};
int longMonths[7] = {1, 3, 5, 7, 8, 10, 12};
int february = 2;

struct TaskLog
{
    std::vector<Task> tasks;
    
    

    TaskLog()
    : tasks()
    {Task_Load();}

 

    void Task_Save()
    {
        // Open the file for writing, replacing its previous contents
        std::ofstream taskList("TaskList.txt");

        if (!taskList.is_open())
        {
            std::cout << "Could not open file for saving\n";
            return;
        }

        for (const Task& task : tasks)
        {
            taskList << task.Task_Id << ';'
                    << task.Task_Name << ';'
                    << task.Task_Due_Date.day << ';'
                    << task.Task_Due_Date.month << ';'
                    << task.Task_Due_Date.year << ';'
                    << static_cast<int>(task.Task_Priority) << ';'
                    << task.Task_Done << '\n';
        }

        if (!taskList)
        {
            std::cout << "Error while saving tasks\n";
        }
        taskList.close();
    }

    void Task_Load()
    {
        std::ifstream taskList("TaskList.txt");

        // A missing file is normal on the first launch
        if (!taskList.is_open())
        {
            return;
        }

        tasks.clear();

        std::string line;

        while (std::getline(taskList, line))
        {
            std::stringstream ss(line);
            std::string name;
            std::string field;

            int id, day, month, year, priority, done;

            try
            {
                // Read ID
                if (!std::getline(ss, field, ';'))
                    continue;
                id = std::stoi(field);

                // Read task name (spaces are allowed)
                if (!std::getline(ss, name, ';'))
                    continue;

                // Read date
                if (!std::getline(ss, field, ';'))
                    continue;
                day = std::stoi(field);

                if (!std::getline(ss, field, ';'))
                    continue;
                month = std::stoi(field);

                if (!std::getline(ss, field, ';'))
                    continue;
                year = std::stoi(field);

                // Read priority
                if (!std::getline(ss, field, ';'))
                    continue;
                priority = std::stoi(field);

                // Read completion status
                if (!std::getline(ss, field, ';'))
                    continue;
                done = std::stoi(field);

                // Validate values before creating the task
                if (priority < 0 || priority > 2 ||
                    (done != 0 && done != 1))
                {
                    continue;
                }

                // Reconstruct the Task object
                tasks.emplace_back(
                    id,
                    name,
                    Task::Date(day, month, year),
                    static_cast<Task::Priority>(priority)
                );

                // Restore the completion status
                tasks.back().Task_Done = (done == 1);
            }
            catch (const std::exception&)
            {
                // Skip malformed lines
                continue;
            }
        }
    }

    // Generates a random ID from 1 to 100 that is not used by any existing task
    int Generate_Id()
    {

    if (tasks.size() >= 100)
    {
        return -1; // No IDs available
    }

    int id;

    do
    {
        id = rand() % 100 + 1;
    }
    while (
        // Repeat while the generated ID already belongs to an existing task (IDs must be unique)
        std::any_of(tasks.begin(), tasks.end(),
            [id](const Task& task)
            {
                return task.Task_Id == id;
            })
    );

    return id;
    }

    void Task_Add()
    {
        int id = Generate_Id();
        std::string description;
        int priority;
        int day, month, year;

        // Check whether the maximum number of tasks (100) has been reached. If so, refuse to add more;
        // the user has to delete some tasks first.
        if (tasks.size() >= 100)
        {
            std::cout << "You have reached the maximum amount of tasks. GET TO WORK AND DELETE SOME" << std::endl;
            return;
        }

        // Read the task's name with getline to capture all characters, spaces included.
        // The name is stored in 'description' and passed to the Task constructor.
        
        std::cout << "Enter task's name: ";
        std::getline(std::cin, description);
        std::cout << std::endl;

        //Date handling. I hate my life.
        std::cout << "Set Task's due date (day, month, year)" << std::endl;
        //Day input
        std::cin >> day;

        if (std::cin.fail())
        { 
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std:: cout << "Invalid input" << std::endl;
            return;
        }

        if (day < 1 || day > 31)
        {
            std::cout << "Wrong date. Try again" << std::endl;
            return;
        }
        //Month input
        std::cin >> month;

        if (month < 1 || month > 12)
        {
            std::cout << "Wrong Date. Try again" << std::endl;
            return;
        }
        //Year input
        std::cin >> year;

        if (year < 2026 || year > 2036)
        {
            std::cout << "Wrong Date. Try again" << std::endl;
            return;
        }
        
        //shortening days according to months
        for (int loopMonth : shortMonths)
        {
            if (month == loopMonth && day > 30 )
            { day = 30;}
        }

        if (month == 2 && day > 29)
        {
            if (year % 4 == 0)
            {
                day = 29;
            }
            else
            {
                day = 28;
            }
        }


        do
        {
            std::cout << "Set Task's Priority level (0 - LOW, 1 - MEDIUM or 2 - HIGH) : ";
            std::cin >> priority;

            if (priority < 0 || priority > 2)
            { 
                std::cout << "Wrong priority level" << std::endl;
            }
        } while (priority < 0 || priority > 2);

        tasks.emplace_back(id, description, Task::Date(day, month, year), static_cast<Task::Priority>(priority));
        
        Task_Save();
        std::cout << std::endl << "Task created successfully! Task's ID number is : " << id << std::endl;
    }

    // Prints all current tasks
    void Task_View()
    {
        std::cout << "Current Tasks: " << std::endl;

        for (const Task& task : tasks)
        {
            std::cout << "[ ";
            std::cout << task.Task_Id;
            std::cout << " ; ";
            std::cout << task.Task_Name;
            std::cout << " ; ";
            std::cout << "Priority: " << Priority_To_String(task.Task_Priority);
            std::cout << " ; Due Date: ";
            task.Task_Due_Date.Print();
            std::cout << " ; ";
            if (task.Task_Done == false)
            {
                std::cout << "NOT FINISHED";
            }
            else
            {
                std::cout << "FINISHED";
            }
            std::cout << " ]";
            std::cout << std::endl << std::endl;
        }
    }

    // Loops through the vector looking for a task with the given ID and marks it as finished
    void Task_Mark_As_Finished()
    {   
        int Searched_Task;
        std::cout << "Enter Task's ID: ";
        std::cin >> Searched_Task;

        for (Task& Task_From_Log : tasks)
        {
            if (Searched_Task == Task_From_Log.Task_Id)
            {
                Task_From_Log.Task_Done = true;
                std::cout << "Task marked as done!" << std::endl;
                Task_Save();
                return;
            }
        }
        

        std::cout << "Task is missing. Please, try again!" << std::endl;
    }

    void Task_Delete_Finished()
{
    // Erase-remove idiom: remove_if shifts the unfinished tasks to the front of the vector and returns
    // an iterator to the new logical end; erase then deletes the leftover elements after that point.
    tasks.erase(
        remove_if(tasks.begin(), tasks.end(),
            [](const Task& task)
            {
                return task.Task_Done == true;
            }),
        tasks.end()
    );
    Task_Save();
    std::cout << "Tasks marked as FINISHED deleted!" << std::endl;
}
};

