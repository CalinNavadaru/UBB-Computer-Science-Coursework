clc; clear; close all; format long;


function x = newton_sys(F, J, x0, tol, Nmax)
    for k = 1:Nmax
        delta = J(x0)\F(x0);
        x = x0 - delta;
        if norm(x - x0) < tol
            return;
        end
        x0 = x;
    end
    x = x0;
end
