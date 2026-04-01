clc; clear; close all; format long;
function [x, iter] = jacobi(A, b, x0, tol, max_iter)
    n = length(b);
    x = x0;
    iter = 0;
    
    x_new = zeros(n, 1);
    
    while iter < max_iter
        iter = iter + 1;
        
        for i = 1:n
            sum_j = 0;
            for j = 1:n
                if j ~= i
                    sum_j = sum_j + A(i,j) * x(j);
                end
            end
            x_new(i) = (b(i) - sum_j) / A(i,i);
        end
        
        if norm(x_new - x, inf) < tol
            x = x_new;
            break;
        end
        
        x = x_new;
    end
end
