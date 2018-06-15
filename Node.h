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
	virtual void Rely(std::set<std::string>&)=0;//依赖的输入节点 
	std::string PrintRely();
	virtual Tensor eval(std::map<std::string,Tensor>&)=0;//求值 
	virtual void Release()=0;//释放保存的值 
	Tensor Eval(std::map<std::string,Tensor>&);//使用map 
	Tensor Eval(const std::initializer_list<std::pair<std::string,Tensor>>&);//使用初始化列表 
	//以下为增加部分
	virtual void input_gradient(map<Node*, Node*>&) {};
	virtual map<Node*, Node*>& grad() {
		return *(new map<Node*, Node*>);
	};//没用，只是为了提供默认实现
	virtual void grad(map<Node*, Node*>& grads) 
	{
		input_gradient(grads);
	}
	//内部调用的grad


};


#endif
/*
建图方案：
grad建图
不论建不建图，grad应该是一个map，值应该是节点或节点指针类型，那么这个节点应该是原节点类型吗？显然不是，因为这个节点是新图中的节点
通过在老节点中增加一些参数能不能满足求导运算的规则呢？
首先指针最好是双向指针
然后每个结点的求导规则都不相同，我们可以有一个叫return grad权的虚函数，该节点返回子节点的偏导数值（当然，值可以是未定的，
可以是指向节点的指针）


改造原节点类



eval计算（全新的eval）
问题是我们需要全新的运算规则，即一种递归向上的规则，子节点value+=边权*父节点
你怎么确定子节点的值就是这个值?所以此处需要父子节点的双向指针
边权变量，可能是指向某个结点的指针，计算时调用getvalue
grad返回值实际上是一个图中所有节点的指针列表
在真正计算时实现自下而上的赋值功能
既然要求求导出来也是一个节点，并且这些节点支持运算，那么eval函数应该对新节点仍然适用，所以新结点的value应该就是Node的value，那么可见
偏导数的值应该被存在value里，当然，这个值并没有算出来，实际计算的时候应该是先在新图里进行eval_1运算，然后进行求导节点内部的eval运算



建新图，不重载原eval，在新图里照常算，在原节点内增加一些操作和成员以便求导运算
注意，新图和原图并不完全一样
可能的问题：


*/