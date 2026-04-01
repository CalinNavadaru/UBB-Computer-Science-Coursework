clc; clear; close all; format long;

rezolva_metode_iterative(10, 1e-6, 1000);

function rezolva_metode_iterative(n, tol, max_iter)
    
    x_exact = (1:n)';  % [1; 2; ...; n]
    
    A = rand(n);  
    for i = 1:n
        A(i,i) = sum(abs(A(i,:))) + 1; 
    end

    b = A * x_exact;
    
    x0 = zeros(n, 1); 
    fprintf('\n=== Metoda Jacobi ===\n');
    [x_jacobi, iter_jacobi] = jacobi(A, b, x0, tol, max_iter);
    fprintf('Eroare: %.2e | Iterații: %d\n', norm(x_jacobi - x_exact, inf), iter_jacobi);

    fprintf('\n=== Metoda Gauss-Seidel ===\n');
    [x_gs, iter_gs] = gauss_seidel(A, b, x0, tol, max_iter);
    fprintf('Eroare: %.2e | Iterații: %d\n', norm(x_gs - x_exact, inf), iter_gs);

    fprintf('\n=== Metoda SOR ===\n');
    [x_sor, iter_sor] = sor(A, b, x0, tol, max_iter);
    fprintf('Eroare: %.2e | Iterații: %d\n', norm(x_sor - x_exact, inf), iter_sor);
end

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

function [x, iter] = gauss_seidel(A, b, x0, tol, max_iter)
    n = length(b);
    x = x0;
    iter = 0;
    while iter < max_iter
        iter = iter + 1;
        x_old = x;
        for i = 1:n
            s1 = A(i,1:i-1)*x(1:i-1);
            s2 = A(i,i+1:end)*x_old(i+1:end);
            x(i) = (b(i) - s1 - s2)/A(i,i);
        end
        if norm(x - x_old, inf) < tol
            break;
        end
    end
end
