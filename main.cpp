#include "Meow.h" 
//#include <bits/stdc++.h> 
float NewtonMethod(Node* topnode,Node* var)
{
int num=0;
	float x=-1;//x是解的位置
	float diff = 1000;
	while(abs(diff)>0.0001)
	{
	Node* node1 = (topnode->grad())[var];
	diff=(((*topnode)/(*node1)).Eval({{"x1",x}})).Value();
	x-=diff;
	cout<<"Round: "<<num<<endl;
	cout<<"x="<<x<<endl;
	num++;
	}
	cout << "Result:" << endl;
	cout << x;
	return x;
}

int main() 
{
	/*auto x = Placeholder(3, 3, "x");
	auto y = Placeholder("y");
	auto z = Constant(3, "z");
	auto v = Variable(3, 3, "v");
	auto t = x + (v ^ y);
	double **M1 = new double* [3];
	M1[0] = new double [3]{10, 0, 0};
	M1[1] = new double [3]{0, 10, 0};
	M1[2] = new double [3]{0, 0, 10};
	Tensor a(3, 3, M1);
	v.Set(a);
	v.Add(a);
	std::cout << t.Eval({{"x", a}, {"y", 2}}).Print();
	auto t2 = Ln(t);
	t.Debug();
	std::cout << t2.Eval({{"x", a}, {"y", 2}}).Print();
	std::cout << t2.PrintRely();
	std::cout << t2.PrintExpr();*/
	/*auto x = Constant(2);
	auto y = Constant(3);
	Add z = x + y;
	auto t = z * x;
	map<Node*,Node*>& c=t.grad();
	cout <<c.size() << endl;
	std::cout << (c[&y]->grad())[&x]->Eval({}).Print() <<endl;;
	std::cout << c[&x]->Eval({}).Print()<<endl;*/
	//求导测试
	/*auto x = Placeholder("1");
	auto y = Placeholder("2");
	auto t = x * x;
	auto L = t /y;
	auto test = Constant(1);
	auto grads = L.grad();
	std::cout << grads[&y]->Eval({ {"1",3},{"2",2} }).Print() << endl;
	std::cout << grads[&t]->Eval({ { "1",3 },{ "2",2 } }).Print() << endl;
	std::cout << grads[&x]->Eval({ { "1",3 },{ "2",2 } }).Print() << endl;
	cout<<(grads[&y]->grad())[&x]->Eval({ { "1",3 },{ "2",2 } }).Print() << endl;*/
	//求导测试2
	/*auto x = Constant(2);
	auto y = Constant(4);
	auto z = *(new Exp(x/y))+*(new Ln(x));
	auto w = Sigmoid(*(new Sin(z)));
	auto grads = w.grad();
	cout << grads[&y]->Eval({}).Print() << endl;
	cout << grads[&x]->Eval({}).Print() << endl;*/
	//牛顿迭代法测试
	/*auto x1 = Placeholder("x1");
	auto c3 = Constant((3));
	auto c2 = Constant(2);
	auto c1 = Constant(1);
	auto f = x1*x1*x1*x1*x1+c3*x1*x1*x1+x1+c2*x1*x1+c1;
	*/
	//NewtonMethod(&f, &x1);
	//Ln测试
	auto x = Constant(-1);
	auto y = Ln(x);
	cout << y.Eval({}).Print() << endl;

	return 0;
}
// ConsoleApplication4.cpp: 定义控制台应用程序的入口点。
//
