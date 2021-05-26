//Starter Test stimulus file for AddSub10 

load AddSub10.hdl,
output-file AddSub10.out,
compare-to AddSub10.cmp,
output-list a%B1.10.1 b%B1.10.1 sub%B1.1.1 out%B1.10.1 carry%B3.1.3;

set a %B0000000000,
set b %B0000000000,
set sub 0,
eval,
output;

//fill in more test cases here to thoroughly check correctness of your chip