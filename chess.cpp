#include <iostream> 
#include <string> 
using namespace std;

// Structure for defining coordinates on the board as row and coloumn.
struct coordinate{
   int row;
   int coloumn;
   coordinate(){
       row = coloumn = 0;
   }
   coordinate(int x,int y){
       row = x;
       coloumn = y;
   }
};


class Movement{
    
    public:
    // to move one piece from a block to another
    void movePiece(coordinate x, coordinate y, string board[], bool attack){
        if(attack){
            if(abs(int(board[x.row][x.coloumn]) - int(board[y.row][y.coloumn])) < 26){
                cout<<"Can not attack your own.."<<endl;
                return;
            }
        }
        board[y.row][y.coloumn] = board[x.row][x.coloumn];
        board[x.row][x.coloumn] = ' ';
        cout<<"Chess piece has been moved"<<endl;
    }
    // Handle pawn movement 
    void handlePawn(coordinate x, coordinate y, string board[]){
        // Check if forward movement or cross movement are not Invalid
        if(abs(y.row - x.row) > 2 || abs(y.coloumn - x.coloumn) > 1){
               cout<<"Invalid Move"<<endl;
               return;
        }
        // For a pawn moving two blocks forward in initial state.
        else if(y.coloumn == x.coloumn && abs(y.row - x.row) == 2){
            if(x.row == 1 || x.row == 6){
               movePiece(x,y,board,false);
            }
            else{
                if(board[y.row][y.coloumn] != ' '){
                    cout<<"A chess piece is already present there"<<endl;
                }
                cout<<"Can only move pawn 2 steps initially"<<endl;
                return;
            }
        }
        // Chess piece moving 1 block ahead.
        else if(y.coloumn == x.coloumn && abs(y.row - x.row) == 1){
            // A block already present at location
            if(board[y.row][y.coloumn] != ' '){
                cout<<"A chess piece is already present there"<<endl;
                return;
            }
            else{
                movePiece(x,y,board,false);
            }
        }
        // cross move while killing a pawn.
        else if(abs(y.row - x.row) == 1 && abs(y.coloumn - x.coloumn) == 1){
            if(board[y.row][y.coloumn] == ' '){
                cout<<"No opponent chess piece to kill"<<endl;
                return;
            }
            else{
                movePiece(x,y,board,true);
            }
        }
    }
    // Handling bishop movements 
    void handleBishop(coordinate x, coordinate y, string board[]){

         if(abs(x.row - y.row) != abs(x.coloumn - y.coloumn)){
            cout<<"Invalid Move, can only move diagonally"<<endl;
            return;
         }
         // The bishop can move possibly in 4 diagonals
         else{
             // boolean to check if this is an attack or not
             bool attack = board[y.row][y.row] != ' ' ? true : false;
             // boolean to check if there is a piece in between the path
             bool flag = true;
              if(x.row > y.row && x.coloumn > y.coloumn){
                 int n = x.row - y.row;
                 for(int i = 1; i < n; i++){
                     if(board[x.row - i][x.coloumn - i] != ' '){
                         flag = false;
                     }
                 }
              }
              else if(x.row < y.row && x.coloumn < y.coloumn){
                int n = y.row - x.row;
                for(int i = 1; i < n; i++){
                    if(board[x.row + i][x.coloumn + i] != ' '){
                        flag = false;
                    }
                }
              }
              else if(x.row < y.row && x.coloumn > y.coloumn){
                  int n = y.row - x.row;
                  for(int i=1; i<n; i++){
                      if(board[x.row + i][x.coloumn - i] != ' '){
                          flag = false;
                      }
                  }
              }
              else{
                   int n = x.row - y.row;
                   for(int i=1; i<n; i++){
                       if(board[x.row - i][x.coloumn + i] != ' '){
                           flag = false;
                       }
                   }
              }

              if(flag){
                  movePiece(x,y,board,attack);
              }
              else{
                  cout<<"Cannot cross a piece"<<endl;
                  return;
              }
         }
    }

    // handling knight movement 
    void handleKnight(coordinate x, coordinate y, string board[]){
        if(abs(x.row - y.row) == 2 && abs(x.coloumn - y.coloumn) == 1 
            || 
           abs(x.row - y.row) == 1 && abs(x.coloumn - y.coloumn) == 2){
               bool attack = board[y.row][y.coloumn] != ' ' ? true : false; 
               movePiece(x,y,board,attack);
           }
        else{
            cout<<"Invalid move"<<endl;
            return;
        }
    }

    // handling rook movement 
    void handleRook(coordinate x, coordinate y, string board[]){
        if(x.row != y.row && x.coloumn != y.coloumn){
            cout<<"Not a valid move"<<endl;
            return;
        }
        else{
            bool attack = board[y.row][y.coloumn] != ' '?true:false;
            bool flag = true;
            if(x.row == y.row){
                if(x.coloumn < y.coloumn){
                   for(int i=(x.coloumn + 1); i < y.coloumn; i++){
                       if(board[x.row][i] != ' '){
                           flag = false;
                       }
                   }
                }
                else{
                   for(int i=(y.coloumn + 1); i < x.coloumn; i++){
                       if(board[x.row][i] != ' '){
                           flag = false;
                       }
                   }
                }
            }
            else if(x.coloumn == y.coloumn){
                if(x.row < y.row){
                   for(int i=(x.row + 1); i < y.row; i++){
                       if(board[i][x.coloumn] != ' '){
                           flag = false;
                       }
                   }
                }
                else{
                   for(int i=(y.row + 1); i < x.row; i++){
                       if(board[i][x.coloumn] != ' '){
                           flag = false;
                       }
                   }
                }
            }

            if(flag){
                movePiece(x,y,board,attack);
            }else{
                cout<<"Cannot cross a piece"<<endl;
                return;
            }
        }
    }

    // handling queen's movement
    void handleQueen(coordinate x, coordinate y, string board[]){
        if(x.row == y.row || x.coloumn == y.coloumn){
            handleRook(x,y,board);
        }
        else{
            handleBishop(x,y,board);
        }
    }
    
    // handling king's movement 
    void handleKing(coordinate x, coordinate y, string board[]){
        if(abs(x.row - y.row) > 1 || abs(x.coloumn - y.coloumn) > 1){
            cout<<"Invalid move"<<endl;
            return;
        }
        else{
           bool attack = board[y.row][y.coloumn] != ' ' ? true : false;
           movePiece(x,y,board,attack);
        }
    }
};
class ChessBoard : public Movement{

   public:
   string board[8];
   ChessBoard(){
       for(int i=0; i<8; i++){

        if(i == 0){
            board[i] = "RNBQKBNR";
        }
        else if(i == 7){
            board[i] = "rnbqkbnr";
        }
        else if(i == 1){
            board[i] = "PPPPPPPP";
        }
        else if(i == 6){
            board[i] = "pppppppp";
        }
        else{
            board[i] = "        ";
        }
    }
   }

   int returnColoumn(char x){
       return (int(x) - 65);
   }

   void displayBoard(){
      cout<<endl;
      cout<<"        CHESS"<<endl;
      cout<<endl;
      cout<<"   - - - - - - - -"<<endl;
      for(int i=7; i>=0; i--){
        for(int j=0; j<8; j++){
            if(j == 0){
                cout<<i<<" |";
            }
            cout<<board[i][j]<<"|";
        }
         cout<<endl;
         cout<<"   - - - - - - - -"<<endl;
        }
       cout<<endl;
       cout<<"   A B C D E F G H"<<endl;
       cout<<endl;
   }

   void move(string a, string b){

       coordinate x,y;       

       x.row = atoi(a.substr(1,1).c_str());
       x.coloumn = returnColoumn(a[0]);
       y.row = atoi(b.substr(1,1).c_str());
       y.coloumn = returnColoumn(b[0]);
       
       // If there is no piece at the location
       if(board[x.row][x.coloumn] == ' '){
           cout<<"No chess piece available at position "<<a<<endl;
           return;
       }
       // If the coordinates given lie outside the board
       else if(x.row > 8 || x.row < 0 || y.row > 8 || y.row < 0 || x.coloumn > 8 || x.coloumn < 0 || y.coloumn > 8 || y.coloumn < 0){
           cout<<"Coordinates are out of scope"<<endl;
           return;
       }
       else{
           // If the piece is a pawn
           if(board[x.row][x.coloumn] == 'p' || board[x.row][x.coloumn] == 'P'){
               handlePawn(x,y,board);
               return;
           }
           // If the piece is a bishop
           if(board[x.row][x.coloumn] == 'b' || board[x.row][x.coloumn] == 'B'){
               handleBishop(x,y,board);
               return;
           } 
           // If the piece is a knight
           if(board[x.row][x.coloumn] == 'n' || board[x.row][x.coloumn] == 'N'){
               handleKnight(x,y,board);
               return;
           } 
           // If the piece is a rook
           if(board[x.row][x.coloumn] == 'r' || board[x.row][x.coloumn] == 'R'){
               handleKnight(x,y,board);
               return;
           }
           // If the piece is a queen
           if(board[x.row][x.coloumn] == 'q' || board[x.row][x.coloumn] == 'Q'){
               handleQueen(x,y,board);
               return;
           }
           // If the piece is a king
           if(board[x.row][x.coloumn] == 'k' || board[x.row][x.coloumn] == 'K'){
               handleKing(x,y,board);
               return;
           }
       }
   }
};

int main(){
    ChessBoard game;
    game.displayBoard();
    return 0;
}

// Run function 
// cd "d:\ColtSteele\" ; if ($?) { g++ chess.cpp -o chess } ; if ($?) { .\chess }