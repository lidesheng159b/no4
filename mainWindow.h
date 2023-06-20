#pragma once
#include <qstandarditemmodel.h>
#include <QtWidgets/QMainWindow>
#include "ui_IMGPro.h"
#include "Drawing.h"
#include<iostream>
//using namespace std;
//extern class DrawingContext;
class IMGPro : public QMainWindow
{
    Q_OBJECT

public:
    IMGPro(QWidget *parent = nullptr);
    ~IMGPro();
    void InitSource();//���ڳ�ʼ�����ͼ��
    void MakeDrawing();
private:
    DrawingContext drawingContext;//���һ��ͼ�������Ķ���
private:
    Ui::IMGProClass ui;//�����ui��IMGPro.ui��ϵ������
    QTreeView* treeView; // ���һ��QTreeView��Ա
    

private slots:  //qt�������﷨��д�ۺ���Ҫ������
    //void slot_try1();//���Բۺ���
    void on_treeView_customContextMenuRequested(const QPoint& pos);
    

public slots:
    //void showErrorDialog(const QString& errorMessage);
    void setStateInMain1(int i);
    void select_on();//����ѡ��

//signals:
    //void try1(int b);     // �����ź�
private: 
    QMenu* menu;//�˵�����ָ�룬������ʾͼ������������Ĳ˵�
    QStandardItemModel* model;//����ģ�Ͷ���ָ�룬���ڹ���ͼ������
    QStandardItem* rootItem1;//ͼ���ļ���1
    QStandardItem* rootItem2;//ͼ���ļ���2


};
