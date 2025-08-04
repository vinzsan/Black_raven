	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Error create window"
	.text
	.p2align 4
	.globl	create_win
	.type	create_win, @function
create_win:
.LFB6454:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	%edx, %r8d
	movl	%ecx, %r9d
	movl	$805240832, %edx
	movl	%esi, %ecx
	movl	$805240832, %esi
	call	SDL_CreateWindow@PLT
	testq	%rax, %rax
	je	.L5
.L1:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L5:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	movq	%rax, 8(%rsp)
	call	perror@PLT
	movq	8(%rsp), %rax
	jmp	.L1
	.cfi_endproc
.LFE6454:
	.size	create_win, .-create_win
	.p2align 4
	.globl	rendering
	.type	rendering, @function
rendering:
.LFB6455:
	.cfi_startproc
	jmp	SDL_CreateRenderer@PLT
	.cfi_endproc
.LFE6455:
	.size	rendering, .-rendering
	.p2align 4
	.globl	write_data
	.type	write_data, @function
write_data:
.LFB6457:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	imulq	%rdx, %rsi
	movq	%rcx, %rbp
	movl	$4095, %edx
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %r8
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rcx), %rax
	leaq	(%rax,%rsi), %rcx
	subq	%rax, %rdx
	movq	%r8, %rsi
	cmpq	$4094, %rcx
	cmova	%rdx, %rbx
	addq	0(%rbp), %rax
	movq	%rax, %rdi
	movq	%rbx, %rdx
	call	memcpy@PLT
	movq	8(%rbp), %rax
	movq	0(%rbp), %rdx
	addq	%rbx, %rax
	movq	%rax, 8(%rbp)
	movb	$0, (%rdx,%rax)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE6457:
	.size	write_data, .-write_data
	.section	.rodata.str1.1
.LC1:
	.string	"Error create surface"
	.text
	.p2align 4
	.globl	create_texture_surf
	.type	create_texture_surf, @function
create_texture_surf:
.LFB6456:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	movq	%rsi, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	IMG_Load@PLT
	testq	%rax, %rax
	je	.L14
	movq	%rbp, %rdi
	movq	%rax, %rbx
	movq	%rax, %rsi
	call	SDL_CreateTextureFromSurface@PLT
	movq	%rbx, %rdi
	movq	%rax, %rbp
	call	SDL_FreeSurface@PLT
.L10:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	leaq	.LC1(%rip), %rdi
	xorl	%ebp, %ebp
	call	perror@PLT
	jmp	.L10
	.cfi_endproc
.LFE6456:
	.size	create_texture_surf, .-create_texture_surf
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Error tidak dapat memuat resource"
	.section	.rodata.str1.1
.LC3:
	.string	"http://voltraz.xyz"
.LC4:
	.string	"accept : application/json"
.LC5:
	.string	""
.LC6:
	.string	"Error request get method"
.LC7:
	.string	"w"
.LC8:
	.string	"log.json"
.LC9:
	.string	"Error file isnt exist"
	.text
	.p2align 4
	.globl	multithread
	.type	multithread, @function
multithread:
.LFB6458:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	call	curl_easy_init@PLT
	movl	$1, %esi
	movl	$4096, %edi
	movq	%rax, %rbx
	call	calloc@PLT
	movq	$0, 8(%rsp)
	movq	%rax, (%rsp)
	testq	%rax, %rax
	je	.L22
	testq	%rbx, %rbx
	je	.L18
	leaq	.LC3(%rip), %rdx
	movl	$10002, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	call	curl_easy_setopt@PLT
	movl	$10015, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	leaq	.LC4(%rip), %rdx
	call	curl_easy_setopt@PLT
	movl	$10102, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	leaq	.LC5(%rip), %rdx
	call	curl_easy_setopt@PLT
	movl	$20011, %esi
	movq	%rbx, %rdi
	xorl	%eax, %eax
	leaq	write_data(%rip), %rdx
	call	curl_easy_setopt@PLT
	movq	%rbx, %rdi
	movq	%rsp, %rdx
	movl	$10001, %esi
	xorl	%eax, %eax
	call	curl_easy_setopt@PLT
	movq	%rbx, %rdi
	call	curl_easy_perform@PLT
.L19:
	leaq	.LC7(%rip), %rsi
	leaq	.LC8(%rip), %rdi
	call	fopen@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L23
.L20:
	movq	8(%rsp), %rdx
	movq	(%rsp), %rdi
	movq	%rbp, %rcx
	movl	$1, %esi
	call	fwrite@PLT
	movq	%rbx, %rdi
	call	curl_easy_cleanup@PLT
	movq	(%rsp), %rdi
	call	free@PLT
.L17:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
	xorl	%edi, %edi
	call	curl_easy_strerror@PLT
	movq	stderr(%rip), %rdi
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdx
	xorl	%eax, %eax
	call	fprintf@PLT
	jmp	.L19
.L22:
	leaq	.LC2(%rip), %rdi
	call	perror@PLT
	jmp	.L17
.L23:
	leaq	.LC9(%rip), %rdi
	call	perror@PLT
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$4096, %edx
	call	fwrite@PLT
	jmp	.L20
	.cfi_endproc
.LFE6458:
	.size	multithread, .-multithread
	.section	.rodata.str1.1
.LC12:
	.string	"background.jpeg"
.LC13:
	.string	"background2.jpeg"
.LC14:
	.string	"Click 'q' untuk keluar"
.LC15:
	.string	"ESC : Debug mode"
.LC16:
	.string	"Press 'h' to hide text"
.LC17:
	.string	" "
.LC18:
	.string	"Black Raven"
.LC19:
	.string	"1"
.LC20:
	.string	"SDL_RENDER_SCALE_QUALITY"
.LC21:
	.string	"0xProtoNerdFont-Regular.ttf"
.LC22:
	.string	"waifu1.jpeg"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB6459:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$48, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$584, %rsp
	.cfi_def_cfa_offset 640
	call	malloc@PLT
	leaq	create_win(%rip), %rdx
	movl	$32, %edi
	leaq	416(%rsp), %r12
	movq	%rax, %rbx
	leaq	rendering(%rip), %rax
	movq	%rdx, %xmm0
	movq	%rax, %xmm5
	leaq	352(%rsp), %r14
	leaq	384(%rsp), %rbp
	punpcklqdq	%xmm5, %xmm0
	movups	%xmm0, 24(%rbx)
	call	SDL_Init@PLT
	movl	$3, %edi
	call	IMG_Init@PLT
	call	TTF_Init@PLT
	call	curl_easy_init@PLT
	movl	$4129, %ecx
	movl	$600, %edx
	movl	$800, %esi
	leaq	.LC18(%rip), %rdi
	call	create_win
	leaq	.LC19(%rip), %rsi
	leaq	.LC20(%rip), %rdi
	movq	%rax, %r15
	movq	%rax, 16(%rsp)
	call	SDL_SetHint@PLT
	movl	$2, %edx
	movq	%r15, %rdi
	movl	$-1, %esi
	call	SDL_CreateRenderer@PLT
	leaq	.LC14(%rip), %rdx
	movq	%rbx, 24(%rsp)
	movq	%r13, %rbx
	movq	%rax, %r15
	leaq	.LC15(%rip), %rax
	movq	%rdx, %xmm0
	movq	%rax, %xmm6
	leaq	.LC17(%rip), %rax
	leaq	.LC16(%rip), %rdx
	movq	%rax, %xmm7
	leaq	288(%rsp), %rax
	punpcklqdq	%xmm6, %xmm0
	movq	%rax, 112(%rsp)
	leaq	320(%rsp), %rax
	movaps	%xmm0, 416(%rsp)
	movq	%rdx, %xmm0
	movq	%rax, %r13
	movq	%rax, 8(%rsp)
	punpcklqdq	%xmm7, %xmm0
	movaps	%xmm0, 432(%rsp)
.L25:
	movl	$24, %esi
	leaq	.LC21(%rip), %rdi
	call	TTF_OpenFont@PLT
	movq	(%r12,%rbx), %rsi
	xorl	%edx, %edx
	movq	%rax, %rdi
	movq	112(%rsp), %rax
	movq	%rdi, (%rax,%rbx)
	call	TTF_RenderText_Blended@PLT
	movq	%r15, %rdi
	movq	%rax, (%rbx,%r13)
	movq	%rax, %rsi
	movq	16(%rax), %rax
	movq	%rax, (%rbx,%r14)
	call	SDL_CreateTextureFromSurface@PLT
	movl	$1, %esi
	movq	%rax, 0(%rbp,%rbx)
	movq	%rax, %rdi
	addq	$8, %rbx
	call	SDL_SetTextureAlphaMod@PLT
	cmpq	$32, %rbx
	jne	.L25
	leaq	.LC13(%rip), %rax
	xorl	%r13d, %r13d
	leaq	.LC12(%rip), %rdx
	movq	%rbp, 32(%rsp)
	movq	%rax, %xmm5
	movq	%rdx, %xmm0
	leaq	.LC22(%rip), %rax
	movq	%r13, %rbx
	movq	%rax, 208(%rsp)
	punpcklqdq	%xmm5, %xmm0
	leaq	192(%rsp), %rcx
	leaq	256(%rsp), %rax
	movaps	%xmm0, 192(%rsp)
	leaq	224(%rsp), %r12
	movq	%rax, %r13
	movq	%rcx, %rbp
.L26:
	movq	0(%rbp,%rbx), %rdi
	call	IMG_Load@PLT
	movq	%r15, %rdi
	movq	%rax, %rsi
	movq	%rax, 0(%r13,%rbx)
	call	SDL_CreateTextureFromSurface@PLT
	movl	$1, %esi
	movq	%rax, (%r12,%rbx)
	movq	%rax, %rdi
	addq	$8, %rbx
	call	SDL_SetTextureBlendMode@PLT
	cmpq	$24, %rbx
	jne	.L26
	movq	256(%rsp), %rdi
	movq	24(%rsp), %rbx
	movq	32(%rsp), %rbp
	call	SDL_FreeSurface@PLT
	movq	264(%rsp), %rdi
	call	SDL_FreeSurface@PLT
	movq	272(%rsp), %rdi
	call	SDL_FreeSurface@PLT
	movq	8(%rsp), %r13
.L27:
	movq	0(%r13), %rdi
	addq	$8, %r13
	call	SDL_FreeSurface@PLT
	cmpq	%r13, %r14
	jne	.L27
	leaq	156(%rsp), %rdx
	leaq	152(%rsp), %rsi
	movq	%r15, %rdi
	call	SDL_GetRendererOutputSize@PLT
	movq	224(%rsp), %rdx
	movd	156(%rsp), %xmm0
	movl	$1, (%rbx)
	movd	152(%rsp), %xmm6
	movq	.LC23(%rip), %rax
	movl	$1, 4(%rbx)
	movq	180(%rsp), %xmm1
	movq	%rdx, 120(%rsp)
	punpckldq	%xmm6, %xmm0
	movq	232(%rsp), %rdx
	movl	$1, 8(%rbx)
	psubd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	movl	$1, 12(%rbx)
	movq	%rdx, 128(%rsp)
	movq	240(%rsp), %rdx
	movq	%rax, 184(%rsp)
	pcmpgtd	%xmm0, %xmm1
	movl	$255, 16(%rbx)
	movl	(%rbx), %eax
	movq	%rdx, 40(%rsp)
	movq	384(%rsp), %rdx
	psubd	%xmm1, %xmm0
	movq	%rdx, 136(%rsp)
	psrad	$1, %xmm0
	pshufd	$225, %xmm0, %xmm0
	movq	%xmm0, 176(%rsp)
	testl	%eax, %eax
	je	.L73
	movl	352(%rsp), %eax
	movl	$0x00000000, 24(%rsp)
	leaq	448(%rsp), %r14
	movl	$5, 8(%rsp)
	movl	%eax, 56(%rsp)
	movl	356(%rsp), %eax
	movl	%eax, 68(%rsp)
	movl	364(%rsp), %eax
	movl	%eax, 64(%rsp)
	movl	372(%rsp), %eax
	movl	%eax, 60(%rsp)
	movl	380(%rsp), %eax
	movl	%eax, 52(%rsp)
	leaq	164(%rsp), %rax
	movq	%rax, 80(%rsp)
	leaq	160(%rsp), %rax
	movq	%rax, 72(%rsp)
	leaq	172(%rsp), %rax
	movq	%rax, 96(%rsp)
	leaq	168(%rsp), %rax
	movq	%rax, 88(%rsp)
	leaq	176(%rsp), %rax
	movq	%rax, 104(%rsp)
	.p2align 4,,10
	.p2align 3
.L72:
	xorl	%edi, %edi
	call	SDL_GetKeyboardState@PLT
	movq	%rax, %r13
	.p2align 4,,10
	.p2align 3
.L30:
	movq	%r14, %rdi
	call	SDL_PollEvent@PLT
	testl	%eax, %eax
	je	.L83
.L43:
	cmpl	$256, 448(%rsp)
	jne	.L31
	movl	$0, (%rbx)
.L31:
	movl	468(%rsp), %eax
	cmpl	$113, %eax
	je	.L84
	cmpl	$49, %eax
	jne	.L34
	movl	$1, 4(%rbx)
	movq	%r14, %rdi
	call	SDL_PollEvent@PLT
	testl	%eax, %eax
	jne	.L43
.L83:
	movq	80(%rsp), %rdx
	movq	72(%rsp), %rsi
	movl	%eax, 32(%rsp)
	movq	16(%rsp), %rdi
	call	SDL_GetWindowSize@PLT
	cmpb	$0, 81(%r13)
	movl	32(%rsp), %eax
	jne	.L44
	movl	180(%rsp), %edx
.L45:
	cmpb	$0, 79(%r13)
	movl	176(%rsp), %esi
	je	.L46
	movl	8(%rsp), %ecx
	addl	%ecx, %esi
	movl	%esi, 176(%rsp)
.L46:
	cmpb	$0, 80(%r13)
	je	.L47
	movl	8(%rsp), %ecx
	subl	%ecx, %esi
	movl	%esi, 176(%rsp)
.L47:
	cmpb	$0, 44(%r13)
	jne	.L75
	movss	.LC24(%rip), %xmm2
	addss	24(%rsp), %xmm2
	cvttss2sil	%xmm2, %r8d
	movss	%xmm2, 24(%rsp)
.L48:
	cmpb	$0, 23(%r13)
	movl	184(%rsp), %edi
	movl	188(%rsp), %ecx
	je	.L49
	addl	$5, %edi
	addl	$5, %ecx
	movl	%edi, 184(%rsp)
	movl	%ecx, 188(%rsp)
.L49:
	cmpb	$0, 28(%r13)
	je	.L50
	subl	$5, %edi
	subl	$5, %ecx
	movl	%edi, 184(%rsp)
	movl	%ecx, 188(%rsp)
.L50:
	cmpb	$1, 22(%r13)
	sbbl	$-1, 8(%rsp)
	cmpb	$0, 37(%r13)
	je	.L52
	movl	16(%rbx), %r9d
	cmpl	$255, %r9d
	jg	.L52
	movl	16(%rbx), %r9d
	addl	$5, %r9d
	movl	%r9d, 16(%rbx)
.L52:
	cmpb	$0, 38(%r13)
	je	.L53
	movl	16(%rbx), %r9d
	subl	$5, %r9d
	movl	%r9d, 16(%rbx)
.L53:
	testl	%esi, %esi
	jns	.L54
	movl	$0, 176(%rsp)
	xorl	%esi, %esi
.L54:
	movl	160(%rsp), %r10d
	movl	%r10d, %r9d
	subl	%edi, %r9d
	cmpl	%esi, %r9d
	jl	.L55
	addl	%edi, %esi
	movl	%r10d, %eax
	subl	%esi, %eax
.L56:
	movl	164(%rsp), %edi
	xorl	%r9d, %r9d
	movl	%edi, %esi
	subl	%ecx, %esi
	testl	%edx, %edx
	cmovs	%r9d, %edx
	cmpl	%esi, %edx
	cmovg	%esi, %edx
	addl	%r8d, %edx
	addl	%edx, %ecx
	cmpl	%ecx, %edi
	jg	.L57
	movl	$0x00000000, 24(%rsp)
	movl	%esi, %edx
.L57:
	movl	%edx, 180(%rsp)
	movl	16(%rbx), %edx
	cmpl	$255, %edx
	jle	.L58
	movl	$255, 16(%rbx)
.L58:
	movl	16(%rbx), %edx
	testl	%edx, %edx
	jns	.L59
	movl	$0, 16(%rbx)
.L59:
	cmpl	$100, %eax
	jg	.L60
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	divss	.LC25(%rip), %xmm0
	mulss	.LC26(%rip), %xmm0
	cvttss2sil	%xmm0, %eax
	movl	%eax, 16(%rbx)
.L61:
	movq	%r15, %rdi
	call	SDL_RenderClear@PLT
	xorl	%ecx, %ecx
	movl	$255, %r8d
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r15, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movq	96(%rsp), %rdx
	movq	88(%rsp), %rsi
	movq	16(%rsp), %rdi
	call	SDL_GetWindowSize@PLT
	movl	168(%rsp), %esi
	movl	56(%rsp), %edi
	movl	172(%rsp), %edx
	movl	68(%rsp), %r10d
	movl	%esi, %ecx
	movl	64(%rsp), %r8d
	movl	60(%rsp), %r11d
	movl	%edi, 520(%rsp)
	subl	%edi, %ecx
	movl	%esi, %edi
	movl	%r10d, 524(%rsp)
	movl	%ecx, %eax
	movl	%r8d, 540(%rsp)
	shrl	$31, %eax
	movl	%r11d, 556(%rsp)
	addl	%ecx, %eax
	movl	%edx, %ecx
	subl	%r10d, %ecx
	sarl	%eax
	movl	52(%rsp), %r10d
	movl	%eax, 512(%rsp)
	movl	%ecx, %eax
	shrl	$31, %eax
	movl	%r10d, 572(%rsp)
	addl	%ecx, %eax
	movl	360(%rsp), %ecx
	sarl	%eax
	subl	%ecx, %edi
	movl	%eax, 516(%rsp)
	movl	%edi, %eax
	movl	%ecx, 536(%rsp)
	movl	368(%rsp), %ecx
	shrl	$31, %eax
	addl	%edi, %eax
	movl	%edx, %edi
	movl	%ecx, 552(%rsp)
	subl	%r8d, %edi
	sarl	%eax
	movl	%eax, 528(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	movl	%esi, %edi
	subl	%ecx, %edi
	sarl	%eax
	movl	376(%rsp), %ecx
	movl	%eax, 532(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	movl	%ecx, 568(%rsp)
	addl	%edi, %eax
	movl	%edx, %edi
	subl	%r11d, %edi
	sarl	%eax
	movl	%eax, 544(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	movl	%esi, %edi
	subl	%ecx, %edi
	sarl	%eax
	movl	%eax, 548(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	movl	%edx, %edi
	xorl	%r13d, %r13d
	subl	%r10d, %edi
	sarl	%eax
	movl	%eax, 560(%rsp)
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	movq	%r15, %rdi
	sarl	%eax
	movl	%eax, 564(%rsp)
	call	SDL_RenderSetLogicalSize@PLT
.L62:
	movl	16(%rbx), %esi
	movq	(%r12,%r13), %rdi
	movzbl	%sil, %esi
	call	SDL_SetTextureAlphaMod@PLT
	movl	16(%rbx), %esi
	movq	0(%rbp,%r13), %rdi
	addq	$8, %r13
	movzbl	%sil, %esi
	call	SDL_SetTextureAlphaMod@PLT
	cmpq	$24, %r13
	jne	.L62
	movl	4(%rbx), %eax
	cmpl	$1, %eax
	je	.L63
	cmpl	$2, %eax
	jne	.L65
	movq	128(%rsp), %rsi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
.L65:
	movq	104(%rsp), %rcx
	movq	40(%rsp), %rsi
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	movl	8(%rbx), %eax
	cmpl	$3, %eax
	je	.L66
	jg	.L67
	cmpl	$1, %eax
	je	.L68
	cmpl	$2, %eax
	jne	.L70
	movq	392(%rsp), %rsi
	leaq	528(%rsp), %rcx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	.p2align 4,,10
	.p2align 3
.L70:
	movq	%r15, %rdi
	call	SDL_RenderPresent@PLT
	movl	$16, %edi
	call	SDL_Delay@PLT
	movl	(%rbx), %eax
	testl	%eax, %eax
	jne	.L72
.L73:
	movq	16(%rsp), %rdi
	xorl	%r12d, %r12d
	call	SDL_DestroyWindow@PLT
	movq	%r15, %rdi
	call	SDL_DestroyRenderer@PLT
	movq	120(%rsp), %rdi
	call	SDL_DestroyTexture@PLT
	movq	128(%rsp), %rdi
	call	SDL_DestroyTexture@PLT
	movq	40(%rsp), %rdi
	call	SDL_DestroyTexture@PLT
	movq	112(%rsp), %r13
.L29:
	movq	0(%rbp,%r12), %rdi
	call	SDL_DestroyTexture@PLT
	movq	0(%r13,%r12), %rdi
	addq	$8, %r12
	call	TTF_CloseFont@PLT
	cmpq	$32, %r12
	jne	.L29
	call	TTF_Quit@PLT
	movq	%rbx, %rdi
	call	free@PLT
	addq	$584, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L84:
	.cfi_restore_state
	movl	$0, (%rbx)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L34:
	cmpl	$50, %eax
	jne	.L35
	movl	$2, 4(%rbx)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L35:
	cmpl	$119, %eax
	je	.L85
	cmpl	$101, %eax
	je	.L86
	cmpl	$27, %eax
	jne	.L38
	movl	$0, 4(%rbx)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L85:
	movl	$1, 8(%rbx)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L67:
	cmpl	$4, %eax
	jne	.L70
	movq	408(%rsp), %rsi
	leaq	560(%rsp), %rcx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L86:
	movl	$2, 8(%rbx)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L44:
	movl	8(%rsp), %edx
	addl	180(%rsp), %edx
	movl	%edx, 180(%rsp)
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L60:
	movl	$255, 16(%rbx)
	jmp	.L61
	.p2align 4,,10
	.p2align 3
.L55:
	movl	%r9d, 176(%rsp)
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L75:
	movss	.LC11(%rip), %xmm4
	movl	$-7, %r8d
	movss	%xmm4, 24(%rsp)
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L63:
	movq	120(%rsp), %rsi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	jmp	.L65
	.p2align 4,,10
	.p2align 3
.L66:
	movq	400(%rsp), %rsi
	leaq	544(%rsp), %rcx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L68:
	movq	136(%rsp), %rsi
	leaq	512(%rsp), %rcx
	xorl	%edx, %edx
	movq	%r15, %rdi
	call	SDL_RenderCopy@PLT
	jmp	.L70
.L38:
	cmpl	$114, %eax
	jne	.L39
	movq	.LC23(%rip), %rax
	movq	%rax, 184(%rsp)
	movl	$4, 8(%rbx)
	jmp	.L30
.L39:
	cmpl	$117, %eax
	je	.L74
	cmpl	$52, %eax
	jne	.L41
	movl	$3, 8(%rbx)
	jmp	.L30
.L74:
	movl	$5, 8(%rsp)
	jmp	.L30
.L41:
	cmpl	$104, %eax
	jne	.L30
	movl	$4, 8(%rbx)
	jmp	.L30
	.cfi_endproc
.LFE6459:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC11:
	.long	-1058013184
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC23:
	.long	64
	.long	64
	.section	.rodata.cst4
	.align 4
.LC24:
	.long	1056964608
	.align 4
.LC25:
	.long	1120403456
	.align 4
.LC26:
	.long	1132396544
	.ident	"GCC: (Debian 12.2.0-14+deb12u1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
