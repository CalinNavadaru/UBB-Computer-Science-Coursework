clc; clear; close all; format long;

n = 4;
[A, b] = gen_sistem(n);
x_sol = A \ b;
Ab = [A, b];

disp('Soluția obținută:');
disp(x_sol);
disp("--------------------------------------");
disp('Solutie cu gauss:');
disp(gauss_elimination(Ab));
disp("--------------------------------------");
disp('Solutie cu LUP: ');
[L, U, P] = LUP_decomp(A);
disp(LUP_solve(L, U, P, b));

function [A, b] = gen_sistem(n)
    x_true = ones(n, 1); 

    while true
        A = rand(n);    
        if abs(det(A)) > 1e-8 
            break;
        end
    end

    b = A * x_true;     
end

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


function [L, U, P] = LUP_decomp(A)
    n = size(A, 1);
    P = eye(n);
    L = zeros(n);
    U = A;
    
    for k = 1:n-1
        [~, i_max] = max(abs(U(k:n, k)));
        i = i_max + k - 1;
        
        U([k i], :) = U([i k], :);
        
        P([k i], :) = P([i k], :);
        
        if k > 1
            L([k i], 1:k-1) = L([i k], 1:k-1);
        end

        for j = k+1:n
            L(j, k) = U(j, k) / U(k, k);
            U(j, :) = U(j, :) - L(j, k) * U(k, :);
        end
    end
    
    L = L + eye(n);
end

function x = LUP_solve(L, U, P, b)
    n = length(b);
    Pb = P * b;

    y = zeros(n,1);
    for i = 1:n
        y(i) = Pb(i) - L(i,1:i-1)*y(1:i-1);
    end

    x = zeros(n,1);
    for i = n:-1:1
        x(i) = (y(i) - U(i,i+1:n)*x(i+1:n)) / U(i,i);
    end
end
