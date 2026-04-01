clc; clear; close all; format long;

x0 = [1; 0];
x0_1 = [1; 3];
sol1_newton = newton_sys(@F1, @J1, x0, 1e-8, 1000);
sol1_succ = succesiuni_sys(@F1, @J1, x0_1, 1e-8, 100);

disp("Newton");
disp(sol1_newton);
disp("Succesiuni");
disp(sol1_succ);

function F = F1(x)
    F = [x(1)^2 + x(2)^2 - 1;
         x(1)^3 - x(2)];
end

function J = J1(x)
    J = [2*x(1), 2*x(2);
         3*x(1)^2, -1];
end

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

function x = newton_sys(F, J, x0, tol, Nmax)
    for k = 1:Nmax
        delta = J(x0)\F(x0);
        x = x0 - delta;
        if norm(x - x0) < tol
            return;
        end
        x0 = x;
    end
    x = x0;
end
