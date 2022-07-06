/* This module is responsible for both syntax and semantics.
 * I use Parser object to break strings to tokens by chosen delimiters.
 * Parser is made with strtok and there are some dependancies of this knowledge which I HAVE to resolve.
 * I might change Parser to fix those pitfalls.

 * EXAMPLE: When I have multiple consecutive commas that are NOT separated by space, strtok will skip both,
 * thus will leave me unaware to that fact.
 *
 * SOLUTION: MAYBE ADD SPACE MANUALLY BEFORE AND AFTER EACH COMMA.*/

#include "matparser.h"
#include "parser.h"
#include <ctype.h>
#include <string.h>

/* CONSTANT VALUES */
#define NUM_OF_MATS 6
#define SPACE ' '
#define DECIMAL '.'
#define STR_MAT_A "MAT_A"
#define STR_MAT_B "MAT_B"
#define STR_MAT_C "MAT_C"
#define STR_MAT_D "MAT_D"
#define STR_MAT_E "MAT_E"
#define STR_MAT_F "MAT_F"

/* INNER STATIC FUNCTION DECLARATIONS */


/* Params:  A c-string a_str and a pointer to struct Args.
 * Task:    Test a_str for being a valid operator.
 * Output:  Sets operator enum specifier to relevant member at 'a_args' and returns valid if
 *          found or relevant Status otherwise.
 * */
/***** MAYBE SEND PARSER OBJECT INSTEAD OF STRING - TOO SPECIFIC. *****/
static Status get_operator(String a_str, Args *a_args);

/* Params:  A Parser object 'a_prs' and a pointer to a double 'a_scalar'.
 * Task:    Test if the next token in 'a_prs' is a real number.
 * Output:  Sets found scalar to *a_scalar and returns valid if a real number is found or relevant
 *          status otherwise.
 * */
static Status get_next_double(Parser a_prs, double *a_scalar);

/* Params:  A Parser object 'a_prs' and a pointer to a MatName 'a_mname'.
 * Task:    Test if the next token in 'a_prs' is a valid matrix name.
 * Output:  Sets found matrix enum value to *a_mname and returns valid if a matrix name was found or relevant
 *          status otherwise.
 * */
static Status get_next_matrix(Parser a_prs, MatName *a_mname);

/* Params:  A Parser object 'a_prs' and a pointer to struct Args 'a_args'.
 * Task:    Try and extract exactly three arguments - a matrix and a scalar, and a matrix respectively.
 * Output:  valid if all extracted in the right order and according to syntax. If not, a relevant status
 *          will be returned.
 * */
static Status mat_scalar_operator(Parser a_prs, Args *m_args);

/* Params:
 * Task:
 * Output:
 * */
/*static Status print_mat_operator(Parser a_prs, Args *m_args);*/

/* Params:  A Parser object 'a_prs' and a pointer to struct Args 'a_args'.
 * Task:    Try and extract exactly two arguments - a matrix and an array of scalars respectively.
 * Output:  valid if all extracted in the right order and according to syntax. If not, a relevant status
 *          will be returned.
 * */
static Status read_mat_operator(Parser a_prs, Args *m_args);

/* Params:  A Parser object 'a_prs' and a pointer to struct Args 'a_args'.
 * Task:    Try and extract exactly one argument - an operator.
 * Output:  valid if all extracted in the right order and according to syntax. If not, a relevant status
 *          will be returned.
 * */
static Status mat_operators(Parser a_prs, Args *a_args, size_t a_param_count);

/* IMPLEMENTATIONS */

void showError(Status a_status){
    static String msgs[] = {
            "",
            "unknown operator.",
            "illegal matrix name.",
            "extraneous text after command.",
            "multiple consecutive commas",
            "missing argument.",
            "illegal comma.",
            "illegal decimal pont",
            "not a real number.",
            "missing a comma."
    };
    printf("%s\n",msgs[a_status]);
}


Status processCommand(String a_str,Args *a_args){
    Status              result      = valid;
    Parser              p           = buildParser();
    const String        delims[]    = {SPACES_DELIM,COMMA_DELIM,NULL};/*Delimiters to be sent to Parser object.*/


    parseString(p,a_str,delims);
    if(hasNextToken(p) == False){
        result = empty_line;
    }
    if(result == valid && (result = get_operator(getNextToken(p),a_args)) == valid){
        switch (a_args->m_operator) {
            case Read_Mat:
                result = read_mat_operator(p, a_args);
                break;
            case Print_Mat:
                result = mat_operators(p,a_args,0);
                break;/*NOT YET IMPLEMENTED*/
            case Add_Mat:/*ALL THREE SHARE SAME PARAMETER PATTERN.*/
            case Sub_Mat:
            case Mul_Mat:
                result = mat_operators(p,a_args,2);
                break;

            case Mul_Scalar:
                result = mat_scalar_operator(p,a_args);
                break;
            case Trans_Mat:
                result = mat_operators(p,a_args,1);
                break;
            case Stop:/*MAY NOT BE RELEVANT - REMOVE(?)*/
                if(hasNextToken(p) == True){
                    result = extraneous_text;
                }
                break;

        }
    }

    return result;
}



static Status mat_operators(Parser a_prs, Args *a_args, size_t a_param_count){
    Status          result = valid;
    size_t          i = 0;

    for(i = 0 ; i <= a_param_count && result == valid; ++i){
        result = get_next_matrix(a_prs,&a_args->m_matrices[i]);
    }

    if(i > a_param_count){
        if(result == missing_comma){/* Additional text after last argument.(CASE 1)*/
            result = extraneous_text;
        }
        else if(result == valid && hasNextToken(a_prs) == True){/* Additional text after last argument.(CASE 2)*/
            result = extraneous_text;
        }
    }
    else if(i == 1 && result == multiple_commas){/* Comma before the first argument.*/
        result = illegal_comma;
    }

    return result;
}


static Status mat_scalar_operator(Parser a_prs, Args *m_args){
    Status          result = valid;

    if((result = get_next_matrix(a_prs,m_args->m_matrices)) == valid){
        if((result = get_next_double(a_prs,m_args->m_scalars)) == valid){
            if((result = get_next_matrix(a_prs,&m_args->m_matrices[1])) == valid){
                if(hasNextToken(a_prs) == True){
                    result = extraneous_text;
                }
                else if(result == missing_comma){
                    result = extraneous_text;
                }
            }
        }
    }
    else if(result == multiple_commas){
        result = illegal_comma;
    }
    return result;
}



static Status read_mat_operator(Parser a_prs, Args *a_args){
    Status          result  = valid;
    size_t          index   = 0;
    double          garbage = 0.0;

    if((result = get_next_matrix(a_prs,a_args->m_matrices)) == valid){
        while(hasNextToken(a_prs) == True && result == valid){

            if(index < MAT_ELEMENTS){
                result = get_next_double(a_prs,a_args->m_scalars + index);
                ++index;
            }
            else result = get_next_double(a_prs,&garbage);
        }
        if(index == 0 && result == valid){
            result = missing_argument;
        }
        else if(result == missing_argument){
            result = extraneous_text;
        }
        while(valid == result && index<MAT_ELEMENTS && index > 0){
            a_args->m_scalars[index++] = 0;
        }

    }
    else if(result == multiple_commas){
        result = illegal_comma;
    }

    return result;
}

static Status get_operator(String a_str, Args *a_args){
    static struct {
        String      m_op_text;
        MatOp       m_op;
    } operators[] = {
            {"read_mat",Read_Mat},
            {"print_mat",Print_Mat},
            {"add_mat",Add_Mat},
            {"sub_mat",Sub_Mat},
            {"mul_mat",Mul_Mat},
            {"mul_scalar",Mul_Scalar},
            {"trans_mat",Trans_Mat},
            {"stop",Stop},
            {NULL,Stop}
    };
    size_t          i = 0;
    Status          result = valid;

    for(i = 0 ; operators[i].m_op_text ; ++i){
        if(strcmp(operators[i].m_op_text,a_str) == 0){
            a_args->m_operator = operators[i].m_op;
            break;
        }
    }
    if(operators[i].m_op_text == NULL_STRING){
        result = illegal_operator;
    }
    return result;
}

static Status get_next_matrix(Parser a_prs, MatName *a_mname){
    static struct {
        const String mat_text;
        MatName mat_name;
    } matrices[] = {
            {STR_MAT_A,MAT_A},
            {STR_MAT_B,MAT_B},
            {STR_MAT_C,MAT_C},
            {STR_MAT_D,MAT_D},
            {STR_MAT_E,MAT_E},
            {STR_MAT_F,MAT_F},
            {NULL,MAT_F}
    };
    Status          result  = valid;
    size_t          i       = 0;
    String          str     = NULL_STRING;

    str = getNextToken(a_prs);
    if(NULL == str){
        result = missing_argument;
    }
    str = strtok(str,SPACES_DELIM);

    if(valid == result && NULL_STRING == str){
        result = multiple_commas;
    }
    for(i = 0; matrices[i].mat_text && str; ++i){
        if(strcmp(str,matrices[i].mat_text) == 0){
            *a_mname = matrices[i].mat_name;
            break;
        }
    }
    if(result == valid){
        str = strtok(NULL,SPACES_DELIM);
    }
    if(str != NULL){
        result = missing_comma;
    }
    else if(matrices[i].mat_text == NULL){
        result = illegal_mat_name;
    }

    return result;
}




static Status get_next_double(Parser a_prs, double *a_scalar){
    Status          result  = valid;
    String          str     = NULL_STRING,
            endptr  = NULL_STRING;


    str = strtok(getNextToken(a_prs),SPACES_DELIM);
    if(NULL != str){
        *a_scalar = strtod(str,&endptr);
    }

    if(NULL == str){
        result = (hasNextToken(a_prs) == True)? multiple_commas : missing_argument;
    }
    else if(result == valid && *endptr != 0){
        result = (*endptr == DECIMAL)? illegal_decimal : not_a_real_number;
    }
    else if(strtok(NULL, SPACES_DELIM) != NULL ){
        result = missing_comma;
    }
    return result;
}






