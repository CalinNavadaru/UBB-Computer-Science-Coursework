clc; clear; close all; format long;
n = 5;
A = zeros(n);
for i = 1:n
    for j = 1:n
        if j == i
            A(i, j) = 1;
        elseif j < i
            A(i, j) = -1;
        end
    end
    A(i, n) = 1;
end

b = (2 - (0:n-1))';
x_sol = A \ b;
disp(A * x_sol);
disp(A);
disp(b);
disp('Soluția obținută:');
disp(x_sol);
disp("--------------------------------------");
disp('Solutie cu LUP: ');
[L, U, P] = LUP_decomp(A);
disp(LUP_solve(L, U, P, b));
disp("--------------------------------------");
disp('Solutie cu QR: ');
[Q, R] = QR_gram_schmidt(A);
disp(solveQR(Q, R, b));

function x = solveQR(Q, R, b)
    y = Q' * b;     
    n = length(b);
    x = zeros(n, 1);

    for i = n:-1:1
        x(i) = (y(i) - R(i, i+1:end) * x(i+1:end)) / R(i, i);
    end
end


function [Q, R] = QR_gram_schmidt(A)
    [n, m] = size(A);
    Q = zeros(n, m);
    R = zeros(m, m);

    for j = 1:m
        v = A(:, j);
        for i = 1:j-1
            R(i, j) = Q(:, i)' * A(:, j);
            v = v - R(i, j) * Q(:, i);
        end
        R(j, j) = norm(v);
        Q(:, j) = v / R(j, j);
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
