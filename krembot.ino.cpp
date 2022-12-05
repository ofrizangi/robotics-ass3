#include "krembot.ino.h"

using namespace std;

int col, row;

int ** occupancyGrid;
int ** weightedGrid;
Real resolution;
CVector2 origin;
int height, width;
CVector2 pos;
CDegrees degreeX;

string name_1 ="/home/sivan-jhirad/krembot_ws/walking_on_grid/grid.txt";
string name_2 ="/home/sivan-jhirad/krembot_ws/walking_on_grid/grid-whith-robot-loc.txt";


enum State
{
    move,
    turn
} state = turn;

void WSTC_controller::setup() {
    krembot.setup();
    krembot.Led.write(0,255,0);

    occupancyGrid = mapMsg.occupancyGrid;
    weightedGrid = mapMsg.weightedGrid;
    resolution = mapMsg.resolution;
    origin = mapMsg.origin;
    height = mapMsg.height;
    width = mapMsg.width;


    save_grid_to_file(name_1, occupancyGrid, height, width);

    pos = posMsg.pos;
    degreeX = posMsg.degreeX;

    pos_to_col_row(pos, &col, &row);
    save_grid_to_file_with_robot_location(name_2, occupancyGrid, height, width, col, row);

}

void WSTC_controller::loop() {
    krembot.loop();

    pos = posMsg.pos;
    degreeX = posMsg.degreeX;

}

void WSTC_controller::pos_to_col_row(CVector2 pos, int * pCol, int * pRow){
    *pCol = (pos.GetX() - origin.GetX()) / resolution;
    *pRow = (pos.GetY() - origin.GetY()) / resolution;
}

void WSTC_controller::save_grid_to_file(string name, int** grid, int _height, int _width){
    ofstream m_cOutput;
    m_cOutput.open(name, ios_base::trunc | ios_base::out);
    for (int row = _height-1; row>=0 ; row--){
        for (int col=0; col< _width; col++){
            m_cOutput << grid[row][col];
        }
        m_cOutput << endl;
    }
    m_cOutput.close();
}

void WSTC_controller::save_grid_to_file_with_robot_location(string name, int** grid, int _height,
                                                                     int _width, int robot_col, int robot_row){
    ofstream m_cOutput;
    m_cOutput.open(name, ios_base::trunc | ios_base::out);
    int to_print;
    for (int row = _height-1; row>=0 ; row--){
        for (int col=0; col< _width; col++){
            if ((col == robot_col) && (row == robot_row)){
                to_print = 2;
            }
            else {
                to_print = grid[row][col];
            }
            m_cOutput << to_print;
        }
        m_cOutput << endl;
    }
    m_cOutput.close();
}
