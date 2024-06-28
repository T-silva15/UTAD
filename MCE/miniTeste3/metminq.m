format long
x =[-1,1,2];
y=[1.4,3.4,7.3];

% g(x) = ax/x+b
% Y = 1/y
% X = 1/x

%X=1./x;
X = x;

Y=(log(y)/log(3));

M=[3,sum(X);sum(X),sum(X.^2)];
N=[sum(Y);sum(Y.*X)];

sol=M\N;

A=sol(1)
B=sol(2)
%a=1/A;
%b=a*B;
a = A;
b = B;
% 
% erro=0;
% for i=1:5
%     erro=erro +( (a*x(i))/(x(i)+b) - y(i) )^2;
% end
% erro;
% erro=sqrt(erro)

