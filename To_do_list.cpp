//included Libraries
#include <iostream>
#include <limits>

//included files
#include "Task.h"
#include "TaskLog.h"

int main()
{
    srand(time(nullptr));
    TaskLog log;
    int choice;

    do{
        std::cout << "\n 1 - Add Task\n 2 - View Tasks\n 3 - Change Task to FININSHED\n 4 - Delete FININSHED Tasks\n 5 - Exit\n" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            log.Task_Add();
            break;
        case 2:
            log.Task_View();
            break;
        case 3:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            log.Task_Mark_As_Finished();
            break;
        case 4:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            log.Task_Delete_Finished();
            break;
        case 5:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Wrong NUmber" << std::endl;
        }

    }
    while (choice != 5);
    



}