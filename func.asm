global f1
global f2
global f3
global f1_
global f2_
global f3_

section .data
const2 dq 2.0
const3 dq 3.0
const7 dq 7.0

section .text
f1:; f1 = lnx
    finit
    push ebp
    mov ebp, esp
    fld1
    fld qword[ebp + 8]
    fyl2x  ;st0 = log2(x)
    fldln2
    fmulp ;st0 = log2(x) * ln(2) = ln(x)
    leave
    ret
    
f2:; f2 = -2x + 14
    finit
    push ebp
    mov ebp, esp
    fldz
    fld qword[const2]
    fsubp ;st0 = -2
    fld qword[ebp + 8]
    fmulp ; st0 = -2x
    fld qword[const2]
    fld qword[const7]
    fmulp ; st0 = 14, st1 = -2x
    faddp ST1, ST0
    leave 
    ret
    
f3:; f3 = 1/(2-x) + 6
    finit
    push ebp
    mov ebp, esp
    fld1
    fld qword[const2]
    fld qword[ebp + 8]
    fsubp ;st0 = 2-x, st1 = 1
    fdivp ; st0 = 1/(2-x)
    fld qword[const2]
    fld qword[const3]
    fmulp ; st0 = 6
    faddp ; st0 = 1/(2-x) + 6
    leave 
    ret
    
f1_:
    finit
    push ebp
    mov ebp, esp
    fld1
    fld qword[ebp + 8]
    fdivp ; st0 = 1/x
    leave 
    ret
    
f2_:
    finit
    push ebp
    mov ebp, esp
    fldz
    fld qword[const2]
    fsubp ; st0 = -2
    leave 
    ret
    
f3_:
    finit
    push ebp
    mov ebp, esp
    fld1
    fld qword[const2]
    fld qword[ebp + 8]
    fsubp ; st0 = 2-x
    fld qword[const2]
    fld qword[ebp + 8]
    fsubp
    fmulp ; st0 = (2-x)^2
    fdivp ; st0 = 1/(2-x)^2
    leave
    ret
    
    