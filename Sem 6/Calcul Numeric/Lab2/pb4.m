clc; clear; close all; format long;
float_to_bin(15);

function float_to_bin(value)
    if isa(value, 'single')
        num_bits = 32;
        exp_bits = 8;
        frac_bits = 23;
    else
        value = double(value);  % Convertim în double dacă nu e single
        num_bits = 64;
        exp_bits = 11;
        frac_bits = 52;
    end
    
    bits = dec2bin(typecast(value, 'uint64'), num_bits);
    
    sign_bit = bits(1); 
    exponent_bits = bits(2:exp_bits+1);  
    significand_bits = bits(exp_bits+2:end);  
    
    fprintf('Semn: %s\n', sign_bit);
    fprintf('Exponent: %s\n', exponent_bits);
    fprintf('Mantisa: %s\n', significand_bits);
end
