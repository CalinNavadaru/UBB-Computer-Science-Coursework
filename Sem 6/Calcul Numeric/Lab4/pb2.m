clc; clear; close all; format long;

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

        % Eliminare Gauss
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

