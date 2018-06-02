#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::vector;

void clearConsole() { cout << std::string(200, '\n'); }

void displayBoard(vector<vector<int>> board) {
  clearConsole();
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c < board[r].size(); c++) {
      cout << setw(4) << board[r][c] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void shift(vector<vector<int>> &board) {
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c < board[r].size() - 1; c++) {
      if (board[r][c + 1] == 0) {
        board[r][c + 1] = board[r][c];
        board[r][c] = 0;
      }
    }
  }
}

// Assumes board already shifted
void combine(vector<vector<int>> &board) {
  for (int r = 0; r < board.size(); r++) {
    for (int c = board[r].size() - 1; c > 0; c--) {
      if (board[r][c] == board[r][c - 1]) {
        board[r][c] += board[r][c - 1];
        board[r][c - 1] = 0;
        c--;
      }
    }
  }
}

void spawn(vector<vector<int>> &board) {
  int rr, rc, r24;
  do {
    rr = rand() % board.size();
    rc = rand() % board.size();
    r24 = rand() % 2;
  } while (board[rr][rc] != 0);
  if (r24 == 0) board[rr][rc] = 2;
  else board[rr][rc] = 4;
}

void flipHorizontal(vector<vector<int>> &board) {
  for (int r = 0; r < board.size(); r++) {
    std::reverse(board[r].begin(), board[r].end());
  }
}

void flipDiagonal(vector<vector<int>> &board) {
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c <= r; c++) {
      int temp = board[r][c];
      board[r][c] = board[c][r];
      board[c][r] = temp;
    }
  }
}

bool changed(vector<vector<int>> prevBoard, vector<vector<int>> newBoard) {
  for (int r = 0; r < prevBoard.size(); r++) {
    for (int c = 0; c < prevBoard[r].size(); c++) {
      if (prevBoard[r][c] != newBoard[r][c])
        return true;
    }
  }
  return false;
}

void move(vector<vector<int>> &board) {
  shift(board);
  combine(board);
  shift(board);
  spawn(board);
}

int main() {
  srand(time(0));
  vector<vector<int>> board = {{0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0}};

  /*vector<vector<int>> boardWithIndex = {{00, 01, 02, 03},
                                        {10, 11, 12, 13},
                                        {20, 21, 22, 23},
                                        {30, 31, 32, 33}};*/


  spawn(board);
  spawn(board);

  char keyPressed;

  do {
    displayBoard(board);

    cin >> keyPressed;

    switch (keyPressed) {
      case 'w':
        flipHorizontal(board);
        flipDiagonal(board);
        move(board);
        flipDiagonal(board);
        flipHorizontal(board);
        break;
      case 'a':
        flipHorizontal(board);
        move(board);
        flipHorizontal(board);
        break;
      case 's':
        flipDiagonal(board);
        move(board);
        flipDiagonal(board);
        break;
      case 'd':
        move(board);
        break;
      default:break;
    }

  } while (keyPressed != '/');

}


