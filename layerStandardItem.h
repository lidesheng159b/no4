#pragma once
#include <qstandarditemmodel.h>
#include "layerTreeItem.h"

/// <summary>
/// �����Լ���QstandItem ����Ŀ.
/// </summary>
class layerStandardItem :public QStandardItem
{
public:

	using QStandardItem::QStandardItem; // �� QStandardItem �����ռ��е� QStandardItem ���Ա���뵱ǰ������

	layerStandardItem() : QStandardItem() { // ������Ϊ layerStandardItem �Ĺ��캯��
		//ð�ź����QStandardItem()��ʾ����QStandardItem���Ĭ�Ϲ��캯�������������Ķ���
		//�����ڵ�ǰ��Ĺ��캯���ڣ����ȵ���QStandardItem��Ĺ��캯������ʼ�����࣬Ȼ��ִ��InitData��������������еĳ�ʼ��������
		InitData(); // ���� InitData ������ʼ������
	}

	layerStandardItem(const QString& str) :QStandardItem(str)
	{
		InitData();
		gTreeData->gName = str.toStdString().c_str(); //��QString���͵Ĳ���ת��ΪC����ַ���(const char*)
	}

	~layerStandardItem();
	
	std::shared_ptr<layerTreeItem> gTreeData{ nullptr };//����ָ�룬<>����Ϊģ�����

private:

	void InitData();

};

