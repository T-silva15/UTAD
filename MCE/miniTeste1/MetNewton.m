function [x,i] = MetNewton(x0,tol,show)
    % define iterator
    i=0;
    % define max loop count
    %nmax=50;

    % checks for number of arguments
    % logical variable that decides whether or not to show screen output
    % if nothing is specified default to true(show)
    if nargin < 3
        show = true;
    end
    
    % checks for number of arguments
    % if tolerance is not input, default it to 0.00005
    if nargin < 2 
        tol=0.5e-5; 
    end

    % initializes error 
    erro = 10000;

    % output check
    if show
        fprintf('Metodo Newton\n');
    end

    % main loop
    while (erro>tol) % &&(i<=nmax))
        % calculates value of function on point x0
        % Newton algorithm
        x = x0 - func(x0)/dfunc(x0);
        
        % calculates relative error of x0
        erro = abs(x-x0)/abs(x);
        
        % increments iterator
        i=i+1;

    % output check
    if show
        % prints values for that iteration
        fprintf('i = %3d     x = %.10f     erro = %.10f\n', i, x0,erro)
    end
        format long;
        x0=x;
    end
end