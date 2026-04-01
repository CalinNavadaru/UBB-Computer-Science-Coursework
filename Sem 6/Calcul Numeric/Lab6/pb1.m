clc; clear; close all; format long;
x = linspace(-1, 1, 100); 
f = sin(pi * x);          
n = 3;                    

N = length(x);
A = zeros(N, n+1);
for i = 0:n
    for j = 1:N
        A(j, i+1) = x(j)^i;
    end
end

AtA = zeros(n+1, n+1);
Atf = zeros(n+1, 1);
for i = 1:(n+1)
    for j = 1:(n+1)
        for k = 1:N
            AtA(i,j) = AtA(i,j) + A(k,i) * A(k,j);
        end
    end
    for k = 1:N
        Atf(i) = Atf(i) + A(k,i) * f(k);
    end
end

a = gaussElim(AtA, Atf); 

phi = A * a;

plot(x, f, 'b', x, phi, 'r--')
legend('f(x)', 'Aproximare')
title('Aproximare L2 cu baza polinomială')

function x = gaussElim(A, b)
    n = length(b);
    Ab = [A b];
    for i = 1:n
        for j = i+1:n
            m = Ab(j,i) / Ab(i,i);
            Ab(j,:) = Ab(j,:) - m * Ab(i,:);
        end
    end
    x = zeros(n,1);
    for i = n:-1:1
        x(i) = (Ab(i,end) - Ab(i,1:n) * x) / Ab(i,i);
    end
end
