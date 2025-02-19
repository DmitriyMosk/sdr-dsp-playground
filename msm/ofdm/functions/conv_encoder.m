% https://techlibrary.ru/b1/2v1j1l1j1t1j1o_2k.2q._2z1c1g1r1t1p1y1o2c1f_1l1p1e2c._2001.pdf (28 страница)

function out = conv_encoder(bits)
    % CONVCODER - Свёрточное кодирование входного вектора бит.
    %
    % Вход:
    %   bits - Вектор бит (0 или 1)
    %
    % Выход:
    %   out  - Вектор закодированных бит (длина = 2 * length(bits))

    k = 7; % степень кодирования
    G1_oct = 171;
    G2_oct = 133;
    
    % Преобразуем генераторы (полиномы) в двоичный вектор
    G1 = arrayfun(@(x) str2double(x), dec2bin(oct2dec(G1_oct), k));
    G2 = arrayfun(@(x) str2double(x), dec2bin(oct2dec(G2_oct), k));
    
    nBits = length(bits);
    out = zeros(1, 2 * nBits);
    
    % Инициализация сдвигового регистра
    shiftReg = zeros(1, k);
    for i = 1:nBits
        % Обновление регистра: новый бит попадает в начало, остальные сдвигаются
        shiftReg = [bits(i), shiftReg(1:end-1)];
        % Вычисление выходных битов
        out1 = mod(sum(G1 .* shiftReg), 2);
        out2 = mod(sum(G2 .* shiftReg), 2);
        out(2*i-1:2*i) = [out1, out2];
    end
end
