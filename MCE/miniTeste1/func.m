function [y] = func(x)
    % function to be called in another script
    % returns value of x in a specified point of a function 
    %y = exp(-x) - x;
    % y = exp(x) - 3*x;
    % y = exp(x)/3;
    % y = -sqrt(exp(x-1));
    % y = x+1+atan(x);
    y = exp(6*x) + 1.441*exp(4*x) - 0.3330;
end