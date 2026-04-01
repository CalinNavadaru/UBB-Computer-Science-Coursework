clc; clear; close all; format long;

t = [0, 3, 5, 8, 13];
s = [0, 225, 383, 623, 993];
v = [75, 77, 80, 74, 72];

t_eval = 10;

[pos_h, speed_h] = hermite_interp_cu_derivata(t_eval, t, s, v);

pp_s = spline(t, s);         
pp_v = fnder(pp_s);          
pos_spline = ppval(pp_s, t_eval);
speed_spline = ppval(pp_v, t_eval);

fprintf("=== Comparatie Hermite vs Spline în t = %.2f ===\n", t_eval);
fprintf(">> Poziție estimată:\n");
fprintf("   Hermite : %.3f m\n", pos_h);
fprintf("   Spline  : %.3f m\n", pos_spline);
fprintf("   Diferență: %.3f m\n\n", abs(pos_h - pos_spline));

fprintf(">> Viteză estimată:\n");
fprintf("   Hermite : %.3f m/s\n", speed_h);
fprintf("   Spline  : %.3f m/s\n", speed_spline);
fprintf("   Diferență: %.3f m/s\n", abs(speed_h - speed_spline));

function [Hx, Hpx] = hermite_interp_cu_derivata(x, xi, fi, fpi)
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
Hpx = zeros(size(x));

for k = 1:length(x)
    xt = x(k);
    term = 1;
    dterm = 0;
    Hx(k) = Q(1,1);
    Hpx(k) = 0;

    for i = 1:2*n-1
        dterm = dterm * (xt - z(i)) + term * 1;
        term = term * (xt - z(i));

        Hx(k) = Hx(k) + Q(i+1,i+1) * term;
        Hpx(k) = Hpx(k) + Q(i+1,i+1) * dterm;
    end
end
end
