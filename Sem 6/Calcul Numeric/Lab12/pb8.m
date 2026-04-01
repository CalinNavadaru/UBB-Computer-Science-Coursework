clc; clear; close all; format long;

x0 = [12; -13; 10]; 
sol2_newton = newton_sys(@F2, @J2, x0, 1e-8, 100);
sol2_succ = succesiuni_sys(@F2, @J2, x0, 1e-8, 100);

disp("Newton");
disp(sol2_newton);
disp("Succesiuni");
disp(sol2_succ);

fprintf('Soluții pentru cele 4 puncte de pornire:\n\n');
start_points = [1 1 0; -1 -1 0; 1 -1 0; -1 1 0];

for i = 1:4
    x0 = start_points(i, :)';
    solN = newton_sys(@F2, @J2, x0, 1e-8, 100);
    solS = succesiuni_sys(@F2, @J2, x0, 1e-8, 100);
    
    fprintf('Punct start %d: [%g, %g, %g]\n', i, x0);
    fprintf('  Newton     : [%g, %g, %g]\n', solN);
    fprintf('  Succesiuni : [%g, %g, %g]\n\n', solS);
end



function F = F2(x)
    F = [9*x(1)^2 + 36*x(2)^2 + 4*x(3)^2 - 36;
         x(1)^2 - 2*x(2)^2 - 20*x(3);
         x(1)^2 - x(2)^2 + x(3)^2];
end

function J = J2(x)
    J = [18*x(1), 72*x(2), 8*x(3);
         2*x(1), -4*x(2), -20;
         2*x(1), -2*x(2), 2*x(3)];
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
