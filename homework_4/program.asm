%macro        sys 1-*
    %rep %0
    %rotate -1
        push qword %1
    %endrep

    pop rax
    %if %0 > 1
           pop rbx
     %if %0 > 2
           pop rcx
      %if %0 > 3
           pop rdx
       %if %0 > 4
           pop rsi
        %if %0 > 5
           pop rdi
         %if %0 > 6
          %error "Too many params for syscall"
         %endif
        %endif
       %endif
      %endif
     %endif
    %endif
    int 80h
%endmacro

%macro        print 1-*
    %rep %0
        mov rdi, %1
        call _print_string
    %endrep
%endmacro

%macro        print_i 1-*
    %rep %0
        mov rdi, %1
        call _print_uint
    %endrep
%endmacro

%macro        swap 2
    mov r8, %1
    mov r9, %2
    mov %1, r9
    mov %2, r8
%endmacro

section .data
helpmsg: db `Usage:\n\
    ./langs -n <integer::count of elements> <str::output file> <str::output sorted file> \
or\n\
    ./langs -f <str::input file> <str::output file> <str::output sorted file>\n`, 0

helplen equ $-helpmsg
err1msg: db "Couldn't open source file for reading", 0
err1len equ $-err1msg
err2msg db "Couldn't open destination file for writing", 0
err2len equ $-err1msg

first_line_out: db `Filled container:\n\
Container contains `, 0
first_line_out_sorted: db `Sorted container:\n\
Container contains `, 0
first_line_out2: db ` elements.\n`, 0
lang_line: db ": It is ", 0
lang_line2: db " language: name = ", 0
lang_line3: db " (", 0
lang_line4: db "% | ", 0
lang_line5: db "), ", 0
abstract_type: db "abstract types support = ", 0
inheritance_type: db "inheritance = ", 0
typing_type: db "typing = ", 0
lazy_type: db ", lazy calculations = ", 0
lang_line6: db ". year / name.size() = ", 0
newline: db `\n`, 0
true_type: db "true", 0
false_type: db "false", 0
proc_lang: db "Procedure", 0
oop_lang: db "Object-oriented", 0
func_lang: db "Functional", 0
strict_lang: db "STRICT", 0
dynamic_lang: db "DYNAMIC", 0
single_lang: db "SINGLE", 0
multiple_lang: db "MULTIPLE", 0
interface_lang: db "INTERFACE", 0
procedure: db "procedure", 0
functional: db "functional", 0
oop: db "oop", 0
dot: db ".", 0

section .bss
    buf     resb 256
    bufsize equ     $-buf
    buffer  resq    1
    buffersize equ     $-buffer
    buf_ptr      resq 1
    buf2_ptr     resq 1
    year_buf     resq 1
    len_buf      resq 1
    year2_buf    resq 1
    len2_buf     resq 1
    mul_buf      resq 1
    mul2_buf     resq 1
    cur_buf      resq 1
    i_list_ptr   resq 1
    j_list_ptr   resq 1
    max_list_ptr resq 1
    i_cnt        resq 1
    j_cnt        resq 1


    fdsrc                 resq    1
    fddest                resq    1
    fddest_sorted         resq    1
    argc                  resq    1
    argvp                 resq    1

    element_count         resq    1

    list_pointer          resq    1
    list_start            resb    1400096  ; память под список структур
    list_start_size       equ $-list_start

    memory_pointer        resq    1
    memory                resb    100000048 ; память под данные структур
    memory_size           equ     $-memory

    output_cnt            resq    1
    output_pointer        resq    1
    output_buffer         resb    100000048
    output_size           equ     $-output_buffer

    seed                  resq    1
section .text
struc lang_elem
    .type:         resq    1
    .name          resq    1
    .popularity    resq    1
    .year          resq    1
    .ext:          resq    1
    .ext2:         resq    1
    lang_elem_nxt  resq    1
endstruc
%include "library.inc"

sys_write   equ 1       ; the linux WRITE syscall
sys_exit    equ 60      ; the linux EXIT syscall
sys_stdout  equ 1       ; the file descriptor for standard output (to print/write to)

section .data
    linebreak   db  0x0A    ; ASCII character 10, a line break
    gen_mode    db  '-n', 0
    file_mode   db  '-f', 0
    mode        db  "-x", 0
    input         db  "in", 0
    output        db  "out", 0
    output_sort   db  "out_sort", 0
    length: db 0x0
section .text
global _start
_start:
    mov rax, memory
    mov [memory_pointer], rax

    mov rax, output_buffer
    mov [output_pointer], rax

    mov rax, 0
    mov [output_cnt], rax

    mov rax, list_start
    mov [list_pointer], rax

    mov rax, 48
    mov [seed], rax

    pop qword [argc]
    mov [argvp], rsp
    cmp qword [argc], 5
    je .parse_mode
    sys 4, 2, helpmsg, helplen
    sys 1, 1

    .parse_mode:
    pop rdi
    mov rdi, [rsp]
    mov rsi, gen_mode
    call string_equals
    cmp rax, 1
    je .g_mode

    mov rdi, [rsp]
    mov rsi, file_mode
    call string_equals
    cmp rax, 1
    je .f_mode
    jmp print_help_message

    .g_mode:
        pop rdi
        pop rdi
        call parse_uint
        mov [element_count], rax


        pop rdi
        mov rsi, buf
        mov rdx, bufsize
        call string_copy
        mov rdi, buf
        sys 5, rdi, 241h, 0666o
        cmp rax, 0
        jge .g_dest_open_ok
        sys 4, 2, err2msg, err2len
        sys 1, 3
        .g_dest_open_ok:
            mov [fddest], rax

        pop rdi
        mov rsi, buf
        mov rdx, bufsize
        call string_copy
        mov rdi, buf
        sys 5, rdi, 241h, 0666o
        cmp rax, 0
        jge .g_dest_sort_open_ok
        sys 4, 2, err2msg, err2len
        sys 1, 3
        .g_dest_sort_open_ok:
            mov [fddest_sorted], rax

        jmp generate_elements

    .f_mode:    
        pop rdi
        pop rdi
        mov rsi, buf
        mov rdx, bufsize
        call string_copy
        mov rdi, buf
        sys 5, rdi, 0 ; O_RDONLY
        cmp rax, 0
        jge .source_open_ok
        sys 4, 2, err1msg, err1len
        sys 1, 2
        .source_open_ok:
            mov [fdsrc], rax

        pop rdi
        mov rsi, buf
        mov rdx, bufsize
        call string_copy
        mov rdi, buf
        sys 5, rdi, 241h, 0666o
        cmp rax, 0
        jge .dest_open_ok
        sys 4, 2, err2msg, err2len
        sys 1, 3
        .dest_open_ok:
            mov [fddest], rax

        pop rdi
        mov rsi, buf
        mov rdx, bufsize
        call string_copy
        mov rdi, buf
        sys 5, rdi, 241h, 0666o
        cmp rax, 0
        jge .dest_sort_open_ok
        sys 4, 2, err2msg, err2len
        sys 1, 3
        .dest_sort_open_ok:
            mov [fddest_sorted], rax

        jmp read_elements

; rdi: верхняя граница
; 
; rax: число
get_random_number_from_zero_to:
    push r10
    mov rax, [seed]
    imul rax, 48484841
    add rax, 421413
    add rax, rdi
    xor rax, 439723417
    mov [seed], rax

    mov r10, rdi
    inc r10
    xor rdx, rdx
    div r10
    mov rax, rdx
    pop r10
    ret


; rdi -- указатель на строку
write_to_memory:  

    mov   rsi, [memory_pointer]  
    mov   rdx, memory_size      ; фиктивно
    call  string_copy

    mov   rsi, [memory_pointer]
    add   rsi, rax
    mov   [memory_pointer], rsi
    ret


gen_type:
    mov rdi, 2
    call get_random_number_from_zero_to
    cmp rax, 0
    jne .oop
    mov rdi, procedure
    call write_to_memory
    ret

    .oop:
    cmp rax, 1
    jne .f
    mov rdi, oop
    call write_to_memory
    ret
    
    .f:
    cmp rax, 2
    
    mov rdi, functional
    call write_to_memory
    ret


; - 
; rdi -- сгенерированное имя
gen_name:
    xor r10, r10
    mov rax, buf
    mov [cur_buf], rax
    .loop:
        mov rdi, 25
        call get_random_number_from_zero_to
        add rax, 'a'
        mov rdi, [cur_buf]
        mov [rdi], rax
                
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax

        inc r10
        cmp r10, 5
        jle .loop
    mov rax, 0
    mov [cur_buf], rax

    mov rdi, buf
    call write_to_memory
    ret

gen_popularity:
    mov rax, buf
    mov [cur_buf], rax
    mov rdi, 9
    call get_random_number_from_zero_to
    add rax, '0'
    mov rdi, [cur_buf]
    mov [rdi], rax
            
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax

    mov rax, '.'
    mov rdi, [cur_buf]
    mov [rdi], rax
            
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax

    mov [cur_buf], rax
    mov rdi, 9
    call get_random_number_from_zero_to
    add rax, '0'
    mov rdi, [cur_buf]
    mov [rdi], rax
            
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax

    mov rax, 0
    mov rdi, [cur_buf]
    mov [rdi], rax
    
    mov rdi, buf
    call write_to_memory
    ret


gen_year:
    xor r10, r10
    mov rax, buf
    mov [cur_buf], rax

    mov rax, '1'
    mov rdi, [cur_buf]
    mov [rdi], rax
            
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax
    .loop:
        mov rdi, 9
        call get_random_number_from_zero_to
        add rax, '0'
        mov rdi, [cur_buf]
        mov [rdi], rax
                
        mov rax, [cur_buf]
        inc rax
        mov [cur_buf], rax

        inc r10
        cmp r10, 3
        jl .loop
    mov rax, 0
    mov [cur_buf], rax

    mov rdi, buf
    call write_to_memory
    ret

; rdi     
gen_ext:
    xor r10, r10
    mov rax, buf
    mov [cur_buf], rax


    call get_random_number_from_zero_to
    add rax, '0'
    mov rdi, [cur_buf]
    mov [rdi], rax
            
    mov rax, [cur_buf]
    inc rax
    mov [cur_buf], rax

    mov rax, 0
    mov [cur_buf], rax

    mov rdi, buf
    call write_to_memory
    ret
    
gen_ext2:
    jmp gen_ext

generate_elements:
    xor r10, r10
    .loop:
        push r10
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.type], rdi
        .type:
        call gen_type

        
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.name], rdi
        .name:
        call gen_name

        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.popularity], rdi
        .popularity:
        call gen_popularity


        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.year], rdi
        .year:
        call gen_year


        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.ext], rdi

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.type]
        mov dil, [rdi]
        cmp dil, 'o'
        je .three
        mov rdi, 1
        jmp .ext
        .three:
        mov rdi, 2
        .ext:
        call gen_ext

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.type]
        mov dil, [rdi]
        cmp dil, 'f'
        jne .nxt
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.ext2], rdi
        .ext2:
        mov rdi, 1
        call gen_ext2
        
        .nxt:
        pop r10
        inc r10

        mov rax, [list_pointer]
        add rax, lang_elem_size ; занимаем место
        mov [list_pointer], rax

        cmp r10, [element_count]
        jl .loop
    .end:
        ; sys 1, 1
        jmp print_unsorted_elements


_read_char:
    sys 3, [fdsrc], buffer, 1
    ret

_read_word:
  mov   r8, memory_size
  mov   r9, [memory_pointer] 
  xor   r10, r10 
  
  .read:
    call _read_char
    test  rax, rax
    jz    .term_zero
    mov   rcx, [buffer]
    mov   byte[r9+r10], cl
    mov   cl, byte[r9+r10]
    cmp   cl, ' '
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
    inc   r10
    mov   rax, [memory_pointer]
    add   rax, r10
    mov   [memory_pointer], rax
    mov   rax, r9
    ret
  .overflow:
    xor   rdx, r8 
    xor   rax, rax
    ret

read_elements:
    xor rax, rax
    mov [element_count], rax
    .loop:
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.type], rdi
        .type:
        call _read_word
        cmp rdx, 0
        jle .end

        
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.name], rdi
        .name:
        call _read_word
        cmp rdx, 0
        jle .end

        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.popularity], rdi
        .popularity:
        call _read_word
        cmp rdx, 0
        jle .end


        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.year], rdi
        .year:
        call _read_word
        cmp rdx, 0
        jle .end

        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.ext], rdi
        .ext:
        call _read_word
        cmp rdx, 0
        jle .end

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.type]
        mov dil, [rdi]
        cmp dil, 'f'
        jne .nxt
        mov rax, [list_pointer]
        mov rdi, [memory_pointer]
        mov [rax+lang_elem.ext2], rdi
        .ext2:
        call _read_word
        cmp rdx, 0
        jle .end
        
        .nxt:
        mov rax, [element_count]
        inc rax
        mov [element_count], rax

        mov rax, [list_pointer]
        add rax, lang_elem_size ; занимаем место
        mov [list_pointer], rax


        jmp .loop
    .end:
        jmp print_unsorted_elements

_flush_output:
    ; ret
    sys 4, [fddest], output_buffer, [output_cnt]
    
    mov rax, 0
    mov [output_cnt], rax

    mov rax, output_buffer
    mov [output_pointer], rax
    ret


_print_string:
    call string_length

    mov   rsi, [output_pointer]  
    mov   rdx, output_size      ; фиктивно
    call  string_copy
    dec rax

    mov   rsi, [output_pointer]
    add   rsi, rax
    mov   [output_pointer], rsi
    add   [output_cnt], rax

    ; sys 4, [fddest], rdi, rax
    ret

print_unsorted_elements:
    print   first_line_out
    print_i [element_count]
    print   first_line_out2

    call print_elements
    jmp sort_elements

_print_uint:
  mov   r10, 10
  mov   rax, rdi
  mov   rdi, rsp
  sub rsp, 21
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

  mov rsi, buf
  mov rdx, bufsize
  call string_copy
  mov rdi, buf
  call  _print_string
  add   rsp, 21
  ret

_print_bool:
    cmp dil, '0'
    je .false
    print true_type
    ret
    .false:
        print false_type
        ret

print_proc:
    print proc_lang
    print lang_line2

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.name]
    call _print_string
    print lang_line3

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.popularity]
    call _print_string    
    print lang_line4

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.year]
    call _print_string
    print lang_line5

    print abstract_type
    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.ext]
    mov rdi, [rdi]
    call _print_bool

    print lang_line6
    ret

print_oop:
    print oop_lang
    print lang_line2

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.name]
    call _print_string
    print lang_line3

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.popularity]
    call _print_string    
    print lang_line4

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.year]
    call _print_string
    print lang_line5

    print inheritance_type
    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.ext]
    mov dil, [rdi]
    
    .s:
    cmp dil, '0'
    jne .m 
    print single_lang
    jmp .end
    
    .m:
    cmp dil, '1'
    jne .i
    print multiple_lang
    jmp .end

    .i:
    cmp dil, '2'
    jne .end
    print interface_lang
    jmp .end

    .end:
        print lang_line6
        ret

print_func:
    print func_lang
    print lang_line2

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.name]
    call _print_string
    print lang_line3

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.popularity]
    call _print_string    
    print lang_line4

    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.year]
    call _print_string
    print lang_line5

    print typing_type
    mov rax, [list_pointer]
    mov rdi, [rax+lang_elem.ext]
    mov dil, [rdi]
    
    .s:
    cmp dil, '0'
    jne .d 
    print strict_lang
    jmp .lazy
    
    .d:
    cmp dil, '1'
    jne .end
    print dynamic_lang
    jmp .lazy

    .lazy:
        print lazy_type
        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.ext2]
        mov rdi, [rdi]
        call _print_bool
        print lang_line6
    .end:
        ret

print_elements:
    mov rax, list_start
    mov [list_pointer], rax

    xor r9, r9
    .loop:
        cmp r9, [element_count]
        jge .end
        print_i r9
        print lang_line

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.type]
        mov dil, [rdi]
        .p:
        cmp  dil, 'p'
        jne .o
        call print_proc
        jmp .nxt
        
        .o:
        cmp dil, 'o'
        jne .f
        call print_oop
        jmp .nxt
        
        .f:
        cmp dil, 'f'
        jne .nxt
        call print_func
        jmp .nxt

        .nxt:

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.year]
        
        call parse_uint
        mov [year_buf], rax

        mov rax, [list_pointer]
        mov rdi, [rax+lang_elem.name]
        call string_length
        mov [len_buf], rax

        xor rdx, rdx
        mov rax, [year_buf]
        mov r10, [len_buf]
        div r10
        push rdx
        print_i rax
        print dot
        xor rdx, rdx
        pop rax
        imul rax, 1000
        mov r10, [len_buf]
        div r10
        
        push rax
        cmp rax, 100
        jge .print_zero_zero
        .print_one_zero:
            mov rdi, 0
            call _print_uint
            pop rax
            push rax
            cmp rax, 10
            jge .print_zero_zero
        .print_two_zero:
            mov rdi, 0
            call _print_uint
        .print_zero_zero:
            pop rax
            print_i rax


        print newline
        mov rax, [list_pointer]
        add rax, lang_elem_size
        mov [list_pointer], rax
        inc r9
        ; call _flush_output
        jmp .loop
    .end:
        call _flush_output
        ret

; сложение дробей заменено на сравнение произведений
cmp_elem:
    mov [buf_ptr], rdi
    mov [buf2_ptr], rsi

    mov rax, [buf_ptr]
    mov rdi, [rax+lang_elem.year]
    
    call parse_uint
    mov [year_buf], rax

    mov rax, [buf2_ptr]
    mov rdi, [rax+lang_elem.name]
    call string_length
    mov [len2_buf], rax

    mov rax, [year_buf]
    mov r10, [len2_buf]
    imul rax, r10
    mov [mul_buf], rax
    ; правая часть
    mov rax, [buf2_ptr]
    mov rdi, [rax+lang_elem.year]
    
    call parse_uint
    mov [year2_buf], rax

    mov rax, [buf_ptr]
    mov rdi, [rax+lang_elem.name]
    call string_length
    mov [len_buf], rax

    mov rax, [year2_buf]
    mov r10, [len_buf]
    imul rax, r10
    mov [mul2_buf], rax


    mov rax, [mul_buf]
    mov rdi, [mul2_buf]
    cmp rax, rdi
    jge .less
    mov rax, 1
    ret
    .less:
        mov rax, 0
    ret 

swap_elem:
    mov [buf_ptr], rdi
    mov [buf2_ptr], rsi
    
    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.type], [rcx+lang_elem.type]

    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.name], [rcx+lang_elem.name]
    

    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.popularity], [rcx+lang_elem.popularity]


    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.year], [rcx+lang_elem.year]

    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.ext], [rcx+lang_elem.ext]

    mov rax, [buf_ptr]
    mov rcx, [buf2_ptr]
    swap [rax+lang_elem.ext2], [rcx+lang_elem.ext2]

    ret

sort_elements:

    mov rax, list_start
    mov [list_pointer], rax

    xor rax, rax
    mov [i_cnt], rax
    inc rax
    mov [j_cnt], rax

    mov rdi, [list_pointer]
    mov [i_list_ptr], rdi
    add rdi, lang_elem_size
    mov [j_list_ptr], rdi
    .loop:
        mov rdi, [i_list_ptr]
        mov [max_list_ptr], rdi
        mov rax, [element_count] 
        dec rax
        cmp [i_cnt], rax
        jge .end
        .loop2:
            mov rax, [element_count] 
            cmp [j_cnt], rax
            jge  .swap 

            mov rdi, [max_list_ptr]
            mov rsi, [j_list_ptr]
            call cmp_elem
            cmp rax, 1
            jne .skip
            mov rsi, [j_list_ptr]   ; обновление максимума
            mov [max_list_ptr], rsi
            

            .skip:
            mov rdi, [j_list_ptr]
            add rdi, lang_elem_size
            mov [j_list_ptr], rdi

            mov rax, [j_cnt]
            inc rax
            mov [j_cnt], rax

            jmp .loop2

        .swap:
        mov rdi, [i_list_ptr]
        mov rsi, [max_list_ptr]
        call swap_elem


        mov rax, [i_cnt]
        inc rax
        mov [i_cnt], rax
        inc rax
        mov [j_cnt], rax
        ; сдвиг list_pointer
        mov rax, [list_pointer]
        add rax, lang_elem_size
        mov [list_pointer], rax
        ; сдвиг текущих указателей
        mov rdi, [list_pointer]
        mov [i_list_ptr], rdi
        add rdi, lang_elem_size
        mov [j_list_ptr], rdi

        jmp .loop
    .end:
    jmp print_sorted_elements

print_sorted_elements:
    mov rax, [fddest_sorted]
    mov [fddest], rax
    print first_line_out_sorted
    print_i [element_count]
    print   first_line_out2
    call print_elements
    jmp exit

print_help_message:
    call print_newline
    mov rdi, helpmsg
    call print_string
exit:
    mov rax,    sys_exit
    mov rdi,    0       
    syscall             
