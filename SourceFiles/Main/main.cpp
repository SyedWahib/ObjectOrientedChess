#include "../../Headers/Board/Board.h"
#include <iostream>
#include <limits>

static void displayInstructions()
{
    std::cout << "\n- Choose 'Start New Game' to begin playing chess\n\n"
        << "- Move pieces by choosing your square in the (column alphabet + integer row) format\n\n"
        << "- All the capital letters are WHITE and the small letters black\n\n"
        << "(For example, A2 when prompted for square to move from, and A4 for the square to move to)\n\n"
        << "- All standard chess moves except en passant can be made\n\n"
        << "- To exit, select the appropriate menu option\n"
        << std::endl;
}

static void displayMenu()
{
   std:: cout << "-------------------------------\n"
              << "      Chess Main Menu      \n"
              << "-------------------------------\n\n"
              << "1. Start New Game \n"
              << "2. View Instructions \n"
              << "3. Exit \n\n"
              << "Enter your choice: \n";
}

static void runGameLoop()
{
    Board chessBoard;
    chessBoard.displayBoard();

    while (chessBoard.movePiece())
    {
        // Runs movepiece until it results in false
    }
}

int main()
{   int choice;
    bool running = true;

    while (running)
    {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail())
        {
            //Clearing input buffer on failed input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std:: cout << "Invalid input. PLease enter a number between 1 and 3 \n\n";
            continue;
        }

        switch(choice)
        {
            case 1:
                runGameLoop();
                break;
            case 2:
                displayInstructions();
                break;
            
            case 3:
                running = false;
                std::cout << "Exiting, Thanks for playing! \n";
                break;
            default:
                std::cout << "Invalid choice. Please select an option from 1 to 3 \n";

        }
        std:: cout << std:: endl;
    }
    return 0;
}