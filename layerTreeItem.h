#pragma once
#include <iostream>
#include <memory>
#include <list>
//#pragma execution_character_set("utf-8")    // ��������������⣬ע�⣡����
/// <summary>
/// Tree ����ͼԪ���ݽṹ
/// </summary>
class layerTreeItem
{
public:

    layerTreeItem() {};
    ~layerTreeItem() {};
    static long layerNumsID;//��̬��������¼������
    void SetData(const std::string& name);//���ý������

    int GUID;//���ID

    std::string gName{ "" };//�������

    std::shared_ptr<std::list<layerTreeItem>> gChilds{ nullptr };//�ӽڵ��б�

    std::string toString() const {
        return "ture dude";
    }
    
};

