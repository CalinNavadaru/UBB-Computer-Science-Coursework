clc;
clear;
close all;
format long;

n_values = [10, 11, 12, 13, 14, 15];
for idx = 1:length(n_values)
    n = n_values(idx);
    
    t = -1 + (0:n-1) * 2 / n;  
    V = vander(t); 
    
    norm_V = norm(V, inf);  
    norm_V_inv = norm(inv(V), inf);  
    
    cond_V = norm_V * norm_V_inv;
    
    fprintf('Pentru n = %d:\n', n);
    fprintf('Norma Cebisev a lui V_n(t): %.2e\n', norm_V);
    fprintf('Norma Cebisev a lui V_n(t)^{-1}: %.2e\n', norm_V_inv);
    fprintf('Conditia matricei Vandermonde: %.2e\n\n', cond_V);
end

n_values = [10, 11, 12, 13, 14, 15];
for idx = 1:length(n_values)
    n = n_values(idx);
    
    t = 1 ./ (1:n+1);
    V = vander(t); 
    
    norm_V = norm(V, inf); 
    norm_V_inv = norm(inv(V), inf); 
    
    cond_V = norm_V * norm_V_inv;
    
    fprintf('Pentru n = %d:\n', n);
    fprintf('Norma Cebisev a lui V_n(t) pentru tk = 1 / k : %.2e\n', norm_V);
    fprintf('Norma Cebisev a lui V_n(t)^{-1} pentru tk = 1 / k : %.2e\n', norm_V_inv);
    fprintf('Conditia matricei Vandermonde pentru tk = 1 / k : %.2e\n\n', cond_V);
end
