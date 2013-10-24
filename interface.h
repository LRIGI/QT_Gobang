#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QtDebug>

#include <vector>

#include <ctime>

#include "function.h"


using namespace std;

class Interface : public QWidget
{
  Q_OBJECT

public:
    Interface(QWidget *parent = 0);
    void setVariable(int N);

protected:
	void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event); //mouse click
    void mouseReleaseEvent(QMouseEvent * event);
    void contextMenuEvent ( QContextMenuEvent * event );
    void QShowEvent();

private:
    void localBattle();

    //----greeedy----
    //void randomchoose(vector<vector<int> > & chessboard, int &N);
    int p_score(int num, int * bp);
    void setscore(vector<vector<int> > & chessboard,const int i, const int j, const int who, vector<vector<int> > & state, int &N);
    void vsBattleGreedy(vector<vector<int> > & chessboard, int &N);
    vector<vector<int> > HumanState, ComputerState;
    //----greeedy----

    //---game tree---
    void vsBattleGametree();
    typedef int Map[15][15];

    const int MIN = -1000000;
    const int MAX = 1000000;
    const int MAX_CHILDS = 10;
    const int SEARCH_DEPTH = 3;
    const int dir[4][2] = {{0,  1}, {-1, 0}, {0, -1}, {1,  0}};
    const int level_score[18] = {0, 10,   50,   50,   100,    100,    200,   500, 1000, 1000, 2000,    2000,      5000 ,     5000,     5000,   10000, 10000, 80000};

    const double p_accept = 0.3;

    struct Tree
    {
        vector<Tree*> childs;
        Tree* father;
        int depth;
        int value;
        Map map;
        int first;
        int firstPoint[2];
        int point[2];
        bool cut;
    };

    Map currentMap;		//0 no chess;1 people; 2 white
    int whoseTurn;		// 0: people's turn  1: computer turn
    int win;
    //int hand;			//play times
    int cut;			//cut times

    void computer_think(vector<vector<int> > & chessboard, int &N);
    void alpha_beta(Tree*);
    void clear(Tree*);
    void scanMap(Tree *&pTree, int turn);
    int total_score(Map map, int turn);
    bool addToMap(Map &map, int i, int j);
    int PriorityGet(int i, int j, int level, Map record);
    int LinkSS4(int x,int y, Map map);
    /*211110 or 211101 or 211011*/
    /*210111 or 11110 or 11101 */
    /* 11011 or 10111*/
    int LinkSS3(int x,int y, Map map);
    /*211100 or 211010 or 211001*/
    /*210110 or 210101 or 21011*/
    /*11100 or 10110 or 10011 */
    /*10101*/
    int LinkS5(int x,int y, Map map);	/*1011101*/
    int LinkS4(int x,int y, Map map);	/*1010101*/
    int LinkS3(int x,int y, Map map);	/*1010100*/
    int LinkF5(int x,int y, Map map);	/*11111*/
    int LinkF4(int x,int y, Map map);	/*11110*/
    int LinkF3(int x,int y, Map map);	/*011100 or 010110*/
    int LinkF2(int x,int y, Map map);	/*011000 or 010100 or 010010*/
    int LinkF1(int x,int y, Map map);	/*1*/

    void game_tree(vector<vector<int> > & chessboard, int &N);

    //---game tree---


    void onlineBattleServer();
    void onlineBattleClient();

    int isWin();
    void judge();

//    void player(void);
//    void greedy(void);


    //void stringToInt(char temp[30]);
    void listen();

    void intToString(int x, char string[30]);

    QLabel *label;

    Function network;

    int mode;
    int N; //N*N
    int size; //square size
    int width;
    bool color;

    int ip1;
    int ip2;
    int ip3;
    int ip4;
    int port;

    int x_index;
    int y_index;

    int countForClient;
    bool roundCheck;//in mode3,4, need to wait for response before play next round
    bool listenCheck;
    bool beginClient; //just for begin of client

    bool firstTime; //first begin

    vector<vector<int> > data;
    vector<vector<int> > regretData;

    //Action
    QAction *newAction;
    QAction *regretAction;
    QAction *switchZeroAction;
    QAction *switchOneAction;
    QAction *switchTwoAction;

private slots:
    void getVariable(int mode, int N, int ip1, int ip2, int ip3, int ip4, int port);
    void newgame();
    void regret();
    void switchZero();
    void switchOne();
    void switchTwo();


};

#endif
