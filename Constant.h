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
	//求导添加部分
	virtual map<Node*, Node*>& grad()//主函数调用的grad
	{
		Node* gradnode = new Constant(Tensor(1));
		map<Node*, Node*> &grads = *(new map<Node*, Node*>);
		grads[this] = gradnode;
		input_gradient(grads);//在这一步要注意有的子节点的gradnode是不存在的
		return grads;
	}
	
};



#endif
