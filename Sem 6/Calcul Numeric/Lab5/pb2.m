clc; clear; close all; format long;
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
