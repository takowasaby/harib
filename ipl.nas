; hello-os
; TAB=4

		ORG		0x7c00

; �ȉ��͕W���I��FAT12�t�H�[�}�b�g�t���b�s�[�f�B�X�N�̂��߂̋L�q

		JMP 	entry
		DB		0x90
		DB		"HELLOIPL"		; �u�[�g�Z�N�^�̖��O�����R�ɏ����Ă悢�i8�o�C�g�j
		DW		512				; 1�Z�N�^�̑傫���i512�ɂ��Ȃ���΂����Ȃ��j
		DB		1				; �N���X�^�̑傫���i1�Z�N�^�ɂ��Ȃ���΂����Ȃ��j
		DW		1				; FAT���ǂ�����n�܂邩�i���ʂ�1�Z�N�^�ڂ���ɂ���j
		DB		2				; FAT�̌��i2�ɂ��Ȃ���΂����Ȃ��j
		DW		224				; ���[�g�f�B���N�g���̈�̑傫���i���ʂ�224�G���g���ɂ���j
		DW		2880			; ���̃h���C�u�̑傫���i2880�Z�N�^�ɂ��Ȃ���΂����Ȃ��j
		DB		0xf0			; ���f�B�A�̃^�C�v�i0xf0�ɂ��Ȃ���΂����Ȃ��j
		DW		9				; FAT�̈�̒����i9�Z�N�^�ɂ��Ȃ���΂����Ȃ��j
		DW		18				; 1�g���b�N�ɂ����̃Z�N�^�����邩�i18�ɂ��Ȃ���΂����Ȃ��j
		DW		2				; �w�b�h�̐��i2�ɂ��Ȃ���΂����Ȃ��j
		DD		0				; �p�[�e�B�V�������g���ĂȂ��̂ł����͕K��0
		DD		2880			; ���̃h���C�u�傫����������x����
		DB		0,0,0x29		; �悭�킩��Ȃ����ǂ��̒l�ɂ��Ă����Ƃ����炵��
		DD		0xffffffff		; ���Ԃ�{�����[���V���A���ԍ�
		DB		"HELLO-OS   "	; �f�B�X�N�̖��O�i11�o�C�g�j
		DB		"FAT12   "		; �t�H�[�}�b�g�̖��O�i8�o�C�g�j
		RESB	18				; �Ƃ肠����18�o�C�g�����Ă���

; �v���O�����{��

entry:
		MOV		AX,0
		MOV 	SS,AX
		MOV 	SP,0x7c00
		MOV 	DS,AX
		
; �f�B�X�N��ǂ�

		MOV 	AX,0x0820
		MOV 	ES,AX
		MOV 	CH,0
		MOV 	DH,0
		MOV 	CL,2
readloop:
		MOV 	SI,0
retry:
		MOV 	AH,0x02
		MOV 	AL,1
		MOV 	BX,0
		MOV		DL,0x00
		INT 	0x13
		JNC 	next
		ADD 	SI,1
		CMP 	SI,5
		JAE 	error
		MOV 	AH,0x00
		MOV 	DL,0x00
		INT		0x13
		JMP 	retry
next:
		MOV 	AX,ES
		ADD 	AX,0x0020
		MOV 	ES,AX
		ADD 	CL,1
		CMP 	CL,18
		JBE 	readloop

fin:
		HLT
		JMP 	fin

error:
		MOV 	SI,msg
putloop:
		MOV 	AL,[SI]
		ADD 	SI,1
		CMP 	AL,0
		JE		fin
		MOV 	AH,0x0e
		MOV 	BX,15
		INT 	0x10
		JMP		putloop
msg:
		DB		0x0a, 0x0a		; ���s��2��
		DB		"load error"
		DB		0x0a			; ���s
		DB		0

		RESB	0x7dfe-$			; 0x001fe�܂ł�0x00�Ŗ��߂閽��

		DB		0x55, 0xaa
