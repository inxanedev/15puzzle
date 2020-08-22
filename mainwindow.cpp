#include "mainwindow.h"
#include "ui_mainwindow.h"

QPushButton *btns[15];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *arr[] = {
        ui->btn1,
        ui->btn2,
        ui->btn3,
        ui->btn4,
        ui->btn5,
        ui->btn6,
        ui->btn7,
        ui->btn8,
        ui->btn9,
        ui->btn10,
        ui->btn11,
        ui->btn12,
        ui->btn13,
        ui->btn14,
        ui->btn15
    };
    std::copy(arr, arr + 15, btns);
    for (QPushButton *btn : btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(performSwap()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
int grid[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};
struct XY {
    int x, y;
};
XY findNum(int num) {
    XY result;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (grid[y][x] == num) {
                result.x = x;
                result.y = y;
            }
        }
    }
    return result;
}
void gridSwap(int y, int x, XY coords) {
    if (grid[y][x] == 16) {
        std::swap(grid[y][x], grid[coords.y][coords.x]);
    }
}

void MainWindow::performSwap() {
    QPushButton *btn = (QPushButton *)sender();
    int num = btn->text().toInt();
    XY numCoords = findNum(num);

    // Middle 2x2
    if (numCoords.y == 1 || numCoords.y == 2) {
        if (numCoords.x == 1 || numCoords.x == 2) {
            gridSwap(numCoords.y + 1, numCoords.x, numCoords);
            gridSwap(numCoords.y - 1, numCoords.x, numCoords);
            gridSwap(numCoords.y, numCoords.x + 1, numCoords);
            gridSwap(numCoords.y, numCoords.x - 1, numCoords);
        }
    }
    // Corners
    if (numCoords.y == 0 && numCoords.x == 0) {
        gridSwap(numCoords.y + 1, numCoords.x, numCoords);
        gridSwap(numCoords.y, numCoords.x + 1, numCoords);
    } else if (numCoords.y == 0 && numCoords.x == 3) {
        gridSwap(numCoords.y, numCoords.x - 1, numCoords);
        gridSwap(numCoords.y + 1, numCoords.x, numCoords);
    } else if (numCoords.y == 3 && numCoords.x == 0) {
        gridSwap(numCoords.y - 1, numCoords.x, numCoords);
        gridSwap(numCoords.y, numCoords.x + 1, numCoords);
    } else if (numCoords.y == 3 && numCoords.x == 3) {
        gridSwap(numCoords.y - 1, numCoords.x, numCoords);
        gridSwap(numCoords.y, numCoords.x - 1, numCoords);
    }
    // Edges
    if ((numCoords.x == 1 || numCoords.x == 2) && numCoords.y == 0) {
        gridSwap(numCoords.y, numCoords.x - 1, numCoords);
        gridSwap(numCoords.y, numCoords.x + 1, numCoords);
        gridSwap(numCoords.y + 1, numCoords.x, numCoords);
    } else if ((numCoords.y == 1 || numCoords.y == 2) && numCoords.x == 0) {
        gridSwap(numCoords.y, numCoords.x + 1, numCoords);
        gridSwap(numCoords.y + 1, numCoords.x, numCoords);
        gridSwap(numCoords.y - 1, numCoords.x, numCoords);
    } else if ((numCoords.y == 1 || numCoords.y == 2) && numCoords.x == 3) {
        gridSwap(numCoords.y, numCoords.x - 1, numCoords);
        gridSwap(numCoords.y + 1, numCoords.x, numCoords);
        gridSwap(numCoords.y - 1, numCoords.x, numCoords);
    } else if ((numCoords.x == 1 || numCoords.x == 2) && numCoords.y == 3) {
        gridSwap(numCoords.y, numCoords.x + 1, numCoords);
        gridSwap(numCoords.y, numCoords.x - 1, numCoords);
        gridSwap(numCoords.y - 1, numCoords.x, numCoords);
    }
    // Change button positions
    XY temp;
    for (QPushButton *btn : btns) {
        temp = findNum(btn->text().toInt());
        btn->setGeometry((temp.x * 70), (temp.y * 70), 71, 71);
    }
}
