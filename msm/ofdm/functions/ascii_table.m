function [outDecode, outEncode] = ascii_table() 
    ascii_chars_encode = containers.Map();

    % ascii_chars_encode('NUL') = '0000000';
    % ascii_chars_encode('SOH') = '0000001';
    % ascii_chars_encode('STX') = '0000010';
    % ascii_chars_encode('ETX') = '0000011';
    % ascii_chars_encode('EOT') = '0000100';
    % ascii_chars_encode('ENQ') = '0000101';
    % ascii_chars_encode('ACK') = '0000110';
    % ascii_chars_encode('BEL') = '0000111';
    % ascii_chars_encode('BS')  = '0001000';
    % ascii_chars_encode('HT')  = '0001001';
    % ascii_chars_encode('LF')  = '0001010';
    % ascii_chars_encode('VT')  = '0001011';
    % ascii_chars_encode('FF')  = '0001100';
    % ascii_chars_encode('CR')  = '0001101';
    % ascii_chars_encode('SO')  = '0001110';
    % ascii_chars_encode('SI')  = '0001111';
    % ascii_chars_encode('DLE') = '0010000';
    % ascii_chars_encode('DC1') = '0010001';
    % ascii_chars_encode('DC2') = '0010010';
    % ascii_chars_encode('DC3') = '0010011';
    % ascii_chars_encode('DC4') = '0010100';
    % ascii_chars_encode('NAK') = '0010101';
    % ascii_chars_encode('SYN') = '0010110';
    % ascii_chars_encode('ETB') = '0010111';
    % ascii_chars_encode('CAN') = '0011000';
    % ascii_chars_encode('EM')  = '0011001';
    % ascii_chars_encode('SUB') = '0011010';
    % ascii_chars_encode('ESC') = '0011011';
    % ascii_chars_encode('FS')  = '0011100';
    % ascii_chars_encode('GS')  = '0011101';
    % ascii_chars_encode('RS')  = '0011110';
    % ascii_chars_encode('US')  = '0011111';
    ascii_chars_encode(' ')   = '0100000';
    % ascii_chars_encode('!')   = '0100001';
    % ascii_chars_encode('"')   = '0100010';
    % ascii_chars_encode('#')   = '0100011';
    % ascii_chars_encode('$')   = '0100100';
    % ascii_chars_encode('%')   = '0100101';
    % ascii_chars_encode('&')   = '0100110';
    % ascii_chars_encode('\'')  = '0100111';
    % ascii_chars_encode('(')   = '0101000';
    % ascii_chars_encode(')')   = '0101001';
    % ascii_chars_encode('*')   = '0101010';
    % ascii_chars_encode('+')   = '0101011';
    % ascii_chars_encode(',')   = '0101100';
    % ascii_chars_encode('-')   = '0101101';
    ascii_chars_encode('.')   = '0101110';
    % ascii_chars_encode('/')   = '0101111';
    ascii_chars_encode('0')   = '0110000';
    ascii_chars_encode('1')   = '0110001';
    ascii_chars_encode('2')   = '0110010';
    ascii_chars_encode('3')   = '0110011';
    ascii_chars_encode('4')   = '0110100';
    ascii_chars_encode('5')   = '0110101';
    ascii_chars_encode('6')   = '0110110';
    ascii_chars_encode('7')   = '0110111';
    ascii_chars_encode('8')   = '0111000';
    ascii_chars_encode('9')   = '0111001';
    % ascii_chars_encode(':')   = '0111010';
    % ascii_chars_encode(';')   = '0111011';
    % ascii_chars_encode('<')   = '0111100';
    % ascii_chars_encode('=')   = '0111101';
    % ascii_chars_encode('>')   = '0111110';
    % ascii_chars_encode('?')   = '0111111';
    % ascii_chars_encode('@')   = '1000000';
    ascii_chars_encode('A')   = '1000001';
    ascii_chars_encode('B')   = '1000010';
    ascii_chars_encode('C')   = '1000011';
    ascii_chars_encode('D')   = '1000100';
    ascii_chars_encode('E')   = '1000101';
    ascii_chars_encode('F')   = '1000110';
    ascii_chars_encode('G')   = '1000111';
    ascii_chars_encode('H')   = '1001000';
    ascii_chars_encode('I')   = '1001001';
    ascii_chars_encode('J')   = '1001010';
    ascii_chars_encode('K')   = '1001011';
    ascii_chars_encode('L')   = '1001100';
    ascii_chars_encode('M')   = '1001101';
    ascii_chars_encode('N')   = '1001110';
    ascii_chars_encode('O')   = '1001111';
    ascii_chars_encode('P')   = '1010000';
    ascii_chars_encode('Q')   = '1010001';
    ascii_chars_encode('R')   = '1010010';
    ascii_chars_encode('S')   = '1010011';
    ascii_chars_encode('T')   = '1010100';
    ascii_chars_encode('U')   = '1010101';
    ascii_chars_encode('V')   = '1010110';
    ascii_chars_encode('W')   = '1010111';
    ascii_chars_encode('X')   = '1011000';
    ascii_chars_encode('Y')   = '1011001';
    ascii_chars_encode('Z')   = '1011010';
    % ascii_chars_encode('[')   = '1011011';
    % ascii_chars_encode('\\')  = '1011100';
    % ascii_chars_encode(']')   = '1011101';
    % ascii_chars_encode('^')   = '1011110';
    % ascii_chars_encode('_')   = '1011111';
    % ascii_chars_encode('`')   = '1100000';
    ascii_chars_encode('a')   = '1100001';
    ascii_chars_encode('b')   = '1100010';
    ascii_chars_encode('c')   = '1100011';
    ascii_chars_encode('d')   = '1100100';
    ascii_chars_encode('e')   = '1100101';
    ascii_chars_encode('f')   = '1100110';
    ascii_chars_encode('g')   = '1100111';
    ascii_chars_encode('h')   = '1101000';
    ascii_chars_encode('i')   = '1101001';
    ascii_chars_encode('j')   = '1101010';
    ascii_chars_encode('k')   = '1101011';
    ascii_chars_encode('l')   = '1101100';
    ascii_chars_encode('m')   = '1101101';
    ascii_chars_encode('n')   = '1101110';
    ascii_chars_encode('o')   = '1101111';
    ascii_chars_encode('p')   = '1110000';
    ascii_chars_encode('q')   = '1110001';
    ascii_chars_encode('r')   = '1110010';
    ascii_chars_encode('s')   = '1110011';
    ascii_chars_encode('t')   = '1110100';
    ascii_chars_encode('u')   = '1110101';
    ascii_chars_encode('v')   = '1110110';
    ascii_chars_encode('w')   = '1110111';
    ascii_chars_encode('x')   = '1111000';
    ascii_chars_encode('y')   = '1111001';
    ascii_chars_encode('z')   = '1111010';
    % ascii_chars_encode('{')   = '1111011';
    % ascii_chars_encode('|')   = '1111100';
    % ascii_chars_encode('}')   = '1111101';
    % ascii_chars_encode('~')   = '1111110';
    % ascii_chars_encode('DEL') = '1111111';


    ascii_chars_decode = containers.Map();
    keys = ascii_chars_encode.keys();
    for i = 1:length(keys)
        key = keys{i};
        value = ascii_chars_encode(key);
        ascii_chars_decode(value) = key;
    end

    outDecode = ascii_chars_decode; 
    outEncode = ascii_chars_encode;
end