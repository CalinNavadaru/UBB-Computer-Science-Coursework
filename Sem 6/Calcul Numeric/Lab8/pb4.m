clc; clear; close all; format long;

xi = [0, 1, 2];
fi = exp(xi);
fpi = exp(xi);  
x_eval = 0.25;

H_val = hermite_interp(x_eval, xi, fi, fpi);

L_val = lagrange_interp(x_eval, xi, fi);

f_exact = exp(x_eval);

fprintf('Interpolare Hermite: %.10f\n', H_val);
fprintf('Interpolare Lagrange: %.10f\n', L_val);
fprintf('Valoare exactă e^%.2f: %.10f\n', x_eval, f_exact);
fprintf('Eroare Hermite: %.2e\n', abs(f_exact - H_val));
fprintf('Eroare Lagrange: %.2e\n', abs(f_exact - L_val));

syms x
f7 = diff(exp(x), 6); 
M = double(exp(2)); 
u = (x_eval - xi(1))^2 * (x_eval - xi(2))^2 * (x_eval - xi(3))^2;
Rn = M * double(u) / factorial(6);
fprintf('Delimitare teoretică eroare Hermite: %.2e\n', Rn);

function Lx = lagrange_interp(x, xi, fi)
    n = length(xi);
    Lx = 0;
    for i = 1:n
        Li = 1;
        for j = [1:i-1, i+1:n]
            Li = Li * (x - xi(j)) / (xi(i) - xi(j));
        end
        Lx = Lx + Li * fi(i);
    end
end

function Hx = hermite_interp(x, xi, fi, fpi)
n = length(xi);
z = zeros(2*n, 1);
Q = zeros(2*n, 2*n);

for i = 1:n
    z(2*i-1) = xi(i);
    z(2*i) = xi(i);
    Q(2*i-1,1) = fi(i);
    Q(2*i,1) = fi(i);
    Q(2*i,2) = fpi(i);
    if i ~= 1
        Q(2*i-1,2) = (Q(2*i-1,1) - Q(2*i-2,1)) / (z(2*i-1) - z(2*i-2));
    end
end

for j = 3:2*n
    for i = j:2*n
        Q(i,j) = (Q(i,j-1) - Q(i-1,j-1)) / (z(i) - z(i-j+1));
    end
end

Hx = zeros(size(x));
for k = 1:length(x)
    xt = x(k);
    term = 1;
    Hx(k) = Q(1,1);
    for i = 1:2*n-1
        term = term * (xt - z(i));
        Hx(k) = Hx(k) + Q(i+1,i+1) * term;
    end
end
end
