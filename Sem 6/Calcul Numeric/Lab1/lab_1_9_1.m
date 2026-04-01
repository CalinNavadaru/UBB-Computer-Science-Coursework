clc; clear; close all; format long;

x = linspace(-1, 1, 100); 
J0_2x = besselj(0, 2*x);
R_bessel = my_bessel_zero_pade(2, 4, x);


figure;
plot(x, J0_2x, 'b', 'LineWidth', 2); hold on;  
plot(x, R_bessel, 'r--', 'LineWidth', 2);
legend('J0(2x)', 'Padé');
xlabel('x');
ylabel('Valoare');
title('Aproximare Padé pentru J0(2x)');
grid on;

function R = my_bessel_zero_pade(m, k, x)
    % Aproximare Padé [m/k] a functiei exp
    % m - gradul numaratorului
    % k - gradul numitorului
    % x - punctele la care evaluam
    c = zeros(m+k+1, 1);
    c(1) = 1;
    for p = 1:m+k
        c(2 * p + 1) = ((-1) ^ p) / (factorial(p) ^ 2);
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