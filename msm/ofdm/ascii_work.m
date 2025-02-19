clc;

testChrsTrue = 'a'; 
disp(can_ascii_encode(testChrsTrue));
testChrsTrueEncoded = ascii_encode(testChrsTrue);
disp(testChrsTrueEncoded);

testChrsTrueDecoded = ascii_decode(testChrsTrueEncoded);
disp(testChrsTrue);
disp(testChrsTrueDecoded);


% testChrsFalse = '!'; 
% disp(can_ascii_encode(testChrsFalse));
% testChrsFalseEncoded = ascii_encode(testChrsFalse);
% disp(testChrsFalseEncoded);

% testChrsFalseDecoded = ascii_decode(testChrsFalseEncoded);
% disp(testChrsFalse);
% disp(testChrsFalseDecoded);

:-1 :-1 :-1 :-1