#pragma once
#include "ui_IMGPro.h"
//#include"mainWindow.h"
#include "Useui.h"
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
//#include<qlabel.h>

void ui_init(Ui::IMGProClass* ui_ptr);
extern Ui::IMGProClass* Dui;//������һ��


// ����״̬��
class DrawingState:public QLabel {
	Q_OBJECT
public:
    virtual void draw() = 0;
    DrawingState(QWidget* parent = 0)
    {
        m_StartPoint = m_EndPoint = QPoint(0, 0);
        m_Pixmap = QPixmap(Dui->widget->width(), Dui->widget->height());
    };
 

public://����ͼ��չ��
    QPixmap m_Pixmap;
    QPoint m_StartPoint;
    QPoint m_EndPoint;
    QPixmap GetPixmap() { return m_Pixmap; }

public:
  void setStartPoint(QPoint point) {
		m_StartPoint = point;
	}
    void setEndPoint(QPoint point) {
		m_EndPoint = point;
    }


};

// ����״̬��
class DrawingLINESTRING : public DrawingState {
public:
    void draw() override {};
    

};//��

class DrawingPOLYGON : public DrawingState {
public:
    //QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
    void draw() override {};
    bool isContain(QPoint& p, QVector<QPoint> s);
};//�����

class DrawingPOINT:public DrawingState {
public:
    void draw() override {
        //QMessageBox::critical(Dui->centralWidget, QStringLiteral("��"), QStringLiteral("����"));
    };
};//��

class DrawingSECTOR:public DrawingState {
public:
    void draw() override {};
};//����

class DrawingCIRCLE :public DrawingState {
public:
    void draw() override {};
    bool IsContain(QPoint& p, QPoint p1, QPoint p2);//Բѡ��,��һ���ǵ���㣬�ڶ�����Բ�ģ���������Բ�ϵĵ�
};//Բ��

class DrawingTEXT :public DrawingState {
public:
    void draw() override;
};//�ı�

class DrawingBITMAP :public DrawingState {
public:
    void draw() override;
};//λͼ




// ��������
class DrawingContext:public QWidget {
    Q_OBJECT
private:
    DrawingState* currentState;//��ǰ״̬
    QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
public:
    DrawingContext(QWidget* parent = 0) : currentState(nullptr) {//��������������¼��Ͳ��ᱻTableWidget����

        setFocusPolicy(Qt::StrongFocus);
        
    }//��ʼ��
    //DrawingContext(QWidget* parent = 0) : currentState(nullptr) {}//��ʼ��
    // ���õ�ǰ״̬
    void setCurrentState(DrawingState* state) {
        currentState = state;
    }
    // ִ�л��Ʋ���
    void draw();
    // �¼�������
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event);

    //����
    int type;//��ʱ���Ƶ�����
    int c;//�����ѡ����
    int m_icount;//�������
    QPoint p1, p2;//ƽ�Ƽ�¼��
    QPoint init_1;//��ʼ�����¼�㡣
    QVector<QVector<QPoint>> C;//���Բ
    QVector<QVector<QPoint>> L;//�����
    QVector<QPoint> P;//��ŵ�
    QVector<QVector<QPoint>> T;//��������Ρ�
    QVector<QVector<int>> SEC;//������Ρ�
    QVector<QVector<QPoint>> PL;//��Ŷ���Ρ�
    QVector<QVector<int>> SEL;//�洢ѡ����Ϣ,1Ϊline,2Ϊpoint,3Ϊpolygon,4Ϊcircle,5Ϊ����,�ڶ�λ��Ϊ�����б�š�
    //���ú�����Ҫ
    DrawingPOLYGON polygon;
    DrawingLINESTRING line;
    DrawingPOINT point;
    DrawingSECTOR sector;
    DrawingCIRCLE circle;
    DrawingTEXT text;
    DrawingBITMAP bitmap;
    //������������
    bool isDrawing=0;//�Ƿ����
    bool isSelecting=0;//�Ƿ�ѡ��


};

////���󽻻�
//class Widget : public QWidget
//{
//    Q_OBJECT
//private:
//    bool m_MouseDown;
//protected:
//    void mousePressEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
//    void mouseReleaseEvent(QMouseEvent* event);
//    void paintEvent(QPaintEvent* event);
//public:
//    Widget(QWidget* parent = 0);
//    ~Widget();
//private slots:
//};

