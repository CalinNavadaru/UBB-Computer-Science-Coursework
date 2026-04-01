clc; clear; close all; format long;

function I = trapez_repetat(f, a, b, n)
    h = (b - a) / n;
    x = a + (1:n-1) * h;
    I = (b - a) / (2 * n) * (f(a) + 2 * sum(f(x)) + f(b));
end

function I = dreptunghi_repetat(f, a, b, n)
    h = (b - a) / n;
    x = a + h/2 : h : b - h/2;  
    I = h * sum(f(x));
end

function I = simpson_repetat(f, a, b, n)
    if mod(n, 2) ~= 0
        error('n trebuie sa fie par pentru formula Simpson.');
    end
    h = (b - a) / n;
    x = a:h:b;
    I = h/3 * (f(x(1)) + ...
        4 * sum(f(x(2:2:end-1))) + ...
        2 * sum(f(x(3:2:end-2))) + ...
        f(x(end)));
end


