#include "Meow.h" 
void Add::Judge(const Tensor& A,const Tensor& B)const
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Add node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Add::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A+B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Add::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Sub
void Sub::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Sub node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Sub::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A-B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}		
	}
	return *value;
}

void Sub::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Mul
void Mul::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()&&B.Type()&&A.M()!=B.N())
		throw std::invalid_argument("Error : Mul node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Mul::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A*B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Mul::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Div
void Div::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Div node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Div::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A/B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Div::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Pow
void Pow::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Pow node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Pow::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(pow(A,B));
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Pow::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//比较运算符部分

//Greater
void Greater::Judge(const Tensor& A, const Tensor& B)const
{
	if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
		throw std::invalid_argument("Error : Greater node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Greater::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor A = a->eval(Inputs);
		Tensor B = b->eval(Inputs);
		Judge(A, B);
		value = new Tensor(A>B);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}

void Greater::Release()
{
	a->Release();
	b->Release();
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}

//Greater_Equal
void Greater_Equal::Judge(const Tensor& A, const Tensor& B)const
{
	if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
		throw std::invalid_argument("Error : Greater_Equal node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Greater_Equal::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor A = a->eval(Inputs);
		Tensor B = b->eval(Inputs);
		Judge(A, B);
		value = new Tensor(A >= B);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}

void Greater_Equal::Release()
{
	a->Release();
	b->Release();
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}

//Less
void Less::Judge(const Tensor& A, const Tensor& B)const
{
	if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
		throw std::invalid_argument("Error : Less node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Less::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor A = a->eval(Inputs);
		Tensor B = b->eval(Inputs);
		Judge(A, B);
		value = new Tensor(A<B);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}

void Less::Release()
{
	a->Release();
	b->Release();
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}

//Less_Equal
void Less_Equal::Judge(const Tensor& A, const Tensor& B)const
{
	if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
		throw std::invalid_argument("Error : Less_Equal node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Less_Equal::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor A = a->eval(Inputs);
		Tensor B = b->eval(Inputs);
		Judge(A, B);
		value = new Tensor(A >= B);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}

void Less_Equal::Release()
{
	a->Release();
	b->Release();
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}


//Bind
Tensor Bind::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor B = b->eval(Inputs);
		Tensor A = a->eval(Inputs);
		value = new Tensor(A);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}

void Bind::Release()
{
	a->Release();
	b->Release();
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}
//求导功能区
void Add::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	if (grads[b] == nullptr)
	{
		grads[b] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)(&((Node&)(*grads[a]) + (Node&)(*grads[this])));
	grads[b] = (Node*)&(*grads[b] + *grads[this]);
}

void Add::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
	b->grad(grads);
}
map<Node*, Node*>& Add::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	b->grad(*grads);
	return *grads;
}
//
void Sub::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	if (grads[b] == nullptr)
	{
		grads[b] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)(&(*grads[a] + *grads[this]));
	grads[b] = (Node*)&(*grads[b] - *grads[this]);
}

void Sub::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
	b->grad(grads);
}
map<Node*, Node*>& Sub::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	b->grad(*grads);
	return *grads;
}
//
void Mul::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	if (grads[b] == nullptr)
	{
		grads[b] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*(*b));
	grads[b] = (Node*)&(*grads[b] + (*grads[this])*(*a));
}

void Mul::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
	b->grad(grads);
}
map<Node*, Node*>& Mul::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	b->grad(*grads);
	return *grads;
}
//
void Div::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	if (grads[b] == nullptr)
	{
		grads[b] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this]) / (*b));
	grads[b] = (Node*)&(*grads[b] + (*grads[this])*(*a)*(*(new Constant(Tensor(-1))))/((*b)*(*b)));
}

void Div::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
	b->grad(grads);
}
map<Node*, Node*>&  Div::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	b->grad(*grads);
	return *grads;
}
//
void Pow::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	if (grads[b] == nullptr)
	{
		grads[b] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*((*b))*(*(new Pow(*a, (*b - *(new Constant(1)))))));
	grads[b] = (Node*)&(*grads[b] + (*grads[this])*(*(new Ln(*a))*(*this)));
}

void Pow::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
	b->grad(grads);
}
map<Node*, Node*>&  Pow::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	b->grad(*grads);
	return *grads;
}