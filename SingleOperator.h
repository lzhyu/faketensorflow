#ifndef SINGLEOPERATOR
#include "Node.h"
#include"DoubleOperator.h"
#define SINGLEOPERATOR
class Cos;
class Sin;
class SingleOperator:public Node
{
protected:
	Node *a;
	virtual Tensor* calc(const Tensor&)=0;
	Tensor eval(std::map<std::string,Tensor>&);
	void Release()
	{
		a->Release();
		if(value!=nullptr)
		{
			delete value;
			value=nullptr;
		}
	}
public:
	SingleOperator(const std::string& _nm,Node &_a):Node(_nm),a(&_a){}
	void Rely(std::set<std::string>& lib){a->Rely(lib);}
	//����Ӳ���
	virtual void grad(map<Node*, Node*>& grads)override;//�ڲ����õ�grad
	virtual map<Node*, Node*>& grad()override;//���������õ�grad
};

class Exp:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(exp(A));}
public:
	Exp(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "exp("+a->Expr()+")";
	}
	//����Ӳ���
	virtual void input_gradient(map<Node*, Node*>& grads)override;//Ϊ�Լ��Լ��ӽڵ����ϵ��ͼ

};

class Ln:public SingleOperator//����˶����򾯸�
{
private:
	Tensor* calc(const Tensor& A){
		if (A.Value() < 0.00001)
		{
			cerr << " Error: log operator��s input must be positive" << endl;
		}
		return new Tensor(ln(A));}
public:
	Ln(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "ln("+a->Expr()+")";
	}
	//����Ӳ��֣�����������������ע�⣬���鲢û���޶���������Ҫ���ڴ���
	virtual void input_gradient(map<Node*, Node*>& grads)override;//Ϊ�Լ��Լ��ӽڵ����ϵ��ͼ

};

class Sin:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(sin(A));}
public:
	Sin(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "sin("+a->Expr()+")";
	}
	//����Ӳ���
	virtual void input_gradient(map<Node*, Node*>& grads)override;//Ϊ�Լ��Լ��ӽڵ����ϵ��ͼ

};

class Cos:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(cos(A));}
public:
	Cos(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "cos("+a->Expr()+")";
	}
	//����Ӳ���
	virtual void input_gradient(map<Node*, Node*>& grads)override;

};

class Tan:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(tan(A));}
public:
	Tan(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "tan("+a->Expr()+")";
	}
	//����Ӳ���
	virtual void input_gradient(map<Node*, Node*>& grads)override;//Ϊ�Լ��Լ��ӽڵ����ϵ��ͼ

};
class Asin:public SingleOperator//��Ӷ�������
{
private:
	Tensor* calc(const Tensor& A){
		if ((A.Value() > 1) || (A.Value()<-1))
		{
			cerr << "Error:Absolute value of Asin operator��s input must be greater than 1" << endl;
		}
		return new Tensor(asin(A));}
public:
	Asin(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "asin("+a->Expr()+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};

class Acos:public SingleOperator//��Ӷ�������
{
private:
	Tensor* calc(const Tensor& A){
		if ((A.Value() > 1) || (A.Value()<-1))
		{
			cerr << "Error:Absolute value of Acos operator��s input must be greater than 1" << endl;
		}
		return new Tensor(acos(A));}
public:
	Acos(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "acos("+a->Expr()+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};

class Atan:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A){return new Tensor(atan(A));}
public:
	Atan(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "atan("+a->Expr()+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};

class Quadratic:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Quadratic(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "Quadratic_Cost("+a->Expr()+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};

class Sigmoid:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Sigmoid(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "Sigmoid("+a->Expr()+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};

class Transpose:public SingleOperator
{
private:
	Tensor* calc(const Tensor& A);
public:
	Transpose(Node &_a,const std::string& _nm=""):SingleOperator(_nm,_a){}
	
	std::string Expr()
	{
		return "("+a->Expr()+")^T";
	}
};

class PowC:public SingleOperator
{
private:
	double c;
	Tensor* calc(const Tensor& A)override{return new Tensor(pow(A,c));}
public:
	PowC(Node &_a,double _c,const std::string& _nm=""):SingleOperator(_nm,_a),c(_c){}
	
	double C(){return c;}
	
	std::string Expr()
	{
		std::string pc=std::to_string(c);
		return "("+a->Expr()+"^"+pc+")";
	}
	virtual void input_gradient(map<Node*, Node*>& grads)override;
};
//��Ӳ���
class Assert :public SingleOperator
{
private:
	Tensor * calc(const Tensor& A) { return new Tensor(0); }
protected:
	Tensor eval(std::map<std::string, Tensor>&)override;
public:
	Assert(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

	std::string Expr()
	{
		return a->Expr();
	}
};

#endif
