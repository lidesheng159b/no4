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
        QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("��δѡ�����ģʽ"));
    }
}

void DrawingContext::mousePressEvent(QMouseEvent* event) {
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("����"));
    if (isSelecting == 0) {
        if (event->button() == Qt::LeftButton && currentState)
        {//���Ϊ���
            if (auto polygonState = dynamic_cast<DrawingPOLYGON*>(currentState) && isDrawing == 1) //��ת��ʧ�����˳�
            {
                // ���ƶ����
                if (PL.isEmpty()) {
                    PL.push_back(QVector<QPoint>());//�ͼ�һ����ջ
                }
                PL.back().append(event->pos());//������ӵ�PL
                update();
            }
            else if (type == 5 && isDrawing == 1)//����
            {

            }
            else if (type == 4 && isDrawing == 1)//Բ��
            {
                if (C.isEmpty()) {
                    C.push_back(QVector<QPoint>());//�ͼ�һ����ջ
                }
                if (C.back().isEmpty()) {
                    C.back().append(event->pos());//������ӵ�L
                }
                update();
            }
            else if (type == 1 && isDrawing == 1)//��
            {
                if (L.isEmpty()) {
                    L.push_back(QVector<QPoint>());//�ͼ�һ����ջ
                }
                L.back().append(event->pos());//������ӵ�L
                update();
            }
            else if (type == 2 && isDrawing == 1)//��
            {
                if (P.isEmpty()) {
                    P.push_back(QPoint());//�ͼ�һ���յ�
                }
                P.append(event->pos());//������ӵ�P
                update();
            }

        }
    }
    if (isSelecting == 1) {
        if (event->button() == Qt::LeftButton) {
            currentState = nullptr;//�ÿ�
            QPoint p(event->x(), event->y());
            QVector<QVector<int>> temp;
            SEL = temp;//�����һ�εĴ洢���顣
            //Բ��(4)
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
            C.back()[1] = temp;//�޸ĵڶ�����
            isDrawing = 0;
            update();
        }
    }
 
}

void DrawingContext::mouseMoveEvent(QMouseEvent* event) {
    setMouseTracking(true);//ʵʱ������λ��
    if (type == 4 && isDrawing == 1)//����Բ�ε�ʵʱ����
    {
        if (C.isEmpty()) { C.append(QVector<QPoint>()); }//��ֹ��ջ
        if (C.back().size() == 1 || C.back().size() == 2) {
            QPoint temp = QPoint(event->pos());
            if (C.back().size() == 1) {
                C.back().append(temp);
            }
            C.back().last() = temp;//�޸ĵڶ�����
            update();
        }
    }
    if (isSelecting == 1 && SEL.size() != 0)//����ѡ��״̬��ѡ����ͼ��
    {
        double dx, dy;
        if (event->buttons() & Qt::LeftButton)//���һֱ����
        {
            p2 = event->pos();//p2��p1�д���p1ÿ�λ��¼p2�ϴε�λ�ã���Ϊƽ�Ƶ�x,yС�����ӻ�׼��
            if (p1.x() != 0 && p1.y() != 0)//������һ�Σ�����p1��¼��һ��p2��λ�á�
            {
                dx = p2.x() - p1.x();//��ʶƽ�ƾ���
                dy = p2.y() - p1.y();//��ʶƽ�ƾ���
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
            update();//�����ػ溯��
        }
    }
    if (is_cut == true)
    {
        if (event->buttons() & Qt::LeftButton)//���һֱ����
        {
            p2 = event->pos();
            update();
        }
    }
    return QWidget::mouseMoveEvent(event);
}

void DrawingContext::keyPressEvent(QKeyEvent* event) 
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Plus) {//+����ӣ��س���������
        if (type == 3) {//�����
            PL.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
             type = 0;
             isDrawing = 0;
            }
            update();
        }
        if (type == 4) {//Բ��
            C.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            update();
        }
        if (type == 1) {//��
            L.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            update();
        }
        if (type == 2) {//��
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
    //QWidget::paintEvent(event); // ���ø����paintEvent��ȷ��Ĭ�ϻ�ͼ����Ҳ��ִ��
    QPainter painter(this);//���滭������
    painter.setRenderHint(QPainter::Antialiasing, true);//�����
    painter.setPen(QPen(Qt::black, 3));//��������
    QPainter painter_t;
    if (currentState) {
        painter_t.begin(&currentState->m_Pixmap); // ����������ڲ���ʼ����
        painter_t.setRenderHint(QPainter::Antialiasing, true);//�����
        painter_t.setPen(QPen(Qt::black, 3));//������������
    }
    //��ʱ��ֹ���ƣ�ֻ����Щ�Ѿ�������İ���pixmapͶ��ȥ
    if (type == 0&& isDrawing==0&& currentState) 
    {
        QPixmap temp = currentState->GetPixmap();
        painter.drawPixmap(0, 0, temp);
        
    }
    //����(1)
    if (currentState ) {
        for (int i = 0; i < L.size(); i++)
        {
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            painter.setPen(QPen(Qt::black, 3));//��������
            painter_t.setPen(QPen(Qt::black, 3));//��������
            painter.drawPolyline(L.at(i).data(), L.at(i).size());
            painter_t.drawPolyline(L.at(i).data(), L.at(i).size());
            
            for (int j = 0; j < L.at(i).size(); j++)
            {
                painter.setPen(QPen(Qt::blue, 5));//��������
                painter_t.setPen(QPen(Qt::blue, 5));//��������
                painter.drawPoint(L.at(i).at(j));
                painter_t.drawPoint(L.at(i).at(j));

            }

        }
    }
    //����(2)
    if (currentState) {
        for (int i = 0; i < P.size(); i++)
        {
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            
            painter.setPen(QPen(Qt::black, 3));//��������
            painter_t.setPen(QPen(Qt::black, 3));//��������
            painter.drawPoints(P.data(),P.size());
            painter_t.drawPoints(P.data(), P.size());

        }
    }
   
    //�������(3)
    if (currentState)
    {
        for (int i = 0; i < PL.size(); i++)
        {
            //if (i == 0) currentState->m_Pixmap.fill(Qt::white);
            if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
            painter.setPen(QPen(Qt::black, 3));//��������
            painter_t.setPen(QPen(Qt::black, 3));//��������
            painter.drawPolygon(PL.at(i).data(), PL.at(i).size());
            painter_t.drawPolygon(PL.at(i).data(), PL.at(i).size());
            for (int j = 0; j < PL.at(i).size(); j++)
            {
                painter.setPen(QPen(Qt::blue, 5));//��������
                painter_t.setPen(QPen(Qt::blue, 5));//��������
				painter.drawPoint(PL.at(i).at(j));
                painter_t.drawPoint(PL.at(i).at(j));
			}
            
        }
    }
    //��Բ��(4)
    if (currentState ) {
        int radius = 0;
        
        for (int i = 0; i < C.size(); i++)
        {
            if (C.at(i).size() == 2)
            {
                int radius = qSqrt(qPow(C.at(i)[0].x() - C.at(i)[1].x(), 2) + qPow(C.at(i)[0].y() - C.at(i)[1].y(), 2));
               
                if (i == 0) { currentState->m_Pixmap.fill(Qt::white); };
                painter.setPen(QPen(Qt::black, 3));//��������
                painter_t.setPen(QPen(Qt::black, 3));//��������
                painter.drawEllipse(C.at(i)[0], radius, radius);
                painter_t.drawEllipse(C.at(i)[0], radius, radius);
                for (int j = 0; j < 1; j++)
                {
                    painter.setPen(QPen(Qt::blue, 5));//��������
                    painter_t.setPen(QPen(Qt::blue, 5));//��������
                    painter.drawPoint(C.at(i).at(j));
                    painter_t.drawPoint(C.at(i).at(j));
                }
            }

        }
    }
    //������
    if (currentState && type == 1) {

    }

}

//****************************************************//
//              �ж��Ƿ���ͼ����                       //
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


