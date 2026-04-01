clc; clear; close all; format long;

for n = 10:16
    cond_num = cond_hilbert(n); 
    fprintf('Cond(%d) = %.2e\n', n, cond_num);
end

function val_cond = cond_hilbert(n)
    val_cond = (sqrt(2) + 1)^(4 * n + 4) / (2^(14/4) * sqrt(pi * n));
end
