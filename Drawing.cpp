#include<iostream>
#include"Drawing.h"
using namespace std;

Ui::IMGProClass* Dui = nullptr;

void ui_init(Ui::IMGProClass* ui_ptr)
{
    Dui = ui_ptr;
}





//--------------------------------------------------------
void DrawingContext::draw() {
    if (currentState)
    {
        currentState->draw();
    }
    else 
    {
        QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("还未选择绘制模式"));
    }
}

void DrawingContext::mousePressEvent(QMouseEvent* event) {
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("错误"));
    if (isSelecting == 0) {
        if (event->button() == Qt::LeftButton && currentState)
        {//检查为左键
            if (auto polygonState = dynamic_cast<DrawingPOLYGON*>(currentState) && isDrawing == 1) //若转换失败则退出
            {
                // 绘制多边形
                if (PL.isEmpty()) {
                    PL.push_back(QVector<QPoint>());//就加一个空栈
                }
                PL.back().append(event->pos());//将点添加到PL
                update();
            }
            else if (type == 5 && isDrawing == 1)//扇形
            {

            }
            else if (type == 4 && isDrawing == 1)//圆形
            {
                if (C.isEmpty()) {
                    C.push_back(QVector<QPoint>());//就加一个空栈
                }
                if (C.back().isEmpty()) {
                    C.back().append(event->pos());//将点添加到L
                }
                update();
            }
            else if (type == 1 && isDrawing == 1)//线
            {
                if (L.isEmpty()) {
                    L.push_back(QVector<QPoint>());//就加一个空栈
                }
                L.back().append(event->pos());//将点添加到L
                update();
            }
            else if (type == 2 && isDrawing == 1)//点
            {
                if (P.isEmpty()) {
                    P.push_back(QPoint());//就加一个空点
                }
                P.append(event->pos());//将点添加到P
                update();
            }

        }
    }
    if (isSelecting == 1) {
        if (event->button() == Qt::LeftButton) {
            currentState = nullptr;//置空
            QPoint p(event->x(), event->y());
            QVector<QVector<int>> temp;
            SEL = temp;//清空上一次的存储数组。
            //圆形(4)
            for (int i = 0; i < C.size(); i++)
            {
                if (circle.IsContain(p, C[i][0], C[i][1]))
                {
                    SEL.push_back(QVector<int>());
                    SEL.back().push_back(4);
                    SEL.back().push_back(i);
                }
            }
        }
    }
}

void DrawingContext::mouseReleaseEvent(QMouseEvent* event) {
    if (type == 4 && isDrawing == 1) 
    {
        if (C.back().size() == 2) {
            QPoint temp = QPoint(event->pos());
            C.back()[1] = temp;//修改第二个点
            isDrawing = 0;
            update();
        }
    }
 
}

void DrawingContext::mouseMoveEvent(QMouseEvent* event) {
    setMouseTracking(true);//实时检测鼠标位置
    if (type == 4 && isDrawing == 1)//用于圆形的实时绘制
    {
        if (C.isEmpty()) { C.append(QVector<QPoint>()); }//防止空栈
        if (C.back().size() == 1 || C.back().size() == 2) {
            QPoint temp = QPoint(event->pos());
            if (C.back().size() == 1) {
                C.back().append(temp);
            }
            C.back().last() = temp;//修改第二个点
            update();
        }
    }
    if (isSelecting == 1 && SEL.size() != 0)//处于选中状态且选中了图形
    {
        double dx, dy;
        if (event->buttons() & Qt::LeftButton)//左键一直按下
        {
            p2 = event->pos();//p2与p1有次序，p1每次会记录p2上次的位置，作为平移的x,y小量增加基准。
            if (p1.x() != 0 && p1.y() != 0)//跳过第一次，即让p1记录第一次p2的位置。
            {
                dx = p2.x() - p1.x();//标识平移距离
                dy = p2.y() - p1.y();//标识平移距离
                if (SEL[c][0] == 1)
                {
                    L[SEL[c][1]][0].rx() += dx;
                    L[SEL[c][1]][0].ry() += dy;
                    L[SEL[c][1]][1].rx() += dx;
                    L[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 2)
                {
                    C[SEL[c][1]][0].rx() += dx;
                    C[SEL[c][1]][0].ry() += dy;
                    C[SEL[c][1]][1].rx() += dx;
                    C[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 3)
                {
                    T[SEL[c][1]][0].rx() += dx;
                    T[SEL[c][1]][0].ry() += dy;
                    T[SEL[c][1]][1].rx() += dx;
                    T[SEL[c][1]][1].ry() += dy;
                    T[SEL[c][1]][2].rx() += dx;
                    T[SEL[c][1]][2].ry() += dy;
                }
                else if (SEL[c][0] == 4)
                {
                    R[SEL[c][1]][0].rx() += dx;
                    R[SEL[c][1]][0].ry() += dy;
                    R[SEL[c][1]][1].rx() += dx;
                    R[SEL[c][1]][1].ry() += dy;
                    R[SEL[c][1]][2].rx() += dx;
                    R[SEL[c][1]][2].ry() += dy;
                    R[SEL[c][1]][3].rx() += dx;
                    R[SEL[c][1]][3].ry() += dy;
                }
                else if (SEL[c][0] == 5)
                {
                    for (int i = 0; i < PL[SEL[c][1]].size(); i++)
                    {
                        PL[SEL[c][1]][i].rx() += dx;
                        PL[SEL[c][1]][i].ry() += dy;
                    }
                }
            }
            p1 = p2;
            update();//窗口重绘函数
        }
    }
    if (is_cut == true)
    {
        if (event->buttons() & Qt::LeftButton)//左键一直按下
        {
            p2 = event->pos();
            update();
        }
    }
    return QWidget::mouseMoveEvent(event);
}

void DrawingContext::keyPressEvent(QKeyEvent* event) 
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Plus) {//+号添加，回车结束绘制
        if (type == 3) {//多边形
            PL.push_back(QVector<QPoint>());//就加一个空栈
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
             type = 0;
             isDrawing = 0;
            }
            update();
        }
        if (type == 4) {//圆形
            C.push_back(QVector<QPoint>());//就加一个空栈
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            update();
        }
        if (type == 1) {//线
            L.push_back(QVector<QPoint>());//就加一个空栈
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            update();
        }
        if (type == 2) {//点
            P.push_back(QPoint());
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            update();
        }
    }
    
    else {
        update();
    }
   
}

void DrawingContext::paintEvent(QPaintEvent* event)
{
    //QWidget::paintEvent(event); // 调用父类的paintEvent，确保默认绘图操作也会执行
    QPainter painter(this);//界面画笔设置
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    painter.setPen(QPen(Qt::black, 3));//画笔设置
    QPainter painter_t;
    if (currentState) {
        painter_t.begin(&currentState->m_Pixmap); // 在条件语句内部开始绘制
        painter_t.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
        painter_t.setPen(QPen(Qt::black, 3));//画布画笔设置
    }
    //此时终止绘制，只把那些已经绘制完的按照pixmap投上去
    if (type == 0&& isDrawing==0&& currentState) 
    {
        QPixmap temp = currentState->GetPixmap();
        painter.drawPixmap(0, 0, temp);
        
    }
    //画线(1)
    if (currentState ) {
        for (int i = 0; i < L.size(); i++)
        {
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            painter.setPen(QPen(Qt::black, 3));//画笔设置
            painter_t.setPen(QPen(Qt::black, 3));//画笔设置
            painter.drawPolyline(L.at(i).data(), L.at(i).size());
            painter_t.drawPolyline(L.at(i).data(), L.at(i).size());
            
            for (int j = 0; j < L.at(i).size(); j++)
            {
                painter.setPen(QPen(Qt::blue, 5));//画笔设置
                painter_t.setPen(QPen(Qt::blue, 5));//画笔设置
                painter.drawPoint(L.at(i).at(j));
                painter_t.drawPoint(L.at(i).at(j));

            }

        }
    }
    //画点(2)
    if (currentState) {
        for (int i = 0; i < P.size(); i++)
        {
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            
            painter.setPen(QPen(Qt::black, 3));//画笔设置
            painter_t.setPen(QPen(Qt::black, 3));//画笔设置
            painter.drawPoints(P.data(),P.size());
            painter_t.drawPoints(P.data(), P.size());

        }
    }
   
    //画多边形(3)
    if (currentState)
    {
        for (int i = 0; i < PL.size(); i++)
        {
            //if (i == 0) currentState->m_Pixmap.fill(Qt::white);
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            painter.setPen(QPen(Qt::black, 3));//画笔设置
            painter_t.setPen(QPen(Qt::black, 3));//画笔设置
            painter.drawPolygon(PL.at(i).data(), PL.at(i).size());
            painter_t.drawPolygon(PL.at(i).data(), PL.at(i).size());
            for (int j = 0; j < PL.at(i).size(); j++)
            {
                painter.setPen(QPen(Qt::blue, 5));//画笔设置
                painter_t.setPen(QPen(Qt::blue, 5));//画笔设置
				painter.drawPoint(PL.at(i).at(j));
                painter_t.drawPoint(PL.at(i).at(j));
			}
            
        }
    }
    //画圆形(4)
    if (currentState ) {
        int radius = 0;
        
        for (int i = 0; i < C.size(); i++)
        {
            if (C.at(i).size() == 2)
            {
                int radius = qSqrt(qPow(C.at(i)[0].x() - C.at(i)[1].x(), 2) + qPow(C.at(i)[0].y() - C.at(i)[1].y(), 2));
               
                if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
                painter.setPen(QPen(Qt::black, 3));//画笔设置
                painter_t.setPen(QPen(Qt::black, 3));//画笔设置
                painter.drawEllipse(C.at(i)[0], radius, radius);
                painter_t.drawEllipse(C.at(i)[0], radius, radius);
                for (int j = 0; j < 1; j++)
                {
                    painter.setPen(QPen(Qt::blue, 5));//画笔设置
                    painter_t.setPen(QPen(Qt::blue, 5));//画笔设置
                    painter.drawPoint(C.at(i).at(j));
                    painter_t.drawPoint(C.at(i).at(j));
                }
            }

        }
    }
    //画扇形
    if (currentState && type == 1) {

    }

}

//****************************************************//
//              判断是否在图形内                       //
//                                                    //
// ***************************************************//
bool DrawingPOLYGON::isContain(QPoint& p, QVector<QPoint> s)
{
    if (s[0].x() == s[1].x())
    {
        QPoint p1 = s[0];
        QPoint p2 = s[2];
        if (p1.x() < p2.x() && p1.y() < p2.y())
        {
            if (p.x() >= p1.x() && p.x() <= p2.x() && p.y() >= p1.y() && p.y() <= p2.y())
                return true;
            else return false;
        }
        else if (p1.x() < p2.x() && p1.y() > p2.y())
        {
            if (p.x() >= p1.x() && p.x() <= p2.x() && p.y() >= p2.y() && p.y() <= p1.y())
                return true;
            else return false;
        }
        else if (p1.x() > p2.x() && p1.y() > p2.y())
        {
            if (p.x() >= p2.x() && p.x() <= p1.x() && p.y() >= p2.y() && p.y() <= p1.y())
                return true;
            else return false;
        }
        else if (p1.x() > p2.x() && p1.y() < p2.y())
        {
            if (p.x() >= p2.x() && p.x() <= p1.x() && p.y() >= p1.y() && p.y() <= p2.y())
                return true;
            else return false;
        }
    }
    else
    {
        int i, j = s.size() - 1;
        bool oddNodes = false;
        for (i = 0; i < s.size(); i++)
        {
            if (s[i].ry() < p.ry() && s[j].ry() >= p.ry() || s[j].ry() < p.ry() && s[i].ry() >= p.ry())
            {
                if (s[i].x() + (p.y() - s[i].y()) / (s[j].y() - s[i].y()) * (s[j].x() - s[i].x()) < p.x())
                    oddNodes = !oddNodes;
            }
            j = i;
        }
        return oddNodes;
    }
}

bool DrawingCIRCLE::IsContain(QPoint& p, QPoint p1, QPoint p2)
{
    int radius0 = qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
    int radius1 = qSqrt(qPow(p1.x() - p.x(), 2) + qPow(p1.y() - p.y(), 2));
    if (radius0 > radius1) {
        return true;
    }
    else return false;
}


