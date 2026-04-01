clc; clear; close all; format long;

function p = steffensen(g, p0, tol, Nmax)
    for i = 1:Nmax
        p1 = g(p0);
        p2 = g(p1);
        p = p0 - (p1 - p0)^2 / (p2 - 2*p1 + p0);
        if abs(p - p0) < tol
            return;
        end
        p0 = p;
    end
    p = p0;
end
