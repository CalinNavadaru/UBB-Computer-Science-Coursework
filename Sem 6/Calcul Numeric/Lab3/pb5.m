clc; clear; close all; format long;
for n=2:25
    f = @(x) x.^n .* exp(x - 1);
    E=recdir(n);
    E_real = integral(f, 0, 1);
    fprintf('E(%2d)=%+6.4e E_real=%2d\n', n, E, E_real);
    fprintf('Eroarea pentru E(%2d) este %2d\n', n, abs(E - E_real));
end

for k=1:18
    E=recinv(1,k);
    err=abs(E-exp(-1))/exp(-1);
    fprintf('k=%2d, err=%e\n', k,err);
end

function E=recdir(n)

E=1/exp(1);
for k=2:n
    E=1-k*E;
end
end

function E=recinv(n,k)

E=0;
for j=n+k:-1:n+1
    E=(1-E)/j;
end
end