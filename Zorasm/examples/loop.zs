; loop 69 times

#main
    !push  69			; push `69` to mem stack
    !store @0			; store it into global stack from addr 0
    !load @0			; load from global stack addr 0 to the mem stack
    !dec				; decrement `--`
    !store @0			; store the decremented value
    !load @0			; reload
    !print				; print to the stdout 
    !push "\n"  		; push newline string to the stack
    !print				; print new line
    !load @0			; load to the mem as int, the previous allocated number
    !push 1				; push `1` as int to mem
    !gte				; compare `n >= 1`
    !jmp #end			; jump to (2 + 1) instruction if the top of the (mem stack != 0)

#end
    !halt 0				; exit the program with status code 0
