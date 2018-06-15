#ifndef CONSTANT
#include "Node.h"
#define CONSTANT
class Constant:public Node
{
private:
	Tensor eval(std::map<std::string,Tensor>&); 
	void Release(){} 
public:
	Constant(const Tensor& _t,const std::string& _nm=""):Node(_nm,new Tensor(_t)){}
	std::string Expr()
	{
		return std::string("Constant(")+name+")";
	}
	void Rely(std::set<std::string>& lib){}
	//����Ӳ���
	virtual map<Node*, Node*>& grad()//���������õ�grad
	{
		Node* gradnode = new Constant(Tensor(1));
		map<Node*, Node*> &grads = *(new map<Node*, Node*>);
		grads[this] = gradnode;
		input_gradient(grads);//����һ��Ҫע���е��ӽڵ��gradnode�ǲ����ڵ�
		return grads;
	}
	
};



#endif
