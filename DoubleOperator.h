#ifndef DOUBLEOPERATOR
#include "Node.h"
#define DOUBLEOPERATOR  
using namespace std;;
class Add;
class Mul;
class Sub;
class Div;
Sub& operator -(Node& A, Node& B);
Add& operator+(Node& A, Node& B);
Mul& operator *(Node& A, Node& B);
Div& operator /(Node& A, Node& B);
class Add:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&)const; 
	Tensor eval(std::map<std::string,Tensor>&);
	void Release(); 
public:
	Add(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Add(const Add &t)=default;
	
	Add(Add &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"+"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
//求导功能区
	virtual void input_gradient(map<Node*, Node*>& grads)override;//为自己以及子节点的联系建图//怎么找grad
	virtual void grad(map<Node*, Node*>& grads)override;//内部调用的grad
	virtual map<Node*, Node*>& grad()override;//主函数调用的grad
};

class Sub:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor& );
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Sub(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Sub(const Sub &t)=default;
	
	Sub(Sub &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()	
	{
		return "("+a->Expr()+"-"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;//为自己以及子节点的联系建图//怎么找grad
	virtual void grad(map<Node*, Node*>& grads)override; //内部调用的grad
	virtual map<Node*, Node*>& grad()override;//主函数调用的grad
};

class Mul:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Mul(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Mul(const Mul &t)=default;
	Mul(Mul &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"*"+b->Expr()+")";
	}
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	//求导添加部分
	virtual void input_gradient(map<Node*, Node*>& grads)override;//为自己以及子节点的联系建图//怎么找grad
	virtual void grad(map<Node*, Node*>& grads)override;//内部调用的grad
	virtual map<Node*, Node*>& grad()override;//主函数调用的grad
};
class Div:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>& Inputs);
	void Release();
public:
	Div(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Div(const Div &t)=default;
	
	Div(Div &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"/"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	//求导添加部分
	virtual void input_gradient(map<Node*, Node*>& grads)override;//为自己以及子节点的联系建图//怎么找grad
	virtual void grad(map<Node*, Node*>& grads)override;//内部调用的grad
	virtual map<Node*, Node*>& grad()override;//主函数调用的grad
};

class Pow:public Node//没求导
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Pow(Node &_a,Node &_b,const std
		::string &_nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Pow(const Pow &t)=default;
	
	Pow(Pow &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"^"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	//求导
	virtual void input_gradient(map<Node*, Node*>& grads)override;//为自己以及子节点的联系建图//怎么找grad
	virtual void grad(map<Node*, Node*>& grads)override;//内部调用的grad
	virtual map<Node*, Node*>&  grad()override;//主函数调用的grad
};
//比较运算符添加部分
class Greater :public Node
{
private:
	Node * a, *b;
	void Judge(const Tensor&, const Tensor&)const;
	Tensor eval(std::map<std::string, Tensor>&);
	void Release();
public:
	Greater(Node &_a, Node &_b, const std::string& _nm = "") :Node(_nm), a(&_a), b(&_b) {}
	Greater(const Greater &t) = default;

	Greater(Greater &&t) :Node(t.name, t.value)
	{
		a = t.a; b = t.b;
		debug = t.debug;
		t.a = t.b = nullptr;
		t.value = nullptr;
	}

	std::string Expr()
	{
		return "(" + a->Expr() + ">" + b->Expr() + ")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Greater_Equal :public Node
{
private:
	Node * a, *b;
	void Judge(const Tensor&, const Tensor&)const;
	Tensor eval(std::map<std::string, Tensor>&);
	void Release();
public:
	Greater_Equal(Node &_a, Node &_b, const std::string& _nm = "") :Node(_nm), a(&_a), b(&_b) {}
	Greater_Equal(const Greater_Equal &t) = default;

	Greater_Equal(Greater_Equal &&t) :Node(t.name, t.value)
	{
		a = t.a; b = t.b;
		debug = t.debug;
		t.a = t.b = nullptr;
		t.value = nullptr;
	}

	std::string Expr()
	{
		return "(" + a->Expr() + ">=" + b->Expr() + ")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Less :public Node
{
private:
	Node * a, *b;
	void Judge(const Tensor&, const Tensor&)const;
	Tensor eval(std::map<std::string, Tensor>&);
	void Release();
public:
	Less(Node &_a, Node &_b, const std::string& _nm = "") :Node(_nm), a(&_a), b(&_b) {}
	Less(const Less &t) = default;

	Less(Less &&t) :Node(t.name, t.value)
	{
		a = t.a; b = t.b;
		debug = t.debug;
		t.a = t.b = nullptr;
		t.value = nullptr;
	}

	std::string Expr()
	{
		return "(" + a->Expr() + "<" + b->Expr() + ")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Less_Equal :public Node
{
private:
	Node * a, *b;
	void Judge(const Tensor&, const Tensor&)const;
	Tensor eval(std::map<std::string, Tensor>&);
	void Release();
public:
	Less_Equal(Node &_a, Node &_b, const std::string& _nm = "") :Node(_nm), a(&_a), b(&_b) {}
	Less_Equal(const Less_Equal &t) = default;

	Less_Equal(Less_Equal &&t) :Node(t.name, t.value)
	{
		a = t.a; b = t.b;
		debug = t.debug;
		t.a = t.b = nullptr;
		t.value = nullptr;
	}

	std::string Expr()
	{
		return "(" + a->Expr() + "<=" + b->Expr() + ")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Bind :public Node
{
private:
	Node * a, *b;
	Tensor eval(std::map<std::string, Tensor>&);
	void Release();
public:
	Bind(Node &_a, Node &_b, const std::string& _nm = "") :Node(_nm), a(&_a), b(&_b) {}
	Bind(const Bind &t) = default;

	Bind(Bind &&t) :Node(t.name, t.value)
	{
		a = t.a; b = t.b;
		debug = t.debug;
		t.a = t.b = nullptr;
		t.value = nullptr;
	}

	std::string Expr()
	{
		return "(bind" + a->Expr() + " with " + b->Expr() + ")";
	}

	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};
//比较运算符添加结束
inline Add& operator +(Node& A,Node& B)
{
	Add* tmp=new Add(A,B);
	return *tmp;
} 

inline Sub& operator -(Node& A,Node& B)
{
	Sub* tmp=new Sub(A,B);
	return *tmp;
}

inline Mul& operator *(Node& A,Node& B)
{
	Mul* tmp=new Mul(A,B);
	return *tmp;
}

inline Div& operator /(Node& A,Node& B)
{
	Div* tmp=new Div(A,B);
	return *tmp;
}

inline Pow& operator ^(Node& A,Node& B)
{
	Pow* tmp=new Pow(A,B);
	return *tmp;
}
//比较运算
inline Greater& operator >(Node& A, Node& B)
{
	Greater* tmp = new Greater(A, B);
	return *tmp;
}

inline Greater_Equal& operator >=(Node& A, Node& B)
{
	Greater_Equal* tmp = new Greater_Equal(A, B);
	return *tmp;
}

inline Less& operator <(Node& A, Node& B)
{
	Less* tmp = new Less(A, B);
	return *tmp;
}

inline Less_Equal& operator <=(Node& A, Node& B)
{
	Less_Equal* tmp = new Less_Equal(A, B);
	return *tmp;
}
#endif
