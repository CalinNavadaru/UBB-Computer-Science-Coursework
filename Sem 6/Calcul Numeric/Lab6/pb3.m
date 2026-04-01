clc; clear; close all; format long;
AB = 35; AC = 67; AD = 89; BD = 53; CD = 20;

A = [1 1 1;    % AD
     1 1 0;    % AC
     0 1 1;    % BD
     1 0 0;    % AB
     0 0 1];   % CD
b = [AD; AC; BD; AB; CD];

AtA = A' * A;
Atb = A' * b;
x = gaussElim(AtA, Atb);

fprintf('AB = %.2f m\nBC = %.2f m\nCD = %.2f m\n', x(1), x(2), x(3));

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
