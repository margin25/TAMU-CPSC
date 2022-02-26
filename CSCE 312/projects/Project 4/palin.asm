// Mualla Argin 728003004

// File name: palin.asm

// The program develops a Palindrome checker application. 
// The input to the program is a 5 digit integer A and is stored in RAM[0] (R0).
// A helper value of 10 is stored in RAM[8] (R8) by virtue of the tst file command.
// Number A is a positive integer.
// A has exactly 5 digits and no more no less.

// Program functions as follows: 
// Extract the individual digits from number A and store them in R2-R6 registers in that order.
// Result of 1 is stored in R1 if the number A is a Palindrome else result of 0 is stored in R1

// Put your code below this line
// Register 0
@R0 
D = M       
@y//
//
M = D  
@0 
D = A 
@a
M = D 
// Register 8
@R8
//
D = M //      
@t
//
M = D 
//
(loop1)
    @y
    D = M       
    @x
    D = D - M   
    @carry
    D;JLT 
    @end 
    D;JLT       
    @zero 
    D;JEQ       
    @a
    M = M + 1   
    @x
    D = M        
    @n
    M = M - D    
    @loop1     
    0;JMP
(zero)
    @a
    //
    M = M + 1   
//
(carry)
    @t
    D = D + M
    @R2 // Register 2
    M = D
    //
@0 
D = A 
@a1
M = D 
//
(loop2)
    //  
    @a
    D = M       
    @x
    D = D - M   
    @carry2
    D;JLT 
    @end 
    D;JLT       
    @zero2 
    D;JEQ       
    @a1
    M = M + 1   
    @x
    //
    D = M        
    @a
    M = M - D    
    @loop2     
    0;JMP
    //
(zero2)
    @a1
    M = M + 1   
(carry2)
    @x
    D = D + M
    @R3 // Register 3
    M = D
@0 
D = A 
@a2
M = D 
(loop3)
    @a1
    D = M       
    @x
    D = D - M   
    @carry3
    D;JLT 
    @end 
    D;JLT       
    @zero3
    D;JEQ       
    @a2
    M = M + 1   
    @x
    D = M        
    @a1
    M = M - D    
    @loop3     
    0;JMP
(zero3)
    @a2
    M = M + 1   
(carry3)
    @x
    D = D + M
    @R4
    M = D
    //
@0 
D = A 
@a3
M = D 
(loop4)
    @a2
    D = M       
    @x
    D = D - M   
    //
    @carry4
    D;JLT 
    @end 
    D;JLT       
    //
    @zero4
    D;JEQ       
    //
    @a3
    M = M + 1   
    //
    @x
    D = M        
    @a2
    M = M - D    
    //
    @loop4     
    0;JMP
(zero4)
    @a3
    M = M + 1   
//
(carry4)
    @x
    D = D + M
    @R5
    M = D
@0 
D = A 
@a4
M = D 

(loop5)
    @a3
    D = M       
    @x
    D = D - M   
    @carry5
    D;JLT 
    @end 
    D;JLT       
    @zero5
    D;JEQ       
    @a4
    M = M + 1   
    @x
    D = M        
    @a3
    M = M - D    
    @loop5     
    0;JMP
(zero5)
    @a4
    M = M + 1   
(carry5)
    @x
    D = D + M
    @R6
    M = D
@R2
D = M
@10
D = D - A
@replace1
D;JEQ
@proceed1
0;JMP
(replace1)
    @R2
    M = 0
(proceed1)
    @R3
    D = M
    @10
    D = D - A
    @replace2
    D;JEQ
    @proceed2
    0;JMP
    (replace2)
        @R3
        M = 0
(proceed2)
    @R4 // Register 4
    D = M
    @10
    D = D - A
    @replace3
    D;JEQ
    @proceed3
    0;JMP
    (replace3)
        @R4
        M = 0
(proceed3)
    @R5
    D = M
    @10
    D = D - A
    @replace4
    D;JEQ
    @proceed4
    0;JMP
    (replace4)
        @R5 // Register 5
        M = 0
(proceed4)
    @R6
    D = M
    @10
    D = D - A
    @replace5
    D;JEQ
    @proceed5
    0;JMP
    (replace5)
        @R6
        M = 0
(proceed5)
@R2 
D = M       
@y1 
M = D  
@R3 
D = M       
@y2
M = D 
@R4
D = M       
@y3
M = D 
@R5 //Register 5
D = M       
@y4 
M = D 
@R6 // Register 6
D = M       
@y5 
M = D 
@y1
D = M
@y5
D = D - M
@final
D;JEQ
@end
0;JMP
(final)
    @y2
    D = M
    @y4
    D = D - M
    @final1
    D;JEQ
    @end
    0;JMP
    (final1)
        // Register 1
        @R1
        M = 1
(end)
    @end
    0;JMP