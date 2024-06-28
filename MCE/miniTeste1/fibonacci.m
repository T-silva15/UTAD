size = input('Tamanho do Fibonacci: ');
fib = ones(1,size);
i = 3;

% while loop
%while (i<=size)
%    fib(i) = fib(i-1) + fib(i-2);
%    i = i + 1;
%end

for i = 3:size        
    fib(i) = fib(i-1) + fib(i-2);
end

i = 1;
while (i<=size)
    fprintf("Fibonacci %.0f: %.0f \n",i, fib(i))
    i=i+1;
end