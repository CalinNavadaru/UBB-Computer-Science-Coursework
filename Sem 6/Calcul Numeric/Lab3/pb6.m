clc;
clear;
close all;
format long;
n = 5;

p = 1;
for i = 1:n
    p = conv(p, [1 -i]);
    p = conv(p, [1 -i]);
end

roots_p = roots(p);

for i = 1:length(roots_p)
    cond_number = condpol(p, roots_p(i));
    fprintf('Rădăcina %d: %f, Numărul de condiționare: %+6.4e\n', i, roots_p(i), cond_number);
end

for repeat = 1:10
    perturbation = 1e-10 * rand(1, length(p));
    p_perturbed = p + perturbation; 
    
    roots_p_perturbed = roots(p_perturbed);
    
    for i = 1:length(roots_p_perturbed)
        cond_number_perturbed = condpol(p_perturbed, roots_p_perturbed(i));
        fprintf('Experiment %d - Rădăcina %d: %f, Numărul de condiționare (perturbat): %+6.4e\n', repeat, i, roots_p_perturbed(i), cond_number_perturbed);
    end
end


function nc=condpol(p,xi)
if nargin<2
    xi=roots(p);
end
n=length(p)-1;
derivata_p=(n:-1:1).*p(1:end-1); 
nc=1./(abs(xi.*polyval(derivata_p,xi))).*(polyval(abs(p(2:end)),abs(xi)));
end
