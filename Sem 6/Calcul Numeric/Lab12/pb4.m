clc; clear; close all; format long;


function p = succesiuni(g, p0, tol, Nmax)
    for i = 1:Nmax
        p = g(p0);
        if abs(p - p0) < tol
            return;
        end
        p0 = p;
    end
    p = p0;
end
