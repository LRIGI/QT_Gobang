#include "interface.h"
//#include "function.h"
#include <iostream>

using namespace std;

Interface::Interface(QWidget *parent) : QWidget(parent)
{
  //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
  N = 15;
  width = 20; //fix grid width
  color = true;
  firstTime = true;

  setWindowTitle("Gobang");




  // QPushButton *plus = new QPushButton("+", this);
  // plus->setGeometry(50, 40, 75, 30);

  // QPushButton *minus = new QPushButton("-", this);
  // minus->setGeometry(50, 100, 75, 30);

  // label = new QLabel("0", this);
  // label->setGeometry(190, 80, 20, 30);

  // connect(plus, SIGNAL(clicked()), this, SLOT(OnPlus()));
  // connect(minus, SIGNAL(clicked()), this, SLOT(OnMinus()));

  //paintEvent();

  cout << "initilized N: " << N << " width: " << width << " size: " <<size << endl;

}

void Interface::getVariable(int _mode, int _N, int _ip1, int _ip2, int _ip3, int _ip4, int _port){
    mode = _mode;
    N = _N;
    ip1 = _ip1;
    ip2 = _ip2;
    ip3 = _ip3;
    ip4 = _ip4;
    port = _port;



    qDebug() << "GetVariable mode: " << mode << " size: " << N << " IP: " << ip1 << "." << ip2 << "." << ip3 <<"." <<ip4 << " port: "<<port;

    cout << "new game" << endl;
    newgame();

    cout << "getVariable end" << endl;
}

void Interface::paintEvent(QPaintEvent *event){
    //create a QPainter and pass a pointer to the device
    QPainter painter(this);

    //Background
    painter.setBrush(Qt::transparent);
    painter.drawRect(0, 0, size, size);

    //Grid
   for (int x = width; x <= N*width; x += width)
    {
        painter.drawLine(x, width, x, N*width); 
    }
    for (int y = width; y <= N*width; y += width)
    {
        painter.drawLine(width, y, N*width, y);
    }

    //piece
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            if (data[x][y] == 1){ //black
                brush.setColor(Qt::black);
                painter.setBrush(brush);    
                painter.drawEllipse((x+1)*width-width/2, (y+1)*width-width/2, width, width);
            }
            else if (data[x][y] == 2){ //white
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse((x+1)*width-width/2, (y+1)*width-width/2, width, width);
            }
        }
    }

   cout << "paint N: " << N << " width: " << width << " size: " <<size << endl;

    //change window size
   resize(size, size);

   countForClient++;
   if(countForClient == 5 && mode == 4 && beginClient == false){
       listen();
       beginClient = true;
   }
}

void Interface::QShowEvent(){
    cout << "Qshow!" << endl;

//    if(mode == 4){
//        listen();
//    }
}

void Interface::mouseReleaseEvent(QMouseEvent * event){
    //mouse info
    int x = event->x();
    int y = event->y();

    cout << "mouseRelease!Enter roundCheck!: " << roundCheck << " listenCheck: " << listenCheck << endl;
    if (event->button() == Qt::LeftButton && x > width/2 && x < size-width/2 && y > width/2 && y < size-width/2){
        if((mode == 3 || mode == 4) &&  roundCheck == true && listenCheck == false){
            listenCheck = true;
            cout << "listen()" << endl;

            //cout << "disable" << endl;
            //QWidget::setEnabled(false);

            //update();

            listen(); //return from listen!!!

            //cout << "enable" << endl;
            //QWidget::setEnabled(true);
        }

        cout << "mouseRelease!Leave roundCheck: " << roundCheck << " listenCheck: " << listenCheck << endl;
    }
    //cout << "mouseRelease! roundCheck: " << roundCheck << " listenCheck: " << listenCheck << endl;
}

void Interface::mousePressEvent(QMouseEvent * event){
  //mouse info
  int x = event->x();
  int y = event->y();

  cout << "roundCheck: " << roundCheck << " listenCheck: " << listenCheck << endl;
  if (event->button() == Qt::LeftButton){
      //store regret data
      for(int i = 0; i < N; i++){
          for(int j = 0; j < N; j++){
              regretData[i][j] = data[i][j];
          }
      }

      if((mode == 3 || mode == 4) && roundCheck == false){
          cout << "send()" << endl;
          roundCheck = true;
          //within the chessboard and not in the middle point
        if(x > width/2 && x < size-width/2 && y > width/2 && y < size-width/2 && (x+width/2)%width!=0 && (y+width/2)%width!=0 ){
                x_index = (x+width/2)/width-1;
                y_index = (y+width/2)/width-1;

            if(color == true && data[x_index][y_index] == 0){
              color = false;
              data[x_index][y_index] = 1;
            }else if(color == false && data[x_index][y_index] == 0){
              color = true;
              data[x_index][y_index] = 2;
            }

              if(mode == 3){
                  cout << "server send" << endl;
                  network.send(x_index,y_index);
                  //listen();
              }else if(mode == 4){
                  cout << "client send" << endl;
                  network.send(x_index,y_index);
                  //listen();
              }

              //judge
              judge();

              //update QWidget
              update();

              //QWidget::setEnabled(false);
        }
      }else if(mode == 0 || mode == 1 || mode == 2){
              //within the chessboard and not in the middle point
            if(x > width/2 && x < size-width/2 && y > width/2 && y < size-width/2 && (x+width/2)%width!=0 && (y+width/2)%width!=0 ){
                x_index = (x+width/2)/width-1;
                y_index = (y+width/2)/width-1;

                if(color == true && data[x_index][y_index] == 0){
                  color = false;
                  data[x_index][y_index] = 1;
                }else if(color == false && data[x_index][y_index] == 0){
                  color = true;
                  data[x_index][y_index] = 2;
                }

                qDebug() << "statement x: " << x << "statement y: " << y;
                qDebug() << "index x: " << x_index << "index y: " << y_index;
                qDebug() << "color: " << color;


                //mode
                switch(mode){
                    case 0: localBattle(); break;
                    case 1: vsBattleGreedy(data, N); break;
                    case 2: vsBattleGametree(); break;
                    default: break;
                }

                //judge
                judge();

                //update QWidget
                update();
          }
      }else if(mode == 5){ //vs demo
          cout << "Greeedy's move!" << endl;
          vsBattleGreedy(data, N);
          judge();
          //cout << "color: " << color << endl;

          cout << "Game tree's move!" << endl;
          vsBattleGametree();
          judge();
          update();
          //cout << "color: " << color << endl;
      }
  }

  cout << "mouse end!" << endl;

}

void Interface::listen(){
    cout << "listening!" << endl;

    int * coordinate;
    coordinate = network.receive();

    x_index = *(coordinate++);
    y_index = *coordinate;

    if(color == true && data[x_index][y_index] == 0){
      color = false;
      data[x_index][y_index] = 1;
    }else if(color == false && data[x_index][y_index] == 0){
      color = true;
      data[x_index][y_index] = 2;
    }

    roundCheck = false;
    listenCheck = false;

    judge();

    update();

    //cout << "enable" << endl;
    //QWidget::setEnabled(true);
    //QWidget::setEnabled(false);

    cout << "listen() ends! roundCheck: " << roundCheck << " listenCheck: " << listenCheck<< endl;
}

void Interface::contextMenuEvent ( QContextMenuEvent * event ){ //right click
    if(mode != 3 && mode !=4 && mode !=5){
        newAction = new QAction(tr("New game"), this);
        connect(newAction, SIGNAL(triggered()), this, SLOT(newgame()));
        regretAction = new QAction(tr("Regret one step"), this);
        connect(regretAction, SIGNAL(triggered()), this, SLOT(regret()));
        if(mode != 0){
            switchZeroAction = new QAction(tr("Switch to Local Battle"), this);
            connect(switchZeroAction, SIGNAL(triggered()), this, SLOT(switchZero()));
        }
        if(mode != 1){
            switchOneAction = new QAction(tr("Switch to VS Battle - Greedy"), this);
            connect(switchOneAction, SIGNAL(triggered()), this, SLOT(switchOne()));
        }
        if(mode != 2){
            switchTwoAction = new QAction(tr("Switch to VS Battle - Game Tree"), this);
            connect(switchTwoAction, SIGNAL(triggered()), this, SLOT(switchTwo()));
        }
        QMenu menu(this);
        menu.addAction(newAction);
        menu.addAction(regretAction);
        if(mode != 0){
            menu.addAction(switchZeroAction);
        }
        if(mode != 1){
            menu.addAction(switchOneAction);
        }
        if(mode != 2){
            menu.addAction(switchTwoAction);
        }
        menu.exec(event->globalPos());
    }
}

void Interface::intToString(int x, char string[30]){
    int i = 0;
    char temp[30];
    int length = 0;

    //get num one by one
    do{
        //cout << char(x%10 + '0') << endl;
        temp[i++] = char(x%10 + '0');
        x = x/10;
    }while(x != 0);
    temp[i] = '\0';

    //reverse
    length = strlen(temp);
    for(i = 0; i < length; i++){
        string[i] = temp[length-i-1];
    }
    string[i] = '\0';

    //cout << "x: " << x << " string: " << string << endl;
}

void Interface::newgame(){
    cout << "newgame!"<< endl;

    int * coordinate;

    countForClient = 0;
    color = true;
    roundCheck = false;
    listenCheck = false;
    beginClient = false;

    char host[30] = "localhost";
    if(mode == 4){
        char tempHost[30] = "";
        if(ip1!=0 || ip2 !=0 || ip3 != 0 || ip4 !=0){
            char ipTemp[10];
            intToString(ip1, ipTemp);
            strcat(tempHost, ipTemp);
            strcat(tempHost, ".");

            intToString(ip2, ipTemp);
            strcat(tempHost, ipTemp);
            strcat(tempHost, ".");

            intToString(ip3, ipTemp);
            strcat(tempHost, ipTemp);
            strcat(tempHost, ".");

            intToString(ip4, ipTemp);
            strcat(tempHost, ipTemp);

        }
        strcpy(host, tempHost);
        //cout << host << endl;
    }

    if(mode == 3){
        network.server(port);
        network.send(N,0);
        //cout << "server" << endl;
    }else if(mode == 4){
        //color = false;
        network.client(host, port);
        cout << "server" << endl;

        coordinate = network.receive();
        cout << "before N" << endl;
        N = *coordinate;
        cout << N << endl;
    }else if(mode == 5){
        //color= false;
    }

    //initiate data
    if(firstTime == true){
        vector<int> temp(N, 0);
        for (int i = 0; i < N; i++){
          data.push_back(temp);
          regretData.push_back(temp);
        }
        size = width*(N+1);

        firstTime = false;
    }else{
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                data[i][j] = 0;
            }
        }
        update();
    }


    //setTitle
    if(mode == 3){
        setWindowTitle("Gobang-Server");
    }else if(mode == 4){
        setWindowTitle("Gobang-Client");
    }else{
        setWindowTitle("Gobang");
    }



}

void Interface::regret(){
    cout << "regret!" << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            data[i][j] = regretData[i][j];
        }
    }
    if(mode == 0){
        color = (color == true? false:true);
    }
    update();
}

void Interface::switchZero(){
    mode = 0;
    newgame();
}

void Interface::switchOne(){
    mode = 1;
    newgame();
}

void Interface::switchTwo(){
    mode = 2;
    newgame();
}

//---------------localBattle--------------------------
void Interface::localBattle(){
    cout << "localBattle!" << endl;
}

//---------------onlineBattleServer--------------------------
void Interface::onlineBattleServer(){
    cout << "onlineBattleServer!" << endl;
}

//---------------onlineBattleClient--------------------------
void Interface::onlineBattleClient(){
    cout << "onlineBattleClient!" << endl;
}

//---------------Greedy--------------------------
//greedy algorithm AI
int Interface::p_score(int num, int bp[])
{
    int max=0;
    if (num >=4)
    {
        max += 10000;
    }
    else if(num ==3)
    {
        if(bp[1]==1 && bp[0] ==1)
        {
            max=max+0;
        }
        else if(bp[1]==0 && bp[0]==0)
        {
            max=max+3000;
        }
        else
        {
            max=max+900;
        }
    }
    else if(num==2)
    {
        if(bp[0]==0 && bp[1]==0)
        {
            max=max+460;
        }
        else if(bp[0]==1 && bp[1]==1)
        {
            max=max+0;
        }
        else
        {
            max=max+30;
        }
    }
    else if(num==1)
    {
        if(bp[0]==0 && bp[1]==0)
        {
            max=max+45;
        }
        else if(bp[0]==1 && bp[1]==1)
        {
            max=max+0;
        }
        else
        {
            max=max+5;
        }
    }
    else if(num==0)
    {
        if(bp[0]==0 && bp[1]==0)
        {
            max=max+3;
        }
        else if(bp[0]==1 && bp[1]==1)
        {
            max=max+0;
        }
        else
        {
            max=max+1;
        }
    }
    return max;

}


void Interface::setscore(vector<vector<int> > & chessboard,const int i, const int j, const int who, vector<vector<int> > & state, int &N)
{
    int opposite;
    if(who==1)
    {
        opposite=2;
    }
    else if(who==2)
    {
        opposite=1;
    }
    else
    {
        return;
    }

    int bp[2], k, num, max=0, temp=0;

    //x axis
    //to right
    bp[0]=1;
    bp[1]=1;
    num=0;
    for(k=1;k<N-i;k++)
    {
        if(chessboard[i+k][j] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i+k][j] == 0)
        {
            bp[1]=0;
            break;
        }
        if(chessboard[i+k][j]==opposite)
        {
            bp[1]=1;
            break;
        }
    }

    //to left
    for(k=1; k<=i; k++)
    {
        if(chessboard[i-k][j] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i-k][j] == 0)
        {
            bp[0]=0;
            break;
        }
        if(chessboard[i-k][j] == opposite)
        {
            bp[0]=1;
            break;
        }
    }

    temp=p_score(num,bp);
    max=max+temp;

    //axis y
    bp[0]=1;
    bp[1]=1;
    num=0;

    //downside
    for(k=1;k<N-j;k++)
    {
        if(chessboard[i][j+k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i][j+k] == 0)
        {
            bp[1]=0;
            break;
        }
        if(chessboard[i][j+k] == opposite)
        {
            bp[1]=1;
            break;
        }
    }

    //upside
    for(k=1;k<=j;k++)
    {
        if(chessboard[i][j-k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i][j-k] == 0)
        {
            bp[0]=0;
            break;
        }
        if(chessboard[i][j-k] == opposite)
        {
            bp[0]=1;
            break;
        }
    }

    temp=p_score(num,bp);
    max=max+temp;

    //upper left to right down

    bp[0]=1;
    bp[1]=1;
    num=0;

    //downside
    for(k=1; k<N-i && k<N-j; k++)
    {
        if(chessboard[i+k][j+k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i+k][j+k] == 0)
        {
            bp[1]=0;
            break;
        }
        if(chessboard[i+k][j+k] == opposite)
        {
            bp[1]=1;
            break;
        }
    }

    //updise
    for(k=1; k<=i && k<=j; k++)
    {
        if(chessboard[i-k][j-k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i-k][j-k] == 0)
        {
            bp[0]=0;
            break;
        }
        if(chessboard[i-k][j-k] == opposite)
        {
            bp[0]=1;
            break;
        }
    }

    temp=p_score(num,bp);
    max=max+temp;

    //upper right to left down
    bp[0]=1;
    bp[1]=1;
    num=0;

    //downside
    for(k=1; k<=i && k<N-j; k++)
    {
        if(chessboard[i-k][j+k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i-k][j+k] == 0)
        {
            bp[1]=0;
            break;
        }
        if(chessboard[i-k][j+k] == opposite)
        {
            bp[1]=1;
            break;
        }
    }

    //upper
    for(k=1; k<N-i && k<=j; k++)
    {
        if(chessboard[i+k][j-k] == who)
        {
            num++;
            continue;
        }
        if(chessboard[i+k][j-k] == 0)
        {
            bp[0]=0;
            break;
        }
        if(chessboard[i+k][j-k] == opposite)
        {
            bp[0]=1;
            break;
        }
    }

    temp=p_score(num,bp);
    max=max+temp;

    if(max >state[i][j])
    {
        state[i][j]=max;
    }
}

void Interface::vsBattleGreedy(vector<vector<int> > & chessboard, int &N)
{
    int total=0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(chessboard[i][j]!=0)
            {
                total=total+1;
            }
        }
    }
    if(total==0)
    {
        int x=rand()%N;
        int y=rand()%N;
        chessboard[x][y]=2;
        return;
    }

    vector<vector<int> > HumanState, ComputerState;
    vector<int> temp(N,0);
    for(int i=0; i<N; i++)
    {
        HumanState.push_back(temp);
        ComputerState.push_back(temp);
    }
    int pos1_x=-1;
    int pos1_y=-1;
    int pos2_x=-1;
    int pos2_y=-1;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N;j++)
        {
            if(chessboard[i][j]==0)
            {
                setscore(chessboard,i,j,1,HumanState,N);
                setscore(chessboard,i,j,2,ComputerState,N);
            }
        }
    }

    int maxP=0; //state of people
    int maxC=0; //state of computer

    for(int i=0; i<N;i++)
    {
        for(int j=0; j<N; j++)
        {
            if(HumanState[i][j] > maxP)
            {
                maxP=HumanState[i][j];
                pos1_x=i;
                pos1_y=j;
            }
            if(ComputerState[i][j] > maxC)
            {
                maxC=ComputerState[i][j];
                pos2_x=i;
                pos2_y=j;
            }
        }
    }

    cout << "pos1_x: " << pos1_x << " pos1_y: "<< pos1_y << " pos2_x: " << pos2_x << " pos2_y: " << pos2_y << endl;

    if(maxP>=maxC)
    {
        if(color == true){
          color = false;
          chessboard[pos1_x][pos1_y] = 1;
        }else if(color == false){
          color = true;
          chessboard[pos1_x][pos1_y] = 2;
        }

        //chessboard[pos1_x][pos1_y]=2;
        //cout<<endl;
    }
    else
    {
        if(color == true){
          color = false;
          chessboard[pos2_x][pos2_y] = 1;
        }else if(color == false){
          color = true;
          chessboard[pos2_x][pos2_y] = 2;
        }

        chessboard[pos2_x][pos2_y]=2;
        //cout<<endl;
    }
}

int Interface::isWin(){
    int total=0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(data[i][j]!=0)
            {
                total=total+1;
            }
        }
    }
    if(total==N*N)
    {
        return 3;
    }
    int state=0;

    for(int x=0;x<N;x++)
    {
        for(int y=0;y<N;y++)
        {
            if(data[x][y]==0)
            {
                continue;
            }
            for(int choice=0;choice<4;choice++)
            {
                int axis_x,axis_y;
                switch(choice)
                {
                    case 0:  //search 5 chess on x axis
                        axis_x=x+1;
                        while(axis_x<N && data[axis_x][y]==data[x][y])
                        {
                            state++;
                            axis_x++;
                        }
                        if(state>=4)
                        {
                            return data[x][y];
                        }
                        else
                        {
                            state=0;
                        }
                        break;
                    case 1:  //search 5 chess on y axis
                        axis_y=y+1;
                        while(axis_y<N && data[x][axis_y]==data[x][y])
                        {
                            state++;
                            axis_y++;
                        }
                        if(state>=4)
                        {
                            return data[x][y];
                        }
                        else
                        {
                            state=0;
                        }
                        break;
                    case 2: //upper left to right down
                        axis_x=x+1;
                        axis_y=y+1;
                        while(axis_x<N && axis_y<N && data[axis_x][axis_y]==data[x][y])
                        {
                            state++;
                            axis_x++;
                            axis_y++;
                        }
                        if(state>=4)
                        {
                            return data[x][y];
                        }
                        else
                        {
                            state=0;
                        }
                        break;
                    case 3: //upper right to left down
                        axis_x=x-1;
                        axis_y=y+1;
                        while(axis_x>=0 && axis_y<N && data[axis_x][axis_y]==data[x][y])
                        {
                            state++;
                            axis_x--;
                            axis_y++;
                        }
                        if(state>=4)
                        {
                            return data[x][y];
                        }
                        else
                        {
                            state=0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 0;
}

void Interface::judge(){
    int result = isWin();
    switch(result){
      case 1: QMessageBox::information(this, tr("Game over"), tr("Black win!")); newgame(); break;
      case 2: QMessageBox::information(this, tr("Game over"), tr("White win!")); newgame(); break;
      case 3: QMessageBox::information(this, tr("Game over"), tr("Draw!")); newgame(); break;
      default: break;
    }
}

//---------------Game tree--------------------------
void Interface::vsBattleGametree(){
    cout << "vsBattleGametree!" << endl;
    game_tree(data, N);
}

int Interface::total_score(Map map, int turn)
{
    //cout << "-----------score-----------\n";
    //printMap(map);
    int score = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (map[i][j] != 0)
            {
                int temp = 0;
                for (int level = 17; level > 0; level--)
                {
                    temp = PriorityGet(i, j, level, map) * level_score[level];
                    if (temp != 0)
                    {
                        score += (map[i][j] == 2) ?  temp : temp * (int)(-1);
                        break;
                    }
                }
            }
        }
    }
    return score;
}

int Interface::PriorityGet(int i, int j, int level, Map map)
{
    switch(level)
    {
    case 17:
        if(LinkF5(i, j, map))//30000
        {
            return 1;
        }
        break;
    case 16:
        if(LinkF4(i, j, map))//10000
        {
            return 1;
        }
        break;
    case 15:
        if(LinkSS4(i, j, map) > 2)//10000
        {
            return 1;
        }
        break;
    case 14:
        if(LinkS5(i, j, map))//10000
        {
            return 1;
        }
        break;
    case 13:
        if(LinkSS4(i, j, map) && LinkS4(i, j, map))//5000
        {
            return 1;
        }
        break;
    case 12:
        if(LinkSS4(i, j, map) && LinkF3(i, j, map))//5000
        {
            return 1;
        }
        break;
    case 11:
        if(LinkS4(i, j, map) && LinkF3(i, j, map))//5000
        {
            return 1;
        }
        break;
    case 10:
        if(LinkF3(i, j, map) > 2)//5000
        {
            return 1;
        }
        break;
    case 9:
        if(LinkS4(i, j, map))//500
        {
            return 1;
        }
        break;
    case 8:
        if(LinkSS4(i, j, map))//200
        {
            return 1;
        }
        break;
    case 7:
        if(LinkF3(i, j, map))//200
        {
            return 1;
        }
        break;
    case 6:
        if(LinkSS3(i, j, map) > 1)//100
        {
            return 1;
        }
        break;
    case 5:
        if(LinkS3(i, j, map) > 1)//100
        {
            return 1;
        }
        break;
    case 4:
        if(LinkF2(i, j, map) > 2)//100
        {
            return 1;
        }
        break;
    case 3:
        if(LinkF2(i, j, map))//50
        {
            return 1;
        }
        break;
    case 2:
        if(LinkSS3(i, j, map))//50
        {
            return 1;
        }
        break;
    case 1:
        if(LinkF1(i, j, map))//10
        {
            return 1;
        }
        break;
    }
    return 0;
}

int Interface::LinkSS4(int x,int y, Map map)
{
    int a[8][6]={{2,1,1,1,1,0},{2,1,0,1,1,1},{2,1,1,0,1,1},
    {2,1,1,1,0,1},{1,2,2,2,2,0},{1,2,0,2,2,2},
    {1,2,2,0,2,2},{1,2,2,2,0,2}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;

    num=map[x][y];
    Old_x=x;
    Old_y=y;

    for(int i = 0; i < 8; i++)
    {
        if(num != a[i][1])continue;
        for(int j = 0; j < 2;j++)
        {
            for(int k = 0; k < 4; k++){
                x = Old_x;
                y = Old_y;
                while(x>=0&&y<15&&x<15&&y>=0)
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J=5;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2)
                            A_J--;
                        else
                            A_J++;
                    }
                    if((A_J == 6 && j == 0)||(A_J < 0 && j == 1))
                        count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    for(int i = 0;i < 8; i++)
    {
        if(num != a[i][1])
            continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x=Old_x;
                y=Old_y;

                while(x >= 0 && y < 15 && x < 15 && y >= 0)
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 1;

                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J])
                        && (A_J > 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }

                    if((A_J == 6 && j == 0) || (A_J == 0 && j == 1))
                    {
                        if((y == 0 && M_J != 0) || (x == 0 && M_I != 0)
                            || (y == 14 && M_J < 14))count++;
                        if((M_I == 15 && x < 14)||(M_J == 15 && y < 14)) count++;
                    }
                    x += b[k][0];
                    y += b[k][1];

                }

            }
        }
    }

    return count;
}

int Interface::LinkSS3(int x,int y, Map map)
{
    int a[12][6] = {{2,1,1,1,0,0},{2,1,1,0,1,0},{2,1,1,0,0,1},
    {2,1,0,1,1,0},{2,1,0,1,0,1},{2,1,0,0,1,1},
    {1,2,2,2,0,0},{1,2,2,0,2,0},{1,2,2,0,0,2},
    {1,2,0,2,2,0},{1,2,0,2,0,2},{1,2,0,0,2,2}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;

    num=map[x][y];
    Old_x=x;
    Old_y=y;


    for(int i = 0; i < 12; i++)
    {
        if(num != a[i][1]) continue;
        for(int j = 0; j < 2;j++)
        {
            for(int k = 0;k < 4;k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x <15 && y >= 0)
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J])
                        && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 6 && j == 0) || (A_J < 0 && j == 1))count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    for(int i = 0;i < 12;i++)
    {
        if(num != a[i][1])continue;
        for(int j = 0;j < 2;j++)
        {
            for(int k = 0;k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0)
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 1;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J])
                        && (A_J>0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 6 && j == 0) || (A_J == 0 && j == 1))
                    {
                        if((y == 0 && M_J != 0) || (x == 0 && M_I != 0)
                            || (y == 14 && M_J < 14)) count++;
                        if((M_I == 15 && x < 14) || (M_J == 15 && y < 14))count++;

                    }
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    return count;

}

int Interface::LinkS5(int x,int y, Map map)
{
    int a[2][7]={{1,0,1,1,1,0,1},{2,0,2,2,2,0,2}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;
    num = map[x][y];
    Old_x = x;
    Old_y = y;
    for(int i = 0;i < 2; i++)
    {
        if(num != a[i][0]) continue;
        for(int j = 0;j < 2; j++)
        {
            for(int k = 0; k < 4; k++){
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 6;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 7))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 7 && j == 0) || (A_J < 0 && j == 1)) count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    return count;
}

int Interface::LinkS4(int x,int y, Map map)
{
    int a[2][7]={{1,0,1,0,1,0,1},{2,0,2,0,2,0,2}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;
    num = map[x][y];
    Old_x = x;
    Old_y = y;
    for(int i = 0; i < 2; i++)
    {
        if(num != a[i][0]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++){
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 6;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0&&A_J < 7))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 7 && j == 0) || (A_J < 0 && j == 1))count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    return count;
}

int Interface::LinkS3(int x,int y, Map map)
{
    int a[2][7]={{1,0,1,0,1,0,0},{2,0,2,0,2,0,0}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;
    num = map[x][y];
    Old_x = x;
    Old_y = y;
    for(int i = 0; i < 2; i++)
    {
        if(num != a[i][0]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 6;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 7))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 7 && j == 0) || (A_J < 0 && j == 1))count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }

    return count;
}

int Interface::LinkF5(int x,int y, Map map)
{
    int a[2][6]={{1,1,1,1,1},{2,2,2,2,2}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;

    num = map[x][y];
    Old_x = x;
    Old_y = y;

    for(int i = 0; i < 2; i++)
    {
        if(num != a[i][1]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0&& y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J=4;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 5 && j == 0) || ( A_J < 0 && j == 1)) count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }
    return count;
}

int Interface::LinkF4(int x,int y, Map map)
{
    int a[2][6]={{0,1,1,1,1,0},{0,2,2,2,2,0}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;

    num = map[x][y];
    Old_x = x;
    Old_y = y;

    for(int i = 0; i < 2; i++)
    {
        if(num != a[i][1]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 6 && j == 0) || (A_J < 0 && j == 1)) count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }
    return count;
}

int Interface::LinkF3(int x,int y, Map map)
{
    int a[4][6]={{0,1,1,0,1,0},{0,1,1,1,0,0},{0,2,2,0,2,0},{0,2,2,2,0,0}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;

    num = map[x][y];
    Old_x = x;
    Old_y = y;

    for(int i = 0; i < 4; i++)
    {
        if(num != a[i][1]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 6 && j == 0) || (A_J < 0 && j == 1)) count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }
    return count;
}

int Interface::LinkF2(int x,int y, Map map)
{
    int a[6][6]={{0,1,1,0,0,0},{0,1,0,1,0,0},{0,1,0,0,1,0},
    {0,2,2,0,0,0},{0,2,0,2,0,0},{0,2,0,0,2,0}};
    int b[4][2]={{-1,0},{0,-1},{-1,-1},{-1,1}};
    int M_I,M_J,count=0,A_J,Old_x,Old_y,num;
    num = map[x][y];
    Old_x = x;
    Old_y = y;
    for(int i = 0; i < 6; i++)
    {
        if(num != a[i][1]) continue;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                x = Old_x;
                y = Old_y;
                while(x >= 0 && y < 15 && x < 15 && y >= 0
                    && (map[x][y] == 0 || map[x][y] == num))
                {
                    M_I = x;
                    M_J = y;
                    if(j % 2) A_J = 5;
                    else A_J = 0;
                    while(M_I >= 0 && M_I < 15 && M_J >= 0 && M_J < 15
                        && (map[M_I][M_J] == a[i][A_J]) && (A_J >= 0 && A_J < 6))
                    {
                        M_I -= b[k][0];
                        M_J -= b[k][1];
                        if(j % 2) A_J--;
                        else A_J++;
                    }
                    if((A_J == 6 && j == 0) || (A_J < 0 && j == 1)) count++;
                    x += b[k][0];
                    y += b[k][1];
                }
            }
        }
    }
    return count;
}

int Interface::LinkF1(int x,int y, Map map)
{
    if(x < 15 && x >= 0 && y < 15 && y >= 0)
        return 1;
    return 0;
}

void Interface::scanMap(Tree *&pTree, int turn)
{
    Map record;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            record[i][j] = pTree->map[i][j];


    for(int level = 17; level > 0; level--)
    {

        int i = 7;
        int j = 7;
        int step = 0;
        int direct = 0;
        int direct_num = 1;

        while(i < 15 && j < 15 && i >= 0 && j >= 0)
        {
            if(record[i][j] == 0)
            {
                bool flag = false;
                record[i][j] = turn;

                if(PriorityGet(i, j, level, record) == 1)
                {
                    flag = true;
                    Tree *child = new Tree();
                    for (int p_i = 0; p_i < 15; p_i++)
                        for (int p_j = 0; p_j < 15; p_j++)
                            child->map[p_i][p_j] = record[p_i][p_j];
                    child->depth = pTree->depth + 1;
                    child->value = child->depth % 2 == 0 ? MIN : MAX;
                    child->first = -1;
                    child->cut = false;
                    child->father = pTree;
                    child->point[0] = i + 1;
                    child->point[1] = j + 1;
                    pTree->childs.push_back(child);
                    if (pTree->childs.size() == MAX_CHILDS)
                        return;
                }


                if (flag == false && level > 11)
                {
                    record[i][j] = 3 - turn;
                    if(PriorityGet(i, j, level, record) == 1)
                    {
                        record[i][j] = turn;
                        Tree *child = new Tree();
                        for (int p_i = 0; p_i < 15; p_i++)
                            for (int p_j = 0; p_j < 15; p_j++)
                                child->map[p_i][p_j] = record[p_i][p_j];
                        child->depth = pTree->depth + 1;
                        child->value = child->depth % 2 == 0 ? MIN : MAX;
                        child->first = -1;
                        child->cut = false;
                        child->father = pTree;
                        child->point[0] = i + 1;
                        child->point[1] = j + 1;
                        pTree->childs.push_back(child);
                        if (pTree->childs.size() == MAX_CHILDS)
                            return;
                    }
                }
                record[i][j] = 0;
            }

            step++;
            if(step > direct_num)
            {
                direct = (direct + 1) % 4;
                if(direct % 2 == 0)
                {
                    direct_num++;
                }
                step = 1;
            }

            i += dir[direct][0];
            j += dir[direct][1];
        }
    }
}

void Interface::alpha_beta(Tree* pTree)
{

    if (pTree->cut)
        return;

    if (pTree->depth >= SEARCH_DEPTH)
    {
        pTree->value = total_score(pTree->map, 2 - pTree->depth % 2);
        return;
    }


    scanMap(pTree, 2 - pTree->depth % 2);
    //print(pTree);

    int count = 0;


    for (vector<Tree*>::iterator it = pTree->childs.begin(); it != pTree->childs.end(); it++, count++)
    {
        alpha_beta(*it);
        int v = (*it)->value;
        if (pTree->first == -1)
        {
            pTree->value = v;
            pTree->first = count;
            pTree->firstPoint[0] = (pTree->childs.at(pTree->first))->point[0];
            pTree->firstPoint[1] = (pTree->childs.at(pTree->first))->point[1];
        }
        else if (pTree->depth % 2 == 0 && v >= pTree->value)
        {
            double p = (double)rand() / (double)(RAND_MAX);
            if (v > pTree->value || p > p_accept)
            {
                pTree->value = v;
                pTree->first = count;
                pTree->firstPoint[0] = (pTree->childs.at(pTree->first))->point[0];
                pTree->firstPoint[1] = (pTree->childs.at(pTree->first))->point[1];
            }
        }
        else if (pTree->depth % 2 != 0 && v <= pTree->value)
        {
            double p = (double)rand() / (double)(RAND_MAX);
            if (v < pTree->value || p > p_accept)
            {
                pTree->value = v;
                pTree->first = count;
                pTree->firstPoint[0] = (pTree->childs.at(pTree->first))->point[0];
                pTree->firstPoint[1] = (pTree->childs.at(pTree->first))->point[1];
            }
        }


        Tree *pF = pTree->father;
        while(pF != NULL)
        {
            if (((pTree->depth % 2 == 0 && pTree->value > pF->value) || (pTree->depth % 2 == 1 && pTree->value < pF->value))
                && pF->value != MIN && pF->value != MAX)
            {
                it++;


                while (it != pTree->childs.end())
                {
                    (*it)->cut = true;
                    cut++;
                    it++;
                }

                return;
            }

            pF = pF->father;
            if (pF != NULL)
                pF = pF->father;
            else
                break;
        }
    }
}

void Interface::clear(Tree* pTree)
{
    for (vector<Tree*>::iterator it = pTree->childs.begin(); it != pTree->childs.end(); it++)
        if (*it != NULL)
            delete *it;
    delete pTree;
}

bool Interface::addToMap(Map &map, int i, int j)
{
    if ((i >0 && i < 16 && j >0 && j < 16) && map[i-1][j-1] == 0)
    {
        if(color == true){
          color = false;
          map[i-1][j-1] = 1;
        }else if(color == false){
          color = true;
          map[i-1][j-1] = 2;
        }

        //map[i-1][j-1] = 2;
        return true;
    }
    else
        return false;
}

void Interface::computer_think(vector<vector<int> > & chessboard, int &N)
{
    Tree *thinkTree = new Tree();
    thinkTree->father = NULL;
    thinkTree->depth = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            currentMap[i][j]=chessboard[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            thinkTree->map[i][j] = currentMap[i][j];

    thinkTree->childs.clear();
    thinkTree->value = MIN;
    thinkTree->first = -1;
    thinkTree->cut = false;
    alpha_beta(thinkTree);
    if (thinkTree->first != -1)
    {
        int x, y;
        x = thinkTree->firstPoint[0];
        y = thinkTree->firstPoint[1];
        //cout<<"AI is coming..."<<endl;
        //cout<<x<<"&"<<y<<endl;
        bool flag=addToMap(currentMap, x, y);
        // drawMap(currentMap, x, y);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                chessboard[i][j]=currentMap[i][j];
    }
    else
    {
        cout << "Cannot find the position!" << endl;
    }
    clear(thinkTree);
}

void Interface::game_tree(vector<vector<int> > & chessboard, int &N)
{
    cout << "computer is thinking" << endl;
    cut = 0;
    computer_think(chessboard,N);
    //cout << "cut = " << cut << endl;
    //hand++;
}



