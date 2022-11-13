#include <stdio.h>
#include <stdbool.h>

#define SIZE 8

#define EMPTY_LETTER "□"
#define BLACK_LETTER "●"
#define WHITE_LETTER "○"

#define EMPTY 0
#define BLACK 1
#define WHITE 2

int board[SIZE][SIZE];

void reset()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            board[i][j] = 0;
}

bool isEmpty(int x, int y)
{
    return !board[x][y];
}

bool checkRange(int x, int y)
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool put(int x, int y, int value)
{
    if (!checkRange(x, y) || !isEmpty(x, y))
        return false;
    board[x][y] = value;
    return true;
}

bool checkWin(int value)
{
    static const int dx[] = {0, 1, 1, 1};
    static const int dy[] = {1, 0, 1, -1};

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] != value)
                continue;
            for (int k = 0; k < 4; k++)
            {
                int x = i, y = j;
                int count = 0;
                while (checkRange(x, y) && board[x][y] == value)
                {
                    count++;
                    x += dx[k];
                    y += dy[k];
                }
                if (count >= 5)
                    return true;
            }
        }
}

void printBoard()
{
    printf("\x1b[0;0H");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            printf(board[i][j] == BLACK   ? BLACK_LETTER
                   : board[i][j] == WHITE ? WHITE_LETTER
                                          : EMPTY_LETTER);
        printf("\n");
    }
}

int main()
{
    int x, y;
    int player = BLACK;

    while (1)
    {
        printBoard();
        printf("%s 차례\n", player == BLACK ? "흑" : "백");
        printf("\x1b[1M좌표 입력(x y): ");
        scanf("%d %d", &x, &y);
        if (!put(x - 1, y - 1, player))
            continue;
        if (checkWin(player))
            break;
        player = player == BLACK ? WHITE : BLACK;
    }

    printf("\x1b[2J");
    printBoard();
    printf("%s 승리\n", player == BLACK ? "흑" : "백");
    pause();
    return 0;
}