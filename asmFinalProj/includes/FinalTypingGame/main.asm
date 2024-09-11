.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode: DWORD
include irvine32.inc
.data
	;define variables here
	screenSizePrompt BYTE "__Screen Size__", 0
	fullSizePrompt BYTE "Fullscreen Window", 0
	miniSizePrompt BYTE "Mini Window", 0
	screenExplain BYTE "To use ", 34, "Fullscreen Window", 34, " first maximize the window then press enter on Fullscreen Window", 0

	gameQueryPrompt BYTE "Which game do you want to play?", 0

	typingTutorPrompt BYTE "TYPING TUTOR",0

	typingGamePrompt BYTE "TYPING GAME",0

	allWordsUsedprompt BYTE "ALL WORDS USED", 0

	gameOver byte 0

	easyPrompt BYTE "EASY",0
	mediumPrompt BYTE "MEDIUM",0
	hardPrompt BYTE "HARD",0

	rightArrowPrompt BYTE "-->",0
	leftArrowPrompt BYTE "<--",0
	blankArrowPrompt BYTE "   ",0
	blankSpacePrompt BYTE "          ",0
	spacePrompt BYTE " ",0

	heartPrompt Byte 3, " ", 0
	liveCount Byte 5
	pointCount WORD 0

	livesPrompt Byte "LIVES: ", 0
	scorePrompt byte "SCORE: ", 0
	dashPrompt Byte "-", 0

	gameDifficulty Byte ?

	screenTest BYTE "a",0


	gameOverPrompt BYTE "GAME OVER!",0

	smallScreenSizeX EQU 120
	smallScreenSizeY EQU 30

	bigScreenSizeX EQU 210
	bigScreenSizeY EQU 50

	usedScreenSizeX Byte ?
	usedScreenSizeY Byte ?

	xPos BYTE 10
	yPos BYTE 29


	;FOR THE LEVEL POSITION


	lastXPos Byte ?
	lastYPos Byte ?

	saveXPos Byte ?
	saveYPos Byte ?

	randomNum byte ?

	;---------------------WORDS--------------------------------------------------
	COMMENT $
	aWords BYTE "act", 0 
		   BYTE "ash", 0
		   BYTE "aim", 0
		   BYTE "also", 0
		   BYTE "atom", 0
		   BYTE "aunt", 0
		   BYTE "apple", 0
		   BYTE "amber", 0
		   BYTE "arrow", 0
		   BYTE "around", 0
		   BYTE "addict", 0
		   BYTE "access", 0
		   BYTE "account", 0
		   BYTE "advance", 0
		   BYTE "article", 0

	bWords BYTE "bag", 0
		   BYTE	"bat", 0
		   BYTE	"bus", 0
		   BYTE	"bank", 0
		   BYTE	"base", 0
		   BYTE	"beat", 0
		   BYTE	"break", 0
		   BYTE	"brave", 0
		   BYTE	"brush", 0
		   BYTE	"banner", 0
		   BYTE	"butter", 0
		   BYTE	"branch", 0
		   BYTE	"barrier", 0
		   BYTE	"bicycle", 0
		   BYTE	"balance", 0

	cWords BYTE "cat", 0
		   BYTE "cab", 0
		   BYTE "cop", 0
		   BYTE "cake", 0
		   BYTE "call", 0
		   BYTE "corn", 0
		   BYTE "cloud", 0
		   BYTE "chair", 0
		   BYTE "crown", 0
		   BYTE "camera", 0
		   BYTE "cactus", 0
		   BYTE "cereal", 0
		   BYTE "concert", 0
		   BYTE "courage", 0
		   BYTE "curtain", 0

	;dWords Byte "dog", 0, "day", 0, "dot", 0, "desk", 0, "duck", 0, "dive", 0, "dream", 0, "drink", 0, "dance", 0, "danger", 0, "doctor", 0, "double", 0, "desktop", 0, "display", 0, "disease", 0

	;eWords Byte "eat", 0, "egg", 0, "end", 0, "echo", 0, "edge", 0, "else", 0, "earth", 0, "eagle", 0, "error", 0, "escape", 0, "expert", 0, "extend", 0, "excited", 0, "elastic", 0, "example", 0

	;fWords Byte "fan", 0, "fix", 0, "fun", 0, "fact", 0, "fast", 0, "fire", 0, "flame", 0, "fairy", 0, "fleet", 0, "feline", 0, "fiasco", 0, "flinch", 0, "foresee", 0, "fortune", 0, "freedom", 0

	;gWords Byte "gap", 0, "get", 0, "gum", 0, "game", 0, "gift", 0, "glow", 0, "giant", 0, "grape", 0, "grass", 0, "garden", 0, "goblin", 0, "gospel", 0, "glimpse", 0, "gravity", 0, "general", 0
	$

	aWords BYTE "act", 0 
		   BYTE "atom", 0
		   BYTE "amber", 0
		   BYTE "access", 0
		   BYTE "advance", 0

	bWords BYTE "bag", 0
		   BYTE	"beat", 0
		   BYTE	"brave", 0
		   BYTE	"branch", 0
		   BYTE	"balance", 0

	cWords BYTE "cat", 0
		   BYTE "corn", 0
		   BYTE "crown", 0
		   BYTE "camera", 0
		   BYTE "concert", 0

	dWords BYTE "dog", 0
		   BYTE "duck", 0
		   BYTE "dream", 0
		   BYTE "double", 0
		   BYTE "desktop", 0

	eWords Byte "eat", 0
		   BYTE "echo", 0
		   BYTE "error", 0
		   BYTE "expert", 0
		   BYTE "elastic", 0

	fWords Byte "fix", 0
		   BYTE "fire", 0
		   BYTE "fairy", 0
		   BYTE "fiasco", 0
		   BYTE "freedom", 0

	gWords Byte "gap", 0
		   BYTE "glow", 0
		   BYTE "grape", 0
		   BYTE "gospel", 0
		   BYTE "glimpse", 0
	;---------------------WORDS--------------------------------------------------
	wordsPerList EQU 5
	lengthOfSmallestWord EQU 3

	lettersCurrentlyUsed DWORD 7 Dup(1)
	wordsXPos BYTE 7 Dup(99h)
	wordsYPos BYTE 7 Dup(77h)
	
	correctBit BYTE 0
	wrongBit BYTE 0
	typingWord DWORD 1
	typingWordX DWORD ?
	typingWordY DWORD ?
	typingWordSize BYTE ?
	typingWordAddy DWORD 1

	typingWordLetter BYTE ?
	typingWordPointer DWORD ?
	
	currentWordSize BYTE ?
	currentWordLetter BYTE ?

	readyPrompt BYTE "READY",0
	timeElapsed DWORD ?
	errorCounter DWORD 0


	poem1 BYTE "I never thought I", 39, "d keep a record of my pain", 13, 10, "or happiness", 13, 10, "like candles lighting the entire soft lace", 13, 10, "of the air", 13, 10, "around the full length of your hair/a shower",
			   13, 10, "organized by God", 13, 10, "in brown and auburn", 13, 10, "undulations luminous like particles", 13, 10, "of flame", 13, 10, 13, 10, "But now I do", 13, 10, "retrieve an afternoon...", 0
	
	Comment $
	poem1 BYTE "I never thought I", 0
	$

	poem1CharCount EQU 267

	accuracyPrompt byte "Accuracy: ", 0
	percentagePrompt byte "%", 0
	wpmPrompt byte "Characters per Second: ", 0

.code

;--------------------------------------------------------------------------------------------------------------------------------------------------------

main PROC
	; write assembly code here
	;call Gotoxy
	;mov edx,OFFSET screenTest
	;call WriteString

	mov eax, (black * 16) + white
	call SetTextColor

	call pickSizeScreen


	;mov eax, magenta + (yellow * 16)
	;call SetTextColor
	;call WriteString

	INVOKE ExitProcess, 0
main ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

storePos PROC
	mov lastXPos, dl
	mov lastYPos, dh

	mov dl, xPos
	mov dh, yPos
	
	call gotoxy
	ret
storePos ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

restorePos PROC
	mov dl, xPos
	mov dh, yPos

	xchg dl, lastXPos
	xchg dh, lastYPos

	ret
restorePos ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

pickSizeScreen PROC
	
	PUSH EAX
	mov eax, white
	call setTextColor
	POP EAX

	mov ecx, 1
	call useSmallScreen

	selectionArrow:
	
	call clrscr
	mov edx, 0

	;getting the 1/5 y axis
	mov eax, 0
	mov al, usedScreenSizeY
	mov bl, 5
	div bl

	mov dh, al
	mov dl, usedScreenSizeX
	shr dl, 1
	
	mov xPos, dl
	mov yPos, dh
	;Half the prompt length
	sub dl, 7

	call Gotoxy
	mov edx,OFFSET screenSizePrompt
	call WriteString


	;Screen size options prompt
	add yPos, 6
	sub xPos, 5
	call storePos
	mov edx,OFFSET miniSizePrompt
	call WriteString


	add yPos, 3
	sub xPos, 3
	call storePos
	mov edx,OFFSET fullSizePrompt
	call WriteString

	;Getting where the arrows gonna be
	sub yPos, 3
	sub xPos, 1
	call saveCurrentPos

	mov dl, 1
	mov dh, usedScreenSizeY
	sub dh, 2
	call gotoXY
	mov edx, OFFSET screenExplain
	call WriteString

	COMMENT $
	call randomNumGen
	mov eax, 0
	mov al, randomNum
	call DumpRegs
	$

		.IF ecx <= 1
			mov ecx, 1

		;Erasing the other arrow
			call restoreSavePos
			add yPos, 3
			sub xPos, 3
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString
	
			add xPos, 22
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString
		
		;Printing the arrow
			call restoreSavePos
			call storePos
			mov edx, OFFSET rightArrowPrompt
			call WriteString

			add xPos, 16
			call storePos
			mov edx, OFFSET leftArrowPrompt
			call WriteString

		.ELSEIF ecx >= 2
			mov ecx, 2
			
		;Erasing other arrow
			call restoreSavePos
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString

			add xPos, 16
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString

		;Printing this arrow
			call restoreSavePos
			add yPos, 3
			sub xPos, 3
			call storePos
			mov edx, OFFSET rightArrowPrompt
			call WriteString
	
			add xPos, 22
			call storePos
			mov edx, OFFSET leftArrowPrompt
			call WriteString

		.ENDIF

		mov dl, usedScreenSizeX
		mov dh, usedScreenSizeY
		dec dl
		dec dh
		call gotoXY

	LookForKey:
		mov  eax, 100        
		call Delay        

		call ReadKey     
	jz   LookForKey 
	call anotherGame ;-------------------------------------------

	;call clrscr
	;call DumpRegs

	cmp dx, VK_UP
	je up_level


	cmp dx, VK_DOWN
	je down_level

	cmp dx, VK_RETURN
	je screenSizeSelected

	jmp LookForKey

	up_level:
		dec ecx
		call useSmallScreen
		jmp selectionArrow

	down_level:
		inc ecx
		call useBigScreen
		jmp selectionArrow


	screenSizeSelected:
	.IF ecx == 1
		call useSmallScreen
	.ELSEIF ecx ==2
		call useBigScreen
	.ENDIF


	call whichGameFunc

	ret

pickSizeScreen ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------------------------------------------------------

whichGameFunc PROC

	PUSHAD

	mov eax, white
	call setTextColor

	call clrscr

	mov edx, 0

	;getting the 1/5 y axis
	mov eax, 0
	mov al, usedScreenSizeY
	mov bl, 5
	div bl

	mov dh, al
	mov dl, usedScreenSizeX
	shr dl, 1
	
	mov xPos, dl
	mov yPos, dh
	;Half the prompt length
	sub dl, 15

	call Gotoxy
	mov edx,OFFSET gameQueryPrompt
	call WriteString


	;Screen size options prompt
	add yPos, 6
	sub xPos, 7
	call storePos
	mov edx,OFFSET typingTutorPrompt
	call WriteString


	add yPos, 3
	add xPos, 1
	call storePos
	mov edx,OFFSET typingGamePrompt
	call WriteString

	;Getting where the arrows gonna be
	sub yPos, 3
	sub xPos, 5
	call saveCurrentPos



	mov ecx, 1

	selectionArrow:

		.IF ecx <= 1
			mov ecx, 1

		;Erasing the other arrow
			call restoreSavePos
			add yPos, 3
			add xPos, 1
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString
	
			add xPos, 16
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString
		
		;Printing the arrow
			call restoreSavePos
			call storePos
			mov edx, OFFSET rightArrowPrompt
			call WriteString

			add xPos, 17
			call storePos
			mov edx, OFFSET leftArrowPrompt
			call WriteString

		.ELSEIF ecx >= 2
			mov ecx, 2
			
		;Erasing other arrow
			call restoreSavePos
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString

			add xPos, 17
			call storePos
			mov edx, OFFSET blankArrowPrompt
			call WriteString

		;Printing this arrow
			call restoreSavePos
			add yPos, 3
			add xPos, 1
			call storePos
			mov edx, OFFSET rightArrowPrompt
			call WriteString
	
			add xPos, 16
			call storePos
			mov edx, OFFSET leftArrowPrompt
			call WriteString

		.ENDIF

		mov dl, usedScreenSizeX
		mov dh, usedScreenSizeY
		dec dl
		dec dh
		call gotoXY

	LookForKey:
		mov  eax, 100        
		call Delay        

		call ReadKey     
	jz   LookForKey 
	call anotherGame ;-------------------------------------------

	;call clrscr
	;call DumpRegs

	cmp dx, VK_UP
	je up_level


	cmp dx, VK_DOWN
	je down_level

	cmp dx, VK_RETURN
	je screenSizeSelected

	jmp LookForKey

	up_level:
		dec ecx
		jmp selectionArrow

	down_level:
		inc ecx
		jmp selectionArrow


	screenSizeSelected:
	.IF ecx == 1
		call typingTutorFunc
	.ELSEIF ecx ==2
		call typingGameFunc
	.ENDIF

	POPAD

	ret

whichGameFunc ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------


typingTutorReset PROC
	mov errorCounter, 0
	ret
typingTutorReset ENDP


;--------------------------------------------------------------------------------------------------------------------------------------------------------

typingTutorFunc PROC
	PUSHAD
	call typingTutorReset

	call clrscr
	mov edx, 0

	;----------------------------COUNTDOWN-------------------------------------------------------
	;getting the 1/5 y axis
	mov ax, 0
	mov al, usedScreenSizeY
	mov bl, 3
	div bl

	mov dh, al
	mov dl, usedScreenSizeX
	shr dl, 1
	
	mov xPos, dl
	mov yPos, dh
	;should be 5 but im making 7
	sub dl, 3

	call Gotoxy
	
	mov edx,OFFSET readyPrompt
	call WriteString

	add yPos, 3
	dec xPos

	call storePos

	mov ecx, 3
	countdown:
		mov eax, ecx
		call writeDec

		call storePos

		mov eax, 1000
		call Delay
	loop countdown
	;----------------------------COUNTDOWN-------------------------------------------------------

	call clrscr

	mov ecx, 0

	mov xPos, 0
	mov yPos, 1
	call storePos

	mov edx, offset poem1
	call writeString

	call storePos
	mov esi, offset poem1

	mov eax, green
	call setTextColor

	nextLetter:
		mov al, byte PTR [esi]
		mov typingWordLetter, al
		.IF al == 0
			jmp gameFinished
		.ENDIF

		LookForKey:
			mov  eax, 20        
			call Delay
			inc ecx

			call ReadKey
		jz LookForKey 
		call anotherGame ;-------------------------------------------

		and eax, 0ffh

		.IF al == typingWordLetter
			call writeChar
			inc esi
			.IF al == 13
				inc esi
				inc yPos
				call storePos
			.ENDIF
			jmp nextLetter
		.ENDIF
		inc errorCounter
	jmp nextLetter



	gameFinished:
	mov eax, white
	call setTextColor

	mov edx, 0
	mov eax, ecx
	mov ecx, 50
	div ecx

	mov ecx, eax
	.IF ecx == 0
		mov ecx, 1
	.ENDIF
	mov eax, poem1CharCount
	mov ebx, 100
	mul ebx
	div ecx

	mov timeElapsed, eax

	;-----------------------------------------------------

	mov edx, 0
	mov eax, poem1CharCount
	sub eax, errorCounter

	mov ecx, 100
	mul ecx
	
	mov ecx, poem1CharCount
	div ecx
	
	mov errorCounter, eax

	;----------------------------------------------------------------

	call clrscr

	mov dl, UsedScreenSizeX
	shr dl, 1
	sub dl, 5
	mov xPos, dl

	mov dh, UsedScreenSizeY
	shr dh, 1
	sub dh, 3
	mov yPos, dh

	call storePos

	mov edx, offset gameOverPrompt
	call writeString

	sub xPos, 2
	add yPos, 3
	call storePos

	mov edx, offset accuracyPrompt
	call writeString
	mov eax, errorCounter
	call writeDec
	mov edx, offset percentagePrompt
	call writeString

	sub xPos, 5
	add yPos, 2
	call storePos

	mov edx, offset wpmPrompt
	call writeString
	mov eax, timeElapsed
	call writeDec

	mov dl, 0
	mov dh, UsedScreenSizeY
	dec dh
	call gotoxy
	
	keyYes:
    mov  eax, 100        
    call Delay        

    call ReadKey     
	jz   keyYes
	call anotherGame ;-------------------------------------------
	Comment $
	.IF al == 27
		call whichGameFunc
	.ENDIF
	.IF ah == 83
		call pickSizeScreen
	.ENDIF
	$
	call anotherGame

	INVOKE ExitProcess, 0

	POPAD
	ret
typingTutorFunc ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

anotherGame PROC
	PUSHAD
	
	.IF al == 27
		POPAD
		call whichGameFunc
	.ENDIF
	.IF ah == 83
		POPAD
		call pickSizeScreen
	.ENDIF
	
	POPAD

	ret
anotherGame ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

	typingGameReset PROC
		PUSHAD
		mov liveCount, 5
		mov pointCount, 0
		mov gameOver, 0

		mov esi, offset lettersCurrentlyUsed
		mov ecx, 7

		typingGameResetLoop:
			mov dword ptr [esi], 1
			add esi, 4

		LOOP typingGameResetLoop

		mov correctBit, 0
		mov wrongBit, 0
		mov typingWord, 1
		mov typingWordAddy, 1

		POPAD

		ret
	typingGameReset ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

typingGameFunc PROC
	PUSHAD

	call typingGameReset

	call clrscr
	mov edx, 0

	;getting the 1/5 y axis
	mov ax, 0
	mov al, usedScreenSizeY
	mov bl, 5
	div bl

	mov dh, al
	mov dl, usedScreenSizeX
	shr dl, 1
	
	mov xPos, dl
	mov yPos, dh
	;should be 5 but im making 7
	sub dl, 5

	;call storePos
	call Gotoxy
	mov edx,OFFSET typingGamePrompt
	call WriteString

	add yPos, 5
	sub xPos, 1
	call storePos
	mov edx,OFFSET easyPrompt
	call WriteString


	add yPos, 2
	sub xPos, 1
	call storePos
	mov edx,OFFSET mediumPrompt
	call WriteString


	add yPos, 2
	add xPos, 1
	call storePos
	mov edx,OFFSET hardPrompt
	call WriteString

	;Setting it back to easy position to make pointer
	sub yPos, 4
	sub xPos, 4


	call difficultyPointer

	call clrscr

	call HUDCreate

	;mov ecx, 20
	spawnWords:
	;push ecx
	
	PUSHAD
	call newWordGen
	POPAD

	mov ecx, 5 ;SPACE BETWEEN WORDS
	gravity:
		PUSH ecx
		call fallingWord
		.IF gameOver == 1
			jmp gameFinished
		.ENDIF

			;movzx eax, correctBit
			;call writeInt
		
		PUSH eax
		mov eax, 30
		div gameDifficulty
		mov ecx, eax
		POP eax

		LookForKey:
			PUSH ecx
			mov  eax, 20        
			call Delay        

			call ReadKey
			jz pastGetting
				call anotherGame ;-------------------------------------------
				call gettingWord
				.IF typingWordAddy != 1
					call typingColor
				.ENDIF
			pastGetting:
			POP ecx
		loop LookForKey 
			;movzx eax, correctBit
			;call writeInt

		POP ecx
	Loop gravity

	;pop ecx
	jmp spawnWords
	
	gameFinished:
		call gameOverScreen
	POPAD
	ret
typingGameFunc ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

gameOverScreen PROC
	
	call clrscr

	mov dl, UsedScreenSizeX
	shr dl, 1
	sub dl, 5
	mov xPos, dl

	mov dh, UsedScreenSizeY
	shr dh, 1
	sub dh, 3
	mov yPos, dh

	call storePos

	mov edx, offset gameOverPrompt
	call writeString


	add yPos, 3
	call storePos
	
	mov eax, 0

	mov edx, offset scorePrompt
	call writeString
	mov ax, pointcount
	call writeInt

	mov dl, 0
	mov dh, UsedScreenSizeY
	dec dh
	call gotoxy
	
	LookForKey:
    mov  eax, 100        
    call Delay        

    call ReadKey     
	jz   LookForKey 

	COMMENT $
	.IF al == 27
		call whichGameFunc
	.ENDIF
	.IF ah == 83
		call pickSizeScreen
	.ENDIF
	$
	call anotherGame

	INVOKE ExitProcess, 0
gameOverScreen ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

newWordGen PROC

	call randomString

	.IF currentWordLetter == 10
		jmp noWords
	.ENDIF

	movzx eax, currentWordLetter

	mov esi, offset wordsXPos
	add esi, eax

	PUSHAD
	call randomXLoc
	POPAD

	mov cl, xPos ;TESTING HERE
	mov byte ptr [esi], cl

	mov esi, offset wordsYPos
	add esi, eax

	mov byte ptr [esi], 0

	noWords:

	ret

newWordGen ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

oneWordCheck PROC

		mov ebx, DWORD ptr [edi]
		.IF ebx != 1
			PUSHAD
			mov esi, offset wordsXPos
			add esi, eax
			mov bl, byte ptr [esi]
			mov xPos, bl

			mov esi, offset wordsYPos
			add esi, eax
			mov bl, byte ptr [esi]
			mov yPos, bl

			mov edx, eax
			mov eax, (black * 16) + black
			call SetTextColor
			mov eax, edx

			call storePos
			mov edx, dword ptr [edi]
			call writestring

			inc byte ptr [esi]
			inc yPos

			mov edx, eax
			mov eax, (black * 16) + white
			call SetTextColor

			mov al, usedScreenSizeY
			sub al, 9
			.IF al == yPos 
				dec liveCount
				.IF typingWordAddy != 1
					mov esi, typingWordY
					mov ah, byte ptr [esi]
						.IF al == ah
							dec liveCount ;PUNISH PLAYER MORE FOR LETTING CURRENT WORD TYPE GO AWAY

							push ebx
							push eax
							mov ebx, typingWordPointer
							mov al, byte ptr [ebx]

							mov typingWord, 1
							mov eax, typingWordAddy
							mov DWORD ptr [eax], 1
							mov correctBit, 0
							mov typingWordAddy, 1

							pop eax
							pop ebx

							call updateHUD

						jmp lostLife
					.ENDIF
				.ENDIF

				mov DWORD ptr [edi], 1

				call updateHUD

				jmp lostLife
			.ENDIF

			call storePos
			mov eax, edx
			mov edx, dword ptr [edi]
			call writestring
			
			lostLife:
			POPAD
		.ENDIF

		add edi, 4
		inc eax

	ret
oneWordCheck ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

fallingWord PROC

	mov ecx, LENGTHOF lettersCurrentlyUsed
	mov eax, 0
	mov edi, offset lettersCurrentlyUsed

	;call clrscr
	allWords:
		call oneWordCheck
	Loop allWords

		
	.IF typingWordAddy != 1
		call typingColor
		mov eax, (black * 16) + white
		call SetTextColor
	.ENDIF

	push edx
	mov dl, usedScreenSizeX
	mov dh, usedScreenSizeY
	dec dl
	dec dh
	call gotoXY
	pop edx
	
	ret

fallingWord ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

typingColor PROC
	PUSHAD
	mov ebx, 0
	mov bl, correctBit
	
	mov esi, typingWord

	mov eax, typingWordX
	mov dl, byte ptr [eax]
	mov eax, typingWordY
	mov dh, byte ptr [eax]
	call gotoxy

	mov ecx, 0
	mov cl,  typingWordSize

	characterPrint:
		shl bl, 1
		jc greenChar

		mov eax, white + (Black*16)
		call SetTextColor
		jmp printingStep

		greenChar:
		mov eax, green + (Black*16)
		call SetTextColor
		jmp printingStep


		printingStep:
		mov al, byte ptr [esi]
		inc esi
		call writeChar

	Loop characterPrint


	POPAD

	ret 
typingColor ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

HUDCreate Proc
	PUSHAD

	mov ecx, 0
	mov eax, 0
	mov cl, usedScreenSizeX

	mov al, usedScreenSizeY
	sub al, 9

	call saveCurrentPos

	mov xPos, 0
	mov yPos, al

	call storePos

	mov edx, offset dashPrompt

	dashDivider:

		call writeString

	loop dashDivider

	call updateHUD

	POPAD

	ret
HUDCreate ENDP

updateHud PROC
	PUSHAD

	.IF liveCount > 10

		mov gameOver, 1
		jmp GameOverSkip
	.ENDIF

	.IF liveCount == 0

		mov gameOver, 1
		jmp GameOverSkip
	.ENDIF

	.IF pointCount == 0FFFFh
		mov pointCount, 0
	.ENDIF

	mov al, usedScreenSizeY
	sub al, 5

	mov xPos, 5
	
	mov yPos, al
	call storePos

	mov edx, offset livesPrompt
	call writeString

	mov eax, red
	call setTextColor

	mov edx, offset heartPrompt

	mov cl, liveCount
	heartPrint:
		call writeString
	loop heartPrint

	mov eax, white
	call setTextColor

	mov edx, offset blankSpacePrompt
	call writeString

	mov al, usedScreenSizeX
	sub al, 30
	mov xPos, al
	call storePos

	mov edx, offset scorePrompt
	call writeString

	call restoreSavePos

	mov eax, 0

	mov ax, pointCount
	call writeInt
	
	mov edx, offset blankSpacePrompt
	call writeString

	GameOverSkip:
	POPAD

	ret

updateHUD ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

gettingWord PROC
	
	and eax, 0ffh
	or al, 32

	sub al, 97d

	.IF typingWord == 1
		
		.IF al > 7
			dec pointCount
			call updateHud
			ret
		.ENDIF

		mov esi, offset lettersCurrentlyUsed
		mov edi, offset aWords
	
		mov ecx, 0
		mov cl, al
		
		.If ecx == 0
			jmp pastLoop
		.ENDIF
		
		checkIfUsed:
			add esi, 4
			add edi, 30 ;SIZE OF EACH LIST
		loop checkIfUsed
		
		pastLoop:

		
		mov ebx, DWORD ptr [esi]

		.IF ebx != 1
			mov correctBit, 80h
			mov typingWordX, offset wordsXPos
			add typingWordX, eax

			mov typingWordY, offset wordsYPos
			add typingWordY, eax

			mov typingWordAddy, esi
			mov typingWord, ebx ;STORING THE ACTUAL WORD NOT ADDRESS <I LIED IT STORES THE ADDRESS>
			
			mov typingWordPointer, ebx
			inc typingWordPointer
			push ebx
			push eax
			inc ebx
			mov al, byte ptr [ebx]
			mov typingWordLetter, al
			pop eax
			pop ebx

			;mov ebx, esi
			sub ebx, edi

			mov ecx, 4
			cmp ebx, 0
			jz pastSizeLoop
			
			sizeLoop:
				sub ebx, ecx
				cmp ebx, 0
				pushf
				inc ecx
				popf
			jnz sizeLoop

			pastSizeLoop:
			mov typingWordSize, cl
		.ENDIF


		ret
	.ENDIF

	add al, 97d

	.IF al == typingWordLetter
		sar correctBit, 1

		inc typingWordPointer ;WHEN DONE THIS SHOULD POINT AT '0' REMEMBER THAT
		push ebx
		push eax
		mov ebx, typingWordPointer
		mov al, byte ptr [ebx]
		
		.IF al == 0
			;mov eax, typingWord
			;mov DWORD ptr [eax], 1

			PUSHAD
			mov eax, 0
			mov al, typingWordSize
			shl eax, 1

			push eax
			mov ah, 0
			add pointCount, ax
			call updateHUD
			pop eax

			mov esi, typingWordX
			mov bl, byte ptr [esi]
			mov xPos, bl

			mov esi, typingWordY
			mov bl, byte ptr [esi]
			mov yPos, bl

			call storePos
			mov edx, offset blankSpacePrompt
			call writestring

			POPAD

			mov typingWord, 1
			mov eax, typingWordAddy
			mov DWORD ptr [eax], 1
			mov correctBit, 0
			mov typingWordAddy, 1

			pop eax
			pop ebx
			ret
		.ENDIF


		mov typingWordLetter, al
		pop eax
		pop ebx
		;call dumpregs
	.ENDIF

		dec pointCount
		call updateHud

	ret
gettingWord ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

randomXLoc PROC
	call randomize
	mov eax, 0
	mov al, usedScreenSizeX
	sub al, currentWordSize
	call RandomRange

	mov xPos, al
	mov yPos, 0

	ret
randomXLoc ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

randomString PROC
	call randomize
	
	mov eax, LENGTHOF lettersCurrentlyUsed
	call RandomRange
	mov randomNum, al

	mov edi, OFFSET lettersCurrentlyUsed
	shl eax, 2
	add edi, eax 
	shr eax, 2

	PUSH EDX
	PUSH EBX
	mov ecx, LENGTHOF lettersCurrentlyUsed
	mov edx, SIZEOF lettersCurrentlyUsed
	
	findAvailable:
	mov ebx, edi
	sub ebx, OFFSET lettersCurrentlyUsed

	.IF ebx > edx
		mov al, 0
		mov edi, OFFSET lettersCurrentlyUsed
	.ENDIF

	mov ebx, DWORD ptr [edi]

	.IF ebx != 1
		add edi, 4
		add al, 1
		loop findAvailable
		mov eax, 10
	.ENDIF

	POP EBX
	POP EDX

	mov currentWordLetter, al
	.IF al == 0
		mov esi, OFFSET aWords
	.ELSEIF al == 1
		mov esi, OFFSET bWords
	.ELSEIF al == 2
		mov esi, OFFSET cWords
	.ELSEIF al == 3
		mov esi, OFFSET dWords
	.ELSEIF al == 4
		mov esi, OFFSET eWords
	.ELSEIF al == 5
		mov esi, OFFSET fWords
	.ELSEIF al == 6
		mov esi, OFFSET gWords
	.ELSEIF al == 10
		;mov edx, offset allWordsUsedprompt
		;call writeString
		jmp screenSizeSelected
		
	.ENDIF

	call randomize
	mov eax, wordsPerList
	call RandomRange
	mov randomNum, al
	movzx ecx, al
	
	mov currentWordSize, lengthOfSmallestWord
	add currentWordSize, al

	.IF ecx == 0
		jmp skipLoop
	.ENDIF
		
	findWord:
		add esi, lengthOfSmallestWord
		add esi, ecx	

	LOOP findWord
	
	skipLoop:

	mov DWORD PTR [edi], esi

	COMMENT $
	mov edx, esi
	call writeString
	call writeInt
	$
	
	screenSizeSelected:

	ret


 randomString ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

difficultyPointer PROC
;I NEED TO BE ABLE TO SAVE MY X AND Y POS
call saveCurrentPos

mov ecx, 1

;call clrscr
;call DumpRegs

selectionArrow:
	call restoreSavePos
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString
	
	add xPos, 9
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString

	sub xPos, 10
	add yPos, 2
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString

	add xPos, 11
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString

	sub xPos, 10
	add yPos, 2
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString

	add xPos, 9
	call storePos
	mov edx, OFFSET blankArrowPrompt
	call WriteString

	.IF ecx <= 1
		mov ecx, 1

		call restoreSavePos
		call storePos
		mov edx, OFFSET rightArrowPrompt
		call WriteString
	
		add xPos, 9
		call storePos
		mov edx, OFFSET leftArrowPrompt
		call WriteString

	.ELSEIF ecx == 2
		
		call restoreSavePos
		
		sub xPos, 1
		add yPos, 2

		call storePos
		mov edx, OFFSET rightArrowPrompt
		call WriteString
	
		add xPos, 11
		call storePos
		mov edx, OFFSET leftArrowPrompt
		call WriteString

	.ELSEIF ecx >= 3
		mov ecx, 3

		call restoreSavePos
		add yPos, 4

		call storePos
		mov edx, OFFSET rightArrowPrompt
		call WriteString
	
		add xPos, 9
		call storePos
		mov edx, OFFSET leftArrowPrompt
		call WriteString

	.ENDIF

	mov dl, usedScreenSizeX
	mov dh, usedScreenSizeY
	dec dl
	dec dh
	call gotoXY

LookForKey:
    mov  eax, 100        
    call Delay        

    call ReadKey     
jz   LookForKey
call anotherGame ;-------------------------------------------

;call clrscr
;call DumpRegs

cmp dx, VK_UP
je up_level


cmp dx, VK_DOWN
je down_level

cmp dx, VK_RETURN
mov gameDifficulty, cl
je levelSelected

jmp LookForKey

up_level:
	dec ecx
	jmp selectionArrow

down_level:
	inc ecx
	jmp selectionArrow


levelSelected:

	mov gameDifficulty, cl

ret

difficultyPointer ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

saveCurrentPos Proc

mov dl, xPos
mov dh, yPos

mov saveXPos, dl
mov saveYPos, dh

ret

saveCurrentPos ENDP


restoreSavePos Proc

mov dl, saveXPos
mov dh, saveYPos

mov xPos, dl
mov yPos, dh

ret

restoreSavePos ENDP

;--------------------------------------------------------------------------------------------------------------------------------------------------------

useSmallScreen Proc
	mov usedScreenSizeX, smallScreenSizeX
	mov usedScreenSizeY, smallScreenSizeY
	
	ret
useSmallScreen ENDP


useBigScreen Proc
	mov usedScreenSizeX, bigScreenSizeX
	mov usedScreenSizeY, bigScreenSizeY
	
	ret
useBigScreen ENDP

END main