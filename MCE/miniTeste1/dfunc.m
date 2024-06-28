function [y] = dfunc(x)
    % function to be called in another script
    % returns value of x in a specified point of a function derivative 
    % MUST CORRESPOND TO THE FUNCTION DEFINED IN FUNC.m
    
    % y = abs(x) - cos(x);
    y = 6*exp(6*x) + (1441*exp(4*x))/250;
    % y = exp(x) - 3;

end