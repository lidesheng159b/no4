#include "layerStandardItem.h"
#include <memory>


layerStandardItem::~layerStandardItem()
{
	
}
void layerStandardItem::InitData()//��ȡ����
{
	if (gTreeData == nullptr) gTreeData = std::make_shared<layerTreeItem>();//��ʼ��һ��layerTreeItem������std::make_shared��װ��shared_ptr����
	// ���ø�item�ɹ�ѡ
	this->setCheckable(true);
	// ����item�ĳ�ʼ��ѡ״̬Ϊ�ѹ�ѡ
	this->setCheckState(Qt::Checked);
	// ����item���ɱ༭
	this->setEditable(false);
}