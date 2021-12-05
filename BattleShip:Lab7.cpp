// Nick Bennett
// C++ 12-8-21
// Lab 7 - Make a game of battleship

#include <iostream>
#include <iomanip>
using namespace std;
typedef char BOARD [10][10][6];
void WelcomeMessage(bool &again);
//pre: given that the code was started
//post: outputting a welcome to the game and given the option to play or not

void setBoards(BOARD board);
//pre: board outputted to the screen isn't storing any 'M' or 'H' to the broad
//post: filling the board with '~' as the water or blanks

void ScreenBoard(BOARD board ,int player);
//pre: nothing is outputted
//post: shows what what the board looks like for both the player and the computer with 'M' or 'H' or '~'

void shipPlace(BOARD board);
//pre: can't place the ships and doesn't fully know if the placement of the ship is valid or not
//post: places ship if the inputted values for the x, y, and direction are valid

void shipPlaceComputer(BOARD board);
//pre: can't place the ship yet, has to wait for the player to finish first
//post: computer randomly puts ships on the board that are valid

void guessplayer(BOARD board ,int &player ,bool &game ,int &losses);
//pre: player can't guess yet
//post: gives you the chance to fire on the computers board, also given the ability to surrender

void guessComputer(BOARD board);
//pre: waiting until the player has guessed for their turn
//post: computer has fired on the player's board and it is a random shot on the board

void GameUpdate(BOARD board);
//pre: no ships have been destroyed
//post: outputs which ship has been destroyed with both boards of the player and computer boards

void GameFinishCheck(BOARD board ,bool &game ,int &losses ,int &wins);
//pre: either the player or computer have won or lost the game yet
//post: seeing if the ship

void playAgain(bool &again ,int &player ,bool &game);
//pre: ending of the game
//post: Asks you if you want to play again if won,lost, or surrendered and adds to wons or losses

void WinLossBoard(int wins ,int losses);
//pre: is not outputted to the screen
//post: gives player wins and losses when chosen to end the game

int main()
{
    BOARD board; //3D BOARD for keeping track of ships
    bool again = true; // continuing loop for playing again
    bool game = true; // continuing loop if game isn't finished
    int player = 0;
    int wins = 0; // counting wins
    int losses = 0; // counting losses
    WelcomeMessage(again);
    do{
        if(!again)
        {
            break;
        }
        setBoards(board); // setting all boards to have ~ as blanks
        shipPlace(board); // user ship placements
        shipPlaceComputer(board); // computer ship placements
        do{
            GameUpdate(board); // checking the boards to see if any of the ship are destroyed on both the player and the computer sides
            guessplayer(board ,player ,game ,losses); // options for guessing on the board and surrender if chosen
            GameFinishCheck(board ,game ,losses ,wins); // seeing if conditions are met to end the game
                if(!game)
                {
                    break;
                }
            guessComputer(board); // computer is guessing your board
            GameFinishCheck(board , game , losses , wins); // seeing if conditions are met to end the game
                if(!game)
                {
                    break;
                }
            } while(game);
        playAgain(again , player , game); // option the play the game again
    } while(again);
    WinLossBoard(wins , losses); // win loss board comes up after the player choose to end the game
    return 0;
}

void WelcomeMessage(bool &again) // prints welcome message and askes what the player wants to do
{
    char play;
    cout << "Welcome to Battleship! Do you want to play? " << endl << "Press 1 to start" << endl << "Press 2 if you don't want to play"<< endl;
    cin >> play;
    if(play != '1')
    {
        again = false;
    }
    system("clear");
}

void setBoards(BOARD board) // starting boards
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            for(int z = 0; z < 6; z ++)
            {
                board [y][x][z]= '~';
            }
        }
    }
}

void ScreenBoard(BOARD board , int player) // outputting the board to the screen
{
    for(int z = 0; z < player + 2; z++)
    {
        cout << endl;
        cout << "   1 2 3 4 5 6 7 8 9 10 X" << endl;
        for(int y = 0; y < 10; y++)
        {
            cout << setw(2) << y +1;
            cout << ' ';
            for(int x = 0; x < 10; x++)
            {
                cout << board [y][x][z] << ' ';
            }
            cout << endl;
        }
    }
}

void shipPlace(BOARD board) // player choose to where to put the ships
{
    char shipType;
    int shipSize;
    int yPosition;
    int xPosition;
    int direction;
    for(int c = 0; c < 5; c++)
    {
        bool print = true;
        ScreenBoard(board , 0);
        switch(c)
        {
            case 0:
            shipSize = 5;
            shipType = '5';
            cout << endl << "Place carrier ship (5 spaces) " << endl;
            break;
                
            case 1:
            shipSize = 4;
            shipType = '4';
            cout << endl << "Place battleship (4 spaces) " << endl;
            break;
                
            case 2:
            shipSize = 3;
            shipType = '3';
            cout << endl << "Place cruiser ship (3 spaces) " << endl;
            break;
                
            case 3:
            shipSize = 3;
            shipType = '2';
            cout << endl << "Place submarine ship (3 spaces) " << endl;
            break;
            
            case 4 :
            shipSize = 2;
            shipType = '1';
            cout << endl << "Place destroyer ship (2 spaces) " << endl;
            break;
        }
        cout << "X axis: ";
        cin >> xPosition;
        if(xPosition > 10 || xPosition <= 0)
        {
            system("clear");
            cout << "Invalid" << endl;
            c--;
            continue;
        }
        cout << "Y axis: ";
        cin >> yPosition;
        if(yPosition > 10 || yPosition <= 0)
        {
            system("clear");
            cout << "Invalid" << endl;
            c--;
            continue;
        }
        cout << "Direction of the ship: Left 1 Right 2 Down 3 Up 4 ";
        cin >> direction;
        for(int x = 0; x < shipSize; x++)
        {
            if(direction == 1)
            {
                if(board [yPosition-1][xPosition-1-x][1] == '#')
                {
                    system("clear");
                    cout << "Invalid" << endl;
                    c--;
                    print = false;
                }
            } else
                if(direction == 2)
                {
                if(board [yPosition-1][xPosition-1+x][1] == '#')
                    {
                        system("clear");
                        cout << "Invalid" << endl;
                        c--;
                        print = false;
                    }
            } else
                if(direction == 3)
                {
                if(board [yPosition-1+x][xPosition-1][1] == '#')
                    {
                        system("clear");
                        cout << "Invalid" << endl;
                        c--;
                        print = false;
                    }
                } else
                if(direction == 4)
                {
                if(board [yPosition-1-x][xPosition-1][1] == '#')
                    {
                        system("clear");
                        cout << "Invalid" << endl;
                        c--;
                        print = false;
                    }
                } else
                if(board [yPosition-1][xPosition-1+x][1] == '#')
                {
                    system("clear");
                    cout << "Invalid" << endl;
                    c--;
                    print = false;
                }
            if(!print)
            {
                break;
            }
        }
        for(int x = 0; x < shipSize; x++)
        {
            if(direction == 1)
            {
                if(xPosition-1-x < 0)
                {
                    system("clear");
                    cout << "Invalid" << endl;
                    c--;
                    print = false;
                }
            } else
                if(direction == 2)
                {
                    if(xPosition-1+x > 9)
                    {
                        system("clear");
                        cout << "Invalid" << endl;
                        c--;
                        print = false;
                    }
                } else
                    if(direction == 3)
                    {
                        if(yPosition-1+x > 9)
                        {
                            system("clear");
                            cout << "Invalid" << endl;
                            c--;
                            print = false;
                        }
            } else
                if(direction == 4)
                {
                    if(yPosition-1-x < 0)
                    {
                        system("clear");
                        cout << "Invalid" << endl;
                        c--;
                        print = false;
                    }
            } else
                {
                if(xPosition-1+x > 9)
                {
                    system("clear");
                    cout << "Invalid" << endl;
                    c--;
                    print = false;
                }
            }
            if(!print)
            {
                break;
            }
        }
        if(print)
        {
            for(int x = 0; x < shipSize; x++)
            {
                if(direction == 1)
                {
                    board [yPosition-1][xPosition-1-x][1] = '#';
                    board [yPosition-1][xPosition-1-x][4] = shipType;
                } else
                    if(direction == 2)
                    {
                    board [yPosition-1][xPosition-1+x][1] = '#';
                    board [yPosition-1][xPosition-1+x][4] = shipType;
                    } else
                        if(direction == 3)
                                {
                                board [yPosition-1+x][xPosition-1][1] = '#';
                                board [yPosition-1+x][xPosition-1][4] = shipType;
                                } else
                                    if(direction == 4)
                                    {
                                    board [yPosition-1-x][xPosition-1][1] = '#';
                                    board [yPosition-1-x][xPosition-1][4] = shipType;
                                    } else
                                        board [yPosition-1][xPosition-1+x][1] = '#';
                                        board [yPosition-1][xPosition-1+x][4] = shipType;
            }
            system("clear");
        }
    }
}

void shipPlaceComputer(BOARD board) // randomly places ships on the board, also checking for overlap
{
    char shipType;
    int shipSize;
    int yPosition;
    int xPosition;
    int direction;
    cout << "The computer has placed their ships. " << endl << endl;
    for(int c = 0; c < 5; c++)
    {
        bool print = true;
        switch(c)
        {
            case 0:
            shipSize = 5;
            shipType = '5';
            break;
                
            case 1:
            shipSize = 4;
            shipType = '4';
            break;
                
            case 2:
            shipSize = 3;
            shipType = '3';
            break;
                
            case 3:
            shipSize = 3;
            shipType = '2';
            break;
                
            case 4:
            shipSize = 2;
            shipType = '1';
            break;
        }
        srand(time(NULL));
        xPosition = rand() %10+1;
        if(xPosition > 10 || xPosition <= 0)
        {
            c--;
            continue;
        }
        yPosition = rand() %10+1;
        if(yPosition > 10 || yPosition <= 0)
        {
            c--;
            continue;
        }
        direction = rand() %4+1;
        for(int x = 0; x < shipSize; x++)
        {
            if(direction == 1)
            {
                if(board [yPosition-1][xPosition-1-x][3] == '#')
                {
                    c--;
                    print = false;
                }
            } else
                if(direction == 2)
                {
                    if(board [yPosition-1][xPosition-1+x][3] == '#')
                    {
                        c--;
                        print = false;
                    }
            } else
                if(direction == 3)
                {
                    if(board [yPosition-1+x][xPosition-1][3] == '#')
                    {
                        c--;
                        print = false;
                    }
            } else
                if(direction == 4)
                {
                    if(board [yPosition-1-x][xPosition-1][3] == '#')
                        {
                            c--;
                            print = false;
                        }
            } else
                if(board [yPosition-1][xPosition-1+x][3] == '#')
                {
                    c--;
                    print = false;
                }
            
            if(!print)
            {
                break;
            }
        }
        for(int x = 0; x < shipSize; x++)
        {
            if(direction == 1)
            {
                if(xPosition-1-x < 0)
                {
                    c--;
                    print = false;
                }
            } else
                if(direction == 2)
                {
                    if(xPosition-1+x > 9)
                    {
                        c--;
                        print = false;
                    }
            } else
                if(direction == 3)
                {
                    if(yPosition-1+x > 9)
                    {
                        c--;
                        print = false;
                    }
            } else
                if(direction == 4)
                {
                    if(yPosition-1-x < 0)
                    {
                        c--;
                        print = false;
                    }
            } else
                if(xPosition-1+x > 9)
                {
                    c--;
                    print = false;
                    break;
                }
            
            if(!print)
            {
                break;
            }
        }
        if(print)
        {
            for(int x = 0; x < shipSize; x++)
            {
                if(direction == 1)
                {
                    board [yPosition-1][xPosition-1-x][3] = '#';
                    board [yPosition-1][xPosition-1-x][5] = shipType;
                } else
                    if(direction == 2)
                    {
                        board [yPosition-1][xPosition-1+x][3] = '#';
                        board [yPosition-1][xPosition-1+x][5] = shipType;
                    } else
                        if(direction == 3)
                        {
                            board [yPosition-1+x][xPosition-1][3] = '#';
                            board [yPosition-1+x][xPosition-1][5] = shipType;
                        } else
                            if(direction == 4)
                            {
                                board [yPosition-1-x][xPosition-1][3] = '#';
                                board [yPosition-1-x][xPosition-1][5] = shipType;
                            } else
                                board [yPosition-1][xPosition-1+x][3] = '#';
                                board [yPosition-1][xPosition-1+x][5] = shipType;
                
            }
        }
    }
    system("clear");
}

void GameFinishCheck(BOARD board , bool &game , int &losses , int &wins) // checking to see if the player or computer have destroyed all of the enemies ships
{
    int carrier = 0;
    int battleship = 0;
    int cruiser = 0;
    int submarine = 0;
    int destroyer = 0;
    int computercarrier = 0;
    int computerbattleship = 0;
    int computercruiser = 0;
    int computersubmarine = 0;
    int computerdestroyer = 0;
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(board [y][x][4]== '5')
            {
                carrier++;
            } else
                if(board [y][x][4]== '4')
                {
                    battleship++;
                } else
                    if(board [y][x][4]== '3')
                    {
                        cruiser++;
                    } else
                        if(board [y][x][4]== '2')
                        {
                            submarine++;
                        } else
                            if(board [y][x][4]== '1')
                            {
                                destroyer++;
                            }
        }
    }
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(board [y][x][5]== '5')
            {
                computercarrier++;
            } else
                if(board [y][x][5]== '4')
                {
                    computerbattleship++;
                } else
                    if(board [y][x][5]== '3')
                    {
                        computercruiser++;
                    } else
                        if(board [y][x][5]== '2')
                        {
                            computersubmarine++;
                        } else
                            if(board [y][x][5]== '1')
                            {
                                computerdestroyer++;
                            }
        }
    }
    if(carrier == 0 && battleship == 0 && cruiser == 0
        && submarine == 0 && destroyer == 0)
        {
            system("clear");
            cout << "All of your were ships destroyed. You lost!" << endl;
            losses++;
            game = false;
        }
    if(computercarrier == 0 && computerbattleship == 0 && computercruiser == 0
        && computersubmarine == 0 && computerdestroyer == 0)
        {
            system("clear");
            cout << "You destroyed all of the computers ships. You win!" << endl;
            wins++;
            game = false;
        }
}

void GameUpdate(BOARD board) // checking to see if any of the ships have been destoryed from both the player and computer board's
{
    int carrier = 0;
    int battleship = 0;
    int cruiser = 0;
    int submarine = 0;
    int destroyer = 0;
    int computercarrier = 0;
    int computerbattleship = 0;
    int computercruiser = 0;
    int computersubmarine = 0;
    int computerdestroyer = 0;
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(board [y][x][4]== '5')
            {
                carrier++;
            } else
                if(board [y][x][4]== '4')
                {
                battleship++;
                }else
                    if(board [y][x][4]== '3')
                    {
                        cruiser++;
                    } else
                        if(board [y][x][4]== '2')
                        {
                            submarine++;
                        } else
                            if(board [y][x][4]== '1')
                            {
                                destroyer++;
                            }
        }
    }
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(board [y][x][5]== '5')
            {
                computercarrier++;
            } else
                if(board [y][x][5]== '4')
                {
                    computerbattleship++;
                } else
                    if(board [y][x][5]== '3')
                    {
                        computercruiser++;
                    } else
                    if(board [y][x][5]== '2')
                    {
                        computersubmarine++;
                    } else
                        if(board [y][x][5]== '1')
                        {
                            computerdestroyer++;
                        }
        }
    }
    if(carrier == 0)
    {
        cout << "Carrier has been destroyed!" << endl;
    }
    if(battleship == 0)
    {
        cout << "Battleship has been destroyed!" << endl;
    }
    if(cruiser == 0)
    {
        cout << "Cruiser has been destroyed!" << endl;
    }
    if(submarine == 0)
    {
        cout << "Submarine has been destroyed!" << endl;
    }
    if(destroyer == 0)
    {
        cout << "Destroyer has been destroyed!" << endl;
    }
    if(computercarrier == 0)
    {
        cout << "Computer's carrier was destroyed!" << endl;
    }
    if(computerbattleship == 0)
    {
        cout << "Computer's battleship was destroyed!" << endl;
    }
    if(computercruiser == 0)
    {
        cout << "Computer's cruiser was destroyed!" << endl;
    }
    if(computersubmarine == 0)
    {
        cout << "Computer's submarine was destroyed!" << endl;
    }
    if(computerdestroyer == 0)
    {
        cout << "Computer's destroyer was destroyed!" << endl;
    }
}

void guessplayer(BOARD board , int &player , bool &game , int &losses) // player gets to fire at the computer's board
{
    int gy;
    int gx;
    bool valid = false;
    ScreenBoard(board ,player);
    cout << endl << "Your turn!" << endl << endl;
    cout << "Enter 111 to surrender." << endl;
    do {
        do {
            cout << "User X axis: ";
            cin >> gx;
            if(gx == 1234)
            {
                player = 2;
            } else
                if(gx == 4321)
                {
                    player = 0;
                } else
                    if(gx == 111 || !cin)
                    {
                        game = false;
                        cout << "Surrendered!" << endl;
                        losses++;
                        valid = true;
                    }
            if(gx <= 10 && gx > 0)
            {
                valid = true;
                gx -= 1;
            } else
                if(gx != 111)
                {
                    cout << "Invalid" << endl;
                }
        } while
           (!valid);
            valid = false;
            do {
                if(gx != 111)
                {
                    cout << "User Y axis: ";
                    cin >> gy;
                } else
                valid = true;
            if(gy <= 10 && gy > 0)
            {
                valid = true;
                gy -= 1;
            } else
                cout << "Invalid" << endl;
        } while
            (!valid);
            valid = false;
            if(gx == 111)
                {
                    valid = true;
                } else
                    if((board [gy][gx][0] == 'M') ||(board [gy][gx][0] == 'H'))
                    {
                        cout << "Invalid" << endl;
                    } else
                        valid = true;
    } while(!valid);
    if(gx != 111)
    {
        if(board [gy][gx][3] == '#')
        {
            board [gy][gx][0] = 'H';
            board [gy][gx][3] = 'H';
            cout << "Hit!" << endl << endl;
        } else
        {
            board [gy][gx][0] = 'M';
            board [gy][gx][3] = 'M';
            cout << "Miss!" << endl << endl;
        }
    }
    if(gx == 111)
    {
        gx = 1;
        gy = 1;
    }
        board [gy][gx][5] = 'X';
}

void guessComputer(BOARD board) // computer randomly guesses to hit the players board
{
    int gy;
    int gx;
    bool valid = false;
    system("clear");
    do {
        do {
            gx = rand() % 10 + 1;
            if(gx <= 10 && gx > 0)
            {
                valid = true;
                gx -= 1;
            }
        } while
           (!valid);
            valid = false;
            do {
                gy = rand() % 10+1;
                if(gy <= 10 && gy > 0)
                    {
                        valid = true;
                        gy -= 1;
                    }
                } while
                   (!valid);
                    valid = false;
                    if((board [gy][gx][2] == 'M') ||(board [gy][gx][2] == 'H'))
                    {
                        valid = false;
                    } else
                        valid = true;
        
    } while
   (!valid);
    cout << "Computer : " << "X - " << gx+1 << " Y - " << gy+1 << endl;
    if(board [gy][gx][1] == '#')
    {
        board [gy][gx][2] = 'H';
        board [gy][gx][1] = 'H';
        cout << "Hit!" << endl << endl;
    } else
    { board [gy][gx][2] = 'M';
        board [gy][gx][1] = 'M';
        cout << "Miss!" << endl << endl;
    }
        board [gy][gx][4] = 'X';
}

void playAgain(bool &again , int &player , bool &game)
{
    char play;
    system("clear");
    cout << "Do you want to play again?" << endl << "Press 1 to play again" << endl << "Press 2 if you don't want to play again"<< endl;;
    cin >> play;
    if(play != '1')
    {
        again = false;
    } else
        player = 0;
        game = true;
        system("clear");
    
}

void WinLossBoard(int wins , int losses)
{
    system("clear");
    cout << endl << endl;
    cout << "You won " << wins << " times." << endl;
    cout << "You lost " << losses << " times." << endl;
   
}
