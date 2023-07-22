org 100h
use16

; get command line args
mov cl, [80h]
test cl, cl
jnz args_found
mov ah, 9
mov dx, no_arg_str
int 21h
mov ax, 4c01h
int 21h
args_found:
; string to integer time
mov si, 82h
dec cl
xor ax, ax
xor bx, bx
arg_loop:
; multiply by 10
mov ax, bx
shl bx, 3
shl ax, 1
add bx, ax
movzx ax, byte [si]
sub ax, '0'
add bx, ax
inc si
loop arg_loop
mov [limit], bx

; set up our array (fill with 1s)
mov di, arr
inc bx
shr bx, 1
mov cx, bx
test cx, 7
jz no_extra
add cx, 8
no_extra:
shr cx, 3
mov [arrsize], cx
mov al, 0ffh
rep stosb

; zero out padding bits
call genmask
dec al
and [arr+bx], al

; start algorithm
mov di, [limit]
; inlined square root procedure. di is input, ax is output.
; this destroys all other general-purpose registers.
; bx holds the last result, cx holds the second last result.
mov ax, di
shr ax, 1
mov bx, ax
sqrt_loop:
mov cx, bx
mov bx, ax
xor dx, dx
mov ax, di
div bx
add ax, bx
shr ax, 1
; loop condition
cmp ax, bx
setne dl
cmp ax, cx
setne dh
test dl, dh
jne sqrt_loop

mov [sqrtlimit], ax
mov si, 3 ; si is loop counter (cx is needed for the shift value)
sieve_loop:
cmp si, [sqrtlimit]
jg sieve_end
; check bit
mov bx, si
shr bx, 1
call genmask
test [arr+bx], al
jz check_end
; clear out any non-primes
mov ax, si
mul ax
mov di, ax ; use di as multiple
clear_loop:
; clear bit
; this procedure is very similar to the check bit, except
; we do a one's complement on ax when generating the mask
mov bx, di
shr bx, 1
call genmask
not al
and [arr+bx], al
; increment di
mov cx, si
shl cx, 1
add di, cx
cmp di, [limit]
jle clear_loop
check_end:
add si, 2
jmp sieve_loop
sieve_end:

; count bits
xor si, si ; stores bit count.
xor bx, bx
mov cx, [arrsize]
mov di, arr
count_loop:
test cx, cx
jz count_end
mov bl, [di]
movzx dx, byte [bitcount+bx]
add si, dx
inc di
dec cx
jmp count_loop
count_end:
mov ah, 9
mov dx, numprimes_str
int 21h
mov ax, si
call printnum

; exit
mov ax, 4c00h
int 21h

; inputs: bx is the bit to compute
; outputs: mask in ax, offset in bx
; destroys the contents of cl
genmask:
; generate the bitmask
mov cl, bl
and cl, 7
mov al, 1
shl al, cl
; compute the offset in the array
shr bx, 3
ret

printnum: ; ax is input integer, cx and dx will be destroyed
mov cx, 10
test ax, ax
jz printnum_zero ; if the input number is 0, just print 0.
printnum_proc:
test ax, ax
jz printnum_end ; if the dividend is zero, then exit. (this should take more than one call to execute)
xor dx, dx
div cx
push dx
call printnum_proc
; print character
mov ah, 6
pop dx
add dl, '0'
int 21h
printnum_end:
ret
printnum_zero:
mov ah, 6
mov dl, '0'
int 21h
ret

no_arg_str db "No limit provided.$"
numprimes_str db "Number of primes: $"

; counting bits at runtime would be extremely slow so here is a table
bitcount db 0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4
         db 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5
         db 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7
         db 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7
         db 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6
         db 3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7
         db 3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7
         db 4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8

; variables
limit dw ?
sqrtlimit dw ?
arrsize dw ?

arr rb 4096 ; bit array