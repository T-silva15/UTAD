function y = DivDiff(x,y)

    if(length(x) > 1)
        y = (DivDiff( x(2 : length(x)) , y(2 : length(y) ) ) - DivDiff(x(1:length(x) -1) , y(1:length(y) -1 )) )/( x(length(x)) - x(1));
        return;
    end

end