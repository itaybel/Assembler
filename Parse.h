

#ifndef PARSER_MATPARSER_H
#define PARSER_MATPARSER_H
#include "misc.h"
#include <stdlib.h>

/* CONSTANT VALUES */
#define NUM_OF_MATS 6
#define SPACES_DELIM " \t"
#define COMMA_DELIM ","
#define COMMA ','
#define MAT_ELEMENTS 16

/* TYPE DEFINITIONS */
typedef         struct args         Args;



/* STATUS ENUMS */
typedef enum stt{
    empty_line = -1,
    valid = 0,
    illegal_operator,
    illegal_mat_name,
    extraneous_text,
    multiple_commas,
    missing_argument,
    illegal_comma,
    illegal_decimal,
    not_a_real_number,
    missing_comma

}Status;

/* OPERATORS ENUMS */
typedef enum mt_op{
    Read_Mat = 0, Print_Mat, Add_Mat, Sub_Mat, Mul_Mat, Mul_Scalar, Trans_Mat, Stop
}MatOp;

/* MATRIX NAMES ENUMS*/
typedef enum mt_name{
    MAT_A = 0, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F
}MatName;

/* ARGUMENT STRUCT */
struct args{
    MatOp           m_operator;                 /* CURRENT OPERATOR ENUM VALUE*/
    MatName        m_matrices[3];               /* MATRIX TYPE ARGUMENT ENUM VALUES */

    double         m_scalars[MAT_ELEMENTS];     /* SCALAR VALUES */

};

/* Params:  A c-string 'a_str' and a pointer to struct Args 'a_args'
 * Task:    Parse string for an operator and arguments. If found - arguments are passed to
 *          a_args.
 * Output:  'valid' if strings syntax and semantics are all correct. Otherwise, relevant  
 *          status is returned.
 * */
Status processCommand(String a_str,Args *a_args);

/* Params:  A Status enum value 'a_status'
 * Task:    Match Status enum value to apropriate message represented by a c-string.
 * Output:
 * */
void showError(Status a_status);







#endif 