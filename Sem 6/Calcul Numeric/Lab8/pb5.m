clc; clear; close all; format long;

xi1 = [0.30, 0.32, 0.35];
fi1 = [0.29552, 0.31457, 0.34290];
fpi1 = [0.95534, 0.94924, 0.93937];
x_eval = 0.34;

H_val1 = hermite_interp(x_eval, xi1, fi1, fpi1);
f_exact = sin(x_eval);

fprintf("=== Fără nodul 0.33 ===\n");
fprintf("Interpolare Hermite: %.8f\n", H_val1);
fprintf("Valoare exactă:      %.8f\n", f_exact);
fprintf("Eroare exactă:       %.2e\n", abs(H_val1 - f_exact));


syms x
M = 1;
u = prod((x_eval - xi1).^2);
Rn1 = M * u / factorial(6);
fprintf("Estimare eroare:     %.2e\n", Rn1);

xi2 = [0.30, 0.32, 0.33, 0.35];
fi2 = [0.29552, 0.31457, sin(0.33), 0.34290];
fpi2 = [0.95534, 0.94924, cos(0.33), 0.93937];

H_val2 = hermite_interp(x_eval, xi2, fi2, fpi2);

fprintf("\n=== Cu nodul 0.33 adăugat ===\n");
fprintf("Interpolare Hermite: %.8f\n", H_val2);
fprintf("Valoare exactă:      %.8f\n", f_exact);
fprintf("Eroare exactă:       %.2e\n", abs(H_val2 - f_exact));

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
