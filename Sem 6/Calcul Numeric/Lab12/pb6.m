clc; clear; close all; format long;


function x = succesiuni_sys(F, J, x0, tol, Nmax)
    Lambda = -inv(J(x0));
    phi = @(x) x + Lambda * F(x);
    for k = 1:Nmax
        x_new = phi(x0);
        if norm(x_new - x0) < tol
            x = x_new;
            return;
        end
        x0 = x_new;
    end
    x = x0;
end
