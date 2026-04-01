clc; clear; close all; format long;

A = [5 -1 0 0 0;
    -1 5 -1 0 0;
    0 -1 5 -1 0;
    0 0 -1 5 -1;
    0 0 0 -1 5];
b = [4; 3; 3; 3; 4;];

disp(jacobi(A, b, [0;0;0;0;0;],1e-6, 100));
disp(sor(A, b, [0;0;0;0;0;],1e-6, 100)); 
disp(A \ b);

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

function [x, iter] = sor(A, b, x0, tol, max_iter)
   
    n = length(b);
    x = x0;
    iter = 0;
    
    D = diag(diag(A));   
    L_plus_U = A - D;    
    p = max(abs(eig(D \ L_plus_U)));  

    omega_opt = 2 / (1 + sqrt(1 - p^2));
    fprintf('Factorul de relaxare optim omega: %f\n', omega_opt);
    
    x_new = x0;
    
    while iter < max_iter
        iter = iter + 1;
        
        for i = 1:n
            sum1 = A(i,1:i-1) * x_new(1:i-1);  
            sum2 = A(i,i+1:n) * x(i+1:n);      
            
            x_new(i) = (1 - omega_opt) * x(i) + (omega_opt / A(i,i)) * (b(i) - sum1 - sum2);
        end
        
        if norm(x_new - x, inf) < tol
            x = x_new;
            break;
        end
        
        x = x_new;
    end
end