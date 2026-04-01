clc; clear; close all; format long;

A = [4, 1+2i, 2-1i; 1-2i, 3, 0; 2+1i, 0, 3];
b = [4; 5; 6];

x = cholesky_solve(A, b);

disp('Soluția sistemului este:');
disp(A \ b);
disp('Solutia folosind Cholesky este: ');
disp(cholesky_solve(A, b));

function x = cholesky_solve(A, b)
    R = cholesky_decomposition(A);
    y = forward_substitution(R', b);
    x = backward_substitution(R, y);
end

function y = forward_substitution(R, b)
    n = length(b);
    y = zeros(n, 1);
    
    for i = 1:n
        y(i) = (b(i) - R(i, 1:i-1) * y(1:i-1)) / R(i,i);
    end
end

function x = backward_substitution(R, y)
    n = length(y);
    x = zeros(n, 1);
    
    for i = n:-1:1
        x(i) = (y(i) - R(i, i+1:n) * x(i+1:n)) / R(i,i);
    end
end


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
