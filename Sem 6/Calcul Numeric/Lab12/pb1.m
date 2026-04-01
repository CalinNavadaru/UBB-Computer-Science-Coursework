clc; clear; close all; format long;

function p = newton(f, df, p0, tol, Nmax)
    for i = 1:Nmax
        p = p0 - f(p0)/df(p0);
        if abs(p - p0) < tol
            return;
        end
        p0 = p;
    end
    p = p0;
end
