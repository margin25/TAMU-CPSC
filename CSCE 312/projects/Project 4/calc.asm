// Mualla Argin 728003004

// File name: calc.asm

// The program develops a calculator application. 
// The operands a and b are integer numbers stored in RAM[0] (R0) and RAM[1] (R1), respectively.
// The operation choice c is stored in RAM[2] (R2), respectively
// if c == 1, do a + b
// if c == 2, do a - b
// if c == 3, do a * b
// if c == 4, do a / b
// For Addition and Subtraction operations the operands a and b can be positive or negative.
// For Multiplication operation only ONE operand can be negative.
// For Division operation BOTH operands must be positive and must be greater than 0.
// Store the final result (quotient for Division) in RAM[3] (R3). Only the Division operation 
// stores the remainder in RAM[4] (R4).

// Ram[0] - R0
@R0 
D = M       
@a 
M = D   
// Ram[1] - R1
@R1 
D = M       
@b 
M = D    
// Ram[2] - R2
@R2 
D = M  
@c 
M = D 
//
@0 
D = A 
// Ram[3] - R3
@R3
M = D   
//
@0 
D = A
// Ram[4] - R4   
@R4
M = D  
//
@0 
D = A   
@y
M = D 
//
@c
D = M 
D = D - 1
@Addition 
D;JEQ
//
D = D - 1
@Subtraction
D;JEQ
//
D = D - 1
@Multiplication 
D;JEQ
//
D = D - 1
@Division
D;JEQ
//
(Addition)
    @a
    D = M      
    @b
    D = D + M  
    @R3
    M=D
    @end
    0;JMP
//
(Subtraction)
    @a
    D = M       
    @b
    D = D - M 
    @R3
    M=D
    @end
    0;JMP
//
(Multiplication)
    @a
    D = M
    @loop
    D;JGE
    @result
    D;JLT
    (result)
        @b
        D = M
        @loop
        D;JGT
        @y
        M = -1
        @end
        D;JLT
    (loop)
        @b
        D=M
        @end
        D;JEQ
        @R1
        D=D-A
        @b
        M=D
        @R3
        D=M
        @0
        D=D+M
        @R3
        M=D
        @loop
        0;JMP
(Division)
    @a
    D = M
    @result1
    D;JGT
    @y
    M = -1
    @end
    //
    D;JLE
    //
    (result1)
        @b
        D = M
        @loop2
        D;JGT
        @y
        M = -1
        @end
        D;JLE
        //
    (loop2)
        //
        @a
        D = M       
        @b
        D = D - M   
        @remainder
        D;JLT 
        @end 
        D;JLT       
        @zero 
        D;JEQ       
        @R3
        M = M + 1   
        @b
        D = M        
        @a
        M = M - D    
        @loop2     
        0;JMP
        //
    (zero)
        @R3
        M = M + 1   
    (remainder)
        @R1
        D = D + M
        @R4
        M = D
    ///
(end)
    @end
    0;JMP 





