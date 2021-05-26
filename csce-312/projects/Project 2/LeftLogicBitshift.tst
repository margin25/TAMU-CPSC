//Starter Test Stimulus for LeftLogicBitshift chip

load LeftLogicBitshift.hdl,
output-file LeftLogicBitshift.out,
compare-to LeftLogicBitshift.cmp,
output-list x%B1.16.1 y%B1.4.1 out%B1.16.1;

set x %B0000000010101011,
set y %B0001,
eval,
output;

set x %B1111111111111111,
set y %B1000,
eval,
output;

set x %B1111111111111111,
set y %B0000,
eval,
output;

//write more tst commands and also complete the .cmp file 