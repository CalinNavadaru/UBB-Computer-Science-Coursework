clc; clear; close all; format long;

x = linspace(-1, 1, 100); 

R_pade = my_exp_pade(1, 1, x);
exp_exact = exp(x); 

figure;
plot(x, exp_exact, 'b', 'LineWidth', 2); hold on;  
plot(x, R_pade, 'r--', 'LineWidth', 2);
legend('e^x', 'Padé');
xlabel('x');
ylabel('Valoare');
title('Aproximare Padé pentru e^x');
grid on;

x = linspace(-0.9, 2, 100);

R_ln = my_ln_pade(3, 1, x);
ln_exact = log(1 + x);
figure;
plot(x, ln_exact, 'b', 'LineWidth', 2); hold on;  
plot(x, R_ln, 'r--', 'LineWidth', 2);
legend('ln(1 + x)', 'Padé');
xlabel('x');
ylabel('Valoare');
title('Aproximare Padé  pentru ln(1 + x)');
grid on;



function R = my_exp_pade(m, k, x)
    % Aproximare Padé [m/k] a functiei exp
    % m - gradul numaratorului
    % k - gradul numitorului
    % x - punctele la care evaluam
    c = zeros(m+k+1, 1);    
    for p = 0:m+k
        c(p+1) = 1 / factorial(p);
    end
    
    % Construim sistemul pentru coeficientii numitorului
    b = zeros(m+k+1, 1);  % Facem b suficient de lung și completăm cu 0
    b(1) = 1; % Primul coeficient este fixat la 1
    if k > 0
        C = toeplitz(c(m+1:m+k), c(m+1:-1:m-k+2));
        bv = -c(m+(1:k)+1);
        
        if cond(C) > 1e12
             %warning("Matricea Toeplitz este aproape singulară. Folosesc pinv().");
             b(2:k+1) = pinv(C) * bv;
        else
            b(2:k+1) = C \ bv;
        end
    end    
    % Calculăm coeficienții numărătorului
    a = zeros(m+1, 1);
    for j = 0:m
        for l = 0:j
               a(j+1) = a(j+1) + c(j-l+1) * b(l+1);
        end
    end
    
    % Construim fracția rațională R(x) = P_m(x) / Q_k(x)
    vp = polyval(flip(a), x); % Evaluare numărător
    vq = polyval(flip(b), x); % Evaluare numitor
    R = vp ./ vq;
end

function R = my_ln_pade(m, k, x)
    % Aproximare Padé [m/k] a functiei ln(1 + x)
    % m - gradul numaratorului
    % k - gradul numitorului
    % x - punctele la care evaluam
    c = zeros(m+k+1, 1);    
    for p = 1:m+k
        c(p+1) = (-1)^(p+1) / p;
    end
    
    % Construim sistemul pentru coeficientii numitorului
    b = zeros(m+k+1, 1);  % Facem b suficient de lung și completăm cu 0
    b(1) = 1; % Primul coeficient este fixat la 1
    if k > 0
        C = toeplitz(c(m+1:m+k), c(m+1:-1:m-k+2));
        bv = -c(m+(1:k)+1);
        
        if cond(C) > 1e12
             %warning("Matricea Toeplitz este aproape singulară. Folosesc pinv().");
             b(2:k+1) = pinv(C) * bv;
        else
            b(2:k+1) = C \ bv;
        end
    end    
    % Calculăm coeficienții numărătorului
    a = zeros(m+1, 1);
    for j = 0:m
        for l = 0:j
               a(j+1) = a(j+1) + c(j-l+1) * b(l+1);
        end
    end
    
    % Construim fracția rațională R(x) = P_m(x) / Q_k(x)
    vp = polyval(flip(a), x); % Evaluare numărător
    vq = polyval(flip(b), x); % Evaluare numitor
    R = vp ./ vq;
end