% variable definition
a=2;
b=6;
c=-20;
delta = b^2 - 4*a*c;

% main expression
x1 = (-b - sqrt(delta))/(2*a);
x2 = (-b + sqrt(delta))/(2*a);

fprintf('x1 = %5.4f\n',x1)
fprintf('x2 = %5.4f\n',x2)

