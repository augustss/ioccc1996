void
dumpcode(int from, int to)
{
    int n, opc, oopc, lit, ofrom;
    char buf[200], *p;

    while(from < to) {
	ofrom = from;
	sprintf(buf, "%-4d:          ", from);
	p = buf + strlen(buf);
	oopc = opc = code[from++] & 0xff;
	if (opc >= LITLIM) {
	    lit = opc%LITMOD;
	    opc = opc-lit;
	    if (lit == LITMAX) {
		lit = (code[from]&0xff) + (code[from+1]&0xff)*256;
		from += 2;
	    } else if (lit > LITMAX) {
		lit = lit + (code[from++]&0xff)*LITMUL-1;
	    }
	}
	switch(opc) {
	case C_NOT: sprintf(p, "NOT"); break;
	case C_NEG: sprintf(p, "NEG"); break;
	case C_ADD: sprintf(p, "ADD"); break;
	case C_SUB: sprintf(p, "SUB"); break;
	case C_DIV: sprintf(p, "DIV"); break;
	case C_MUL: sprintf(p, "MUL"); break;
	case C_MOD: sprintf(p, "MOD"); break;
	case C_EQ: sprintf(p, "EQ"); break;
	case C_NE: sprintf(p, "NE"); break;
	case C_LT: sprintf(p, "LT"); break;
	case C_GT: sprintf(p, "GT"); break;
	case C_LE: sprintf(p, "LE"); break;
	case C_GE: sprintf(p, "GE"); break;
	case C_AND: sprintf(p, "AND"); break;
	case C_OR: sprintf(p, "OR"); break;
	case C_DUP: sprintf(p, "DUP"); break;
	case C_POSTINC: sprintf(p, "POSTINC"); break;
	case C_POSTDEC: sprintf(p, "POSTDEC"); break;
	case C_ASSIGN: sprintf(p, "ASSIGN"); break;
	case C_ASSIGNPOP: sprintf(p, "ASSIGNPOP"); break;
	case C_RETURN: sprintf(p, "RETURN"); break;
	case C_POP: sprintf(p, "POP"); break;
	case C_DEREF: sprintf(p, "DEREF"); break;
	case C_JUMP: sprintf(p, "JUMP %d", lit); break;
	case C_JFALSE: sprintf(p, "JFALSE %d", lit); break;
	case C_TRUE: sprintf(p, "JTRUE %d", lit); break;
	case C_PUSHAL: sprintf(p, "PUSHAL %d", lit); break;
	case C_PUSHL: sprintf(p, "PUSHL %d", lit); break;
	case C_PUSHAA: sprintf(p, "PUSHAA %d", lit); break;
	case C_PUSHA: sprintf(p, "PUSHA %d", lit); break;
	case C_PUSHAG: sprintf(p, "PUSHAG %d", lit); break;
	case C_PUSHG: sprintf(p, "PUSHG %d", lit); break;
	case C_PUSHC: sprintf(p, "PUSHC %d", lit); break;
	case C_PUSHAC: sprintf(p, "PUSHAC %d", lit); break;
	case C_PUSHS: 
	    sprintf(p, "PUSHS %d \"", lit);
	    n = lit;
	    p += strlen(p);
	    while(n--) *p++ = code[from++] ? code[from-1] : '' ;
	    strcpy(p, "\"");
	    break;
	case C_CALL: sprintf(p, "CALL %d", lit); break;
	case C_ALLOC: sprintf(p, "ALLOC %d", lit); break;
	case C_EXIT: sprintf(p, "EXIT"); break;
	default: sprintf(p, "unknown %d", oopc);
	}
	p = buf + 7;
	n = 0;
	while(ofrom < from && n < 3) {
	    sprintf(p, "%02x", code[ofrom++] & 0xff);
	    p += 2;
	    n++;
	}
	*p = ' ';
	fprintf(stderr, "%s\n", buf);
    }
}

#ifdef DISAS
main(){
    int codesize, a;
    int *p;
    getchar();
    getchar();
    codesize = getchar();
    codesize = codesize + getchar()*256;
    a = codesize;
    p = code;
    while(a--)
	*p++ = getchar();
    dumpcode(0, codesize);
    exit(0);
}
#endif
