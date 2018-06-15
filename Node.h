#ifndef NODE
#include <string>
#include <map>
#include <set>
#include "Tensor.h"
#define NODE
using namespace std;
class Constant;
class Node
{
protected:
	bool debug;
	std::string name;
	Tensor* value;
public:
	Node(const std::string& _name,Tensor* _t=nullptr):debug(false),name(_name),value(_t){}
	
	Node(const Node& t):debug(t.debug),name(t.name),value(nullptr)
	{
		if(t.value!=nullptr)
			value=new Tensor(*(t.value));
	}
	
	Node(Node&& t):debug(t.debug),name(t.name),value(t.value)
	{
		t.value=nullptr;
	}
	
	~Node()
	{
		if(value!=nullptr)delete value;
	}
	
	void Debug()
	{
		debug=true;
	}
	
	void NDebug()
	{
		debug=false;
	}
	
	std::string Name(){return name;}
	
	std::string PrintExpr()
	{
		return name+" = "+Expr()+"\n";
	}
	virtual std::string Expr()=0;
	virtual void Rely(std::set<std::string>&)=0;//����������ڵ� 
	std::string PrintRely();
	virtual Tensor eval(std::map<std::string,Tensor>&)=0;//��ֵ 
	virtual void Release()=0;//�ͷű����ֵ 
	Tensor Eval(std::map<std::string,Tensor>&);//ʹ��map 
	Tensor Eval(const std::initializer_list<std::pair<std::string,Tensor>>&);//ʹ�ó�ʼ���б� 
	//����Ϊ���Ӳ���
	virtual void input_gradient(map<Node*, Node*>&) {};
	virtual map<Node*, Node*>& grad() {
		return *(new map<Node*, Node*>);
	};//û�ã�ֻ��Ϊ���ṩĬ��ʵ��
	virtual void grad(map<Node*, Node*>& grads) 
	{
		input_gradient(grads);
	}
	//�ڲ����õ�grad


};


#endif
/*
��ͼ������
grad��ͼ
���۽�����ͼ��gradӦ����һ��map��ֵӦ���ǽڵ��ڵ�ָ�����ͣ���ô����ڵ�Ӧ����ԭ�ڵ���������Ȼ���ǣ���Ϊ����ڵ�����ͼ�еĽڵ�
ͨ�����Ͻڵ�������һЩ�����ܲ�������������Ĺ����أ�
����ָ�������˫��ָ��
Ȼ��ÿ�������󵼹��򶼲���ͬ�����ǿ�����һ����return gradȨ���麯�����ýڵ㷵���ӽڵ��ƫ����ֵ����Ȼ��ֵ������δ���ģ�
������ָ��ڵ��ָ�룩


����ԭ�ڵ���



eval���㣨ȫ�µ�eval��
������������Ҫȫ�µ�������򣬼�һ�ֵݹ����ϵĹ����ӽڵ�value+=��Ȩ*���ڵ�
����ôȷ���ӽڵ��ֵ�������ֵ?���Դ˴���Ҫ���ӽڵ��˫��ָ��
��Ȩ������������ָ��ĳ������ָ�룬����ʱ����getvalue
grad����ֵʵ������һ��ͼ�����нڵ��ָ���б�
����������ʱʵ�����¶��ϵĸ�ֵ����
��ȻҪ���󵼳���Ҳ��һ���ڵ㣬������Щ�ڵ�֧�����㣬��ôeval����Ӧ�ö��½ڵ���Ȼ���ã������½���valueӦ�þ���Node��value����ô�ɼ�
ƫ������ֵӦ�ñ�����value���Ȼ�����ֵ��û���������ʵ�ʼ����ʱ��Ӧ����������ͼ�����eval_1���㣬Ȼ������󵼽ڵ��ڲ���eval����



����ͼ��������ԭeval������ͼ���ճ��㣬��ԭ�ڵ�������һЩ�����ͳ�Ա�Ա�������
ע�⣬��ͼ��ԭͼ������ȫһ��
���ܵ����⣺


*/