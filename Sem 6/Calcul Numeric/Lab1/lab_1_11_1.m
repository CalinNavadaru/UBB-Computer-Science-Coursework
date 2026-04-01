clc; clear; close all; format long;
syms x;
f = exp(x);
r = Taylor_symbolic_cu_rest(f, 6, 0);
disp('Full Taylor Expansion with Remainder:');
disp(r);
disp(subs(r, x, 0));

function T = Taylor_symbolic_cu_rest(f, n, x_val)
    syms x xi; 
    Tn = 0;
    for k = 0:n
        term = (subs(diff(f, x, k), x, x_val) / factorial(k)) * (x - x_val)^k;
        Tn = Tn + term;
    end
    Rn = (subs(diff(f, x, n+1), x, xi) / factorial(n+1)) * (x - x_val)^(n+1);
    T = Tn + Rn;
    
    disp('Taylor Series (without remainder):');
    disp(Tn);
    disp('Remainder Term (Lagrange form):');
    disp(Rn);
end
