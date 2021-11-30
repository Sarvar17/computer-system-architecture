section .text

; Params:
;   rdi: String link
; Out:
;   rax: String length
string_length:
  xor   rax, rax
  .loop:
    cmp   byte [rdi+rax], 0
    je    .end
    inc   rax
    jmp   .loop
  .end:
    ret


; Params:
;  rdi: String link
; Out:
;  !stdout
print_string:
  call  string_length
  mov   rdx, rax
  mov   rax, 1
  mov   rsi, rdi
  mov   rdi, 1
  syscall
  ret


; Params:
;  rdi: Code of char
; Out:
;  !stdout
print_char:
  push  rdi
  mov   rdi, 1
  mov   rdx, 1
  mov   rax, 1
  mov   rsi, rsp
  syscall
  pop   rdi
  ret


; Params:
;  -
; Out:
;  !stdout
print_newline:
  mov  rdi, `\n`
  jmp  print_char


; Params:
;  rdi: Unsigned 8-byte decimal number
; Out:
;  !stdout
print_uint:
  mov   r10, 10
  mov   rax, rdi
  mov   rdi, rsp
  sub   rsp, 21
  dec   rdi
  mov   byte[rdi], 0
  .div_loop:
    xor   rdx, rdx
    div   r10
    add   dl, '0'
    dec   rdi
    mov   [rdi], dl
    test  rax, rax
    jne   .div_loop

  call  print_string
  add   rsp, 21
  ret

; Params:
;  rdi: Unsigned 8-byte decimal number
; Out:
;  !stdout
print_int:
  cmp   rdi, 0
  jge   print_uint

  push  rdi
  mov   rdi, '-'
  call  print_char
  pop   rdi
  
  neg   rdi
  jmp   print_uint


; Params:
;  rdi: First string link
;  rsi: Second string link
; Out:
;  rax: Result
string_equals:
  .loop:
    mov   al, [rdi]
    cmp   al, [rsi]
    jne   .false
    test  al, al
    je    .true
    inc   rdi
    inc   rsi
    jmp   .loop
  .false: 
    xor   rax, rax 
    ret
  .true:
    mov   rax, 1
    ret


; Params:
;  !stdin
; Out:
;  rax: Char from stdin
;       0 if the end of the stream is reached
read_char:
  push  0 
  xor   rax, rax
  xor   rdi, rdi
  mov   rdx, 1
  mov   rsi, rsp
  syscall
  pop   rax 
  ret 

; Params:
;  rdi: Buffer string link
;  rsi: Buffer string size   
; Out:
;  rax: Filled buffer link
;       0 if operation failed
;  rdx: Filled buffer size 
read_word:
  mov   r8, rsi 
  mov   r9, rdi 
  xor   r10, r10 
  xor   rdi, rdi 
  mov   rdx, 1 
  .skip:
    xor   rax, rax 
    mov   rsi, r9 
    syscall
    test  rax, rax
    je    .term_zero 
    cmp   byte[r9], ' ' 
    je    .skip  
    cmp   byte[r9], `\t`
    je    .skip
    cmp   byte[r9], `\n` 
    je    .skip
    inc   r10 
  
  .read:
    xor   rax, rax 
    lea   rsi, [r9+r10] 
    syscall
    mov   cl, byte[r9+r10]
    test  rax, rax
    jz    .term_zero 
    cmp   cl, ' ' 
    je    .term_zero 
    cmp   cl, `\t`
    je    .term_zero 
    cmp   cl, `\n` 
    je    .term_zero 
    cmp   r8, r10 
    jl    .overflow 
    inc   r10 
    jmp   .read 

  .term_zero:
    mov   byte[r9+r10], 0
    mov   rdx, r10 
    mov   rax, r9
    ret
  .overflow:
    xor   rdx, r8 
    xor   rax, rax
    ret


; rdx = 0 если число прочитать не удалось
; Params:
;  rdi: String link
; Out:
;  rax: Decimal number
;  rdx: Decimal number length
;       0 if operation failed
parse_uint:
  xor   r8, r8
  xor   rax, rax
  xor   rdx, rdx

  .loop:
    cmp   byte[rdi+rdx], '0'
    jl    .exit
    cmp   byte[rdi+rdx], '9'
    jg    .exit

    mov   r8b, [rdi+rdx] 
    sub   r8b, '0' 
    imul  rax, 10 
    add   rax, r8 
    inc   rdx 
    jmp   .loop

  .exit:
    ret


; rdx = 0 если число прочитать не удалось
; Params:
;  rdi: String link
; Out:
;  rdx: Number length
;       0 if operation failed
parse_int:
  xor   rax, rax
  cmp   byte[rdi], '-'
  jne   parse_uint
  inc   rdi
  call  parse_uint
  neg   rax
  inc   rdx
  ret 


; Params:
;  rdi: String link
;  rsi: Buffer string link
;  rdx: Buffer string size 
; Out:
;  rax: String length
;       0 if buffer end reached
string_copy:
  xor   rcx, rcx
  .loop:
    cmp   rcx, rdx
    jge   .overflow
    mov   al, [rdi+rcx]
    mov   [rsi+rcx], al
    inc   rcx
    test  al, al
    je    .end
    jmp   .loop
  .overflow:
    xor   rax, rax
    ret
  .end:
    mov   rax, rcx
    ret
