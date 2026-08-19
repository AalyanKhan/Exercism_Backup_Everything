; Everything that comes after a semicolon (;) is a comment

C2 equ 2
C3 equ 3
C4 equ 4
C5 equ 5
C6 equ 6
C7 equ 7
C8 equ 8
C9 equ 9
C10 equ 10
CJ equ 11
CQ equ 12
CK equ 13
CA equ 14

TRUE equ 1
FALSE equ 0

section .text

; You should implement functions in the .text section

; the global directive makes a function visible to the test files
global value_of_card
value_of_card:
    ; This function takes as parameter a number representing a card
    ; The function should return the numerical value of the passed-in card
    ; Check if the card is an Ace (14)
    cmp rdi, CA
    je .is_ace
    
    ; Check if the card is a face card (CJ = 11, CQ = 12, CK = 13)
    cmp rdi, CJ
    jge .is_face_card
    
    ; Otherwise, it's a number card (2 through 10), so return its own value
    mov rax, rdi
    ret
    
.is_ace:
    mov rax, 1          ; Return 1 for an Ace
    ret

.is_face_card:
    mov rax, 10         ; Return 10 for CJ, CQ, or CK
    ret

global higher_card
higher_card:
    ; This function takes as parameters two numbers each representing a card
    ; The function should return which card has the higher value
    ; If both have the same value, both should be returned
    ; If one is higher, the second one should be 0
    ; Preserve our original card inputs since value_of_card will overwrite registers
    push rbx
    push r12
    mov rbx, rdi        ; rbx = card_one (original rank)
    mov r12, rsi        ; r12 = card_two (original rank)

    ; Get the blackjack value of card_one
    mov rdi, rbx
    call value_of_card
    mov r8, rax         ; r8 = value of card_one

    ; Get the blackjack value of card_two
    mov rdi, r12
    call value_of_card
    mov r9, rax         ; r9 = value of card_two

    ; Compare the two blackjack values
    cmp r8, r9
    je .equal
    jg .one_is_greater

.two_is_greater:
    mov rax, r12        ; Return card_two rank
    mov rdx, 0          ; Clear second return register
    jmp .done

.one_is_greater:
    mov rax, rbx        ; Return card_one rank
    mov rdx, 0          ; Clear second return register
    jmp .done

.equal:
    mov rax, rbx        ; Return both original card ranks
    mov rdx, r12

.done:
    pop r12
    pop rbx
    ret

global value_of_ace
value_of_ace:
    ; 1. Check the Hint: If either card in hand is already an Ace (CA = 14), 
    ; the upcoming Ace must strictly be 1.
    cmp rdi, CA
    je .choose_one
    cmp rsi, CA
    je .choose_one

    ; 2. Preserve original registers for calling value_of_card
    push rbx
    push r12
    mov rbx, rdi        
    mov r12, rsi        

    ; Get Blackjack value of card_one
    mov rdi, rbx
    call value_of_card
    mov r8, rax         

    ; Get Blackjack value of card_two
    mov rdi, r12
    call value_of_card
    mov r9, rax         

    ; Clean up the stack
    pop r12
    pop rbx

    ; 3. Standard point check logic
    add r8, r9          ; Combine card totals
    cmp r8, 10
    jle .choose_eleven  ; If score <= 10, next Ace can safely be 11

.choose_one:
    mov rax, 1          ; Return 1
    ret

.choose_eleven:
    mov rax, 11         ; Return 11
    ret


global is_blackjack
is_blackjack:
    ; This function takes as parameters two numbers each representing a card
    ; It returns TRUE if the two cards form a blackjack, and FALSE otherwise.
    push rbx
    push r12
    mov rbx, rdi        ; rbx = card_one
    mov r12, rsi        ; r12 = card_two

    ; Get point value of card_one
    mov rdi, rbx
    call value_of_card
    mov r8, rax         ; r8 = value of card_one

    ; Get point value of card_two
    mov rdi, r12
    call value_of_card
    mov r9, rax         ; r9 = value of card_two

    pop r12
    pop rbx

    ; A blackjack means one card is worth 1 (an Ace) and the other is worth 10
    ; Check Scenario 1: card_one == 1 AND card_two == 10
    cmp r8, 1
    jne .check_scenario_2
    cmp r9, 10
    je .true
    jmp .false

.check_scenario_2:
    ; Check Scenario 2: card_one == 10 AND card_two == 1
    cmp r8, 10
    jne .false
    cmp r9, 1
    je .true

.false:
    mov rax, FALSE
    ret

.true:
    mov rax, TRUE
    ret

    
global can_split_pairs
can_split_pairs:
    ; Checks if both cards have the same blackjack value
    push rbx
    push r12
    mov rbx, rdi
    mov r12, rsi

    ; Call value_of_card for card_one
    mov rdi, rbx
    call value_of_card
    mov r8, rax         ; r8 = value of card_one

    ; Call value_of_card for card_two
    mov rdi, r12
    call value_of_card  ; rax = value of card_two

    pop r12
    pop rbx

    ; Compare values
    cmp r8, rax
    je .split_true
    mov rax, FALSE
    ret

.split_true:
    mov rax, TRUE
    ret

global can_double_down
can_double_down:
    ; Checks if the original hand totals 9, 10, or 11 points
    ; Note: your value_of_card maps CA to 1 point. However, an Ace can act as 11 points.
    push rbx
    push r12
    mov rbx, rdi
    mov r12, rsi

    ; Value of card_one
    mov rdi, rbx
    call value_of_card
    mov r8, rax

    ; Value of card_two
    mov rdi, r12
    call value_of_card
    mov r9, rax

    pop r12
    pop rbx

    ; Calculate hand sum (using default value where Ace = 1)
    mov rcx, r8
    add rcx, r9         ; rcx = card_one + card_two

    ; Test base sum for 9, 10, 11
    cmp rcx, 9
    jl .test_soft_hand  ; Too low for base sum, check if soft hand can save it
    cmp rcx, 11
    jle .double_true    ; Base sum is 9, 10, or 11

.test_soft_hand:
    ; If there is an Ace in the hand, it can also count as 11 (adds 10 to our score)
    cmp rbx, CA
    je .try_soft
    cmp r12, CA
    je .try_soft
    jmp .double_false   ; No ace, and base sum is not 9, 10, 11

.try_soft:
    add rcx, 10         ; Upgrade one Ace from 1 point to 11 points
    cmp rcx, 9
    jl .double_false
    cmp rcx, 11
    jle .double_true

.double_false:
    mov rax, FALSE
    ret

.double_true:
    mov rax, TRUE
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
