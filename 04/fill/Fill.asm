// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@SCREEN
D=A
@i
M=D

(BEGIN)

(UNPRESSED)
    @KBD
    D=M
    @PRESSED
    D;JNE
    @SCREEN
    D=A
    @i
    D=M-D
    @UNPRESSED
    D;JLT
    @i
    AD=M
    M=0
    @i
    M=D-1

(PRESSED)
    @KBD
    D=M
    @UNPRESSED
    D;JEQ
    @SCREEN
    D=A
    @i
    D=M+D
    @24575
    D=A-D
    @PRESSED
    D;JGT
    @i
    AD=M
    M=-1
    @i
    M=D+1

@BEGIN
0;JMP