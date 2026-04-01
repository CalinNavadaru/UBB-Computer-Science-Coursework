clc; clear; close all; format long;
A = [3, -13, 9, 3;
    -6, 4, 1, -18;
    6, -2, 2, 4;
    12, -8, 6, 10];
b = [-19; -34; 16; 26];
Ab = [A, b];
x_sol = A \ b;
disp('Soluția obținută:');
disp(x_sol);
disp("--------------------------------------");
disp('Solutie cu gauss:');
disp(gauss_elimination(Ab));

function x = gauss_elimination(A)
    [n, m] = size(A);
    if m ~= n + 1
        error('Matricea extinsa trebuie sa aiba n coloane + 1');
    end

    for i = 1:n-1
        [~, p] = max(abs(A(i:n, i)));
        p = p + i - 1;

        if A(p, i) == 0
            error('Nu exista solutie unica.');
        end

        if p ~= i
            A([i p], :) = A([p i], :);
        end

        for j = i+1:n
            mji = A(j, i) / A(i, i);
            A(j, :) = A(j, :) - mji * A(i, :);
        end
    end

    if A(n, n) == 0
        error('Nu exista solutie unica.');
    end

    x = zeros(n, 1);
    x(n) = A(n, end) / A(n, n);
    for i = n-1:-1:1
        suma = A(i, i+1:n) * x(i+1:n);
        x(i) = (A(i, end) - suma) / A(i, i);
    end
end