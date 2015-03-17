/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU.
    
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

/*************************/
/* Types of Instructions */
/*************************/

/*
#define DATA_PROC   /* data processing        *
#define LOAD_STORE  /* load/store from memory *
#define IMMEDIATE   /* obvious, I think       *
#define CON_BR      /* conditional branch     *
#define UNCON_BR    /* unconditional branch   *
#define PUSH_PULL   /* obvious                *
#define STOP        /* the best instruction   */


/***********************/
/* Function Prototypes */
/***********************/

/* Sets the instruction register flag */
void set_ir_flg(unsigned short flag);

/* sets the stop flag */
void set_stp_flg(unsigned short flag);
