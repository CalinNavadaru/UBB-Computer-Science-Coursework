clc; clear; close all; format long;
x = [-1.024940 -0.949898 -0.866114 -0.773392 -0.671372 ...
     -0.559524 -0.437067 -0.302909 -0.159493 -0.007464]';
y = [-0.389269 -0.322894 -0.265256 -0.216557 -0.177152 ...
     -0.147582 -0.128618 -0.121353 -0.127348 -0.148895]';
x2 = x.^2;

A1 = [y.^2, x.*y, x, y, ones(length(x),1)];
AtA1 = A1' * A1;
Atx2_1 = A1' * x2;
params1 = gaussElim(AtA1, Atx2_1);
x2_pred1 = A1 * params1;
err1 = sum((x2 - x2_pred1).^2);
R2_1 = 1 - err1 / sum((x2 - mean(x2)).^2);

A2 = [y, ones(length(y),1)];
AtA2 = A2' * A2;
Atx2_2 = A2' * x2;
params2 = gaussElim(AtA2, Atx2_2);
x2_pred2 = A2 * params2;
err2 = sum((x2 - x2_pred2).^2);
R2_2 = 1 - err2 / sum((x2 - mean(x2)).^2);

% Afișare rezultate
fprintf('Model elipsoidal: eroare = %.6f, R2 = %.4f\n', err1, R2_1);
fprintf('Model parabolic : eroare = %.6f, R2 = %.4f\n', err2, R2_2);

% Concluzie
if R2_1 > R2_2
    disp('Modelul elipsoidal este mai probabil.');
else
    disp('Modelul parabolic este mai probabil.');
end

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
