function [retval] = fatorial(x)
    if (fix(x) == x && x >= 0)
        if x == 0
            retval = 1;
        else
            retval = 1;
            for i = 1:x
                retval = retval*i;
            end
        end
    end
end