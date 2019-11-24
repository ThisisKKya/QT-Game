#include "hero.h"

hero::hero(QObject *parent) : QObject(parent)
{

}
void hero::HeroGoLeft()
{
    heroPosX-=3;

}
void hero::HeroGoRight()
{
    heroPosX+=3;
}
bool hero::HeroJump()
{
    JudgeWhatHeroMeets();
    if(heroPosY>groundY-HeroJumpHeight-HeroHeight && flag == 0 ) //跳跃的上界
    {
        heroPosY -= 4;
        qDebug()<<"向上";
    }
    else
    {
        flag = 1;
         qDebug()<<"到顶了";
    }
    if(heroPosY<groundY-HeroHeight && flag == 1) //跳跃的下界
    {
        heroPosY += 4;
        qDebug()<<"向下";
    }
    if(heroPosY>=groundY-HeroHeight && flag == 1)
    {
        return 1;
        qDebug()<<"到底了";
    }
    else
    {
       qDebug()<<"没到底";
        return 0;
    }
}
int hero::JudgeWhatHeroMeets()
{
    int BrickLeft = 400,BrickRight = 500,BrickTop = 480;//因为没有写好具体的砖块类, 因此砖块的大小暂时在这里用临时变量
                                                     //代替, 在砖块类写好后可以把这些量换成砖块的posXrange和posYrange
    int temp = 1 ;
    if(heroPosX>BrickLeft && heroPosX<BrickRight && heroPosY > BrickTop)
    {
        //这里表示的是跳到了砖块的上方,则修改原来的groundY地平线为BrickTop
        groundY = BrickTop;
        qDebug()<<"跳到了上面";
        temp = 2;
    }
    else if(temp == 2)
    {
        //没有则回到原来的地平线;  注意,如果有其他的地形同理
        groundY = 540;//MainWindow::GroundY是主窗口设定的地平线
        StartTimer();
        qDebug()<<"跳到低了吗?";
    }

return 0;
}
bool hero::HeroFallDown()
{
    if(heroPosY<groundY-HeroHeight && flag == 1) //跳跃的下界
    {
        heroPosY += 4;
        return 0;
    }
    else
    {
        return 1;
    }
}
