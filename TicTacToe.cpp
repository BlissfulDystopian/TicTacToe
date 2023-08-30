#include <iostream>

// PR :
// Interface Gameplay

enum GameStatus 
{ 
    InProgress, 
    Draw, 
    Win
};

enum Symbol { 
    Blank,
    O,
    X,
};

//  Interface 
class Board {
protected :    
    int size;
public :
    virtual Symbol GetMarkInsideCell(int, int) = 0;
    
    virtual bool Mark(int, const Symbol&) = 0;
    
    virtual int GetSize() = 0;
};

class ThreeByThreeBoard : public Board {
    Symbol board[3][3];
public :
    ThreeByThreeBoard() {
        size = 3;
        Initialize(); 
    }
    
    void Initialize() { 
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                board[i][j] = Blank;
            }
        }
    }
    
    Symbol GetMarkInsideCell(int i, int j) override {
        return board[i][j];
    }
    
    bool Mark(int index, const Symbol& currentPlayersMark) override {
        if(index >= 0 && index <= size * size) {
            if(board[(index - 1) / size][(index - 1)  % size] == Blank) {
                board[(index - 1) / size][(index - 1)  % size] = currentPlayersMark;
                return true;
            } else {
                std::cout << "Move invalid, cell are marked!\n";
                return false;
            }
            std::cout << "Move invalid, index must bigger than 0 and not bigger than " << size * size << std::endl;
        } else return false;
    }
    int GetSize() override { return size; }
};

class FourByFourBoard : public Board {
    Symbol board[4][4];
public :
    FourByFourBoard() {
        size = 4;
        Initialize(); 
    }
    
    void Initialize() { 
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                board[i][j] = Blank;
            }
        }
    }
    
    Symbol GetMarkInsideCell(int i, int j) override {
        return board[i][j];
    }
    
    bool Mark(int index, const Symbol& currentPlayersMark) override {
        if(index >= 0 && index <= size * size) {
            if(board[(index - 1) / size][(index - 1)  % size] == Blank) {
                board[(index - 1) / size][(index - 1)  % size] = currentPlayersMark;
                return true;
            } else {
                std::cout << "Move invalid, cell are marked!\n";
                return false;
            }
            std::cout << "Move invalid, index must bigger than 0 and not bigger than " << size * size << std::endl;
        } else return false;
    }
    
    int GetSize() override { return size; }
};

class FiveByFiveBoard : public Board {
    Symbol board[5][5];
public :
    FiveByFiveBoard() {
        size = 5;
        Initialize(); 
    }
    
    void Initialize() { 
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                board[i][j] = Blank;
            }
        }
    }
    
    Symbol GetMarkInsideCell(int i, int j) override {
        return board[i][j];
    }
    
    bool Mark(int index, const Symbol& currentPlayersMark) override {
        if(index >= 0 && index <= size * size) {
            if(board[(index - 1) / size][(index - 1)  % size] == Blank) {
                board[(index - 1) / size][(index - 1)  % size] = currentPlayersMark;
                return true;
            } else {
                std::cout << "Move invalid, cell are marked!\n";
                return false;
            }
            std::cout << "Move invalid, index must bigger than 0 and not bigger than " << size * size << std::endl;
        } else return false;
    }
    
    int GetSize() override { return size; }
};
class DisplayManager {
public :
    static void PrintHowToPlay(Board * const board) {
        int flag = 1;
        
        // Upper border
            std::cout << "\n-";
            for(int i = 0; i < board->GetSize(); ++i) {
                std::cout << "----";
            }
            std::cout << std::endl;
        
        for(int i = 0; i < board->GetSize(); ++i) {
            std::cout << "|";
            
            for(int j = 0; j < board->GetSize(); ++j) {
                std::cout << " " << flag << " |";
                flag++;
            }        
            
            // Lower border
            std::cout << "\n-";
            for(int i = 0; i < board->GetSize(); ++i) {
                std::cout << "----";
            }
            std::cout << std::endl;
        }
    }

    static void PrintBoard(Board* const board) { 
        // Upper Border
        std::cout << "\n-";
        for(int i = 0; i < board->GetSize(); ++i) {
            std::cout << "----";
        }
        std::cout << std::endl;

        // Grid
        for(int i = 0; i < board->GetSize(); ++i) {
            std::cout << "|";
            for(int j = 0; j < board->GetSize(); ++j){
                if(board->GetMarkInsideCell(i, j) == Blank)
                    std::cout << "   |";
                else if(board->GetMarkInsideCell(i, j) == O)
                    std::cout << " O |";
                else    
                    std::cout << " X |";
            }
            
            // Lower border
            std::cout << "\n-";
            for(int k = 0; k < board->GetSize(); ++k) {
                std::cout << "----";
            }
            std::cout << std::endl;
        }
    }
};

class Player {
    Symbol symbol;
public :
    Player() { }
    
    Player(Symbol symbol) : symbol(symbol) { }
    
    Symbol GetSymbol() { return symbol; }
    
    int Move() {
        int input;
        if(symbol == O) {
            std::cout << "O's turn\n";

        } else std::cout << "X's turn\n";

        std::cout << "At what index you wanna move? ";
        std::cin >> input;
        return input;
    }
    
    void PrintSymbol() {
        if(symbol == O)
            std::cout << "O";
        else
            std::cout << "X";
    }
};

class GameManager {
    GameStatus currentGameStatus;
    unsigned short markCount;
public :
    GameManager() : markCount(0) { }
    
    void SetGameStatus(GameStatus status) {
        currentGameStatus = status;
    }
    
    GameStatus GetGameStatus() { return currentGameStatus; }

    unsigned short GetMarkCount() { return markCount; }

    void AddMarkCount() { ++markCount; }

    void WinCheck(int moveIndex, Symbol currentPlayerMark, Board* board) {
        // index segregation
        int x = (moveIndex - 1) / board->GetSize();
        int y = (moveIndex - 1) % board->GetSize();
        
        // Vertical
        for(int i = 0; i < board->GetSize(); ++i) {
            if(board->GetMarkInsideCell(x, i) != currentPlayerMark)
                break;
            if(i == board->GetSize() - 1) {
                currentGameStatus = Win;
            }
        }

        // Horizontal
        for(int i = 0; i < board->GetSize(); ++i) {
            if(board->GetMarkInsideCell(i, y) != currentPlayerMark)
                break;
            if(i == board->GetSize() - 1)
                currentGameStatus = Win;
        }

        // Diagonal
        if(x == y) {
            for(int i = 0; i < board->GetSize(); ++i) {
                if(board->GetMarkInsideCell(i, i) != currentPlayerMark)
                    break;
                if(i == board->GetSize() - 1)
                    currentGameStatus = Win;
            }
        }
        // Anti-Diagonal
        if(x + y == board->GetSize() - 1) {
            for(int i = 0; i < board->GetSize(); ++i) {
                if(board->GetMarkInsideCell(i, (board->GetSize() - 1) - i) != currentPlayerMark)
                break;
                if(i == board->GetSize())
                    currentGameStatus = Win;
            }
        }
    }
};

class TicTacToe {
    Board* board;
    Player playerOne, playerTwo, *currentPlayer;
    GameManager currentGameManager;
public :
    TicTacToe() {
        board = BoardSelection();
        playerOne = SymbolSelection();
        playerTwo = (playerOne.GetSymbol() == O) ? X : O;
        ChooseFirstTurn();
        currentGameManager.SetGameStatus(InProgress);
    }
    
    Board* BoardSelection() {
        std::cout << "Choose board :\n1. 3x3\n2. 4x4\n3. 5x5\n";
        int input; std::cin >> input;

        if(input == 1) 
            return new ThreeByThreeBoard();

        else if (input == 2) 
            return new FourByFourBoard();
        
        else return new FiveByFiveBoard();
    }
    
    Player SymbolSelection() {
        std::cout << "Choose your symbol :\n1. O\n2. X\n";
        unsigned short input;
        std::cin >> input;

        if(input == 1)
            return Player(O);
        else
            return Player(X);
    }
    
    void ChooseFirstTurn() {
        std::cout << "Who play first?\n1. O\n2. X\n";
        unsigned short input;
        std::cin >> input;
        if(input == 1) {
            currentPlayer = (playerOne.GetSymbol() == O) ? &playerOne : &playerTwo;
        } else { 
            currentPlayer = (playerOne.GetSymbol() == X) ? &playerOne : &playerTwo;
        }
    }
    
    void Begin() {
        bool isValidMovement = false;
        int moveIndex;
        while(currentGameManager.GetGameStatus() == InProgress) {
            DisplayManager::PrintHowToPlay(board);
            DisplayManager::PrintBoard(board);
            // Marking
            moveIndex = currentPlayer->Move();
            isValidMovement = board->Mark(moveIndex, currentPlayer->GetSymbol());
            // Jika marking tidak valid
            if(!isValidMovement) {
                system("cls");
                continue;
            } else {
                currentGameManager.AddMarkCount();

                // Jika markCount lebih dari ukuran board + 1
                if(currentGameManager.GetMarkCount() >= board->GetSize() + board->GetSize() - 1) {
                    // WinCheck
                    currentGameManager.WinCheck(moveIndex, currentPlayer->GetSymbol(), board);
                }

                // Jika Board penuh
                if(currentGameManager.GetMarkCount() == board->GetSize() * board->GetSize())
                    currentGameManager.SetGameStatus(Draw);
                
                // Jika bukan menang
                if(currentGameManager.GetGameStatus() != Win);
                    currentPlayer = (currentPlayer->GetSymbol() == playerOne.GetSymbol()) ? &playerTwo : &playerOne;
                
                isValidMovement = false;
                system("cls");
            }
        }
        DisplayManager::PrintBoard(board);
        std::cout << "\n";
        if(currentGameManager.GetGameStatus() == Win) {
            currentPlayer->PrintSymbol();
            std::cout << " win the match!\n";
        } else
            std::cout << "The game is ended, no one win this match :|\n";

        delete board;
    }
};

int main() {
    TicTacToe game1;
    game1.Begin();
    return 0;
}