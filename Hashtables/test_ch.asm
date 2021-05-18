; to balance brackets

section .data

newline: db 10
nwl: equ $-newline


section .bss
string resb 500
string_len resw 1
string1 resb 500
str_len1 resw 1
string2 resb 100
str_len2 resw 1
temp resw 1

section .text
      global _start:
      _start:
mov word[string_len], 0
mov ebx, string1
call read_string
mov ecx, 0
mov cx, [string_len]
mov [str_len1], cx

mov ebx, string1
loop2:cmp byte[ebx],34
      je end_loop2
      inc ebx
      jmp loop2
end_loop2:
add ebx, 1
push ebx
mov ebx, string1
mov eax, ebx
add  eax, ecx
add eax, -1
mov byte[eax], 0
pop ebx

mov word[str_len2], 0
mov ecx, 0
mov edx, 0
mov eax, string2



loop1:cmp byte[ebx+ecx], 0
      je check_r
    
     cmp byte[ebx+ecx], 41  ;--)
       je update_l
     next: cmp byte[ebx+ecx], 40  ;---(
              je update_r

      next_no_issue:
      push edx
      mov dl, byte[ebx+ecx]
      mov byte[eax], dl  
      inc eax   
      pop edx

loop_check:
      add ecx, 1
      jmp loop1
    
check_r: cmp edx,0
          je exit_loop1
          mov byte[eax], 41
          inc eax
          add edx, -1
          jmp check_r

exit_loop1: 
     mov byte[eax], 0
     mov ebx, string2
           
      
      call print_string

      mov eax, 1
      mov ebx, 0
      int 80h

update_l:
add edx, -1
cmp edx, 0
jl remove
jmp next

update_r:
add edx, 1
jmp next_no_issue


remove:
add edx, 1
jmp loop_check


read_string:
pusha
reading:
push ebx
mov eax, 3
mov ebx, 0
mov ecx, temp
mov edx, 1
int 80h
pop ebx
cmp byte[temp], 10   ;; check if the input is ’Enter’
je end_reading
inc word[string_len]
mov al,byte[temp]
mov byte[ebx], al
inc ebx
jmp reading

end_reading:
;; Similar to putting a null character at the end of a string
mov byte[ebx], 0
mov ebx, string
popa
ret



print_string:
pusha

printing:
mov al, byte[ebx]
mov [temp], al
cmp byte[temp], 0    ;; checks if the character is NULL character
je end_printing

push ebx
mov eax, 4
mov ebx, 1
mov ecx, temp
mov edx, 1
int 80h
pop ebx
inc ebx
jmp printing

end_printing:
mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, nwl
int 80h
popa
ret



