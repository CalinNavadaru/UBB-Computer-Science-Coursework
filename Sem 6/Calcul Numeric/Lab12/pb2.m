clc; clear; close all; format long;


function p = secant(f, p0, p1, tol, Nmax)
    q0 = f(p0);
    q1 = f(p1);
    for i = 2:Nmax
        p = p1 - q1*(p1 - p0)/(q1 - q0);
        if abs(p - p1) < tol
            return;
        end
        p0 = p1; q0 = q1;
        p1 = p; q1 = f(p);
    end
end
