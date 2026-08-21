; Constants defined for NASM
%ifndef WEIGHT_OF_EMPTY_BOX
    WEIGHT_OF_EMPTY_BOX equ 500
%endif

%ifndef TRUCK_HEIGHT
    TRUCK_HEIGHT equ 300
%endif

%ifndef PAY_PER_BOX
    PAY_PER_BOX equ 5
%endif

%ifndef PAY_PER_TRUCK_TRIP
    PAY_PER_TRUCK_TRIP equ 220
%endif

section .text

; -----------------------------------------------------------------------------
; 1. get_box_weight
; -----------------------------------------------------------------------------
global get_box_weight
get_box_weight:
    ; 1st product: count1 (di) * weight1 (si)
    movzx   eax, di             ; eax = count1
    movzx   r8d, si             ; r8d = weight1
    imul    eax, r8d            ; eax = count1 * weight1

    ; 2nd product: count2 (dx) * weight2 (cx)
    movzx   r9d, cx             ; READ cx FIRST before overwriting ecx!
    movzx   ecx, dx             ; ecx = count2
    imul    ecx, r9d            ; ecx = count2 * weight2

    ; Total = product1 + product2 + empty_box
    add     eax, ecx
    add     eax, WEIGHT_OF_EMPTY_BOX
    ret

; -----------------------------------------------------------------------------
; 2. max_number_of_boxes
; -----------------------------------------------------------------------------
global max_number_of_boxes
max_number_of_boxes:
    mov     ax, TRUCK_HEIGHT
    div     dil
    ret

; -----------------------------------------------------------------------------
; 3. items_to_be_moved
; -----------------------------------------------------------------------------
global items_to_be_moved
items_to_be_moved:
    mov     eax, edi
    sub     eax, esi
    ret

; -----------------------------------------------------------------------------
; 4. calculate_payment
; -----------------------------------------------------------------------------
global calculate_payment
calculate_payment:
    ; Box & Trip Earnings
    mov     eax, esi            ; eax = boxes
    mov     r10d, PAY_PER_BOX   
    imul    rax, r10            ; rax = boxes * 5

    mov     r10d, edx           ; r10d = trips
    imul    r10, PAY_PER_TRUCK_TRIP
    add     rax, r10            ; rax = gross earnings

    ; Deductions
    sub     rax, rdi            ; rax = gross - up_front

    mov     r10d, ecx           ; r10d (32-bit) zero-extends ecx into r10
    imul    r10, r8             ; r10 = broken_items * item_value
    sub     rax, r10            ; rax = net balance

    ; Division across workers
    movzx   r10, r9b            ; r10 = other_workers
    inc     r10                 ; r10 = total_workers

    cqo                         ; sign-extend rax -> rdx:rax
    idiv    r10                 ; rax = share, rdx = remainder

    add     rax, rdx            ; Your total = share + remainder
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif