clc; clear; close all; format long;

n = 4;
a = 0; b = 1;

[w, x] = newton_cotes_inchis(n, a, b);

disp('Noduri:');
disp(x);
disp('Coeficienți:');
disp(w);

function [w, x] = newton_cotes_inchis(n, a, b)
    syms t;
    h = (b - a) / n;
    x = linspace(a, b, n+1);
    w = zeros(1, n+1);

    for i = 1:n+1
        L = 1;
        for j = 1:n+1
            if j ~= i
                L = L * (t - x(j)) / (x(i) - x(j));
            end
        end
        w(i) = double(int(L, t, a, b));
    end
end
