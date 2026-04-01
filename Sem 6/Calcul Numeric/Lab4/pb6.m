clc; clear; close all; format long;

A = [60, 30, 20;
    30, 20, 15;
    20, 15, 12;];
disp("Descompunere LUP: ");
[L, U, P] = LUP_decomp(A);
disp(L);
disp(U);
disp(P);
disp("------------------------------------------------------------");
disp("Descompunere Cholesky: ");
A = [60, 30, 20;
    30, 20, 15;
    20, 15, 12;];
disp(cholesky_decomposition(A));

function R = cholesky_decomposition(A)
    [m, n] = size(A);
    R = A;
    for k = 1:m
        if R(k, k) <= 0
            error('matrix is not HPD') 
        end
        for j = k+1:m
            R(j,j:m) = R(j,j:m) - R(k,j:m) * conj(R(k,j)) / R(k,k);
        end
        R(k,k:m) = R(k,k:m) / sqrt(R(k,k));
    end
    R = triu(R);
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