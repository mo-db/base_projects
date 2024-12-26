	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 1
	.file	0 "/Users/moritz/Repos/base_projects/p_pg1" "ex9_1.c" md5 0xcd2d62667feff6410728d98e160f1946
	.globl	_test_asm                       ; -- Begin function test_asm
	.p2align	2
_test_asm:                              ; @test_asm
Lfunc_begin0:
	.loc	0 8 0                           ; ex9_1.c:8:0
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
Ltmp1:
	.loc	0 9 6 prologue_end              ; ex9_1.c:9:6
	mov	w8, #5                          ; =0x5
	str	w8, [sp, #12]
	.loc	0 10 9                          ; ex9_1.c:10:9
	ldr	w8, [sp, #12]
	add	w8, w8, #10
	str	w8, [sp, #12]
	.loc	0 11 9                          ; ex9_1.c:11:9
	ldr	w0, [sp, #12]
	.loc	0 11 2 epilogue_begin is_stmt 0 ; ex9_1.c:11:2
	add	sp, sp, #16
	ret
Ltmp2:
Lfunc_end0:
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
Lfunc_begin1:
	.loc	0 15 0 is_stmt 1                ; ex9_1.c:15:0
	.cfi_startproc
; %bb.0:
	stp	x28, x27, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	sub	sp, sp, #1056
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-24]
	str	wzr, [sp, #44]
	str	w0, [sp, #40]
	str	x1, [sp, #32]
Ltmp3:
	.loc	0 18 6 prologue_end             ; ex9_1.c:18:6
	ldr	w8, [sp, #40]
	.loc	0 18 11 is_stmt 0               ; ex9_1.c:18:11
	subs	w8, w8, #1
	cset	w8, le
Ltmp4:
	.loc	0 18 6                          ; ex9_1.c:18:6
	tbnz	w8, #0, LBB1_9
	b	LBB1_1
LBB1_1:
Ltmp5:
	.loc	0 19 7 is_stmt 1                ; ex9_1.c:19:7
	str	wzr, [sp, #28]
Ltmp6:
	.loc	0 21 12                         ; ex9_1.c:21:12
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #20]
	.loc	0 21 8 is_stmt 0                ; ex9_1.c:21:8
	b	LBB1_2
LBB1_2:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB1_4 Depth 2
Ltmp7:
	.loc	0 21 19                         ; ex9_1.c:21:19
	ldr	w8, [sp, #20]
	.loc	0 21 23                         ; ex9_1.c:21:23
	ldr	w9, [sp, #40]
	.loc	0 21 21                         ; ex9_1.c:21:21
	subs	w8, w8, w9
	cset	w8, ge
Ltmp8:
	.loc	0 21 3                          ; ex9_1.c:21:3
	tbnz	w8, #0, LBB1_8
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_2 Depth=1
Ltmp9:
	.loc	0 22 4 is_stmt 1                ; ex9_1.c:22:4
	b	LBB1_4
LBB1_4:                                 ;   Parent Loop BB1_2 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	.loc	0 22 18 is_stmt 0               ; ex9_1.c:22:18
	ldr	x8, [sp, #32]
	.loc	0 22 23                         ; ex9_1.c:22:23
	ldrsw	x9, [sp, #20]
	.loc	0 22 18                         ; ex9_1.c:22:18
	add	x10, x8, x9, lsl #3
	.loc	0 22 25                         ; ex9_1.c:22:25
	ldr	x8, [x10]
	add	x9, x8, #1
	str	x9, [x10]
	.loc	0 22 16                         ; ex9_1.c:22:16
	ldrsb	w8, [x8]
	.loc	0 22 14                         ; ex9_1.c:22:14
	str	w8, [sp, #24]
	.loc	0 22 30                         ; ex9_1.c:22:30
	subs	w8, w8, #0
	cset	w8, eq
	.loc	0 22 4                          ; ex9_1.c:22:4
	tbnz	w8, #0, LBB1_6
	b	LBB1_5
LBB1_5:                                 ;   in Loop: Header=BB1_4 Depth=2
Ltmp10:
	.loc	0 23 44 is_stmt 1               ; ex9_1.c:23:44
	ldr	w8, [sp, #24]
	.loc	0 23 38 is_stmt 0               ; ex9_1.c:23:38
	ldrsw	x10, [sp, #28]
Ltmp11:
	.loc	0 22 4 is_stmt 1                ; ex9_1.c:22:4
	mov	x9, x10
Ltmp12:
	.loc	0 23 38                         ; ex9_1.c:23:38
	add	w9, w9, #1
	str	w9, [sp, #28]
	.loc	0 23 5 is_stmt 0                ; ex9_1.c:23:5
	add	x9, sp, #48
	.loc	0 23 42                         ; ex9_1.c:23:42
	strb	w8, [x9, x10]
Ltmp13:
	.loc	0 22 4 is_stmt 1                ; ex9_1.c:22:4
	b	LBB1_4
LBB1_6:                                 ;   in Loop: Header=BB1_2 Depth=1
	.loc	0 25 37                         ; ex9_1.c:25:37
	ldrsw	x9, [sp, #28]
	.loc	0 22 4                          ; ex9_1.c:22:4
	mov	x8, x9
	.loc	0 25 37                         ; ex9_1.c:25:37
	add	w8, w8, #1
	str	w8, [sp, #28]
	.loc	0 25 4 is_stmt 0                ; ex9_1.c:25:4
	add	x8, sp, #48
	add	x9, x8, x9
	.loc	0 25 41                         ; ex9_1.c:25:41
	mov	w8, #32                         ; =0x20
	strb	w8, [x9]
	.loc	0 26 3 is_stmt 1                ; ex9_1.c:26:3
	b	LBB1_7
Ltmp14:
LBB1_7:                                 ;   in Loop: Header=BB1_2 Depth=1
	.loc	0 21 30                         ; ex9_1.c:21:30
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	.loc	0 21 3 is_stmt 0                ; ex9_1.c:21:3
	b	LBB1_2
Ltmp15:
LBB1_8:
	.loc	0 27 16 is_stmt 1               ; ex9_1.c:27:16
	ldr	w8, [sp, #28]
	subs	w9, w8, #1
	str	w9, [sp, #28]
	.loc	0 27 3 is_stmt 0                ; ex9_1.c:27:3
	add	x8, sp, #48
	add	x8, x8, w9, sxtw
	.loc	0 27 40                         ; ex9_1.c:27:40
	strb	wzr, [x8]
	.loc	0 28 2 is_stmt 1                ; ex9_1.c:28:2
	b	LBB1_9
Ltmp16:
LBB1_9:
	.loc	0 29 2                          ; ex9_1.c:29:2
	mov	x9, sp
	add	x8, sp, #48
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	.loc	0 30 25                         ; ex9_1.c:30:25
	bl	_test_asm
	.loc	0 30 2 is_stmt 0                ; ex9_1.c:30:2
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x0
	str	x8, [x9]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	.loc	0 41 2 is_stmt 1                ; ex9_1.c:41:2
	ldur	x9, [x29, #-24]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB1_11
	b	LBB1_10
LBB1_10:
	bl	___stack_chk_fail
LBB1_11:
	mov	w0, #0                          ; =0x0
	.loc	0 41 2 epilogue_begin is_stmt 0 ; ex9_1.c:41:2
	add	sp, sp, #1056
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #32             ; 16-byte Folded Reload
	ret
Ltmp17:
Lfunc_end1:
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Moin, %s.\n"

l_.str.1:                               ; @.str.1
	.asciz	"Number: %d\n"

	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                               ; Abbreviation Code
	.byte	17                              ; DW_TAG_compile_unit
	.byte	1                               ; DW_CHILDREN_yes
	.byte	37                              ; DW_AT_producer
	.byte	37                              ; DW_FORM_strx1
	.byte	19                              ; DW_AT_language
	.byte	5                               ; DW_FORM_data2
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.ascii	"\202|"                         ; DW_AT_LLVM_sysroot
	.byte	37                              ; DW_FORM_strx1
	.ascii	"\357\177"                      ; DW_AT_APPLE_sdk
	.byte	37                              ; DW_FORM_strx1
	.byte	114                             ; DW_AT_str_offsets_base
	.byte	23                              ; DW_FORM_sec_offset
	.byte	16                              ; DW_AT_stmt_list
	.byte	23                              ; DW_FORM_sec_offset
	.byte	27                              ; DW_AT_comp_dir
	.byte	37                              ; DW_FORM_strx1
	.byte	17                              ; DW_AT_low_pc
	.byte	27                              ; DW_FORM_addrx
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.byte	115                             ; DW_AT_addr_base
	.byte	23                              ; DW_FORM_sec_offset
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	2                               ; Abbreviation Code
	.byte	52                              ; DW_TAG_variable
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	2                               ; DW_AT_location
	.byte	24                              ; DW_FORM_exprloc
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	3                               ; Abbreviation Code
	.byte	1                               ; DW_TAG_array_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	4                               ; Abbreviation Code
	.byte	33                              ; DW_TAG_subrange_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	55                              ; DW_AT_count
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	5                               ; Abbreviation Code
	.byte	36                              ; DW_TAG_base_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	62                              ; DW_AT_encoding
	.byte	11                              ; DW_FORM_data1
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	6                               ; Abbreviation Code
	.byte	36                              ; DW_TAG_base_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	62                              ; DW_AT_encoding
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	7                               ; Abbreviation Code
	.byte	46                              ; DW_TAG_subprogram
	.byte	1                               ; DW_CHILDREN_yes
	.byte	17                              ; DW_AT_low_pc
	.byte	27                              ; DW_FORM_addrx
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.ascii	"\347\177"                      ; DW_AT_APPLE_omit_frame_ptr
	.byte	25                              ; DW_FORM_flag_present
	.byte	64                              ; DW_AT_frame_base
	.byte	24                              ; DW_FORM_exprloc
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	63                              ; DW_AT_external
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	8                               ; Abbreviation Code
	.byte	52                              ; DW_TAG_variable
	.byte	0                               ; DW_CHILDREN_no
	.byte	2                               ; DW_AT_location
	.byte	24                              ; DW_FORM_exprloc
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	9                               ; Abbreviation Code
	.byte	46                              ; DW_TAG_subprogram
	.byte	1                               ; DW_CHILDREN_yes
	.byte	17                              ; DW_AT_low_pc
	.byte	27                              ; DW_FORM_addrx
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.byte	64                              ; DW_AT_frame_base
	.byte	24                              ; DW_FORM_exprloc
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	39                              ; DW_AT_prototyped
	.byte	25                              ; DW_FORM_flag_present
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	63                              ; DW_AT_external
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	10                              ; Abbreviation Code
	.byte	5                               ; DW_TAG_formal_parameter
	.byte	0                               ; DW_CHILDREN_no
	.byte	2                               ; DW_AT_location
	.byte	24                              ; DW_FORM_exprloc
	.byte	3                               ; DW_AT_name
	.byte	37                              ; DW_FORM_strx1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	11                              ; Abbreviation Code
	.byte	11                              ; DW_TAG_lexical_block
	.byte	1                               ; DW_CHILDREN_yes
	.byte	17                              ; DW_AT_low_pc
	.byte	27                              ; DW_FORM_addrx
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	12                              ; Abbreviation Code
	.byte	15                              ; DW_TAG_pointer_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	13                              ; Abbreviation Code
	.byte	33                              ; DW_TAG_subrange_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	55                              ; DW_AT_count
	.byte	5                               ; DW_FORM_data2
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	0                               ; EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
.set Lset0, Ldebug_info_end0-Ldebug_info_start0 ; Length of Unit
	.long	Lset0
Ldebug_info_start0:
	.short	5                               ; DWARF version number
	.byte	1                               ; DWARF Unit Type
	.byte	8                               ; Address Size (in bytes)
.set Lset1, Lsection_abbrev-Lsection_abbrev ; Offset Into Abbrev. Section
	.long	Lset1
	.byte	1                               ; Abbrev [1] 0xc:0xe4 DW_TAG_compile_unit
	.byte	0                               ; DW_AT_producer
	.short	29                              ; DW_AT_language
	.byte	1                               ; DW_AT_name
	.byte	2                               ; DW_AT_LLVM_sysroot
	.byte	3                               ; DW_AT_APPLE_sdk
.set Lset2, Lstr_offsets_base0-Lsection_str_off ; DW_AT_str_offsets_base
	.long	Lset2
.set Lset3, Lline_table_start0-Lsection_line ; DW_AT_stmt_list
	.long	Lset3
	.byte	4                               ; DW_AT_comp_dir
	.byte	2                               ; DW_AT_low_pc
.set Lset4, Lfunc_end1-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset4
.set Lset5, Laddr_table_base0-Lsection_info0 ; DW_AT_addr_base
	.long	Lset5
	.byte	2                               ; Abbrev [2] 0x25:0xa DW_TAG_variable
	.long	47                              ; DW_AT_type
	.byte	0                               ; DW_AT_decl_file
	.byte	29                              ; DW_AT_decl_line
	.byte	2                               ; DW_AT_location
	.byte	161
	.byte	0
	.byte	3                               ; Abbrev [3] 0x2f:0xc DW_TAG_array_type
	.long	59                              ; DW_AT_type
	.byte	4                               ; Abbrev [4] 0x34:0x6 DW_TAG_subrange_type
	.long	63                              ; DW_AT_type
	.byte	11                              ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	5                               ; Abbrev [5] 0x3b:0x4 DW_TAG_base_type
	.byte	5                               ; DW_AT_name
	.byte	6                               ; DW_AT_encoding
	.byte	1                               ; DW_AT_byte_size
	.byte	6                               ; Abbrev [6] 0x3f:0x4 DW_TAG_base_type
	.byte	6                               ; DW_AT_name
	.byte	8                               ; DW_AT_byte_size
	.byte	7                               ; DW_AT_encoding
	.byte	2                               ; Abbrev [2] 0x43:0xa DW_TAG_variable
	.long	77                              ; DW_AT_type
	.byte	0                               ; DW_AT_decl_file
	.byte	30                              ; DW_AT_decl_line
	.byte	2                               ; DW_AT_location
	.byte	161
	.byte	1
	.byte	3                               ; Abbrev [3] 0x4d:0xc DW_TAG_array_type
	.long	59                              ; DW_AT_type
	.byte	4                               ; Abbrev [4] 0x52:0x6 DW_TAG_subrange_type
	.long	63                              ; DW_AT_type
	.byte	12                              ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	7                               ; Abbrev [7] 0x59:0x1b DW_TAG_subprogram
	.byte	2                               ; DW_AT_low_pc
.set Lset6, Lfunc_end0-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset6
                                        ; DW_AT_APPLE_omit_frame_ptr
	.byte	1                               ; DW_AT_frame_base
	.byte	111
	.byte	7                               ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	7                               ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
                                        ; DW_AT_external
	.byte	8                               ; Abbrev [8] 0x68:0xb DW_TAG_variable
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	12
	.byte	10                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	9                               ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	9                               ; Abbrev [9] 0x74:0x60 DW_TAG_subprogram
	.byte	3                               ; DW_AT_low_pc
.set Lset7, Lfunc_end1-Lfunc_begin1     ; DW_AT_high_pc
	.long	Lset7
	.byte	1                               ; DW_AT_frame_base
	.byte	109
	.byte	9                               ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
                                        ; DW_AT_prototyped
	.long	212                             ; DW_AT_type
                                        ; DW_AT_external
	.byte	10                              ; Abbrev [10] 0x83:0xb DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	40
	.byte	11                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
	.byte	10                              ; Abbrev [10] 0x8e:0xb DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	32
	.byte	12                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
	.long	216                             ; DW_AT_type
	.byte	8                               ; Abbrev [8] 0x99:0xb DW_TAG_variable
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	48
	.byte	13                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	16                              ; DW_AT_decl_line
	.long	226                             ; DW_AT_type
	.byte	11                              ; Abbrev [11] 0xa4:0x2f DW_TAG_lexical_block
	.byte	4                               ; DW_AT_low_pc
.set Lset8, Ltmp16-Ltmp5                ; DW_AT_high_pc
	.long	Lset8
	.byte	8                               ; Abbrev [8] 0xaa:0xb DW_TAG_variable
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	28
	.byte	14                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	19                              ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
	.byte	8                               ; Abbrev [8] 0xb5:0xb DW_TAG_variable
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	24
	.byte	15                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	20                              ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
	.byte	11                              ; Abbrev [11] 0xc0:0x12 DW_TAG_lexical_block
	.byte	5                               ; DW_AT_low_pc
.set Lset9, Ltmp15-Ltmp6                ; DW_AT_high_pc
	.long	Lset9
	.byte	8                               ; Abbrev [8] 0xc6:0xb DW_TAG_variable
	.byte	2                               ; DW_AT_location
	.byte	143
	.byte	20
	.byte	16                              ; DW_AT_name
	.byte	0                               ; DW_AT_decl_file
	.byte	21                              ; DW_AT_decl_line
	.long	212                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	0                               ; End Of Children Mark
	.byte	0                               ; End Of Children Mark
	.byte	5                               ; Abbrev [5] 0xd4:0x4 DW_TAG_base_type
	.byte	8                               ; DW_AT_name
	.byte	5                               ; DW_AT_encoding
	.byte	4                               ; DW_AT_byte_size
	.byte	12                              ; Abbrev [12] 0xd8:0x5 DW_TAG_pointer_type
	.long	221                             ; DW_AT_type
	.byte	12                              ; Abbrev [12] 0xdd:0x5 DW_TAG_pointer_type
	.long	59                              ; DW_AT_type
	.byte	3                               ; Abbrev [3] 0xe2:0xd DW_TAG_array_type
	.long	59                              ; DW_AT_type
	.byte	13                              ; Abbrev [13] 0xe7:0x7 DW_TAG_subrange_type
	.long	63                              ; DW_AT_type
	.short	1000                            ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	0                               ; End Of Children Mark
Ldebug_info_end0:
	.section	__DWARF,__debug_str_offs,regular,debug
Lsection_str_off:
	.long	72                              ; Length of String Offsets Set
	.short	5
	.short	0
Lstr_offsets_base0:
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple clang version 16.0.0 (clang-1600.0.26.4)" ; string offset=0
	.asciz	"ex9_1.c"                       ; string offset=47
	.asciz	"/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk" ; string offset=55
	.asciz	"MacOSX.sdk"                    ; string offset=107
	.asciz	"/Users/moritz/Repos/base_projects/p_pg1" ; string offset=118
	.asciz	"char"                          ; string offset=158
	.asciz	"__ARRAY_SIZE_TYPE__"           ; string offset=163
	.asciz	"test_asm"                      ; string offset=183
	.asciz	"main"                          ; string offset=192
	.asciz	"int"                           ; string offset=197
	.asciz	"number"                        ; string offset=201
	.asciz	"argc"                          ; string offset=208
	.asciz	"argv"                          ; string offset=213
	.asciz	"input_stream"                  ; string offset=218
	.asciz	"input_stream_counter"          ; string offset=231
	.asciz	"c"                             ; string offset=252
	.asciz	"i"                             ; string offset=254
	.section	__DWARF,__debug_str_offs,regular,debug
	.long	0
	.long	47
	.long	55
	.long	107
	.long	118
	.long	158
	.long	163
	.long	183
	.long	197
	.long	192
	.long	201
	.long	208
	.long	213
	.long	218
	.long	231
	.long	252
	.long	254
	.section	__DWARF,__debug_addr,regular,debug
Lsection_info0:
.set Lset10, Ldebug_addr_end0-Ldebug_addr_start0 ; Length of contribution
	.long	Lset10
Ldebug_addr_start0:
	.short	5                               ; DWARF version number
	.byte	8                               ; Address size
	.byte	0                               ; Segment selector size
Laddr_table_base0:
	.quad	l_.str
	.quad	l_.str.1
	.quad	Lfunc_begin0
	.quad	Lfunc_begin1
	.quad	Ltmp5
	.quad	Ltmp6
Ldebug_addr_end0:
	.section	__DWARF,__debug_names,regular,debug
Ldebug_names_begin:
.set Lset11, Lnames_end0-Lnames_start0  ; Header: unit length
	.long	Lset11
Lnames_start0:
	.short	5                               ; Header: version
	.short	0                               ; Header: padding
	.long	1                               ; Header: compilation unit count
	.long	0                               ; Header: local type unit count
	.long	0                               ; Header: foreign type unit count
	.long	5                               ; Header: bucket count
	.long	5                               ; Header: name count
.set Lset12, Lnames_abbrev_end0-Lnames_abbrev_start0 ; Header: abbreviation table size
	.long	Lset12
	.long	8                               ; Header: augmentation string size
	.ascii	"LLVM0700"                      ; Header: augmentation string
.set Lset13, Lcu_begin0-Lsection_info   ; Compilation unit 0
	.long	Lset13
	.long	0                               ; Bucket 0
	.long	1                               ; Bucket 1
	.long	0                               ; Bucket 2
	.long	2                               ; Bucket 3
	.long	5                               ; Bucket 4
	.long	2090499946                      ; Hash in Bucket 1
	.long	193495088                       ; Hash in Bucket 3
	.long	217009403                       ; Hash in Bucket 3
	.long	-51652923                       ; Hash in Bucket 3
	.long	2090147939                      ; Hash in Bucket 4
	.long	192                             ; String in Bucket 1: main
	.long	197                             ; String in Bucket 3: int
	.long	163                             ; String in Bucket 3: __ARRAY_SIZE_TYPE__
	.long	183                             ; String in Bucket 3: test_asm
	.long	158                             ; String in Bucket 4: char
.set Lset14, Lnames3-Lnames_entries0    ; Offset in Bucket 1
	.long	Lset14
.set Lset15, Lnames4-Lnames_entries0    ; Offset in Bucket 3
	.long	Lset15
.set Lset16, Lnames1-Lnames_entries0    ; Offset in Bucket 3
	.long	Lset16
.set Lset17, Lnames2-Lnames_entries0    ; Offset in Bucket 3
	.long	Lset17
.set Lset18, Lnames0-Lnames_entries0    ; Offset in Bucket 4
	.long	Lset18
Lnames_abbrev_start0:
	.ascii	"\230."                         ; Abbrev code
	.byte	46                              ; DW_TAG_subprogram
	.byte	3                               ; DW_IDX_die_offset
	.byte	19                              ; DW_FORM_ref4
	.byte	4                               ; DW_IDX_parent
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; End of abbrev
	.byte	0                               ; End of abbrev
	.ascii	"\230$"                         ; Abbrev code
	.byte	36                              ; DW_TAG_base_type
	.byte	3                               ; DW_IDX_die_offset
	.byte	19                              ; DW_FORM_ref4
	.byte	4                               ; DW_IDX_parent
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; End of abbrev
	.byte	0                               ; End of abbrev
	.byte	0                               ; End of abbrev list
Lnames_abbrev_end0:
Lnames_entries0:
Lnames3:
L0:
	.ascii	"\230."                         ; Abbreviation code
	.long	116                             ; DW_IDX_die_offset
	.byte	0                               ; DW_IDX_parent
                                        ; End of list: main
Lnames4:
L3:
	.ascii	"\230$"                         ; Abbreviation code
	.long	212                             ; DW_IDX_die_offset
	.byte	0                               ; DW_IDX_parent
                                        ; End of list: int
Lnames1:
L1:
	.ascii	"\230$"                         ; Abbreviation code
	.long	63                              ; DW_IDX_die_offset
	.byte	0                               ; DW_IDX_parent
                                        ; End of list: __ARRAY_SIZE_TYPE__
Lnames2:
L4:
	.ascii	"\230."                         ; Abbreviation code
	.long	89                              ; DW_IDX_die_offset
	.byte	0                               ; DW_IDX_parent
                                        ; End of list: test_asm
Lnames0:
L2:
	.ascii	"\230$"                         ; Abbreviation code
	.long	59                              ; DW_IDX_die_offset
	.byte	0                               ; DW_IDX_parent
                                        ; End of list: char
	.p2align	2, 0x0
Lnames_end0:
.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
