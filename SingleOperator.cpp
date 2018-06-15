#include "Meow.h" 
Tensor SingleOperator::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		value=calc(A);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}
//
void SingleOperator::grad(map<Node*, Node*>& grads)//内部调用的grad
{
	input_gradient(grads);//
	a->grad(grads);
}
map<Node*, Node*>& SingleOperator::grad()//主函数调用的grad
{
	Node* gradnode = new Constant(Tensor(1));
	map<Node*, Node*> *grads = (new map<Node*, Node*>);
	(*grads)[this] = gradnode;
	input_gradient(*grads);//在这一步要注意有的子节点的gradnode是不存在的
	a->grad(*grads);
	return *grads;
}
//input_gradient
void Exp::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图//怎么找grad
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*(*this));
}
void Ln::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])/(*a));
}
void Sin::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*(*(new Cos((*a)))));
}
void Cos::input_gradient(map<Node*, Node*>& grads)
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) - (*grads[this])*(*(new Sin((*a)))));
}
void Tan::input_gradient(map<Node*, Node*>& grads)//为自己以及子节点的联系建图
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this]) / (*(new Cos((*a))))*(*(new Cos((*a)))));
}
//
Tensor* Quadratic::calc(const Tensor& A)
{
	if(!(A.Type()))
		throw std::invalid_argument("Error : Quadratic_Cost node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	return new Tensor(A.Quadratic_Cost());
}

Tensor* Sigmoid::calc(const Tensor& A)
{
	Tensor *tmp=new Tensor(A);
	tmp->Sigmoid();
	return tmp;
}

Tensor* Transpose::calc(const Tensor& A)
{
	if(!A.Type())
		throw std::invalid_argument("Error : Transpose node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	Tensor *tmp=new Tensor(A.M(),A.N());
	tmp->Transpose(A);
	return tmp;
}

//!!!!!!!!!!!!!!!!!!!!MaybeFinished
Tensor Assert::eval(std::map<std::string, Tensor>& Inputs)
{
	if (value == nullptr)
	{
		Tensor A = a->eval(Inputs);
		if (!A.Type() && (A <= 0).Value())
			throw std::domain_error("Error : Assertion " + Expr() + " Failed");
		value = calc(A);
		if (debug)
		{
			std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
			std::cout << value->Print() << '\n';
		}
	}
	return *value;
}
void Asin::input_gradient(map<Node*, Node*>& grads)
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])/(*(new Pow(((*(new Constant(1)))-(*a)*(*a)),*(new Constant(0.5))))));
}
void Acos::input_gradient(map<Node*, Node*>& grads)
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) - (*grads[this]) / Pow(((*(new Constant(1))) - (*a)*(*a)), *(new Constant(0.5))));
}
void Atan::input_gradient(map<Node*, Node*>& grads)
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])/((*(new Constant(1)))+(*a)*(*a)));
}
void PowC::input_gradient(map<Node*, Node*>& grads)
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*(*(new Constant(c-1)))*(*(new PowC(*a,c-1))));
}
void Sigmoid::input_gradient(map<Node*, Node*>& grads)//
{
	if (grads[a] == nullptr)
	{
		grads[a] = new Constant(Tensor(0));
	}
	grads[a] = (Node*)&((*grads[a]) + (*grads[this])*(*this)*((*(new Constant(1))-*this)));
}




